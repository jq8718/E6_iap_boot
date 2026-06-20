/**
 *******************************************************************************
 * @file  ctrim.c
 * @brief This file provides firmware functions to manage the CTRIM
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-19       MADS            First version
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
#include "ctrim.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CTRIM CTRIM模块驱动库
 * @brief CTRIM Driver Library CTRIM模块驱动库
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
 * @defgroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */

/**
 * @brief  CTRIM时钟校准初始化配置
 * @param  [in] pstcInitConfig Trim时钟校准结构体 @ref stc_ctrim_calib_init_t
 * @retval en_result_t
 *           - Ok 配置成功
 *           - ErrorInvalidParameter 无效参数
 */
en_result_t CTRIM_CalibInit(stc_ctrim_calib_init_t *pstcInitConfig)
{
    MODIFY_REG(CTRIM->CR0, CTRIM_CR0_STEP_Msk | CTRIM_CR0_ETRFLT_Msk | CTRIM_CR0_SRC_Msk,
               pstcInitConfig->u32InitStep | pstcInitConfig->u32ExternFilter | pstcInitConfig->u32AccurateClock);

    MODIFY_REG(CTRIM->CR1, CTRIM_CR1_MD_Msk | CTRIM_CR1_AUTO_Msk | CTRIM_CR1_PRS_Msk | CTRIM_CR1_OST_Msk,
               pstcInitConfig->u32Mode | pstcInitConfig->u32RefClockDiv | pstcInitConfig->u32OneShot);

    CTRIM->ARR = (uint32_t)(pstcInitConfig->u16ReloadValue);

    CTRIM->FLIM = (uint32_t)(pstcInitConfig->u16CountErrorLimit);

    return Ok;
}

/**
 * @brief  CTRIM时钟功能初始化配置
 * @param  [in] pstcInitConfig Trim时钟初始化结构体 @ref stc_ctrim_timer_init_t
 * @retval en_result_t
 *           - Ok 配置成功
 *           - ErrorInvalidParameter 无效参数
 */
en_result_t CTRIM_TimerInit(stc_ctrim_timer_init_t *pstcInitConfig)
{
    MODIFY_REG(CTRIM->CR0, CTRIM_CR0_ETRFLT_Msk | CTRIM_CR0_SRC_Msk, pstcInitConfig->u32ExternFilter | pstcInitConfig->u32Clock);

    MODIFY_REG(CTRIM->CR1, CTRIM_CR1_MD_Msk | CTRIM_CR1_AUTO_Msk | CTRIM_CR1_PRS_Msk, CTRIM_CR1_MD_Msk | pstcInitConfig->u32ClockDiv);

    CTRIM->ARR = (uint32_t)(pstcInitConfig->u16ReloadValue);

    return Ok;
}

/**
 * @brief  CTRIM获取误差计数器计数值
 * @retval uint32_t 计数器计数值
 */
uint32_t CTRIM_CounterGet(void)
{
    return (uint32_t)(READ_REG32_BIT(CTRIM->CNT, CTRIM_CNT_CNT_Msk));
}

/**
 * @brief  CTRIM设定自动装载寄存器的值
 * @param  [in] u32AutoReload 重载值 取值范围 0x0 ~ 0xFFFF
 * @retval None
 */
void CTRIM_AutoReloadSet(uint32_t u32AutoReload)
{
    MODIFY_REG32(CTRIM->ARR, CTRIM_ARR_ARR_Msk, u32AutoReload);
}

/**
 * @brief  CTRIM TRIM初始步进量配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] u32TrimStep 初始步进量 @ref CTRIM_Init_Step_Select
 * @retval None
 */
void CTRIM_InitStepSet(uint32_t u32TrimStep)
{
    MODIFY_REG32(CTRIM->CR0, CTRIM_CR0_STEP_Msk, u32TrimStep);
}

/**
 * @brief  CTRIM 外部管脚输入时钟滤波配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] u32ExClockFilter 外部输入时钟滤波配置 @ref CTRIM_ETR_Clock_Filter_Select
 * @retval None
 */
void CTRIM_ExternClockFilterSet(uint32_t u32ExternClockFilter)
{
    MODIFY_REG32(CTRIM->CR0, CTRIM_CR0_ETRFLT_Msk, u32ExternClockFilter);
}

/**
 * @brief  CTRIM精确时钟源选择，必须在CTRIM模块未使能时才可以配置
 * @param  [in] u32ClockSrc 时钟源选择 @ref CTRIM_Accurate_clock_Select
 * @retval None
 */
void CTRIM_AccurateClockSet(uint32_t u32ClockSrc)
{
    MODIFY_REG32(CTRIM->CR0, CTRIM_CR0_SRC_Msk, u32ClockSrc);
}

/**
 * @brief  CTRIM工作模式配置
 * @param  [in] u32Mode 工作模式选择 @ref CTRIM_Mode_Select
 * @retval None
 */
void CTRIM_ModeSet(uint32_t u32Mode)
{
    MODIFY_REG32(CTRIM->CR1, (CTRIM_CR1_AUTO_Msk | CTRIM_CR1_MD_Msk), u32Mode);
}

/**
 * @brief  CTRIM 参考时钟预分频配置,CTRIM->CR1.PRS不能配置为0值，否则CTRIM不能正常工作
 * @param  [in] u32RefClockDiv 参考时钟预分频配置 @ref CTRIM_REF_Clock_Div_Select
 * @retval None
 */
