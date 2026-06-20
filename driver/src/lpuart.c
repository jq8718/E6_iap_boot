/**
 *******************************************************************************
 * @file  lpuart.c
 * @brief This file provides firmware functions to manage the LPUART
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-07-08       MADS            Modify LPUART_Init(),LPUART_StcInit()
                                    and add/delect some functions
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
#include "lpuart.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPUART LPUART模块驱动库
 * @brief LPUART Driver Library LPUART模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup LPUART_Local_Macros LPUART局部宏定义
 * @{
 */
#define LPUART_TIMEOUT (0xFFFFFFu) /* 超时保护计数值 */
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
 * @defgroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */

/**
 * @brief  LPUART初始化函数
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] pstcLpuartInit LPUART初始化配置结构体 @ref stc_lpuart_init_t
 * @retval uint32_t 波特率设定值
 */
uint32_t LPUART_Init(LPUART_TypeDef *LPUARTx, stc_lpuart_init_t *pstcLpuartInit)
{
    uint32_t  u32Bps  = 0u;
    float32_t f32Scnt = 0u;

    CLR_REG(LPUARTx->SCON);

    if (pstcLpuartInit->u32BaudRateGenSelect != LPUART_BAUD_NORMAL)
    {
        pstcLpuartInit->stcBaudRate.u32SclkSelect = LPUART_SCLK_SEL_XTL; /* LPUART_XTL_BAUD_9600/4800: 设置SCL为XTL */
    }

    MODIFY_REG32(LPUARTx->SCON, LPUART_SCON_SCLKSEL_Msk, pstcLpuartInit->stcBaudRate.u32SclkSelect); /* 设置SCLK */

    MODIFY_REG32(LPUARTx->SCON, LPUART_SCON_HDSEL_Msk, pstcLpuartInit->u32TransMode);

    MODIFY_REG32(LPUARTx->SCON,
                 LPUART_SCON_STOPBIT_Msk | LPUART_SCON_B8CONT_Msk | LPUART_SCON_SM_Msk | LPUART_SCON_REN_Msk | LPUART_SCON_HDSEL_Msk | LPUART_SCON_CTSEN_Msk
                     | LPUART_SCON_RTSEN_Msk | LPUART_SCON_OVER_Msk,
                 pstcLpuartInit->u32StopBits | pstcLpuartInit->u32Parity | pstcLpuartInit->u32FrameLength | pstcLpuartInit->u32TransMode
                     | pstcLpuartInit->u32HwControl | (0x2u << LPUART_SCON_OVER_Pos));

    if (pstcLpuartInit->u32BaudRateGenSelect == LPUART_BAUD_NORMAL) /* 用OVER和SCNT产生波特率 */
    {
        WRITE_REG32(LPUARTx->BSEL, LPUART_BAUD_NORMAL);
        if (pstcLpuartInit->stcBaudRate.u32Baud != 0u)
        {
            f32Scnt = (float32_t)(pstcLpuartInit->stcBaudRate.u32Sclk) / (float32_t)(pstcLpuartInit->stcBaudRate.u32Baud << 2u);
            WRITE_REG(LPUARTx->SCNT, (uint16_t)(float32_t)(f32Scnt + 0.5f));

            u32Bps = (uint32_t)(((pstcLpuartInit->stcBaudRate.u32Sclk) / ((uint16_t)(float32_t)(f32Scnt + 0.5f))) >> 2); /* 最终波特率设定值*/
        }
    }
    else if (pstcLpuartInit->u32BaudRateGenSelect == LPUART_XTL_BAUD_9600) /* 时钟源是XTL，由调制生成9600波特率 */
    {
        DDL_Delay1ms(1);
        WRITE_REG32(LPUARTx->BSEL, LPUART_XTL_BAUD_9600);
        WRITE_REG32(LPUARTx->MODU, 0x54Au);
        u32Bps = 9600u;
    }
    else if (pstcLpuartInit->u32BaudRateGenSelect == LPUART_XTL_BAUD_4800) /* 时钟源是XTL，由调制生成4800波特率 */
    {
        DDL_Delay1ms(1);
        WRITE_REG32(LPUARTx->BSEL, LPUART_XTL_BAUD_4800);
        WRITE_REG32(LPUARTx->MODU, 0xEFBu);
        u32Bps = 4800u;
    }
    else
    {
        ;
    }

    return u32Bps;
}

