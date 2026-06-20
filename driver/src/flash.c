/**
 *******************************************************************************
 * @file  flash.c
 * @brief This file provides firmware functions to manage the FLASH
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-04-27       MADS            Modify OP value in continous mode
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024~2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "flash.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_FLASH FLASH模块驱动库
 * @brief FLASH Driver Library FLASH模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Macros FLASH局部宏定义
 * @{
 */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define RAMFUNC __attribute__((section(".ramfunc")))
#elif defined(__ICCARM__)
#define RAMFUNC __ramfunc
#endif

#define FLASH_END_ADDR          (0x0000FFFFu) /* FLASH末尾地址 */

#define FLASH_TIMEOUT           (0xFFFFFFu) /* FLASH超时保护计数值 */

#define FLASH_LOCK_ALL_SECTOR   (0u)          /* FLASH所有sector上锁 */
#define FLASH_UNLOCK_ALL_SECTOR (0xFFFFFFFFu) /* FLASH所有sector解锁 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */

/**
 * @brief  FLASH中断使能
 * @param  [in] u32FlashIntEnable FLASH中断类型 @ref FLASH_Int_Enable_Types
 * @retval None
 */
void FLASH_IntEnable(uint32_t u32FlashIntEnable)
{
    FLASH_BYPASS();
    MODIFY_REG32(FLASH->CR, FLASH_CR_IE_Msk, u32FlashIntEnable);
}

/**
 * @brief  FLASH中断禁止
 * @param  [in] u32FlashIntEnable FLASH中断类型 @ref FLASH_Int_Enable_Types
 * @retval None
 */
void FLASH_IntDisable(uint32_t u32FlashIntEnable)
{
    FLASH_BYPASS();
    CLR_REG32_BIT(FLASH->CR, u32FlashIntEnable);
}

/**
 * @brief  FLASH中断标志获取
 * @param  [in] u32FlashIntFlag FLASH中断类型枚举 @ref FLASH_Int_Flag_Types
 * @retval boolean_t
 *           - TRUE: 标志置位
 *           - FALSE: 标志未置位
 */
boolean_t FLASH_IntFlagGet(uint32_t u32FlashIntFlag)
{
    return READ_REG32_BIT(FLASH->IFR, u32FlashIntFlag) ? TRUE : FALSE;
}

/**
 * @brief  FLASH中断标志清除
 * @param  [in] u32FlashIntFlag FLASH中断类型枚举 @ref FLASH_Int_Flag_Types
 * @retval None
 */
void FLASH_IntFlagClear(uint32_t u32FlashIntFlag)
{
    CLR_REG32_BIT(FLASH->ICLR, u32FlashIntFlag);
}

/**
 * @brief  FLASH所有Sector不允许擦写保护
 * @retval en_result_t
 *           - Ok: 加锁成功
 *           - ErrorTimeout: 加锁失败
 */
