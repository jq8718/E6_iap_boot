/*******************************************************************************
 * @file  config_hc32l021.c
 * @brief This file provides peripherial init for I2C IAP Bootloader
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
   2026-06-20       Claude          Replace LPUART1 with HSI2C slave (PA06/PA07)
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "config_hc32l021.h"
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* RC48M Trim值 */
#define RC48M_CR_TRIM_48M_VAL (*((volatile uint32_t *)(0x001007B0ul)))
#define RC48M_CR_TRIM_4M_VAL  (*((volatile uint32_t *)(0x001007BCul)))

/* 系统时钟相关宏定义 */
#define SYS_CLK_INIT_HZ   (48000000u) /* 系统时钟，单位Hz */
#define SYS_CLK_DEINIT_HZ (4000000u)  /* 系统时钟，单位Hz */

#define FLASH_TIMEOUT     (0xFFFFu)                                        /* FLASH超时保护计数值 */
#define FLASH_END_ADDR    ((uint32_t)(FLASH_START_ADDR + FLASH_SIZE - 1u)) /* FLASH末尾地址 */

/* I2C GPIO 复用配置值（需根据 HC32L021 参考手册核对） */
#define HSI2C_GPIO_PIN06_SEL    (2u)    /* PA06 选 HSI2C_SDA 功能 */
#define HSI2C_GPIO_PIN07_SEL    (2u)    /* PA07 选 HSI2C_SCL 功能 */
#define HSI2C_GPIO_LSEL         (1u)    /* GPIOAUX_CTRL1.HSI2C_LSEL = 1 选择 PA06/07 位置 */

/* FLASH写序列，每次FLASH寄存器修改，都需调用此序列 */
#define FLASH_BYPASS() \
    do \
    { \
        FLASH->BYPASS = 0x5A5A; \
        FLASH->BYPASS = 0xA5A5; \
    } while (0)

/* FLASH 解锁 */
#define FLASH_UNLOCK_All() \
    do \
    { \
        FLASH_BYPASS(); \
        FLASH->SLOCK0 = 0xFFFFFFFFu; \
    } while (0)

/* FLASH 加锁 */
#define FLASH_LOCK_All() \
    do \
    { \
        FLASH_BYPASS(); \
        FLASH->SLOCK0 = 0; \
    } while (0)

/* SYSCTRL 解锁 */
#define SYSCTRL_UNLOCK() \
    do \
    { \
        WRITE_REG16(SYSCTRL->SYSCTRL2, 0x5A5Au); \
        WRITE_REG16(SYSCTRL->SYSCTRL2, 0xA5A5u); \
    } while (0);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
