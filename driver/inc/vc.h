/**
 *******************************************************************************
 * @file  vc.h
 * @brief This file contains all the functions prototypes of the VC driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
   2025-07-08       MADS            Add VC trim function
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

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_VC VC模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup VC_Global_Types VC全局类型定义
 * @{
 */

/**
 * @brief VC初始化配置结构体
 */
typedef struct
{
    uint32_t u32Ch;           /*!< 通道选择 @ref VC_Ch_Select */
    uint32_t u32BiasCurrent;  /*!< 功耗选择 @ref VC_Bias_Current_Select */
    uint32_t u32HysVolt;      /*!< 迟滞电压选择 @ref VC_Hysteresis_Volt_Select */
    uint32_t u32IntMode;      /*!< 中断触发模式选择 @ref VC_Int_Mode_Select */
    uint32_t u32InputPos;     /*!< 电压比较器正端输入信号选择 @ref VC_Input_Positive_Select */
    uint32_t u32InputNeg;     /*!< 电压比较器负端输入信号选择 @ref VC_Input_Negative_Select */
    uint32_t u32FilterTime;   /*!< 数字滤波时间选择 @ref VC_Filter_Time_Select */
    uint32_t u32FilterClk;    /*!< 滤波时钟选择 @ref VC_Filter_Clock_Select  */
    uint32_t u32FilterMode;   /*!< 滤波模式选择 @ref VC_Filter_Mode_Select */
    uint32_t u32OutputPol;    /*!< 输出信号极性配置 @ref VC_Output_Polarity_Config */
    uint8_t  u8TrimSetSelect; /*!< Trim设置选择 @ref VC_Trim_Select */
} stc_vc_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup VC_Global_Macros VC全局宏定义
 * @{
 */

/**
 * @defgroup VC_Ch_Select VC通道选择
 * @{
 */
#define VC_CH0 (0x0u)  /*!< 通道0 */
#define VC_CH1 (0x10u) /*!< 通道1 */
/**
 * @}
 */

/**
 * @defgroup VC_Hysteresis_Volt_Select 迟滞电压选择
 * @{
 */
#define VC_HYSTERESIS_VOLT_NONE (0x0u)                       /*!< 迟滞关闭 */
#define VC_HYSTERESIS_VOLT_10MV (0x1u << VC_VC0_CR0_HYS_Pos) /*!< 迟滞10mv */
#define VC_HYSTERESIS_VOLT_20MV (0x2u << VC_VC0_CR0_HYS_Pos) /*!< 迟滞20mv */
#define VC_HYSTERESIS_VOLT_30MV (0x3u << VC_VC0_CR0_HYS_Pos) /*!< 迟滞30mv */
/**
 * @}
 */

/**
 * @defgroup VC_Bias_Current_Select 功耗选择
 * @{
 */
#define VC_BIAS_CURR_LOW        (0x0u)                        /*!< 低功耗档 */
#define VC_BIAS_CURR_MEDIUM_LOW (0x1u << VC_VC0_CR0_BIAS_Pos) /*!< 中低功耗档 */
#define VC_BIAS_CURR_MEDIUM     (0x2u << VC_VC0_CR0_BIAS_Pos) /*!< 中功耗档 */
#define VC_BIAS_CURR_HIGH       (0x3u << VC_VC0_CR0_BIAS_Pos) /*!< 高功耗档 */
/**
 * @}
 */

/**
 * @defgroup VC_Filter_Mode_Select 滤波器模式选择
 * @{
 */
#define VC_FILTER_MD_NFM (0x0u)                            /*!< 普通滤波模式 Normal Filter Mode */
#define VC_FILTER_MD_PFM (0x1u << VC_VC0_CR1_FLT_MODE_Pos) /*!< 滤峰模式 Peak Filter Mode */
#define VC_FILTER_MD_VFM (0x2u << VC_VC0_CR1_FLT_MODE_Pos) /*!< 滤谷模式 Valley Filter Mode */
#define VC_FILTER_MD_SFM (0x3u << VC_VC0_CR1_FLT_MODE_Pos) /*!< 滤刺模式 Spike Filter Mode */
/**
 * @}
 */

/**
 * @defgroup VC_Filter_Clock_Select 滤波时钟选择
 * @{
 */
#define VC_FILTER_CLK_RC256K (0x0u)                  /*!< 内置RC振荡器，频率约256KHz */
#define VC_FILTER_CLK_PCLK   (VC_VC1_CR1_FLTCLK_Msk) /*!< PCLK */
/**
 * @}
 */

/**
 * @defgroup VC_Filter_Time_Select 数字滤波时间选择
 * @{
 */
#define VC_FILTER_TIME_NONE      (0x0u)                           /*!< 数字滤波无效 */
#define VC_FILTER_TIME_2CYCLE    (0x1u << VC_VC0_CR1_FLTTIME_Pos) /*!< 2个滤波时钟周期 */
#define VC_FILTER_TIME_4CYCLE    (0x2u << VC_VC0_CR1_FLTTIME_Pos) /*!< 4个滤波时钟周期 */
#define VC_FILTER_TIME_8CYCLE    (0x3u << VC_VC0_CR1_FLTTIME_Pos) /*!< 8个滤波时钟周期 */
#define VC_FILTER_TIME_16CYCLE   (0x4u << VC_VC0_CR1_FLTTIME_Pos) /*!< 16个滤波时钟周期 */
#define VC_FILTER_TIME_32CYCLE   (0x5u << VC_VC0_CR1_FLTTIME_Pos) /*!< 32个滤波时钟周期 */
#define VC_FILTER_TIME_64CYCLE   (0x6u << VC_VC0_CR1_FLTTIME_Pos) /*!< 64个滤波时钟周期 */
#define VC_FILTER_TIME_128CYCLE  (0x7u << VC_VC0_CR1_FLTTIME_Pos) /*!< 128个滤波时钟周期 */
#define VC_FILTER_TIME_256CYCLE  (0x8u << VC_VC0_CR1_FLTTIME_Pos) /*!< 256个滤波时钟周期 */
#define VC_FILTER_TIME_512CYCLE  (0x9u << VC_VC0_CR1_FLTTIME_Pos) /*!< 512个滤波时钟周期 */
#define VC_FILTER_TIME_1024CYCLE (0xAu << VC_VC0_CR1_FLTTIME_Pos) /*!< 1024个滤波时钟周期 */
#define VC_FILTER_TIME_2048CYCLE (0xBu << VC_VC0_CR1_FLTTIME_Pos) /*!< 2048个滤波时钟周期 */
#define VC_FILTER_TIME_4096CYCLE (0xCu << VC_VC0_CR1_FLTTIME_Pos) /*!< 4096个滤波时钟周期 */
/**
 * @}
 */

/**
 * @defgroup VC_Input_Positive_Select 电压比较器正端输入信号选择
 * @{
 */
#define VC_POS_SEL_CH0  (0x0u)                        /*!< 输入通道0  VCx_INN0(x=0, PA00; x=1, PA01) */
#define VC_POS_SEL_CH1  (0x1u << VC_VC0_CR1_PSEL_Pos) /*!< 输入通道1  VCx_INN1(x=0, PA02; x=1, PA03) */
#define VC_POS_SEL_CH2  (0x2u << VC_VC0_CR1_PSEL_Pos) /*!< 输入通道2  VCx_INN2(x=0, PA08; x=1, PA10) */
#define VC_POS_SEL_CH3  (0x3u << VC_VC0_CR1_PSEL_Pos) /*!< 输入通道3  VCx_INN3(x=0, PA15; x=1, PA12) */
#define VC_POS_SEL_CH4  (0x4u << VC_VC0_CR1_PSEL_Pos) /*!< 输入通道4  VCx_INN4(x=0/1, 6BDAC) */
#define VC_POS_SEL_CH5  (0x5u << VC_VC0_CR1_PSEL_Pos) /*!< 输入通道5  VCx_INN5(x=0/1, VCORE) */
#define VC_POS_SEL_NONE (0xFu << VC_VC0_CR1_PSEL_Pos) /*!< NONE */
/**
 * @}
 */

/**
 * @defgroup VC_Input_Negative_Select 电压比较器负端输入信号选择
 * @{
 */
#define VC_NEG_SEL_CH0  (0x0u)                        /*!< 输入通道0  VCx_INN0(x=0, PA00; x=1, PA01) */
#define VC_NEG_SEL_CH1  (0x1u << VC_VC0_CR1_NSEL_Pos) /*!< 输入通道1  VCx_INN1(x=0, PA02; x=1, PA03) */
#define VC_NEG_SEL_CH2  (0x2u << VC_VC0_CR1_NSEL_Pos) /*!< 输入通道2  VCx_INN2(x=0, PA08; x=1, PA10) */
#define VC_NEG_SEL_CH3  (0x3u << VC_VC0_CR1_NSEL_Pos) /*!< 输入通道3  VCx_INN3(x=0, PA15; x=1, PA12) */
#define VC_NEG_SEL_CH4  (0x4u << VC_VC0_CR1_NSEL_Pos) /*!< 输入通道4  VCx_INN4(x=0/1, 6BDAC) */
#define VC_NEG_SEL_CH5  (0x5u << VC_VC0_CR1_NSEL_Pos) /*!< 输入通道5  VCx_INN5(x=0/1, VCORE) */
#define VC_NEG_SEL_NONE (0xFu << VC_VC0_CR1_PSEL_Pos) /*!< NONE */
/**
 * @}
 */

/**
 * @defgroup VC_Output_Polarity_Config 输出信号极性配置
 * @{
 */
#define VC_OUTPUT_POL_POS (0x0u)               /*!< 输出信号极性正向 正端大于负端时VCx_OUTP高 */
#define VC_OUTPUT_POL_NEG (VC_VC0_CR2_POL_Msk) /*!< 输出信号极性反向 正端大于负端时VCx_OUTP低 */
/**
 * @}
 */

/**
 * @defgroup VC_Int_Mode_Select 中断触发模式选择
 * @{
 */
#define VC_INT_MD_NONE    (0x0u)                   /*!< 无触发 */
#define VC_INT_MD_FALLING (VC_VC0_CR1_FALLING_Msk) /*!< 下降沿触发 */
#define VC_INT_MD_RISING  (VC_VC0_CR1_RISING_Msk)  /*!< 上升沿触发 */
#define VC_INT_MD_HIGH    (VC_VC0_CR1_LEVEL_Msk)   /*!< 高电平触发 */
/**
 * @}
 */

/**
 * @defgroup VC_Blank_Window_Select 空白窗口源选择源选择
 * @{
 */
#define VC_BLANK_WIN_NONE            (0x0u)                         /*!< 无空白窗口 */
#define VC_BLANK_WIN_ATIM3_OCREF0B   (0x1u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF0B (xx1) */
#define VC_BLANK_WIN_ATIM3_OCREF1B   (0x2u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF1B (x1x) */
#define VC_BLANK_WIN_ATIM3_OCREF2B   (0x4u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF2B (1xx) */
#define VC_BLANK_WIN_ATIM3_OCREF01B  (0x3u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF01B (x11) */
#define VC_BLANK_WIN_ATIM3_OCREF02B  (0x5u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF02B (1x1) */
#define VC_BLANK_WIN_ATIM3_OCREF12B  (0x6u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF12B (11x) */
#define VC_BLANK_WIN_ATIM3_OCREF012B (0x7u << VC_VC0_CR2_BLANK_Pos) /*!< ATIM3 OCREF012B (111) */
/**
 * @}
 */

/**
 * @defgroup VC_Output_Atim3_Config  滤波后信号输出到ATIM3配置
 * @{
 */
#define VC_OUTPUT_ATIM_NONE (0x0u)                    /*!< 禁止滤波后信号输出到ATIM3 */
#define VC_OUTPUT_ATIM_CLR  (VC_VC0_CR2_ATIM3CLR_Msk) /*!< 滤波后信号输出到ATIM3 REFCLR */
#define VC_OUTPUT_ATM_BK    (VC_VC0_CR2_ATIMBK_Msk)   /*!< 滤波后信号输出到ATIM3 刹车 */
/**
 * @}
 */

/**
 * @defgroup VC_Trim_Select VC Trim选择
 * @{
 */
#define VC_TRIM_LOWER_0P5AVCC  (0x0u) /*!< 正端或负端的参考电压小于等于1/2 AVCC */
#define VC_TRIM_HIGHER_0P5AVCC (0x1u) /*!< 正端或负端的参考电压大于1/2 AVCC */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup VC_Global_Functions VC全局函数定义
 * @{
 */
en_result_t VC_Init(stc_vc_init_t *pstcVcInit); /* VC初始化函数 */
void        VC_Enable(uint8_t u8Ch);            /* VC模块使能 */
void        VC_Disable(uint8_t u8Ch);           /* VC模块禁止 */

void VC_ResVoltDivConfig(uint8_t u8Ch, uint32_t u32RefVoltDiv); /* VC电阻分压比例配置 */
void VC_ResVoltDivEnable(void);                                 /* 使能VC电阻分压电路 */
void VC_ResVoltDivDisable(void);                                /* 禁止VC电阻分压电路 */

void      VC_IntModeConfig(uint8_t u8Ch, uint32_t u32IntMode); /* VC中断模式配置 */
void      VC_IntEnable(uint8_t u8Ch);                          /* VC中断使能 */
void      VC_IntDisable(uint8_t u8Ch);                         /* VC中断禁止 */
boolean_t VC_IntFlagGet(uint8_t u8Ch);                         /* 获取VC中断标志  */
void      VC_IntFlagClear(uint8_t u8Ch);                       /* 清除VC中断标志 */

void VC_WindowEnable(uint8_t u8Ch);  /* VC窗口比较功能使能 */
void VC_WindowDisable(uint8_t u8Ch); /* VC窗口比较功能禁止 */

void VC_BlankWindowConfig(uint8_t u8Ch, uint32_t u32BlankWindow); /* VC空白窗口源配置 */

void VC_OutputAtimConfig(uint8_t u8Ch, uint32_t u32OutputAtimMode); /* VC滤波后信号输出到ATIM3配置 */

boolean_t VC_FilterOutputGet(uint8_t u8Ch); /* 获取滤波后的信号电平 */

void VC_TrimSet(uint8_t u8Ch, uint8_t u8TrimSelect); /* Trim设置*/

void VC_StcInit(stc_vc_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