en_result_t FLASH_LockAllSector(void)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    while (FLASH_LOCK_ALL_SECTOR != FLASH->SLOCK0)
    {
        FLASH_BYPASS();
        FLASH->SLOCK0 = FLASH_LOCK_ALL_SECTOR;
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH所有Sector允许擦写保护
 * @retval en_result_t
 *           - Ok: 解锁成功
 *           - ErrorTimeout: 解锁失败
 */
en_result_t FLASH_UnlockAllSector(void)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    while (FLASH_UNLOCK_ALL_SECTOR != FLASH->SLOCK0)
    {
        FLASH_BYPASS();
        FLASH->SLOCK0 = FLASH_UNLOCK_ALL_SECTOR;
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH Sector LOCK 设置
 * @param  [in] u32LockValue 32bits
 *           - 对应bit=0：加锁，对应Sectors不允许擦写
 *           - 对应bit=1：解锁，对应Sectors允许擦写
 * @note   加解锁范围Sectors:[i*4, i*4+3]
 *           -i: 表示u32LockValue的bit位置，0~31;
 * @retval en_result_t
 *           - Ok: 加解锁成功
 *           - ErrorTimeout: 加解锁失败
 */
en_result_t FLASH_LockUnlockSectors(uint32_t u32LockValue)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    while (u32LockValue != *((&FLASH->SLOCK0)))
    {
        FLASH_BYPASS();
        *((&FLASH->SLOCK0)) = u32LockValue;
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH读等待周期设置
 * @param  [in] u32FlashWaitCycle 插入FLASH读等待周期数枚举类型 @ref FLASH_Wait_Cycles
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorTimeout: 配置失败
 */
en_result_t FLASH_WaitCycle(uint32_t u32FlashWaitCycle)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_WAIT_Msk) != u32FlashWaitCycle)
    {
        FLASH_BYPASS();
        MODIFY_REG32(FLASH->CR, FLASH_CR_WAIT_Msk, u32FlashWaitCycle);
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH操作模式配置
 * @param  [in] u32FlashOperateMode 操作模式配置 @ref FLASH_Mode
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorTimeout: 配置失败
 */
en_result_t FLASH_OperateModeConfig(uint32_t u32FlashOperateMode)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    if (READ_REG32_BIT(FLASH->CR, FLASH_CR_OP_Msk | FLASH_CR_CONTP_Msk) != u32FlashOperateMode) /* 模式发生变化 */
    {
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_OP_Msk) != (u32FlashOperateMode & FLASH_CR_OP_Msk)) /* OP发生变化 */
        {
            FLASH_BYPASS();
            MODIFY_REG32(FLASH->CR, FLASH_CR_OP_Msk, u32FlashOperateMode & FLASH_CR_OP_Msk); /* 修改OP值 */

            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk) != (u32FlashOperateMode & FLASH_CR_CONTP_Msk)) /* CONTP发生变化 */
        {
            FLASH_BYPASS();
            MODIFY_REG32(FLASH->CR, FLASH_CR_CONTP_Msk, u32FlashOperateMode & FLASH_CR_CONTP_Msk); /* 修改CONTP值 */

            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }
    return Ok;
}

/**
 * @brief  FLASH连续字节（8位方式）编程,以字节方式向FLASH写入连续的数据
 * @param  [in] u32Addr FLASH目标首地址
 * @param  [in] pu8Data 数据Buffer首地址
 * @param  [in] u32Len 写入数据长度（字节）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 编程、校验、配置失败
 */
en_result_t FLASH_WriteByte(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfig(FLASH_MD_WR)) /* FLASH写（编程）模式 */
    {
        return Error;
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

    return Ok;
}

/**
 * @brief  FLASH连续半字（16位方式）编程，以半字方式向FLASH写入连续的数据
 * @param  [in] u32Addr FLASH目标首地址
 * @param  [in] pu16Data 数据Buffer首地址
 * @param  [in] u32Len 写入数据长度（半字）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 编程、校验、配置失败
 */
en_result_t FLASH_WriteHalfWord(uint32_t u32Addr, uint16_t *pu16Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len * 2u - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfig(FLASH_MD_WR)) /* FLASH写（编程）模式 */
    {
        return Error;
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
        *((volatile uint16_t *)u32Addr) = pu16Data[u32Index];

        /* busy */
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        if (pu16Data[u32Index] != *((volatile uint16_t *)u32Addr))
        {
            return Error;
        }
        u32Addr += 2u;
    }

    return Ok;
}

/**
 * @brief  FLASH连续字（32位方式）编程,以字方式向FLASH写入连续的数据
 * @param  [in] u32Addr FLASH目标首地址
 * @param  [in] pu16Data 数据Buffer首地址
 * @param  [in] u32Len 写入数据长度（字）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 编程、校验、配置失败
 */
