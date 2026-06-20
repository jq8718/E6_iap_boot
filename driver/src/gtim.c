/**
 *******************************************************************************
 * @file  gtim.c
 * @brief This file provides firmware functions to manage the GTIM
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-18       MADS            First version
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
#include "gtim.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GTIM GTIM模块驱动库
 * @brief GTIM Driver Library GTIM模块驱动库
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
 * @defgroup GTIM_Global_Functions GTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器GTIM的初始化配置
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] pstcInitConfig 初始化GTIMx的结构体 @ref stc_gtim_init_t
 * @retval en_result_t
 *           - Ok 配置成功
 *           - ErrorInvalidParameter 无效参数
 */
en_result_t GTIM_Init(GTIM_TypeDef *GTIMx, stc_gtim_init_t *pstcInitConfig)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_MD_Msk | GTIM_CR0_TOGEN_Msk | GTIM_CR0_PRS_Msk | GTIM_CR0_OST_Msk | GTIM_CR0_TRS_Msk | GTIM_CR0_ETP_Msk,
                 pstcInitConfig->u32Mode | pstcInitConfig->u32OneShotEn | pstcInitConfig->u32Prescaler | pstcInitConfig->u32ToggleEn
                     | pstcInitConfig->u32TriggerSrc | pstcInitConfig->u32ExternInputPolarity);

    MODIFY_REG16(GTIMx->ARR, GTIM_ARR_ARR_Msk, (uint16_t)pstcInitConfig->u32AutoReloadValue);

    return Ok;
}

/**
 * @brief  获取GTIM计数器计数值
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval uint32_t GTIMx计数器计数值
 */
uint32_t GTIM_CounterGet(GTIM_TypeDef *GTIMx)
{
    return READ_REG32_BIT(GTIMx->CNT, GTIM_CNT_CNT_Msk);
}

/**
 * @brief  设置GTIM计数器计数值
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u16CountValue 计数值
 * @retval None
 */
void GTIM_CounterSet(GTIM_TypeDef *GTIMx, uint16_t u16CountValue)
{
    WRITE_REG32(GTIMx->CNT, (uint32_t)u16CountValue);
}

/**
 * @brief  设定GTIM重载寄存器的值
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u16AutoReload 重载值
 * @retval None
 */
void GTIM_AutoReloadSet(GTIM_TypeDef *GTIMx, uint16_t u16AutoReload)
{
    WRITE_REG16(GTIMx->ARR, u16AutoReload);
}

/**
 * @brief  开启定时器GTIM模块
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval None
 */
void GTIM_Enable(GTIM_TypeDef *GTIMx)
{
    SET_REG32_BIT(GTIMx->CR0, GTIM_CR0_CEN_Msk);
}

/**
 * @brief  禁止定时器GTIM模块
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval None
 */
void GTIM_Disable(GTIM_TypeDef *GTIMx)
{
    CLR_REG32_BIT(GTIMx->CR0, GTIM_CR0_CEN_Msk);
}

/**
 * @brief  设定定时器GTIM工作模式
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Mode 选择GTIM工作模式 @ref GTIM_Mode_Select
 * @retval None
 */
void GTIM_ModeSet(GTIM_TypeDef *GTIMx, uint32_t u32Mode)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_MD_Msk, u32Mode);
}

/**
 * @brief  定时器GTIM TOG输出使能，TOGP和TOGN输出相位相反的信号
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval None
 */
void GTIM_ToggleEnable(GTIM_TypeDef *GTIMx)
{
    SET_REG32_BIT(GTIMx->CR0, GTIM_CR0_TOGEN_Msk);
}

/**
 * @brief  定时器GTIM TOG输出禁止，TOGP和TOGN同时输出0
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval None
 */
void GTIM_ToggleDisable(GTIM_TypeDef *GTIMx)
{
    CLR_REG32_BIT(GTIMx->CR0, GTIM_CR0_TOGEN_Msk);
}

/**
 * @brief  定时器GTIM模块 计数时钟预除频
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32CounterClockDiv 计数时钟预分频选择 @ref GTIM_Clock_Div
 * @retval None
 */
void GTIM_CounterClockDivSet(GTIM_TypeDef *GTIMx, uint32_t u32CounterClockDiv)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_PRS_Msk, u32CounterClockDiv);
}

/**
 * @brief  设定GTIM计数模式 单次/连续计数模式
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32OneShotMode 单次/连续计数模式 @ref GTIM_OneShot_Continue_Select
 * @retval None
 */
void GTIM_OneShotSet(GTIM_TypeDef *GTIMx, uint32_t u32OneShotMode)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_OST_Msk, u32OneShotMode);
}

/**
 * @brief  设定定时器GTIM触发源
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32TriggerSrc 选择GTIM触发源  @ref GTIM_Trigger_Src_Select
 * @retval None
 */
void GTIM_TriggerSrcSet(GTIM_TypeDef *GTIMx, uint32_t u32TriggerSrc)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_TRS_Msk, u32TriggerSrc);
}

/**
 * @brief  设定定时器GTIM外部输入ETR极性设定
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32ExternInputPolarity 外部输入ETR极性 @ref GTIM_ETR_Input_Polarity
 * @retval None
 */
