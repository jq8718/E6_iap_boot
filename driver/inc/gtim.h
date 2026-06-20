/**
 *******************************************************************************
 * @file  gtim.h
 * @brief This file contains all the functions prototypes of the GTIM driver
 *        library
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

#ifndef __GTIM_H__
#define __GTIM_H__

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
 * @addtogroup DDL_GTIM GTIM模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GTIM_Global_Types GTIM全局类型定义
 * @{
 */

/**
 * @brief GTIMx 初始化配置的结构体
 */
typedef struct
{
    uint32_t u32Mode;                /*!< 工作模式：内部时钟计数、外部输入计数、触发模式、门控模式 @ref GTIM_Mode_Select */
    uint32_t u32OneShotEn;           /*!< 计数模式：连续计数模式或单次计数模式 @ref GTIM_OneShot_Continue_Select */
    uint32_t u32Prescaler;           /*!< 计数器输入信号分频 @ref GTIM_Clock_Div */
    uint32_t u32ToggleEn;            /*!< Toggle_N和Toggle_P输出使能 @ref GTIM_Toggle_Output_Control */
    uint32_t u32TriggerSrc;          /*!< 触发源选择，外部管脚ETR或者上一级BTIM溢出 @ref GTIM_Trigger_Src_Sel */
    uint32_t u32ExternInputPolarity; /*!< 外部输入极性选择 @ref GTIM_ETR_Input_Polarity */
    uint32_t u32AutoReloadValue;     /*!< 配置重载寄存器的值 */
} stc_gtim_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GTIM_Global_Macros GTIM全局宏定义
 * @{
 */

/** @defgroup GTIM_Mode_Select GTIM工作模式配置
 * @{
 */
#define GTIM_MD_PCLK   (0x0u)                    /*!< GTIM 内部时钟计数模式 */
#define GTIM_MD_EXTERN (0x1u << GTIM_CR0_MD_Pos) /*!< GTIM 外部输入计数模式 */
#define GTIM_MD_TRIG   (0x2u << GTIM_CR0_MD_Pos) /*!< GTIM 触发模式 */
#define GTIM_MD_GATE   (0x3u << GTIM_CR0_MD_Pos) /*!< GTIM 门控模式  */
/**
 * @}
 */

/** @defgroup GTIM_OneShot_Continue_Select GTIM单次/连续计数模式
 * @{
 */
#define GTIM_CONTINUOUS_COUNTER (0x0u)             /*!< 连续计数模式 */
#define GTIM_ONESHOT_COUNTER    (GTIM_CR0_OST_Msk) /*!< 单次计数模式 */
/**
 * @}
 */

/** @defgroup GTIM_Clock_Div GTIM预分频器分频系数配置
 * @{
 */
#define GTIM_COUNTER_CLK_DIV1     (0x0u)                     /*!<GTIM Div 1 */
#define GTIM_COUNTER_CLK_DIV2     (0x1u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 2 */
#define GTIM_COUNTER_CLK_DIV4     (0x2u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 4 */
#define GTIM_COUNTER_CLK_DIV8     (0x3u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 8 */
#define GTIM_COUNTER_CLK_DIV16    (0x4u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 16 */
#define GTIM_COUNTER_CLK_DIV32    (0x5u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 32 */
#define GTIM_COUNTER_CLK_DIV64    (0x6u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 64 */
#define GTIM_COUNTER_CLK_DIV128   (0x7u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 128 */
#define GTIM_COUNTER_CLK_DIV256   (0x8u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 256 */
#define GTIM_COUNTER_CLK_DIV512   (0x9u << GTIM_CR0_PRS_Pos) /*!<GTIM Div 512 */
#define GTIM_COUNTER_CLK_DIV1024  (0xAu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 1024 */
#define GTIM_COUNTER_CLK_DIV2048  (0xBu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 2048 */
#define GTIM_COUNTER_CLK_DIV4096  (0xCu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 4096 */
#define GTIM_COUNTER_CLK_DIV8192  (0xDu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 8192 */
#define GTIM_COUNTER_CLK_DIV16384 (0xEu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 16384 */
#define GTIM_COUNTER_CLK_DIV32768 (0xFu << GTIM_CR0_PRS_Pos) /*!<GTIM Div 32768 */
/**
 * @}
 */

/** @defgroup GTIM_Toggle_Output_Control GTIM TOG管脚输出使能控制
 * @{
 */
#define GTIM_TOGGLE_DISABLE (0x0u)               /*!< TOGP、TOGN输出电平都为0 */
#define GTIM_TOGGLE_ENABLE  (GTIM_CR0_TOGEN_Msk) /*!< TOGP、TOGN输出电平相反的信号 */
/**
 * @}
 */

/** @defgroup GTIM_Trigger_Src_Select GTIM触发源选择
 * @{
 */
#define GTIM_TRIG_SRC_ETR  (0x0u)                     /*!< ETR管脚输入的信号 */
#define GTIM_TRIG_SRC_ITR1 (0x1u << GTIM_CR0_TRS_Pos) /*!< ITR1内部互联信号 */
#define GTIM_TRIG_SRC_ITR2 (0x2u << GTIM_CR0_TRS_Pos) /*!< ITR2内部互联信号 */
#define GTIM_TRIG_SRC_ITR3 (0x3u << GTIM_CR0_TRS_Pos) /*!< ITR3内部互联信号 */
/**
 * @}
 */

/** @defgroup GTIM_ETR_Input_Polarity GTIM外部管脚输入的ETR信号极性选择
 * @{
 */
#define GTIM_ETR_POLARITY_NORMAL   (0x0u)             /*!< 外部输入ETR不反向(触发模式上沿触发，门控模式低电平停止计数) */
#define GTIM_ETR_POLARITY_INVERTED (GTIM_CR0_ETP_Msk) /*!< 外部输入ETR反向(触发模式下沿触发，门控模式高电平停止计数) */
/**
 * @}
 */

/** @defgroup GTIM_ETP_Extern_Input_Filter GTIM管脚输入信号滤波配置
 * @{
 */
#define GTIM_ETR_FLT_NONE             (0x0u)                        /*!< ETR输入无滤波 */
#define GTIM_ETR_FLT_PCLK_DIV1_CYCLE2 (0x1u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK，采样点个数2*/
#define GTIM_ETR_FLT_PCLK_DIV1_CYCLE4 (0x2u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK，采样点个数4*/
#define GTIM_ETR_FLT_PCLK_DIV1_CYCLE6 (0x3u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK，采样点个数6*/
#define GTIM_ETR_FLT_PCLK_DIV4_CYCLE4 (0x4u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK/4，采样点个数4*/
#define GTIM_ETR_FLT_PCLK_DIV4_CYCLE6 (0x5u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK/4，采样点个数6*/
#define GTIM_ETR_FLT_PCLK_DIV8_CYCLE4 (0x6u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK/8，采样点个数4*/
#define GTIM_ETR_FLT_PCLK_DIV8_CYCLE6 (0x7u << GTIM_CR1_ETRFLT_Pos) /*!< ETR输入滤波时钟PCLK/8，采样点个数6*/
/**
 * @}
 */

/** @defgroup GTIM_Capture_Compare_Ch_Select GTIM比较捕获通道配置
 * @{
 */
#define GTIM_COMPARE_CAPTURE_CH0 (GTIM_CMMR_CC0M_Pos) /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define GTIM_COMPARE_CAPTURE_CH1 (GTIM_CMMR_CC1M_Pos) /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define GTIM_COMPARE_CAPTURE_CH2 (GTIM_CMMR_CC2M_Pos) /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define GTIM_COMPARE_CAPTURE_CH3 (GTIM_CMMR_CC3M_Pos) /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
/**
 * @}
 */

/** @defgroup GTIM_Capture_Compare_Mode_Config GTIM捕获比较模式配置
 * @{
 */
#define GTIM_COMPARE_CAPTURE_NONE             (0x0u)                       /*!< 无功能 */
#define GTIM_COMPARE_CAPTURE_RISING           (0x1u << GTIM_CMMR_CC0M_Pos) /*!< 上升沿捕获 */
#define GTIM_COMPARE_CAPTURE_FALLING          (0x2u << GTIM_CMMR_CC0M_Pos) /*!< 下降沿捕获 */
#define GTIM_COMPARE_CAPTURE_RISING_FALLING   (0x3u << GTIM_CMMR_CC0M_Pos) /*!< 上下沿同时捕获 */
#define GTIM_COMPARE_CAPTURE_FORCE_LOW_LEVEL  (0x4u << GTIM_CMMR_CC0M_Pos) /*!< 强制输出低电平 */
#define GTIM_COMPARE_CAPTURE_FORCE_HIGH_LEVEL (0x5u << GTIM_CMMR_CC0M_Pos) /*!< 强制输出高电平 */
#define GTIM_COMPARE_CAPTURE_PWM_NORMAL       (0x6u << GTIM_CMMR_CC0M_Pos) /*!< PWM正向输出(CNT >= CCR0输出高电平)  */
#define GTIM_COMPARE_CAPTURE_PWM_INVERTED     (0x7u << GTIM_CMMR_CC0M_Pos) /*!< PWM反向输出(CNT < CCR输出高电平) */
/**
 * @}
 */

/** @defgroup GTIM_Int_Select GTIM中断使能控制
 * @{
 */
#define GTIM_INT_UI       (GTIM_IER_UI_Msk)     /*!< 溢出中断使能控制 */
#define GTIM_INT_TI       (GTIM_IER_TI_Msk)     /*!< 触发中断使能控制 */
#define GTIM_INT_CC0      (GTIM_IER_CC0_Msk)    /*!< GTIM捕获比较0使能控制 */
#define GTIM_INT_CC1      (GTIM_IER_CC1_Msk)    /*!< GTIM捕获比较1使能控制 */
#define GTIM_INT_CC2      (GTIM_IER_CC2_Msk)    /*!< GTIM捕获比较2使能控制 */
#define GTIM_INT_CC3      (GTIM_IER_CC3_Msk)    /*!< GTIM捕获比较3使能控制 */
#define GTIM_OV_TRIG_ADC  (GTIM_IER_OVTRAD_Msk) /*!< GTIM 溢出触发ADC使能控制 */
#define GTIM_CC0_TRIG_ADC (GTIM_IER_C0TRAD_Msk) /*!< GTIM CH0触发ADC使能控制 */
/**
 * @}
 */

/** @defgroup GTIM_Flag_Select GTIM中断标志选择
 * @{
 */
#define GTIM_FLAG_UI  (GTIM_IFR_UI_Msk)  /*!< 溢出中断标志 */
#define GTIM_FLAG_TI  (GTIM_IFR_TI_Msk)  /*!< 触发中断标志 */
#define GTIM_FLAG_CC0 (GTIM_IFR_CC0_Msk) /*!< GTIM捕获比较0中断标志 */
#define GTIM_FLAG_CC1 (GTIM_IFR_CC1_Msk) /*!< GTIM捕获比较1中断标志 */
#define GTIM_FLAG_CC2 (GTIM_IFR_CC2_Msk) /*!< GTIM捕获比较2中断标志 */
#define GTIM_FLAG_CC3 (GTIM_IFR_CC3_Msk) /*!< GTIM捕获比较3中断标志 */
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
 * @addtogroup GTIM_Global_Functions GTIM全局函数定义
 * @{
 */
en_result_t GTIM_Init(GTIM_TypeDef *GTIMx, stc_gtim_init_t *pstcInitConfig); /* 定时器GTIM的初始化配置 */

uint32_t GTIM_CounterGet(GTIM_TypeDef *GTIMx);                         /* 获取GTIM计数器计数值 */
void     GTIM_CounterSet(GTIM_TypeDef *GTIMx, uint16_t u16CountValue); /* 设置GTIM计数器计数值 */

void GTIM_AutoReloadSet(GTIM_TypeDef *GTIMx, uint16_t u16AutoReload); /* 设定GTIM重载寄存器的值 */

void GTIM_Enable(GTIM_TypeDef *GTIMx);  /* 开启定时器GTIM模块 */
void GTIM_Disable(GTIM_TypeDef *GTIMx); /* 禁止定时器GTIM模块 */

void GTIM_ModeSet(GTIM_TypeDef *GTIMx, uint32_t u32Mode); /* 设定定时器GTIM工作模式 */

void GTIM_ToggleEnable(GTIM_TypeDef *GTIMx);  /* 定时器GTIM TOG输出使能 */
void GTIM_ToggleDisable(GTIM_TypeDef *GTIMx); /* 定时器GTIM TOG输出禁止 */

void GTIM_CounterClockDivSet(GTIM_TypeDef *GTIMx, uint32_t u32CounterClockDiv); /* 定时器GTIM模块 计数时钟预除频 */

void GTIM_OneShotSet(GTIM_TypeDef *GTIMx, uint32_t u32OneShotMode); /* 设定GTIM计数模式 单次/连续计数模式 */

void GTIM_TriggerSrcSet(GTIM_TypeDef *GTIMx, uint32_t u32TriggerSrc); /* 设定定时器GTIM触发源 */

void GTIM_ExternInputPolaritySet(GTIM_TypeDef *GTIMx, uint32_t u32ExternInputPolarity); /* 设定定时器GTIM外部输入ETR极性设定 */
void GTIM_ExternInputFilterSet(GTIM_TypeDef *GTIMx, uint32_t u32ExternInputFilter);     /* 设定定时器GTIM外部输入ETR滤波时间 */

void     GTIM_CompareCaptureModeSet(GTIM_TypeDef *GTIMx, uint32_t u32Ch, uint32_t u32CaptureMode); /* 定时器GTIM捕获比较模式选择 */
void     GTIM_CompareCaptureRegSet(GTIM_TypeDef *GTIMx, uint32_t u32Ch, uint32_t u32Capture);      /* 设定GTIM比较捕获（寄存器）值 */
uint32_t GTIM_CompareCaptureRegGet(GTIM_TypeDef *GTIMx, uint32_t u32Ch);                           /* 获取GTIM比较捕获（寄存器）值 */
void     GTIM_CompareCaptureAllDisable(GTIM_TypeDef *GTIMx);                                       /* 禁止所有通道比较捕获功能 */

void GTIM_IntEnable(GTIM_TypeDef *GTIMx, uint32_t u32Int);  /* GTIM中断或触发ADC使能 */
void GTIM_IntDisable(GTIM_TypeDef *GTIMx, uint32_t u32Int); /* GTIM中断禁止 */

boolean_t GTIM_IntFlagGet(GTIM_TypeDef *GTIMx, uint32_t u32IntFlagTypes);   /* 获取GTIM中断标志 */
void      GTIM_IntFlagClear(GTIM_TypeDef *GTIMx, uint32_t u32IntClearFlag); /* 清除GTIM中断标志位 */

void GTIM_StcInit(stc_gtim_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __GTIM_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