en_result_t FLASH_WriteWord(uint32_t u32Addr, uint32_t *pu32Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len * 4u - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfig(FLASH_MD_WR)) /* FLASH写（编程）模式 */
    {
        return Error;
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
        *((volatile uint32_t *)u32Addr) = pu32Data[u32Index];

        /* busy */
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        if (pu32Data[u32Index] != *((volatile uint32_t *)u32Addr))
        {
            return Error;
        }
        u32Addr += 4u;
    }

    return Ok;
}

/**
 * @brief  FLASH扇区擦除,对目标地址所在的FLASH扇区进行擦除，擦除后该扇区FLASH数据为全0xFF
 * @param  [in] u32SectorAddr 所擦除扇区内的地址
 * @retval en_result_t
 *           - Ok: 擦除成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 配置失败
 */
en_result_t FLASH_SectorErase(uint32_t u32SectorAddr)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    if (FLASH_END_ADDR < u32SectorAddr)
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfig(FLASH_MD_SECTOR_ERASE)) /* FLASH扇区（页）擦除模式 */
    {
        return Error;
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

    return Ok;
}

/**
 * @brief  FLASH操作模式配置(RAM中执行)
 * @param  [in] u32FlashOperateMode 操作模式配置 @ref FLASH_Mode
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorTimeout: 超时操作
 */
RAMFUNC en_result_t FLASH_OperateModeConfigRamFunc(uint32_t u32FlashOperateMode)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    if (READ_REG32_BIT(FLASH->CR, FLASH_CR_OP_Msk | FLASH_CR_CONTP_Msk) != u32FlashOperateMode) /* 模式发生变化 */
    {
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_OP_Msk) != (u32FlashOperateMode & FLASH_CR_OP_Msk)) /* OP发生变化 */
        {
            FLASH_BYPASS();
            MODIFY_REG32(FLASH->CR, FLASH_CR_OP_Msk, u32FlashOperateMode & FLASH_CR_OP_Msk); /* 修改OP值 */

            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk) != (u32FlashOperateMode & FLASH_CR_CONTP_Msk)) /* CONTP发生变化 */
        {
            FLASH_BYPASS();
            MODIFY_REG32(FLASH->CR, FLASH_CR_CONTP_Msk, u32FlashOperateMode & FLASH_CR_CONTP_Msk); /* 修改CONTP值 */

            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }
    return Ok;
}

/**
 * @brief  FLASH全片擦除
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - Error: 操作、配置失败
 *           - ErrorTimeout: 操作超时
 */
RAMFUNC en_result_t FLASH_ChipErase(void)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    if (Ok != FLASH_OperateModeConfigRamFunc(FLASH_MD_CHIP_ERASE))
    {
        return Error;
    }

    u32Timeout = FLASH_TIMEOUT;
    while (FLASH_UNLOCK_ALL_SECTOR != FLASH->SLOCK0)
    {
        FLASH_BYPASS();
        FLASH->SLOCK0 = FLASH_UNLOCK_ALL_SECTOR;
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

    *((volatile unsigned int *)0x00000000u) = 0u;

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH字节（8位方式）连续写，用于向FLASH写入1字节数据
 * @param  [in] u32Addr FLASH地址
 * @param  [in] pu8Data 数据Buffer
 * @param  [in] u32Len Buffer长度（字节）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 配置错误
 */
RAMFUNC en_result_t FLASH_ContinousWriteByte(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfigRamFunc(FLASH_MD_CONT_WR))
    {
        return Error;
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

        u32Addr++;
    }

    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 1u)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 1u; /* OP = 1 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk))
    {
        FLASH_BYPASS();
        CLR_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk); /* CONTP = 0 */
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

    return Ok;
}

/**
 * @brief  FLASH半字（16位方式）连续写，用于向FLASH写入半字（2字节）数据
 * @param  [in] u32Addr FLASH地址
 * @param  [in] pu16Data 数据Buffer
 * @param  [in] u32Len Buffer长度（半字）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 配置错误
 */