__STATIC_INLINE void HC32_SysClockInit(void);
__STATIC_INLINE void HC32_SysClockDeInit(void);
__STATIC_INLINE void HC32_GpioInit(void);
__STATIC_INLINE void HC32_GpioDeInit(void);
__STATIC_INLINE void HC32_Btim0Init(void);
__STATIC_INLINE void HC32_Btim0DeInit(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Peripherals init
 * @retval None
 */
void HC32_PeriModuleInit(void)
{
    /* 系统时钟初始化 */
    HC32_SysClockInit();

    /* I2C引脚初始化 */
    HC32_GpioInit();

    /* I2C从机模块初始化 */
    HC32_I2cSlaveInit();

    /* 定时器模块初始化 */
    HC32_Btim0Init();
}

/**
 * @brief  Peripherals deinit
 * @retval None
 */
void HC32_PeriModuleDeInit(void)
{
    /* 系统时钟复位 */
    HC32_SysClockDeInit();

    /* I2C引脚复位 */
    HC32_GpioDeInit();

    /* I2C模块复位 */
    HC32_I2cSlaveDeInit();

    /* 定时器模块复位 */
    HC32_Btim0DeInit();
}

/**
 * @brief  系统时钟初始化
 * @retval None
 */
__STATIC_INLINE void HC32_SysClockInit(void)
{
    /* 设置FLASH wait cycle = 1 */
    FLASH_BYPASS();
    MODIFY_REG32(FLASH->CR, FLASH_CR_WAIT_Msk, 0x1u << FLASH_CR_WAIT_Pos);

    /* 加载48M Trim值 */
    SYSCTRL->RC48M_CR = RC48M_CR_TRIM_48M_VAL;
}

/**
 * @brief  系统时钟复位
 * @retval None
 */
__STATIC_INLINE void HC32_SysClockDeInit(void)
{
    /* 加载4M Trim值 */
    SYSCTRL->RC48M_CR = RC48M_CR_TRIM_4M_VAL;

    /* 设置FLASH wait cycle = 0 */
    FLASH_BYPASS();
    MODIFY_REG32(FLASH->CR, FLASH_CR_WAIT_Msk, 0x0u << FLASH_CR_WAIT_Pos);
}

/**
 * @brief  I2C引脚初始化 (PA06=SDA, PA07=SCL)
 * @retval None
 */
__STATIC_INLINE void HC32_GpioInit(void)
{
    /* 外设模块时钟使能 */
    SYSCTRL->PERI_CLKEN0_f.GPIO_EN = 1;

    /* 选择 HSI2C 引脚位置为 PA06/PA07 */
    SYSCTRL->PERI_CLKEN0_f.GPIO_EN = 1; /* 确保 GPIOAUX 时钟已开 */
    GPIOAUX->CTRL1_f.HSI2C_LSEL = HSI2C_GPIO_LSEL;

    /* 配置PA06为HSI2C_SDA：开漏输出 + 上拉 + 复用功能 */
    GPIOA->DIR_f.PIN06 = 0;             /* 输出方向（开漏模式下可双向） */
    GPIOA->OUT_f.PIN06 = 1;             /* 默认高 */
    GPIOA->OD_f.PIN06  = 1;             /* 开漏 */
    GPIOA->PU_f.PIN06  = 1;             /* 上拉 */
    GPIOA->ADS_f.PIN06 = 0;             /* 数字功能 */
    GPIOA->PIN06_SEL   = HSI2C_GPIO_PIN06_SEL;

    /* 配置PA07为HSI2C_SCL：开漏输出 + 上拉 + 复用功能 */
    GPIOA->DIR_f.PIN07 = 0;
    GPIOA->OUT_f.PIN07 = 1;
    GPIOA->OD_f.PIN07  = 1;             /* 开漏 */
    GPIOA->PU_f.PIN07  = 1;             /* 上拉 */
    GPIOA->ADS_f.PIN07 = 0;
    GPIOA->PIN07_SEL   = HSI2C_GPIO_PIN07_SEL;
}

/**
 * @brief  I2C引脚复位
 * @retval None
 */
__STATIC_INLINE void HC32_GpioDeInit(void)
{
    /* 外设模块时钟关闭 */
    SYSCTRL->PERI_CLKEN0_f.GPIO_EN = 0;
    /* 外设模块复位 */
    SYSCTRL->PERI_RESET0_f.GPIO_RST = 0;
    SYSCTRL->PERI_RESET0_f.GPIO_RST = 1;
}

/**
 * @brief  HSI2C从机初始化
 * @retval None
 */
void HC32_I2cSlaveInit(void)
{
    stc_hsi2c_slave_init_t stcSlaveInit;

    /* 外设模块时钟使能 */
    SYSCTRL->PERI_CLKEN0_f.HSI2C_EN = 1;

    /* 结构体默认值 */
    HSI2C_SlaveStcInit(&stcSlaveInit);

    /* 从机地址、sub-address、方向 */
    stcSlaveInit.u32SlaveAddr0 = I2C_SLAVE_ADDR;
    stcSlaveInit.u8SubAddrSize = 1u;
    stcSlaveInit.enDir         = Hsi2cMasterWriteSlaveRead;

    /* 启用 SCL Clock Stretching：发送/接收/ACK 阶段均可拉低 SCL */
    stcSlaveInit.stcSlaveConfig1.u32FuncSelect =
        HSI2C_SLAVE_TXDSTALL_ENABLE |
        HSI2C_SLAVE_RXSTALL_ENABLE  |
        HSI2C_SLAVE_ACKSTALL_ENABLE;

    /* 从机初始化 */
    HSI2C_SlaveInit(HSI2C, &stcSlaveInit, SYS_CLK_INIT_HZ);

    /* 清除所有从机标志 */
    HSI2C_SlaveFlagClear(HSI2C, HSI2C_SLAVE_FLAG_CLR_ALL);

    /* 使能从机中断：地址有效、STOP、接收数据、发送数据、FIFO错误、位错误 */
    HSI2C_SlaveIntEnable(HSI2C,
                         HSI2C_SLAVE_INT_AVIE |
                         HSI2C_SLAVE_INT_SDIE |
                         HSI2C_SLAVE_INT_RDIE |
                         HSI2C_SLAVE_INT_TDIE |
                         HSI2C_SLAVE_INT_FEIE |
                         HSI2C_SLAVE_INT_BEIE);

    /* NVIC 使能 */
    EnableNvic(HSI2C_IRQn, IrqPriorityLevel0, TRUE);
}

/**
 * @brief  HSI2C从机复位
 * @retval None
 */
void HC32_I2cSlaveDeInit(void)
{
    /* 外设模块时钟关闭 */
    SYSCTRL->PERI_CLKEN0_f.HSI2C_EN = 0;
    /* 外设模块复位 */
    SYSCTRL->PERI_RESET0_f.HSI2C_RST = 0;
    SYSCTRL->PERI_RESET0_f.HSI2C_RST = 1;
}

/**
 * @brief  定时器初始化（1ms）
 * @retval None
 */
__STATIC_INLINE void HC32_Btim0Init(void)
{
    /* 配置BTIM0/1/2有效，GTIM0无效 */
    SYSCTRL_SysctrlUnlock();
    SYSCTRL->SYSCTRL1_f.CTIMER0_FUN_SEL = 1; /* 配置BTIM0/1/2有效，GTIM0无效 */
    SYSCTRL->PERI_CLKEN1_f.CTIM0_EN     = 1; /* CTIM0 时钟使能 */

    MODIFY_REG32(BTIM0->CR, BTIM_CR_OST_Msk | BTIM_CR_MD_Msk | BTIM_CR_PRS_Msk | BTIM_CR_TOGEN_Msk,
                 (0x0u << BTIM_CR_MD_Pos) | (0x0u << BTIM_CR_OST_Pos) | (0x7u << BTIM_CR_PRS_Pos) | (0x0u << BTIM_CR_TOGEN_Pos));

    BTIM0->ARR = (uint16_t)375 - 1;

    CLR_REG32_BIT(BTIM0->ICR, BTIM_IER_UI_Msk);      /* 清除溢出中断标志位 */
    SET_REG32_BIT(BTIM0->IER, BTIM_IER_UI_Msk);      /* 允许BTIM0溢出中断    */
    EnableNvic(CTIM0_IRQn, IrqPriorityLevel3, TRUE); /* NVIC使能 */

    SET_REG32_BIT(BTIM0->CR, BTIM_CR_CEN_Msk); /* 启动BTIM0运行 */
}

/**
 * @brief  定时器复位
 * @retval None
 */
__STATIC_INLINE void HC32_Btim0DeInit(void)
{
    /* 关闭BTIM功能 */
    SYSCTRL->SYSCTRL1_f.CTIMER0_FUN_SEL = 0;
    /* 外设模块时钟关闭 */
    SYSCTRL->PERI_CLKEN1_f.CTIM0_EN = 0;
    /* 外设模块复位 */
    SYSCTRL->PERI_RESET1_f.CTIM0_RST = 0;
    SYSCTRL->PERI_RESET1_f.CTIM0_RST = 1;
}

/**
 * @brief  计算字节缓存数组的CRC16值
 * @param  [in] pu8Data 数据指针起始地址
 * @param  [in] offset 偏移地址
 * @param  [in] size 字节长度
 * @retval CRC16值
 */
uint32_t HC32_CalCrc16(uint8_t *pu8Data, uint32_t u32Offset, uint32_t u32Size)
{
    uint8_t  u8Cnt;
    uint16_t u16CrcResult = 0xA28C;

    while (u32Size != 0)
    {
        u16CrcResult ^= pu8Data[u32Offset++];
        for (u8Cnt = 0; u8Cnt < 8; u8Cnt++)
        {
            if ((u16CrcResult & 0x1) == 0x1)
            {
                u16CrcResult >>= 1;
                u16CrcResult  ^= 0x8408;
            }
            else
            {
                u16CrcResult >>= 1;
            }
        }
        u32Size--;
    }
    u16CrcResult = (uint16_t)(~u16CrcResult);

    return u16CrcResult;
}

/**
 * @brief  获取定时器溢出中断标志位
 * @retval 标志寄存器值
 */
uint32_t HC32_GetTimUIFStatus()
{
    return (READ_REG32_BIT(BTIM0->IFR, BTIM_IFR_UI_Msk));
}

/**
 * @brief  清除定时器1溢出中断标志位
 * @retval None
 */
void HC32_ClrTimUIFStatus()
{
    CLR_REG32_BIT(BTIM0->ICR, BTIM_IFR_UI_Msk);
}

/**
 * @brief  FLASH扇区擦除
 * @param  [in] u32SectorAddr 所擦除扇区内的地址
 * @retval en_result_t
 *           - Ok: 擦除成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 */
en_result_t HC32_FlashEraseSector(uint32_t u32SectorAddr)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    FLASH_BYPASS();
    FLASH->CR_f.RO = 0u; /* FLASH可编程或擦写 */

    FLASH_UNLOCK_All();

    if (FLASH_END_ADDR < u32SectorAddr)
    {
        return ErrorInvalidParameter;
    }
    /* FLASH扇区（页）擦除模式 */
    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 2)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 2; /* FLASH扇区（页）擦除模式 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    /* busy */
    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    /* write data */
    *((volatile uint32_t *)u32SectorAddr) = 0u;

    /* busy */
    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    /* FLASH读模式 */
    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 0)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 0; /* FLASH读模式 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    FLASH_LOCK_All();

    FLASH_BYPASS();
    FLASH->CR_f.RO = 1u; /* FLASH不可编程或擦写 */
    return Ok;
}

