/**
 *******************************************************************************
 * @file  vc.c
 * @brief This file provides firmware functions to manage the VC
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
   2025-07-08       MADS            Add VC trim function and DAC setup time
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "vc.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_VC VC模块驱动库
 * @brief VC Driver Library VC模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup VC_Local_Macros VC局部宏定义
 * @{
 */

/**
 * @brief  RCL Trim值
 */
#define VC_VC0_TRIM_LOWER_0P5AVCC_VAL  (*((volatile uint8_t *)(0x001007C0ul)))
#define VC_VC0_TRIM_HIGHER_0P5AVCC_VAL (*((volatile uint8_t *)(0x001007C1ul)))
#define VC_VC1_TRIM_LOWER_0P5AVCC_VAL  (*((volatile uint8_t *)(0x001007C2ul)))
#define VC_VC1_TRIM_HIGHER_0P5AVCC_VAL (*((volatile uint8_t *)(0x001007C3ul)))
/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup VC_Global_Functions VC全局函数定义
 * @{
 */

/**
 * @brief  VC初始化
 * @param  [in] pstcVcInit VC初始化配置结构体 @ref stc_vc_init_t
 * @retval en_result_t
 *           - Ok: 初始化成功
 */
en_result_t VC_Init(stc_vc_init_t *pstcVcInit)
{
    uint32_t u32TrimValue = 0u;
    uint32_t u32BaseCR0   = (uint32_t)(&VC->VC0_CR0) + pstcVcInit->u32Ch;
    uint32_t u32BaseCR1   = (uint32_t)(&VC->VC0_CR1) + pstcVcInit->u32Ch;
    uint32_t u32BaseCR2   = (uint32_t)(&VC->VC0_CR2) + pstcVcInit->u32Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseCR0, VC_VC0_CR0_BIAS_Msk | VC_VC0_CR0_HYS_Msk, pstcVcInit->u32BiasCurrent | pstcVcInit->u32HysVolt);
    MODIFY_REG32(*(volatile uint32_t *)u32BaseCR1,
                 VC_VC0_CR1_PSEL_Msk | VC_VC0_CR1_NSEL_Msk | VC_VC0_CR1_FLTTIME_Msk | VC_VC0_CR1_FLTCLK_Msk | VC_VC0_CR1_FLT_MODE_Msk | VC_VC0_CR1_FALLING_Msk
                     | VC_VC0_CR1_RISING_Msk | VC_VC0_CR1_LEVEL_Msk,
                 pstcVcInit->u32InputPos | pstcVcInit->u32InputNeg | pstcVcInit->u32FilterTime | pstcVcInit->u32FilterClk | pstcVcInit->u32FilterMode
                     | pstcVcInit->u32IntMode);
    MODIFY_REG32(*(volatile uint32_t *)u32BaseCR2, VC_VC0_CR2_POL_Msk, pstcVcInit->u32OutputPol);

    if (VC_CH0 == pstcVcInit->u32Ch) /* VC0 */
    {
        if (VC_TRIM_LOWER_0P5AVCC == pstcVcInit->u8TrimSetSelect)
        {
            u32TrimValue = (uint32_t)(VC_VC0_TRIM_LOWER_0P5AVCC_VAL);
        }
        else
        {
            u32TrimValue = (uint32_t)(VC_VC0_TRIM_HIGHER_0P5AVCC_VAL);
        }
        MODIFY_REG32(VC->VC_TRIM, VC_VC_TRIM_TRIM0_Msk, u32TrimValue);
    }
    else if (VC_CH1 == pstcVcInit->u32Ch) /* VC0 */ /* VC1 */
    {
        if (VC_TRIM_LOWER_0P5AVCC == pstcVcInit->u8TrimSetSelect)
        {
            u32TrimValue = (uint32_t)(VC_VC1_TRIM_LOWER_0P5AVCC_VAL);
        }
        else
        {
            u32TrimValue = (uint32_t)(VC_VC1_TRIM_HIGHER_0P5AVCC_VAL);
        }
        MODIFY_REG32(VC->VC_TRIM, VC_VC_TRIM_TRIM1_Msk, (u32TrimValue << 4u));
    }
    else
    {
        ;
    }

    DDL_Delay10us(1); /* BGR启动时间，配置BIAS BGR自动打开 */

    return Ok;
}

/**
 * @brief  VC模块使能
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_Enable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR1) + u8Ch;

    SET_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR1_EN_Msk);
}

/**
 * @brief  VC模块禁止
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_Disable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR1) + u8Ch;

    CLR_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR1_EN_Msk);
}

/**
 * @brief  电阻分压比例配置
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @param  [in] u32RefVoltDiv 分压比例 @ref 比例范围为0~63
 * @retval None
 */
void VC_ResVoltDivConfig(uint8_t u8Ch, uint32_t u32RefVoltDiv)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR0) + u8Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR0_DIV_Msk, u32RefVoltDiv);
}

/**
 * @brief  电阻分压电路使能
 * @retval None
 */
void VC_ResVoltDivEnable(void)
{
    SET_REG32_BIT(VC->VC0_CR0, VC_VC0_CR0_DIV_EN_Msk);

    DDL_Delay10us(3u);
}

/**
 * @brief  电阻分压电路禁止
 * @retval None
 */
void VC_ResVoltDivDisable(void)
{
    CLR_REG32_BIT(VC->VC0_CR0, VC_VC0_CR0_DIV_EN_Msk);
}

