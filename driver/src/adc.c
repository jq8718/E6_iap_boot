/**
 *******************************************************************************
 * @file  adc.c
 * @brief This file provides firmware functions to manage the ADC
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-07-07       MADS            Modify ADC_SqrStcInit()
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
#include "adc.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ADC ADC模块驱动库
 * @brief ADC Driver Library ADC模块驱动库
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
 * @defgroup ADC_Global_Functions ADC全局函数定义
 * @{
 */

/**
 * @brief  ADC初始化
 * @param  [in] pstcAdcInit ADC初始化配置结构体 @ref stc_adc_sqr_init_t
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t ADC_SqrInit(stc_adc_sqr_init_t *pstcAdcInit)
{
    SET_REG32_BIT(ADC->CR0, ADC_CR0_EN_Msk); /* ADC 使能 */
    DDL_Delay10us(1);

    MODIFY_REG(ADC->CR0, ADC_CR0_CLKDIV_Msk | ADC_CR0_REF_Msk | ADC_CR0_SAM_Msk | ADC_CR0_IBSEL_Msk,
               (uint32_t)pstcAdcInit->u32ClockDiv | (uint32_t)pstcAdcInit->u32RefVoltage | (uint32_t)pstcAdcInit->u32SampCycle
                   | (uint32_t)pstcAdcInit->u32CurrentSelect);

    MODIFY_REG(ADC->SQR1, ADC_SQR1_CNT_Msk, (pstcAdcInit->u32SqrCount - 1));
    return Ok;
}

/**
 * @brief  配置SQR扫描转换通道
 * @param  [in] u32AdcSqrChMux SQR扫描转换通道顺序 @ref ADC_SQR_Convert_Ch_Select
 * @param  [in] u32AdcChSelect 转换通道 @ref ADC_Input_Ch_Select
 * @retval en_result_t
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t ADC_ConfigSqrCh(uint32_t u32AdcSqrChMux, uint32_t u32AdcChSelect)
{
    en_result_t enResult = Ok;

    switch (u32AdcSqrChMux)
    {
        case ADC_SQR_CH0_MUX:
            ADC->SQR0_f.CH0MUX = u32AdcChSelect;
            break;
        case ADC_SQR_CH1_MUX:
            ADC->SQR0_f.CH1MUX = u32AdcChSelect;
            break;
        case ADC_SQR_CH2_MUX:
            ADC->SQR0_f.CH2MUX = u32AdcChSelect;
            break;
        case ADC_SQR_CH3_MUX:
            ADC->SQR0_f.CH3MUX = u32AdcChSelect;
            break;

        default:
            enResult = ErrorInvalidParameter;
            break;
    }

    return enResult;
}

/**
 * @brief  获取SQR扫描采样值
 * @param  [in] u32AdcSqrChMux SQR扫描通道序号 @ref ADC_SQR_Convert_Ch_Select
 * @retval uint32_t 采样值
 */
uint32_t ADC_SqrResultGet(uint32_t u32AdcSqrChMux)
{
    volatile uint32_t *BaseSqrResultAddress = &(ADC->SQRRESULT0);

    return *(BaseSqrResultAddress + ((uint32_t)u32AdcSqrChMux));
}

/**
 * @brief  ADC转换外部中断触发源使能
 * @param  [in] u32AdcTriggerSelect 触发源选择 @ref ADC_Trigger_Src_Select
 * @retval None
 */
void ADC_ExternTrigEnable(uint32_t u32AdcTriggerSelect)
{
    SET_REG16_BIT(ADC->EXTTRIGGER, u32AdcTriggerSelect);
}
/**
 * @brief  ADC转换外部中断触发源禁止
 * @param  [in] u32AdcTriggerSelect 触发源选择 @ref ADC_Trigger_Src_Select
 * @retval None
 */
void ADC_ExternTrigDisable(uint32_t u32AdcTriggerSelect)
{
    CLR_REG16_BIT(ADC->EXTTRIGGER, u32AdcTriggerSelect);
}

/**
 * @brief  ADC使能
 * @retval None
 */
void ADC_Enable(void)
{
    SET_REG32_BIT(ADC->CR0, ADC_CR0_EN_Msk);
    DDL_Delay10us(1);
}

/**
 * @brief  ADC禁止
 * @retval None
 */
void ADC_Disable(void)
{
    CLR_REG16_BIT(ADC->CR0, ADC_CR0_EN_Msk);
}

/**
 * @brief  ADC SQR扫描转换开始
 * @retval None
 */
void ADC_SqrStart(void)
{
    SET_REG32_BIT(ADC->SQRSTART, ADC_SQRSTART_START_Msk);
}

/**
 * @brief  使能ADC中断
 * @retval None
 */
void ADC_IntEnable(void)
{
    SET_REG32_BIT(ADC->CR0, ADC_CR0_IE_Msk);
}

/**
 * @brief  禁止ADC中断
 * @retval None
 */
void ADC_IntDisable(void)
{
    CLR_REG32_BIT(ADC->CR0, ADC_CR0_IE_Msk);
}

/**
 * @brief  获取ADC中断状态
 * @param  [in] u32AdcInt ADC中断类型 @ref ADC_Status_Select
 * @retval boolean_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t ADC_IntFlagGet(uint32_t u32AdcInt)
{
    return READ_REG32_BIT(ADC->IFR, u32AdcInt) ? TRUE : FALSE;
}

/**
 * @brief  清除ADC中断标志
 * @param  [in] u32AdcInt ADC中断类型 @ref ADC_Status_Select
 * @retval None
 */
void ADC_IntFlagClear(uint32_t u32AdcInt)
{
    CLR_REG32_BIT(ADC->ICR, u32AdcInt);
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_adc_sqr_init_t
 * @retval None
 */
void ADC_SqrStcInit(stc_adc_sqr_init_t *pstcInit)
{
    pstcInit->u32ClockDiv      = ADC_CLK_DIV1;
    pstcInit->u32SampCycle     = ADC_SAMPLE_CYCLE_4;
    pstcInit->u32RefVoltage    = ADC_REF_VOL_AVCC;
    pstcInit->u32CurrentSelect = ADC_IBAS_LOWEST_POWER;
    pstcInit->u32SqrCount      = 1;
}
/**
 * @}
 */

/**
 * @}
 */

/*
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