void GTIM_ExternInputPolaritySet(GTIM_TypeDef *GTIMx, uint32_t u32ExternInputPolarity)
{
    MODIFY_REG32(GTIMx->CR0, GTIM_CR0_ETP_Msk, u32ExternInputPolarity);
}

/**
 * @brief  设定定时器GTIM外部输入ETR滤波时间
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32ExternInputFilter 外部输入ETR滤波时间 @ref GTIM_ETP_External_Input_Filter
 * @retval None
 */
void GTIM_ExternInputFilterSet(GTIM_TypeDef *GTIMx, uint32_t u32ExternInputFilter)
{
    MODIFY_REG32(GTIMx->CR1, GTIM_CR1_ETRFLT, u32ExternInputFilter);
}

/**
 * @brief  定时器GTIM捕获比较模式选择
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Ch 比较捕获通道选择 @ref GTIM_Capture_Compare_Ch_Select
 * @param  [in] u32CaptureMode 捕获比较模式选择 @ref GTIM_Capture_Compare_Mode_Config
 * @retval None
 */
void GTIM_CompareCaptureModeSet(GTIM_TypeDef *GTIMx, uint32_t u32Ch, uint32_t u32CaptureMode)
{
    MODIFY_REG32(GTIMx->CMMR, GTIM_CMMR_CC0M_Msk << u32Ch, u32CaptureMode << u32Ch);
}

/**
 * @brief  设定GTIM比较捕获（寄存器）值
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Ch 比较捕获通道选择 @ref GTIM_Capture_Compare_Ch_Select
 * @param  [in] u32Capture 16位比较捕获寄存器值
 * @retval None
 */
void GTIM_CompareCaptureRegSet(GTIM_TypeDef *GTIMx, uint32_t u32Ch, uint32_t u32Capture)
{
    uint32_t u32BaseAdress;

    u32BaseAdress = (uint32_t)(&GTIMx->CCR0) + (uint32_t)u32Ch;

    MODIFY_REG32(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR_Msk, u32Capture);
}

/**
 * @brief  获取GTIM比较捕获（寄存器）值
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Ch 比较捕获通道选择 @ref GTIM_Capture_Compare_Ch_Select
 * @retval uint32_t 比较捕获寄存器的值
 */
uint32_t GTIM_CompareCaptureRegGet(GTIM_TypeDef *GTIMx, uint32_t u32Ch)
{
    uint32_t u32BaseAdress;

    u32BaseAdress = (uint32_t)(&GTIMx->CCR0) + u32Ch;

    return READ_REG32_BIT(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR_Msk);
}

/**
 * @brief  禁止所有通道比较捕获功能
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @retval None
 */
void GTIM_CompareCaptureAllDisable(GTIM_TypeDef *GTIMx)
{
    CLR_REG32(GTIMx->CMMR);
}

/**
 * @brief  GTIM中断或触发ADC使能
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Int 中断使能控制位 @ref GTIM_Int_Select
 * @retval None
 */
void GTIM_IntEnable(GTIM_TypeDef *GTIMx, uint32_t u32Int)
{
    SET_REG32_BIT(GTIMx->IER, u32Int);
}

/**
 * @brief  GTIM中断禁止
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32Int 中断使能控制位 @ref GTIM_Int_Select
 * @retval None
 */
void GTIM_IntDisable(GTIM_TypeDef *GTIMx, uint32_t u32Int)
{
    CLR_REG32_BIT(GTIMx->IER, u32Int);
}

/**
 * @brief  获取GTIM中断标志
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32IntFlagTypes 中断标志类型 @ref GTIM_Int_Select
 * @retval boolean_t
 *           - TRUE 中断标志置位
 *           - FALSE 中断标志未置位
 */
boolean_t GTIM_IntFlagGet(GTIM_TypeDef *GTIMx, uint32_t u32IntFlagTypes)
{
    return (READ_REG32_BIT(GTIMx->IFR, u32IntFlagTypes) == u32IntFlagTypes) ? TRUE : FALSE;
}

/**
 * @brief  清除GTIM中断标志位
 * @param  [in] GTIMx GTIM单元名宏定义 @ref GTIM_TypeDef
 * @param  [in] u32IntClearFlag 中断清除标志定义 @ref GTIM_Flag_Select
 * @retval None
 */
void GTIM_IntFlagClear(GTIM_TypeDef *GTIMx, uint32_t u32IntClearFlag)
{
    CLR_REG32_BIT(GTIMx->ICR, u32IntClearFlag);
}

/**
 * @brief  GTIM结构体初始化
 * @param  [in] pstcInit 结构体初始化 @ref stc_gtim_init_t
 * @retval None
 */
void GTIM_StcInit(stc_gtim_init_t *pstcInit)
{
    pstcInit->u32Mode                = GTIM_MD_PCLK;
    pstcInit->u32OneShotEn           = GTIM_CONTINUOUS_COUNTER;
    pstcInit->u32Prescaler           = GTIM_COUNTER_CLK_DIV1;
    pstcInit->u32ToggleEn            = GTIM_TOGGLE_DISABLE;
    pstcInit->u32TriggerSrc          = GTIM_TRIG_SRC_ETR;
    pstcInit->u32ExternInputPolarity = GTIM_ETR_POLARITY_NORMAL;
    pstcInit->u32AutoReloadValue     = 0xFFFFu;
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