RAMFUNC en_result_t FLASH_ContinousWriteHalfWord(uint32_t u32Addr, uint16_t *pu16Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len * 2u - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfigRamFunc(FLASH_MD_CONT_WR))
    {
        return Error;
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
        *((volatile uint16_t *)u32Addr) = pu16Data[u32Index];
        /* busy */
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        u32Addr += 2u;
    }

    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 1u)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 1u; /* OP = 1 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk))
    {
        FLASH_BYPASS();
        CLR_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk); /* CONTP = 0 */
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

    return Ok;
}

/**
 * @brief  FLASH字（32位方式）连续写，用于向FLASH写入1个字的数据
 * @param  [in] u32Addr FLASH地址
 * @param  [in] pu32Data 数据Buffer
 * @param  [in] u32Len Buffer长度（字）
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorInvalidParameter: FLASH地址无效
 *           - ErrorTimeout: 操作超时
 *           - Error: 配置错误
 */
RAMFUNC en_result_t FLASH_ContinousWriteWord(uint32_t u32Addr, uint32_t *pu32Data, uint32_t u32Len)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;
    uint32_t          u32Index   = 0u;

    if (FLASH_END_ADDR < (u32Addr + u32Len * 4u - 1u))
    {
        return ErrorInvalidParameter;
    }

    if (Ok != FLASH_OperateModeConfigRamFunc(FLASH_MD_CONT_WR))
    {
        return Error;
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
        *((volatile uint32_t *)u32Addr) = pu32Data[u32Index];
        /* busy */
        u32Timeout = FLASH_TIMEOUT;
        while (READ_REG32_BIT(FLASH->CR, FLASH_CR_BUSY_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        u32Addr += 4u;
    }

    u32Timeout = FLASH_TIMEOUT;
    while (FLASH->CR_f.OP != 1u)
    {
        FLASH_BYPASS();
        FLASH->CR_f.OP = 1u; /* OP = 1 */
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk))
    {
        FLASH_BYPASS();
        CLR_REG32_BIT(FLASH->CR, FLASH_CR_CONTP_Msk); /* CONTP = 0 */
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

    return Ok;
}

/**
 * @brief  FLASH低功耗模式使能
 * @retval en_result_t
 *           - Ok: 操作成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t FLASH_LowPowerEnable(void)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_DPSTB_EN_Msk) != FLASH_CR_DPSTB_EN_Msk)
    {
        FLASH_BYPASS();
        SET_REG32_BIT(FLASH->CR, FLASH_CR_DPSTB_EN_Msk);

        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH低功耗模式禁止
 * @retval en_result_t
 *           - Ok: 操作成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t FLASH_LowPowerDisable(void)
{
    volatile uint32_t u32Timeout = FLASH_TIMEOUT;

    u32Timeout = FLASH_TIMEOUT;
    while (READ_REG32_BIT(FLASH->CR, FLASH_CR_DPSTB_EN_Msk) == FLASH_CR_DPSTB_EN_Msk)
    {
        FLASH_BYPASS();
        CLR_REG32_BIT(FLASH->CR, FLASH_CR_DPSTB_EN_Msk);

        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  FLASH保护状态获取
 * @retval uint32_t 保护状态 @ref FLASH_Protect_Status
 */
uint32_t FLASH_ProtectStatusGet(void)
{
    return READ_REG32_BIT(FLASH->LOCK_ST, FLASH_LOCK_ST_LOCK_ST_Msk);
}

/**
 * @brief  FLASH只读、不可编程或擦写
 * @retval None
 */
void FLASH_ReadOnlyEnable(void)
{
    FLASH->BYPASS  = 0x5A5Au;
    FLASH->BYPASS  = 0xA5A5u;
    FLASH->CR_f.RO = 1u;
}

/**
 * @brief  FLASH可读、可编程、可擦写
 * @retval None
 */
void FLASH_ReadOnlyDisable(void)
{
    FLASH->BYPASS  = 0x5A5Au;
    FLASH->BYPASS  = 0xA5A5u;
    FLASH->CR_f.RO = 0u;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
