/**
 *******************************************************************************
 * @file  adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-07-07       MADS            Modify ADC_IBAS_Current Selection
                                    Modify ADC_TRIG_CTRIM Comment
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

#ifndef __ADC_H__
#define __ADC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_ADC ADC模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC全局类型定义
 * @{
 */

/**
 * @brief  ADC初始化配置结构体
 * @note
 */
typedef struct
{
    uint32_t u32ClockDiv;      /*!< ADC时钟分频选择 @ref ADC_Clock_Divider */
    uint32_t u32SampCycle;     /*!< ADC采样周期选择 @ref ADC_Sample_Cycle */
    uint32_t u32RefVoltage;    /*!< ADC参考电压选择 @ref ADC_Ref_Voltage */
    uint32_t u32CurrentSelect; /*!< ADC IBAS电流选择 @ref ADC_IBAS_Current */
    uint32_t u32SqrCount;      /*!< ADC SQR扫描转换次数，数据范围：1 ~ 4 */
} stc_adc_sqr_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC全局宏定义
 * @{
 */

/**
 * @defgroup ADC_Ref_Voltage ADC参考电压
 * @{
 */
#define ADC_REF_VOL_AVCC   (0x0u << ADC_CR0_REF_Pos) /*!< AVCC */
#define ADC_REF_VOL_EXTERN (0x1u << ADC_CR0_REF_Pos) /*!< 外部输入(max avdd) PA02 */
/**
 * @}
 */

/**
 * @defgroup ADC_IBAS_Current ADC IBAS电流选择
 * @{
 */
#define ADC_IBAS_LOWEST_POWER (0x0u << ADC_CR0_IBSEL_Pos) /*!< 最小低功耗（推荐值） */
#define ADC_IBAS_LOW_POWER    (0x2u << ADC_CR0_IBSEL_Pos) /*!< 较小功耗 */
/**
 * @}
 */

/**
 * @defgroup ADC_Clock_Divider ADC时钟分频选择
 * @{
 */
#define ADC_CLK_DIV1 (0x0u << ADC_CR0_CLKDIV_Pos) /*!< PCLK */
#define ADC_CLK_DIV2 (0x1u << ADC_CR0_CLKDIV_Pos) /*!< 1/2 PCLK */
#define ADC_CLK_DIV4 (0x2u << ADC_CR0_CLKDIV_Pos) /*!< 1/4 PCLK */
#define ADC_CLK_DIV8 (0x3u << ADC_CR0_CLKDIV_Pos) /*!< 1/8 PCLK */
/**
 * @}
 */

/**
 * @defgroup ADC_Sample_Cycle_Select ADC采样周期选择
 * @{
 */
#define ADC_SAMPLE_CYCLE_2   (0x0u << ADC_CR0_SAM_Pos) /*!< 2个采样时钟 */
#define ADC_SAMPLE_CYCLE_3   (0x1u << ADC_CR0_SAM_Pos) /*!< 3个采样时钟 */
#define ADC_SAMPLE_CYCLE_4   (0x2u << ADC_CR0_SAM_Pos) /*!< 4个采样时钟 */
#define ADC_SAMPLE_CYCLE_6   (0x3u << ADC_CR0_SAM_Pos) /*!< 6个采样时钟 */
#define ADC_SAMPLE_CYCLE_8   (0x4u << ADC_CR0_SAM_Pos) /*!< 8个采样时钟 */
#define ADC_SAMPLE_CYCLE_10  (0x5u << ADC_CR0_SAM_Pos) /*!< 10个采样时钟 */
#define ADC_SAMPLE_CYCLE_12  (0x6u << ADC_CR0_SAM_Pos) /*!< 12个采样时钟 */
#define ADC_SAMPLE_CYCLE_16  (0x7u << ADC_CR0_SAM_Pos) /*!< 16个采样时钟 */
#define ADC_SAMPLE_CYCLE_20  (0x8u << ADC_CR0_SAM_Pos) /*!< 20个采样时钟 */
#define ADC_SAMPLE_CYCLE_28  (0x9u << ADC_CR0_SAM_Pos) /*!< 28个采样时钟 */
#define ADC_SAMPLE_CYCLE_36  (0xAu << ADC_CR0_SAM_Pos) /*!< 36个采样时钟 */
#define ADC_SAMPLE_CYCLE_48  (0xBu << ADC_CR0_SAM_Pos) /*!< 48个采样时钟 */
#define ADC_SAMPLE_CYCLE_64  (0xCu << ADC_CR0_SAM_Pos) /*!< 64个采样时钟 */
#define ADC_SAMPLE_CYCLE_72  (0xDu << ADC_CR0_SAM_Pos) /*!< 72个采样时钟 */
#define ADC_SAMPLE_CYCLE_96  (0xEu << ADC_CR0_SAM_Pos) /*!< 96个采样时钟 */
#define ADC_SAMPLE_CYCLE_127 (0xFu << ADC_CR0_SAM_Pos) /*!< 127个采样时钟 */
/**
 * @}
 */

/**
 * @defgroup ADC_Trigger_Src_Select ADC模块触发源选择
 * @{
 */
#define ADC_TRIG_CTIM0   (0x1u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择CTIM0，自动触发ADC采样 */
#define ADC_TRIG_CTIM1   (0x2u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择CTIM1，自动触发ADC采样 */
#define ADC_TRIG_ATIM3   (0x3u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择ATIM3，自动触发ADC采样 */
#define ADC_TRIG_CTRIM   (0x4u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择CTRIM_TOG，TOG的上升沿自动触发ADC采样 */
#define ADC_TRIG_LPUART0 (0x5u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择LPUART0中断源，自动触发ADC采样 */
#define ADC_TRIG_VC0     (0x6u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择VC0中断源，自动触发ADC采样 */
#define ADC_TRIG_PA03    (0x7u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择PA03中断源，自动触发ADC采样 */
#define ADC_TRIG_PA07    (0x8u << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos) /*!< 选择PA07中断源，自动触发ADC采样 */
/**
 * @}
 */

/**
 * @defgroup ADC_SQR_Convert_Ch_Select ADC SQR转换通道选择
 * @{
 */
#define ADC_SQR_CH0_MUX (0x0u) /*!< SQR扫描模式转换通道0 */
#define ADC_SQR_CH1_MUX (0x1u) /*!< SQR扫描模式转换通道1 */
#define ADC_SQR_CH2_MUX (0x2u) /*!< SQR扫描模式转换通道2 */
#define ADC_SQR_CH3_MUX (0x3u) /*!< SQR扫描模式转换通道3 */
/**
 * @}
 */

/**
 * @defgroup ADC_Input_Ch_Select ADC转换通道选择
 * @{
 */
#define ADC_INPUT_CH0 (0x0u) /*!< 使用PA00 */
#define ADC_INPUT_CH1 (0x1u) /*!< 使用PA02 */
#define ADC_INPUT_CH2 (0x2u) /*!< 使用PA03 */
#define ADC_INPUT_CH3 (0x3u) /*!< 使用PA05 */
#define ADC_INPUT_CH4 (0x4u) /*!< 使用PA09 */
#define ADC_INPUT_CH5 (0x5u) /*!< 使用PA10 */
#define ADC_INPUT_CH6 (0x6u) /*!< 使用PA11 */
#define ADC_INPUT_CH7 (0x7u) /*!< 使用PA12 */
#define ADC_INPUT_CH8 (0x8u) /*!< 使用VCAP */
#define ADC_INPUT_CH9 (0x9u) /*!< 使用AVCC/3 */
/**
 * @}
 */

/**
 * @defgroup ADC_Status_Select ADC状态选择
 * @{
 */
#define ADC_FLAG_SQR (ADC_IFR_SQRIF_Msk) /*!< ADC SQR扫描转换完成 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ADC_Global_Functions ADC全局函数定义
 * @{
 */
en_result_t ADC_SqrInit(stc_adc_sqr_init_t *pstcAdcInit); /* ADC初始化 */

void ADC_Enable(void);  /* ADC使能 */
void ADC_Disable(void); /* ADC禁止 */

en_result_t ADC_ConfigSqrCh(uint32_t u32AdcSqrChMux, uint32_t u32AdcChSelect); /* ADC SQR扫描转换模式通道选择配置 */

void ADC_ExternTrigEnable(uint32_t u32AdcTriggerSelect);  /* ADC 转换外部触发源使能 */
void ADC_ExternTrigDisable(uint32_t u32AdcTriggerSelect); /* ADC 转换外部触发源禁止 */

void ADC_SqrStart(void); /* ADC SQR扫描转换模式启动 */

uint32_t ADC_SqrResultGet(uint32_t u32AdcSqrChMux); /* 获取SQR扫描采样值 */

void      ADC_IntEnable(void);                  /* ADC中断使能 */
void      ADC_IntDisable(void);                 /* ADC中断禁止 */
boolean_t ADC_IntFlagGet(uint32_t u32AdcInt);   /* ADC采样完成状态获取 */
void      ADC_IntFlagClear(uint32_t u32AdcInt); /* ADC采样完成状态清除 */

void ADC_SqrStcInit(stc_adc_sqr_init_t *pstcInit); /* 结构体初始化 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