/**
 * @brief  LPUART XTL波特率产生寄存器
 * @note   当XTL时钟为32768时，调用此函数产生9600或者4800波特率
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32BselConfig 波特率选择 @ref LPUART_Baud_Rate_Gen_Select
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
en_result_t LPUART_XtlBselSet(LPUART_TypeDef *LPUARTx, uint32_t u32BselConfig)
{
    en_result_t enRet = Ok;

    if (LPUART_SCLK_SEL_XTL == READ_REG32_BIT(LPUARTx->SCON, LPUART_SCON_SCLKSEL_Msk))
    {
        if (u32BselConfig == LPUART_XTL_BAUD_9600)
        {
            WRITE_REG32(LPUARTx->BSEL, LPUART_XTL_BAUD_9600);
            WRITE_REG32(LPUARTx->MODU, 0x54Au);
        }
        else if (u32BselConfig == LPUART_XTL_BAUD_4800)
        {
            WRITE_REG32(LPUARTx->BSEL, LPUART_XTL_BAUD_4800);
            WRITE_REG32(LPUARTx->MODU, 0xEFBu);
        }
        else
        {
            enRet = Error;
        }
    }
    else
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief  LPUART多机模式配置
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u8Addr 从机设备地址
 * @param  [in] u8AddrMask 从机设备地址掩码
 * @retval None
 */
void LPUART_MultiModeConfig(LPUART_TypeDef *LPUARTx, uint8_t u8Addr, uint8_t u8AddrMask)
{
    SET_REG_BIT(LPUARTx->SCON, LPUART_SCON_ADRDET);
    WRITE_REG8(LPUARTx->SADDR, u8Addr);
    WRITE_REG8(LPUARTx->SADEN, u8AddrMask);
}

/**
 * @brief  LPUART单线半双工模式使能
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval None
 */
void LPUART_HdModeEnable(LPUART_TypeDef *LPUARTx)
{
    SET_REG32_BIT(LPUARTx->SCON, LPUART_SCON_HDSEL_Msk);
}

/**
 * @brief  LPUART单线半双工模式关闭
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval None
 */
void LPUART_HdModeDisable(LPUART_TypeDef *LPUARTx)
{
    CLR_REG32_BIT(LPUARTx->SCON, LPUART_SCON_HDSEL_Msk);
}

/**
 * @brief  LPUART发送或接收等功能使能设置
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32Func 功能 @ref LPUART_Func_Enable
 * @retval None
 */
void LPUART_FuncEnable(LPUART_TypeDef *LPUARTx, uint32_t u32Func)
{
    SET_REG32_BIT(LPUARTx->SCON, u32Func);
}

/**
 * @brief  LPUART发送或接收等功能禁止设置
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32Func 功能 @ref LPUART_Func_Enable
 * @retval None
 */
void LPUART_FuncDisable(LPUART_TypeDef *LPUARTx, uint32_t u32Func)
{
    CLR_REG32_BIT(LPUARTx->SCON, u32Func);
}

/**
 * @brief  LPUART通信中断使能函数设置
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32IntSelect 中断 @ref LPUART_Int_Select
 * @retval None
 */
void LPUART_IntEnable(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect)
{
    SET_REG32_BIT(LPUARTx->SCON, u32IntSelect);
}

/**
 * @brief  LPUART通信中断禁止函数设置
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32IntSelect 中断 @ref LPUART_Int_Select
 * @retval None
 */
void LPUART_IntDisable(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect)
{
    CLR_REG32_BIT(LPUARTx->SCON, u32IntSelect);
}