void CTRIM_RefClockDivSet(uint32_t u32RefClockDiv)
{
    MODIFY_REG32(CTRIM->CR1, CTRIM_CR1_PRS_Msk, u32RefClockDiv);
}

/**
 * @brief  CTRIM校准模式配置
 * @param  [in] u32OneShotMode 校准模式配置 @ref CTRIM_One_Shot_Select
 * @retval None
 */
void CTRIM_OneShotSet(uint32_t u32OneShotMode)
{
    MODIFY_REG32(CTRIM->CR1, CTRIM_CR1_OST_Msk, u32OneShotMode);
}

/**
 * @brief  CTRIM获取误差计数器计数方向
 * @retval uint32_t 误差计数器计数方向 @ref CTRIM_ARR_Count_Dir
 */
uint32_t CTRIM_ARRCoutDirGet(void)
{
    return (uint32_t)(READ_REG32_BIT(CTRIM->ISR, CTRIM_ISR_DIR_Msk));
}

/**
 * @brief  CTRIM获取TrimCode值，及trim结束后的trim校准值
 * @retval uint32_t TrimCode值
 */
uint32_t CTRIM_TrimCodeGet(void)
{
    return (uint32_t)(READ_REG32_BIT(CTRIM->TVAL, CTRIM_TVAL_TVAL_Msk));
}

/**
 * @brief  CTRIM获取计数误差捕获值，校准结束时，ARR寄存器里面的值
 * @retval uint32_t 计数误差捕获值
 */
uint32_t CTRIM_CountErrorCaptureGet(void)
{
    return (uint32_t)(READ_REG32_BIT(CTRIM->FCAP, CTRIM_FCAP_FCAP_Msk));
}

/**
 * @brief  CTRIM设置误差允许值， 一个周期计数结束，ARR寄存器里的值小于当前设定值，则认为校验成功
 * @param  [in] u16ErrorLimit 误差上限值 取值范围 0x0 ~ 0xFFF
 * @retval None
 */
void CTRIM_CountErrorLimitSet(uint16_t u16ErrorLimit)
{
    MODIFY_REG(CTRIM->FLIM, CTRIM_FLIM_FLIM_Msk, (uint32_t)u16ErrorLimit);
}

/**
 * @brief  CTRIM开启模块
 * @retval None
 */
void CTRIM_Enable(void)
{
    SET_REG32_BIT(CTRIM->CR1, CTRIM_CR1_EN_Msk);
}

/**
 * @brief  CTRIM禁止模块
 * @retval None
 */
void CTRIM_Disable(void)
{
    CLR_REG32_BIT(CTRIM->CR1, CTRIM_CR1_EN_Msk);
}

/**
 * @brief  CTRIM中断使能
 * @param  [in] u32Int TRIM类型定义 @ref CTRIM_Int_Select
 * @retval None
 */
void CTRIM_IntEnable(uint32_t u32Int)
{
    SET_REG32_BIT(CTRIM->IER, u32Int);
}

/**
 * @brief  CTRIM中断禁止
 * @param  [in] u32Int TRIM类型定义 @ref CTRIM_Int_Select
 * @retval None
 */
void CTRIM_IntDisable(uint32_t u32Int)
{
    CLR_REG32_BIT(CTRIM->IER, u32Int);
}

/**
 * @brief  CTRIM获取状态标志
 * @param  [in] u32Flag 状态标记,CTRIM_Flag_Select值或值相或的组合 @ref CTRIM_Flag_Select
 * @retval boolean_t
 *           - TRUE 对应每位的功能
 *           - FALSE 对应每位的功能
 */
boolean_t CTRIM_FlagGet(uint32_t u32Flag)
{
    return (READ_REG32_BIT(CTRIM->ISR, u32Flag) == u32Flag) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM清除状态标志
 * @param  [in] u32Flag 状态标记,CTRIM_Flag_Select值或值相或的组合 @ref CTRIM_Flag_Select
 * @retval None
 */
void CTRIM_FlagClear(uint32_t u32Flag)
{
    CLR_REG32_BIT(CTRIM->ICR, u32Flag);
}

/**
 * @brief  CTRIM清除所有标志
 * @retval None
 */
void CTRIM_FlagClearALL(void)
{
    CTRIM->ICR = 0u;
}

/**
 * @brief  结构体初始化
 * @retval None
 */
void CTRIM_CalibStcInit(stc_ctrim_calib_init_t *pstcInit)
{
    pstcInit->u32Mode            = CTRIM_AUTO_CALIB_MD_RC48M;
    pstcInit->u32AccurateClock   = CTRIM_ACCURATE_CLOCK_ETR;
    pstcInit->u32RefClockDiv     = 0u;
    pstcInit->u32OneShot         = CTRIM_ONE_SHOT_REPETITIVE;
    pstcInit->u32InitStep        = CTRIM_INIT_STEP_16;
    pstcInit->u32ExternFilter    = CTRIM_ETR_CLK_FLT_NONE;
    pstcInit->u16ReloadValue     = 0xFFFFu;
    pstcInit->u16CountErrorLimit = 0x10u;
}

/**
 * @brief  CTRIM结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_ctrim_timer_init_t
 * @retval None
 */
void CTRIM_TimerStcInit(stc_ctrim_timer_init_t *pstcInit)
{
    pstcInit->u32Clock        = CTRIM_ACCURATE_CLOCK_ETR;
    pstcInit->u32ClockDiv     = 0u;
    pstcInit->u32ExternFilter = CTRIM_ETR_CLK_FLT_NONE;
    pstcInit->u16ReloadValue  = 0xFFFFu;
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