/**
 * @brief  VC中断模式配置
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @param  [in] u32IntMode VC中断触发模式 @ref VC_Int_Mode_Select
 * @retval None
 */
void VC_IntModeConfig(uint8_t u8Ch, uint32_t u32IntMode)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR1) + u8Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR1_LEVEL_Msk | VC_VC0_CR1_RISING_Msk | VC_VC0_CR1_FALLING_Msk, u32IntMode);
}

/**
 * @brief  VC中断使能
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_IntEnable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR1) + u8Ch;

    SET_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR1_IE_Msk);
}

/**
 * @brief  VC中断禁止
 * @param  [in] u8Ch VC通道号 @ref uint32_t
 * @retval None
 */
void VC_IntDisable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR1) + u8Ch;

    CLR_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR1_IE_Msk);
}

/**
 * @brief  获取VC中断标志
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval uint32_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t VC_IntFlagGet(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_SR) + u8Ch;

    return READ_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_SR_INTF_Msk) ? TRUE : FALSE;
}

/**
 * @brief  清除VC中断标志
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_IntFlagClear(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_SR) + u8Ch;

    CLR_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC1_SR_INTF_Msk);
}

/**
 * @brief  VC滤波后信号输出到ATIM3配置
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @param  [in] u32OutputAtimMode  @ref VC_Output_Atim3_Config
 * @retval None
 */
void VC_OutputAtimConfig(uint8_t u8Ch, uint32_t u32OutputAtimMode)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR2) + u8Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR2_ATIM3CLR_Msk | VC_VC0_CR2_ATIMBK_Msk, u32OutputAtimMode);
}

/**
 * @brief  VC空白窗口源配置
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @param  [in] u32BlankWindow 空白窗口源选择 @ref VC_Blank_Window_Select
 * @retval None
 */
void VC_BlankWindowConfig(uint8_t u8Ch, uint32_t u32BlankWindow)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR2) + u8Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR2_BLANK_Msk, u32BlankWindow);
}

/**
 * @brief  使能VC窗口比较功能
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_WindowEnable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR2) + u8Ch;

    SET_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR2_WINDOW_Msk);
}

/**
 * @brief  禁止VC窗口比较功能
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval None
 */
void VC_WindowDisable(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_CR2) + u8Ch;

    CLR_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_CR2_WINDOW_Msk);
}

/**
 * @brief  获取滤波后的信号电平
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @retval uint32_t
 *           - TRUE: 滤波后的信号电平为高
 *           - FALSE: 滤波后的信号电平为低
 */
boolean_t VC_FilterOutputGet(uint8_t u8Ch)
{
    uint32_t u32BaseAdress = (uint32_t)(&VC->VC0_SR) + u8Ch;

    return READ_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, VC_VC0_SR_FLTV_Msk) ? TRUE : FALSE;
}

/**
 * @brief  Trim值设置
 * @param  [in] u8Ch VC通道号 @ref VC_Ch_Select
 * @param  [in] u8TrimSelect Trim类型选择 @ref VC_Trim_Select
 * @retval None
 */
void VC_TrimSet(uint8_t u8Ch, uint8_t u8TrimSelect)
{
    uint32_t u32TrimValue = 0u;
    if (VC_CH0 == u8Ch) /* VC0 */
    {
        if (VC_TRIM_LOWER_0P5AVCC == u8TrimSelect)
        {
            u32TrimValue = (uint32_t)(VC_VC0_TRIM_LOWER_0P5AVCC_VAL);
        }
        else
        {
            u32TrimValue = (uint32_t)(VC_VC0_TRIM_HIGHER_0P5AVCC_VAL);
        }
        MODIFY_REG32(VC->VC_TRIM, VC_VC_TRIM_TRIM0_Msk, u32TrimValue);
    }
    else if (VC_CH1 == u8Ch) /* VC0 */ /* VC1 */
    {
        if (VC_TRIM_LOWER_0P5AVCC == u8TrimSelect)
        {
            u32TrimValue = (uint32_t)(VC_VC1_TRIM_LOWER_0P5AVCC_VAL);
        }
        else
        {
            u32TrimValue = (uint32_t)(VC_VC1_TRIM_HIGHER_0P5AVCC_VAL);
        }
        MODIFY_REG32(VC->VC_TRIM, VC_VC_TRIM_TRIM1_Msk, (u32TrimValue << 4u));
    }
    else
    {
        ;
    }
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_vc_init_t
 * @retval None
 */
void VC_StcInit(stc_vc_init_t *pstcInit)
{
    pstcInit->u32Ch           = VC_CH0;
    pstcInit->u32HysVolt      = VC_HYSTERESIS_VOLT_NONE;
    pstcInit->u32BiasCurrent  = VC_BIAS_CURR_LOW;
    pstcInit->u32FilterTime   = VC_FILTER_TIME_NONE;
    pstcInit->u32InputPos     = VC_POS_SEL_NONE;
    pstcInit->u32InputNeg     = VC_NEG_SEL_NONE;
    pstcInit->u32FilterClk    = VC_FILTER_CLK_RC256K;
    pstcInit->u32FilterMode   = VC_FILTER_MD_NFM;
    pstcInit->u32OutputPol    = VC_OUTPUT_POL_POS;
    pstcInit->u32IntMode      = VC_INT_MD_NONE;
    pstcInit->u8TrimSetSelect = VC_TRIM_LOWER_0P5AVCC;
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
 ******************************************************************************/