/**
 * @brief  FLASH写入数据 按字节写
 * @param  [in] u32Addr 地址
 * @param  [in] *pu8Data 数据指针
 * @param  [in] u32Len 字节长度
 * @retval en_result_t
 *           - Ok: 擦除成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 */
en_result_t HC32_FlashWriteBytes(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    FLASH_BYPASS();
    FLASH->CR_f.RO = 0u; /* FLASH可编程或擦写 */

    FLASH_UNLOCK_All();

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* FLASH写（编程）模式 */
    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 1)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 1; /* FLASH写（编程）模式 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    /* busy */
    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)u32Addr) = pu8Data[u32Index];

        /* busy */
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        /* 校验 */
        if (pu8Data[u32Index] != *((volatile uint8_t *)u32Addr))
        {
            return Error;
        }
        u32Addr++;
    }

    /* FLASH读模式 */
    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 0)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 0; /* FLASH读模式 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    FLASH_LOCK_All();

    FLASH_BYPASS();
    FLASH->CR_f.RO = 1u; /* FLASH不可编程或擦写 */
    return Ok;
}

/**
 * @brief  FLASH数据读取
 * @param  [in] u32Addr 地址
 * @param  [in] *pu8ReadBuff 数据指针
 * @param  [in] u32ByteLength 字节长度
 * @retval None
 */
void HC32_FlashReadBytes(uint32_t u32Addr, uint8_t *pu8ReadBuff, uint32_t u32ByteLength)
{
    uint32_t i;

    for (i = 0; i < u32ByteLength; i++)
    {
        pu8ReadBuff[i] = *((unsigned char *)(u32Addr + i));
    }
}
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
