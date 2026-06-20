/**
 *******************************************************************************
 * @file  spi.c
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-14       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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

#include "spi.h"
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SPI SPI模块驱动库
 * @brief SPI Driver Library SPI模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
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
 * @defgroup SPI_Global_Functions SPI全局函数定义
 * @{
 */

/**
 * @brief  SPI 总体初始化函数
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] pstcInitConfig 初始化结构体 @ref stc_spi_init_t
 * @retval en_result_t
 *         Ok  SPI初始化成功
 */
en_result_t SPI_Init(SPI_TypeDef *SPIx, stc_spi_init_t *pstcInitConfig)
{
    MODIFY_REG(SPIx->CR0,
               SPI_CR0_BRR_Msk | SPI_CR0_CPHA_Msk | SPI_CR0_CPOL_Msk | SPI_CR0_MSTR_Msk | SPI_CR0_LSBF_Msk | SPI_CR0_WIDTH_Msk | SPI_CR0_SSM_Msk
                   | SPI_CR0_CM_Msk | SPI_CR0_SMP_Msk,
               pstcInitConfig->u32BaudRate | pstcInitConfig->u32CPHA | pstcInitConfig->u32CPOL | pstcInitConfig->u32Mode | pstcInitConfig->u32BitOrder
                   | pstcInitConfig->u32DataWidth | pstcInitConfig->u32NSS | pstcInitConfig->u32TransDir | pstcInitConfig->u32SampleDelay);

    return Ok;
}

/**
 * @brief  开启SPI模块
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Enable(SPI_TypeDef *SPIx)
{
    SET_REG_BIT(SPIx->CR0, SPI_CR0_EN_Msk);
}

/**
 * @brief  禁止SPI模块
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Disable(SPI_TypeDef *SPIx)
{
    CLR_REG_BIT(SPIx->CR0, SPI_CR0_EN_Msk);
}

/**
 * @brief  设定SPI主机模式波特率
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32BaudRate 波特率 @ref SPI_Baudrate_Select
 * @retval None
 */
void SPI_BaudRateSet(SPI_TypeDef *SPIx, uint32_t u32BaudRate)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_BRR_Msk, u32BaudRate);
}

/**
 * @brief  设定SPI串行时钟相位
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPhase 时钟相位选择 @ref SPI_Clock_Phase_Select
 * @retval None
 */
void SPI_ClockPhaseSet(SPI_TypeDef *SPIx, uint32_t u32ClockPhase)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_CPHA_Msk, u32ClockPhase);
}

/**
 * @brief  设定SPI串行时钟极性选择
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPolarity 时钟极性选择 @ref SPI_Clock_Polarity_Select
 * @retval None
 */
void SPI_ClockPolaritySet(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_CPOL_Msk, u32ClockPolarity);
}

/**
 * @brief  设定SPI模式，主机模式或者从机模式
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Mode 模式选择 @ref SPI_Mode_Select
 * @retval None
 */
void SPI_ModeSet(SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_MSTR_Msk, u32Mode);
}

/**
 * @brief  设定SPI数据传输高低位顺序
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransBitOrder 数据传输高低位顺序选择 @ref SPI_Bit_Order_Select
 * @retval None
 */
void SPI_TransBitOrderSet(SPI_TypeDef *SPIx, uint32_t u32TransBitOrder)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_LSBF_Msk, u32TransBitOrder);
}

/**
 * @brief  设定SPI每帧的数据宽度
 * @param  [in] SPIx SPI结构体变量  @ref SPI_TypeDef
 * @param  [in] u32DataWidth 数据宽度 @ref SPI_DataWidth_Select
 * @retval None
 */
void SPI_DataWidthSet(SPI_TypeDef *SPIx, uint32_t u32DataWidth)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_WIDTH_Msk, u32DataWidth);
}