/**
 * @brief  LPUART中断使能位获取
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32IntSelect 中断 @ref LPUART_Int_Select
 * @retval boolean_t
 *           - TRUE: 中断使能
 *           - FALSE: 中断未使能
 */
boolean_t LPUART_IntEnableGet(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect)
{
    return READ_REG32_BIT(LPUARTx->SCON, u32IntSelect) ? TRUE : FALSE;
}

/**
 * @brief  LPUART总状态获取
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval uint8_t 状态标志位
 */
uint8_t LPUART_IntFlagGetAll(LPUART_TypeDef *LPUARTx)
{
    return (uint8_t)(LPUARTx->ISR);
}

/**
 * @brief  LPUART状态全部清除
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval None
 */
void LPUART_IntFlagClearAll(LPUART_TypeDef *LPUARTx)
{
    CLR_REG32_BIT(LPUARTx->ICR, LPUART_FLAG_CLR_ALL);
}

/**
 * @brief  LPUART单个状态获取
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32IntFlag 状态 @ref LPUART_Status_Select
 * @retval boolean_t
 *           - TRUE: 置位
 *           - FALSE: 未置位
 */
boolean_t LPUART_IntFlagGet(LPUART_TypeDef *LPUARTx, uint32_t u32IntFlag)
{
    return READ_REG32_BIT(LPUARTx->ISR, u32IntFlag) ? TRUE : FALSE;
}

/**
 * @brief  LPUART单个状态清除
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u32IntFlag 状态 @ref LPUART_Status_Select
 * @retval None
 */
void LPUART_IntFlagClear(LPUART_TypeDef *LPUARTx, uint32_t u32IntFlag)
{
    CLR_REG32_BIT(LPUARTx->ICR, u32IntFlag);
}

/**
 * @brief  LPUART发送数据函数，查询方式调用此函数，中断方式发送不适用
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] pu8Data 发送数据buffer指针
 * @param  [in] u32Size 发送数据长度（字节）
 * @retval en_result_t
 *           - Ok: 配置成功
 */
en_result_t LPUART_TransmitPoll(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size)
{
    while (u32Size)
    {
        while (!READ_REG_BIT(LPUARTx->ISR, LPUART_ISR_TXE))
        {
            ;
        }
        WRITE_REG8(LPUARTx->SBUF_f.DATA, *pu8Data);

        pu8Data++;
        u32Size--;

        while (!READ_REG_BIT(LPUARTx->ISR, LPUART_ISR_TC))
        {
            ;
        }
        CLR_REG_BIT(LPUARTx->ICR, LPUART_FLAG_TC);
    }

    return Ok;
}

/**
 * @brief  LPUART发送数据函数,查询方式调用此函数，中断方式发送不适用
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] pu8Data 发送数据buffer指针
 * @param  [in] u32Size 发送数据长度（字节）
 * @param  [in] u32TimeOut 最长发送时间
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUART_TransmitPollTimeOut(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32TimeOut)
{
    while (u32Size)
    {
        while (!READ_REG32_BIT(LPUARTx->ISR, LPUART_ISR_TXE))
        {
            if (0x0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        WRITE_REG8(LPUARTx->SBUF_f.DATA, *pu8Data);

        pu8Data++;
        u32Size--;

        while (!READ_REG32_BIT(LPUARTx->ISR, LPUART_ISR_TC))
        {
            if (0x0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        CLR_REG32_BIT(LPUARTx->ICR, LPUART_FLAG_TC);
    }

    return Ok;
}

/**
 * @brief  LPUART发送数据函数，中断方式调用此函数
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] u8Data 发送数据
 * @retval None
 */
void LPUART_DataTransmit(LPUART_TypeDef *LPUARTx, uint8_t u8Data)
{
    WRITE_REG8(LPUARTx->SBUF_f.DATA, u8Data);
}