/**
 * @brief  设定SPI NSS模式
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSMode NSS从机选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_NSSModeSet(SPI_TypeDef *SPIx, uint32_t u32NSSMode)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_SSM_Msk, u32NSSMode);
}

/**
 * @brief  SPI模块作为从机时，配置NSS片选使能或禁止，只有当SSM=1，即软件控制(非外部IO管脚输入)时有效
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSConfig NSS选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSConfig)
{
    MODIFY_REG(SPIx->SSI, SPI_SSI_SSI_Msk, u32NSSConfig);
}

/**
 * @brief  SPI模块作为主机 配置NSS片选输出(到从机)，只有当SSM=1，即硬件控制输出(外部IO管脚NSS输出)时有效
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSConfig NSS选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSConfig)
{
    MODIFY_REG(SPIx->SSI, SPI_SSI_SSI_Msk, u32NSSConfig);
}

/**
 * @brief  获取SPI SSI的值，只有SSM=1时有效
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t 片选使能位状态 @ref SPI_NSS_Soft_Value
 */
uint32_t SPI_NSSSoftValueGet(SPI_TypeDef *SPIx)
{
    return (uint32_t)(READ_REG_BIT(SPIx->SSI, SPI_SSI_SSI_Msk));
}

/**
 * @brief  获取SPI SSLVL的值，只有SSM=1时有效
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t 外部NSS管脚返回电平 @ref SPI_NSS_EXTERN_Input_Level
 */
uint32_t SPI_NSSExternInputGet(SPI_TypeDef *SPIx)
{
    return (uint32_t)(READ_REG_BIT(SPIx->SR, SPI_SR_SSLVL_Msk));
}

/**
 * @brief  设定SPI 通信方式选择
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransDir 通信方式选择 @ref SPI_Transfer_Direction_Select
 * @retval None
 */
void SPI_TransDirSet(SPI_TypeDef *SPIx, uint32_t u32TransDir)
{
    MODIFY_REG(SPIx->CR0, SPI_CR0_CM_Msk, u32TransDir);
}

/**
 * @brief  设定SPI 半双工通信方式选择
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransDir 通信方式选择 @ref SPI_Half_Duplex_Direction_Select
 * @retval None
 */
void SPI_HalfDuplexDirSet(SPI_TypeDef *SPIx, uint32_t u32TransDir)
{
    MODIFY_REG(SPIx->HDOE, SPI_HDOE_HDOE_Msk, u32TransDir);
}

/**
 * @brief  SPI 中断使能
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IntEn SPI中断使能选择位 @ref SPI_INT_Select
 * @retval None
 */
void SPI_IntEnable(SPI_TypeDef *SPIx, uint32_t u32IntEn)
{
    SET_REG_BIT(SPIx->CR1, u32IntEn);
}

/**
 * @brief  SPI中断 禁止
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Int SPI中断使能选择位 @ref SPI_INT_Select
 * @retval None
 */
void SPI_IntDisable(SPI_TypeDef *SPIx, uint32_t u32Int)
{
    CLR_REG_BIT(SPIx->CR1, u32Int);
}

/**
 * @brief  获取 SPI 标志位
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Flag SPI选择标志位 @ref SPI_Flag_Select
 * @retval uint32_t
 *         - TRUE 发生标志位
 *         - FALSE 未发生标志位
 */
boolean_t SPI_FlagGet(SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    return READ_REG_BIT(SPIx->SR, u32Flag) ? TRUE : FALSE;
}

/**
 * @brief  清除 SPI 标志位
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Flag SPI清除标志位选择 @ref SPI_Flag_Select
 * @retval None
 */
void SPI_FlagClear(SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    CLR_REG_BIT(SPIx->ICR, u32Flag);
}

/**
 * @brief  清除 SPI 所有标志位
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @retval None
 */
void SPI_FlagClearALL(SPI_TypeDef *SPIx)
{
    SPIx->ICR = (uint32_t)(0);
}

/**
 * @brief SPI 发送缓冲空标志 置位
 * @param  [in] SPIx SPI结构体变量 @ref SPI_TypeDef
 * @retval None
 */
void SPI_TXEFlagSet(SPI_TypeDef *SPIx)
{
    CLR_REG_BIT(SPIx->ICR, SPI_ICR_TXE_Msk);
}

/**
 * @brief  SPI 发送一数据函数
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data 发送数据
 * @retval en_result_t
 *         - Ok  发送成功
 */
en_result_t SPI_DataTransmit(SPI_TypeDef *SPIx, uint16_t u16Data)
{
    SPIx->DR = u16Data;

    return Ok;
}

/**
 * @brief  SPI 接收一数据函数
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @retval uint8_t 接收一数据
 */
uint16_t SPI_DataReceive(SPI_TypeDef *SPIx)
{
    return (uint16_t)SPIx->DR;
}

/**
 * @brief  SPI 从机预准备第一个数据
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data 预准备第一个数据
 * @retval en_result_t
 *           - Ok  从机预准备第一个数据成功
 */
en_result_t SPI_SlaveDummyDataTransmit(SPI_TypeDef *SPIx, uint16_t u16Data)
{
    while (FALSE == SPIx->SR_f.TXE) {}
    SPIx->DR = u16Data;
    return Ok;
}

/**
 * @brief  SPI 从机预准备第一个数据超时等待
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data 预准备第一个数据
 * @param  [in] u32Timeout 等待时间
 * @retval en_result_t
 *           - Ok 从机预准备第一个数据成功
 *           - ErrorTimeout 等待超时
 */
en_result_t SPI_SlaveDummyDataTransmitTimeout(SPI_TypeDef *SPIx, uint16_t u16Data, uint32_t u32Timeout)
{
    while (FALSE == SPIx->SR_f.TXE)
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    SPIx->DR = u16Data;
    return Ok;
}

/**
 * @brief  SPI 连续发送接收多个数据函数
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] pu16SendBuf 发送数据指针
 * @param  [in] pu16RecBuf 接收数据指针
 * @param  [in] u32Len 发送数据长度
 * @retval en_result_t
 *         - Ok 收发数据成功
 */
en_result_t SPI_TransmitReceive(SPI_TypeDef *SPIx, uint16_t pu16SendBuf[], uint16_t pu16RecBuf[], uint32_t u32Len)
{
    uint32_t u32Index = 0u;
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        while (FALSE == SPIx->SR_f.TXE) {}

        SPIx->DR = pu16SendBuf[u32Index];

        while (FALSE == SPIx->SR_f.RXNE) {}

        pu16RecBuf[u32Index] = (uint16_t)SPIx->DR;
    }

    while (FALSE == SPIx->SR_f.TXE) {}
    while (TRUE == SPIx->SR_f.BUSY) {}

    return Ok;
}

/**
 * @brief  SPI 连续发送接收多个数据等待超时函数
 * @param  [in] SPIx SPI结构体 @ref SPI_TypeDef
 * @param  [in] pu16SendBuf 发送数据指针
 * @param  [in] pu16RecBuf 接收数据指针
 * @param  [in] u32Len 发送数据长度
 * @param  [in] u32Timeout 等待时间
 * @retval en_result_t
 *         - Ok SPI初始化成功
 *         - ErrorTimeout 等待超时
 */
en_result_t SPI_TransmitReceiveTimeout(SPI_TypeDef *SPIx, uint16_t pu16SendBuf[], uint16_t pu16RecBuf[], uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32Index = 0u;

    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        while (FALSE == SPIx->SR_f.TXE)
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        SPIx->DR = pu16SendBuf[u32Index];

        while (FALSE == SPIx->SR_f.RXNE)
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }

        pu16RecBuf[u32Index] = (uint16_t)SPIx->DR;
    }

    while (FALSE == SPIx->SR_f.TXE)
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }
    while (TRUE == SPIx->SR_f.BUSY)
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout; /* 等待超时 */
        }
    }

    return Ok;
}

/**
 * @brief  SPI结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_spi_init_t
 * @retval None
 */
void SPI_StcInit(stc_spi_init_t *pstcInit)
{
    pstcInit->u32BaudRate    = SPI_BAUDRATE_PCLK_DIV2;
    pstcInit->u32Mode        = SPI_MD_SLAVE;
    pstcInit->u32TransDir    = SPI_FULL_DUPLEX;
    pstcInit->u32CPHA        = SPI_CLK_PHASE_1EDGE;
    pstcInit->u32CPOL        = SPI_CLK_POLARITY_LOW;
    pstcInit->u32BitOrder    = SPI_MSB_FIRST;
    pstcInit->u32DataWidth   = SPI_DATA_WIDTH_8BIT;
    pstcInit->u32NSS         = SPI_NSS_HARD_INPUT;
    pstcInit->u32SampleDelay = SPI_SAMPLE_NORMAL;
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