/**
 * @brief  LPUART查询接收数据函数
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] pu8Data 接收数据buffer指针
 * @param  [in] u32Size 接收数据长度（字节）
 * @retval en_result_t
 *           - Ok: 接受完成
 *           - Error: FE或PE错误
 */
en_result_t LPUART_ReceivePoll(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size)
{
    while (u32Size)
    {
        while (!READ_REG32_BIT(LPUARTx->ISR, LPUART_ISR_RC))
        {
            ;
        }
        *pu8Data = READ_REG8(LPUARTx->SBUF);
        CLR_REG32_BIT(LPUARTx->ICR, LPUART_ISR_RC);
        pu8Data++;
        u32Size--;

        if (LPUART_IntFlagGet(LPUARTx, LPUART_FLAG_FE | LPUART_FLAG_PE) != FALSE)
        {
            LPUART_IntFlagClear(LPUARTx, LPUART_FLAG_FE | LPUART_FLAG_PE); /* 清除帧错误/奇偶校验错误标记 */
            return Error;
        }
    }

    return Ok;
}

/**
 * @brief  LPUART查询接收数据函数
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @param  [in] pu8Data 接收数据buffer指针
 * @param  [in] u32Size 接收数据长度（字节）
 * @param  [in] u32TimeOut 最长发送时间
 * @retval en_result_t
 *           - Ok: 接收完成
 *           - ErrorTimeout: 超时
 *           - Error: FE或PE错误
 */
en_result_t LPUART_ReceivePollTimeOut(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32TimeOut)
{
    while (u32Size)
    {
        while (!READ_REG32_BIT(LPUARTx->ISR, LPUART_ISR_RC))
        {
            if (0x0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        *pu8Data = READ_REG8(LPUARTx->SBUF);
        CLR_REG32_BIT(LPUARTx->ICR, LPUART_ISR_RC);
        pu8Data++;
        u32Size--;

        if (LPUART_IntFlagGet(LPUARTx, LPUART_FLAG_FE | LPUART_FLAG_PE) != FALSE)
        {
            LPUART_IntFlagClear(LPUARTx, LPUART_FLAG_FE | LPUART_FLAG_PE); /* 清除帧错误/奇偶校验错误标记 */
            return Error;
        }
    }

    return Ok;
}

/**
 * @brief  LPUART中断接收数据函数
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval uint8_t 接收数据
 */
uint8_t LPUART_DataReceive(LPUART_TypeDef *LPUARTx)
{
    return (uint8_t)(READ_REG32_BIT(LPUARTx->SBUF, LPUART_SBUF_DATA_Msk));
}

/**
 * @brief  获取RB8数值
 * @param  [in] LPUARTx LPUARTx通道 @ref LPUART_TypeDef
 * @retval boolean_t
 *           - TRUE: 置位
 *           - FALSE: 未置位
 */
boolean_t LPUART_Bit8Get(LPUART_TypeDef *LPUARTx)
{
    return READ_REG32_BIT(LPUARTx->SBUF, LPUART_SBUF_DATA8_Msk) ? TRUE : FALSE;
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_lpuart_init_t
 * @retval None
 */
void LPUART_StcInit(stc_lpuart_init_t *pstcInit)
{
    pstcInit->u32TransMode              = LPUART_MODE_HD_TX_RX;
    pstcInit->u32FrameLength            = LPUART_FRAME_LEN_8B_PAR;
    pstcInit->u32Parity                 = LPUART_B8_PARITY_ODD;
    pstcInit->u32StopBits               = LPUART_STOPBITS_2;
    pstcInit->u32HwControl              = LPUART_HWCONTROL_RTS_CTS;
    pstcInit->u32BaudRateGenSelect      = LPUART_BAUD_NORMAL;
    pstcInit->stcBaudRate.u32SclkSelect = LPUART_SCLK_SEL_PCLK;
    pstcInit->stcBaudRate.u32Sclk       = SYSCTRL_HclkFreqGet();
    pstcInit->stcBaudRate.u32Baud       = 0;
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
