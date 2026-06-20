/**
 *******************************************************************************
 * @file  atim3.h
 * @brief This file contains all the functions prototypes of the ATIM3 driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
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

#ifndef __ATIM3_H__
#define __ATIM3_H__

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
 * @addtogroup DDL_ATIM3 ATIM3模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE0_Global_Types ATIM3 Mode0全局类型定义
 * @{
 */

/**
 * @brief ATIM3 mode0 配置结构体定义(模式0)
 */
typedef struct
{
    uint32_t u32WorkMode;         /*!< 工作模式设置 @ref ATIM3_Mode0_Work_Mode */
    uint32_t u32CountClockSelect; /*!< 计数时钟选择 @ref ATIM3_Mode0_Count_Clock */
    uint32_t u32CountMode;        /*!< 计数模式配置 @ref ATIM3_Mode0_Count_Mode */
    uint32_t u32PRS;              /*!< 预除频配置 @ref ATIM3_Mode0_PRS */
    uint32_t u32EnTog;            /*!< 翻转输出使能 @ref ATIM3_Mode0_Tog_ON_OFF */
    uint32_t u32EnGate;           /*!< 门控使能 @ref ATIM3_Mode0_Gate_Enable */
    uint32_t u32GatePolar;        /*!< 门控极性控制 @ref ATIM3_Mode0_Gate_Polar */
} stc_atim3_mode0_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode0_Global_Macros ATIM3 Mode0全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode0_Work_Mode 工作模式
 * @{
 */
#define ATIM3_M0_M0CR_WORK_MODE_TIMER (0x0u) /*!< 定时器模式(模式0) */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_Gate_Polar 门控极性控制
 * @{
 */
#define ATIM3_M0_M0CR_GATE_POLAR_HIGH (0x0u)                       /*!< 端口门控高电平有效 */
#define ATIM3_M0_M0CR_GATE_POLAR_LOW  (ATIM3_MODE0_M0CR_GATEP_Msk) /*!< 端口门控低电平有效 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_Gate_Enable 门控使能
 * @{
 */
#define ATIM3_M0_M0CR_GATE_OFF (0x0u)                      /*!< 定时器门控禁止 */
#define ATIM3_M0_M0CR_GATE_ON  (ATIM3_MODE0_M0CR_GATE_Msk) /*!< 定时器门控使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_PRS 预除频配置
 * @{
 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS1   (0x0u)                             /*!< PCLK */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS2   (0x1u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/2 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS4   (0x2u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/4 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS8   (0x3u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/8 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS16  (0x4u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/16 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS32  (0x5u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/32 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS64  (0x6u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/64 */
#define ATIM3_M0_M0CR_ATIM3CLK_PRS256 (0x7u << ATIM3_MODE0_M0CR_PRS_Pos) /*!< PCLK/256 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_Tog_ON_OFF 翻转输出使能
 * @{
 */
#define ATIM3_M0_M0CR_TOG_OFF (0x0u)                       /*!< 翻转输出禁止 */
#define ATIM3_M0_M0CR_TOG_ON  (ATIM3_MODE0_M0CR_TOGEN_Msk) /*!< 翻转输出使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_Count_Clock 定时/计数功能选择
 * @{
 */
#define ATIM3_M0_M0CR_CT_PCLK (0x0u)                    /*!< 内部计数时钟PCLK */
#define ATIM3_M0_M0CR_CT_ETR  (ATIM3_MODE0_M0CR_CT_Msk) /*!< 外部输入计数时钟ETR */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode0_Count_Mode 计数模式配置
 * @{
 */
#define ATIM3_M0_M0CR_MD_32BIT_FREE (0x0u)                    /*!< 32位自由计数 */
#define ATIM3_M0_M0CR_MD_16BIT_ARR  (ATIM3_MODE0_M0CR_MD_Msk) /*!< 16位重载计数 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE1_Global_Types ATIM3 Mode1全局类型定义
 * @{
 */

/**
 * @brief ATIM3 mode1 配置结构体定义(模式1)
 */
typedef struct
{
    uint32_t u32WorkMode;         /*!< 工作模式设置 @ref ATIM3_Mode1_Work_Mode */
    uint32_t u32PRS;              /*!< 预除频配置 @ref ATIM3_Mode1_PRS */
    uint32_t u32CountClockSelect; /*!< 计数时钟选择 @ref ATIM3_Mode1_Count_Clock */
    uint32_t u32ShotMode;         /*!< 单次测量/循环测量选择 @ref ATIM3_Mode1_Shot_Mode */
} stc_atim3_mode1_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode1_Global_Macros ATIM3 Mode1全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode1_Work_Mode 工作模式
 * @{
 */
#define ATIM3_M1_M1CR_WORK_MODE_PWC (0x1u << ATIM3_MODE1_M1CR_MODE_Pos) /*!< PWC模式(模式1) */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode1_PRS 预除频配置
 * @{
 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS1   (0x0u)                             /*!< PCLK */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS2   (0x1u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/2 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS4   (0x2u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/4 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS8   (0x3u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/8 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS16  (0x4u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/16 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS32  (0x5u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/32 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS64  (0x6u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/64 */
#define ATIM3_M1_M1CR_ATIM3CLK_PRS256 (0x7u << ATIM3_MODE1_M1CR_PRS_Pos) /*!< PCLK/256 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode1_Count_Clock 计数时钟选择
 * @{
 */
#define ATIM3_M1_M1CR_CT_PCLK (0x0u)                    /*!< 内部计数时钟PCLK */
#define ATIM3_M1_M1CR_CT_ETR  (ATIM3_MODE1_M1CR_CT_Msk) /*!< 外部输入计数时钟ETR */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode1_Shot_Mode 单次测量/循环测量选择
 * @{
 */
#define ATIM3_M1_M1CR_SHOT_CYCLE (0x0u)                         /*!< 循环测量 */
#define ATIM3_M1_M1CR_SHOT_ONE   (ATIM3_MODE1_M1CR_ONESHOT_Msk) /*!< 单次测量 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode1_PWC_Start_End_Edge PWC启动停止边沿选择
 * @{
 */
#define ATIM3_M1_M1CR_DETECT_EDGE_RISE_TO_RISE (0x0u)                                                      /*!< 上沿-->上沿 (周期) */
#define ATIM3_M1_M1CR_DETECT_EDGE_FALL_TO_RISE (ATIM3_MODE1_M1CR_EDG1ST_Msk)                               /*!< 下沿-->上沿 (低电平) */
#define ATIM3_M1_M1CR_DETECT_EDGE_RISE_TO_FALL (ATIM3_MODE1_M1CR_EDG2ND_Msk)                               /*!< 上沿-->下沿 (高电平) */
#define ATIM3_M1_M1CR_DETECT_EDGE_FALL_TO_FALL (ATIM3_MODE1_M1CR_EDG2ND_Msk | ATIM3_MODE1_M1CR_EDG1ST_Msk) /*!< 下沿-->下沿 (周期) */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3PWC_Global_Types ATIM3 PWC全局类型定义
 * @{
 */

/**
 * @brief PWC输入配置结构体定义(模式1)
 */
typedef struct
{
    uint32_t u32TsSelect;  /*!< 触发输入源选择 @ref ATIM3_PWC_Trigger_Source */
    uint32_t u32IA0Select; /*!< CHA0输入选择 @ref ATIM3_PWC_IA0S_Input */
    uint32_t u32IB0Select; /*!< CHB0输入选择 @ref ATIM3_PWC_IB0S_Input */
    uint32_t u32ETR;       /*!< ETR相位选择 @ref ATIM3_PWC_ET_Polarity */
    uint32_t u32FltETR;    /*!< ETR滤波设置 @ref ATIM3_PWC_Input_Filter */
    uint32_t u32FltIA0;    /*!< CHA0滤波设置 @ref ATIM3_PWC_Input_Filter */
    uint32_t u32FltIB0;    /*!< CHB0滤波设置 @ref ATIM3_PWC_Input_Filter */
} stc_atim3_pwc_input_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_PWC_Global_Macros ATIM3 PWC全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_PWC_Trigger_Source MSCR_TS触发输入源选择
 * @{
 */
#define ATIM3_M1_MSCR_TS_ETR         (0x0u)                            /*!< 端口ETR的滤波相位选择后的信号ETFP */
#define ATIM3_M1_MSCR_TS_ITR0        (0x1u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 内部互联信号 ITR0 */
#define ATIM3_M1_MSCR_TS_ITR1        (0x2u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 内部互联信号 ITR1 */
#define ATIM3_M1_MSCR_TS_ITR2        (0x3u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 内部互联信号 ITR2 */
#define ATIM3_M1_MSCR_TS_ITR3        (0x4u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 内部互联信号 ITR3 */
#define ATIM3_M1_MSCR_TS_CH0A_EDGE   (0x5u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 端口CH0A的边沿信号 */
#define ATIM3_M1_MSCR_TS_CH0A_FILTER (0x6u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 端口CH0A的滤波相位选择后的信号IAFP */
#define ATIM3_M1_MSCR_TS_CH0B_FILTER (0x7u << ATIM3_MODE1_MSCR_TS_Pos) /*!< 端口CH0B的滤波相位选择后的信号IBFP */
/**
 * @}
 */

/**
 * @defgroup ATIM3_PWC_IA0S_Input MSCR_IA0S CHA0输入选择
 * @{
 */
#define ATIM3_M1_MSCR_IA0S_CH0A       (0x0u)                      /*!< CH0A */
#define ATIM3_M1_MSCR_IA0S_CH012A_XOR (ATIM3_MODE1_MSCR_IA0S_Msk) /*!< CH0A CH1A CH2A XOR */
/**
 * @}
 */

/**
 * @defgroup ATIM3_PWC_IB0S_Input MSCR_IB0S CHB0输入选择
 * @{
 */
#define ATIM3_M1_MSCR_IB0S_CH0B   (0x0u)                      /*!< CH0B */
#define ATIM3_M1_MSCR_IB0S_TS_SEL (ATIM3_MODE1_MSCR_IB0S_Msk) /*!< 内部触发TS选择信号 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_PWC_Input_Filter 滤波时钟配置
 * @{
 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_NONE          (0x0u)                                      /*!< 无滤波 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV1_2 (0x1u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 2个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV1_4 (0x2u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 4个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV1_6 (0x3u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 6个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV4_4 (0x4u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/4 4个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV4_5 (0x5u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/4 6个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV8_4 (0x6u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/8 4个连续有效 */
#define ATIM3_M1_FLTR_FLTA0_B0_ET_3_PCLK_DIV8_6 (0x7u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/8 6个连续有效 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_PWC_ET_Polarity  ETR 输入相位选择
 * @{
 */
#define ATIM3_M1_FLTR_ETP_POLARITY_POSITIVE (0x0u)                     /*!< 同相位 */
#define ATIM3_M1_FLTR_ETP_POLARITY_NEGATIVE (ATIM3_MODE1_FLTR_ETP_Msk) /*!< 反相输入 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 mode23 配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32WorkMode;         /*!< 工作模式设置 @ref ATIM3_Mode23_Work_Mode */
    uint32_t u32CountDir;         /*!< 计数方向 @ref ATIM3_Mode23_DIR */
    uint32_t u32PRS;              /*!< 时钟预除频配置 @ref ATIM3_Mode23_PRS */
    uint32_t u32CountClockSelect; /*!< 计数时钟选择 @ref ATIM3_Mode23_Count_Clock */
    uint32_t u32PWMTypeSelect;    /*!< PWM模式选择（独立/互补） @ref ATIM3_Mode23_PWM_Type */
    uint32_t u32PWM2sSelect;      /*!< OCREFA双点比较功能选择 @ref ATIM3_Mode23_OCREFA_Compare_Type */
    uint32_t u32ShotMode;         /*!< 单次触发模式使能/禁止 @ref ATIM3_Mode23_Shot_Mode */
    uint32_t u32URSSelect;        /*!< 更新源选择 @ref ATIM3_Mode23_Refresh_Source */
} stc_atim3_mode23_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Work_Mode 工作模式
 * @{
 */
#define ATIM3_M23_M23CR_WORK_MODE_SAWTOOTH   (0x2u << ATIM3_MODE23_M23CR_MODE_Pos) /*!< 锯齿波模式(模式2) */
#define ATIM3_M23_M23CR_WORK_MODE_TRIANGULAR (0x3u << ATIM3_MODE23_M23CR_MODE_Pos) /*!< 三角波模式(模式3) */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_PRS 预除频配置
 * @{
 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS1   (0x0u)                               /*!< PCLK */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS2   (0x1u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/2 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS4   (0x2u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/4 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS8   (0x3u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/8 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS16  (0x4u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/16 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS32  (0x5u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/32 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS64  (0x6u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/64 */
#define ATIM3_M23_M23CR_ATIM3CLK_PRS256 (0x7u << ATIM3_MODE23_M23CR_PRS_Pos) /*!< PCLK/256 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_DIR 计数方向
 * @{
 */
#define ATIM3_M23_M23CR_DIR_UP_CNT   (0x0u)                       /*!< 向上计数 */
#define ATIM3_M23_M23CR_DIR_DOWN_CNT (ATIM3_MODE23_M23CR_DIR_Msk) /*!< 向下计数 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Count_Clock 计数时钟选择
 * @{
 */
#define ATIM3_M23_M23CR_CT_PCLK (0x0u)                      /*!< 内部计数时钟PCLK */
#define ATIM3_M23_M23CR_CT_ETR  (ATIM3_MODE23_M23CR_CT_Msk) /*!< 外部输入计数时钟ETR */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_PWM_Type PWM模式选择（独立/互补）
 * @{
 */
#define ATIM3_M23_M23CR_COMP_PWM_INDEPT (0x0u)                        /*!< 独立PWM */
#define ATIM3_M23_M23CR_COMP_PWM_COMP   (ATIM3_MODE23_M23CR_COMP_Msk) /*!< 互补PWM */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_OCREFA_Compare_Type OCREFA双点比较功能选择
 * @{
 */
#define ATIM3_M23_M23CR_PWM2S_COMPARE_DOUBLE_POINT (0x0u)                         /*!< 双点比较 */
#define ATIM3_M23_M23CR_PWM2S_COMPARE_SINGLE_POINT (ATIM3_MODE23_M23CR_PWM2S_Msk) /*!< 单点比较 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Shot_Mode 单次触发模式使能/禁止
 * @{
 */
#define ATIM3_M23_M23CR_SHOT_CYCLE (0x0u)                           /*!< 循环计数 */
#define ATIM3_M23_M23CR_SHOT_ONE   (ATIM3_MODE23_M23CR_ONESHOT_Msk) /*!< 单次，发送事件更新后定时器停止 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Refresh_Source 更新源选择
 * @{
 */
#define ATIM3_M23_M23CR_URS_OV_UND_UG_RST (0x0u)                       /*!< 上溢出/下溢出/软件更新UG/从模式复位 */
#define ATIM3_M23_M23CR_URS_OV_UND        (ATIM3_MODE23_M23CR_URS_Msk) /*!< 上溢出/下溢出 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_CCRxx_Channel CCRxx channel number define
 * @{
 */
#define ATIM3_COMPARE_CAPTURE_CH0A (0x0u) /*!< ATIM3_CCR0A相对于ATIM3_CCR0A的偏移 */
#define ATIM3_COMPARE_CAPTURE_CH0B (0x1u) /*!< ATIM3_CCR0B相对于ATIM3_CCR0A的偏移 */
#define ATIM3_COMPARE_CAPTURE_CH1A (0x2u) /*!< ATIM3_CCR1A相对于ATIM3_CCR0A的偏移 */
#define ATIM3_COMPARE_CAPTURE_CH1B (0x3u) /*!< ATIM3_CCR1B相对于ATIM3_CCR0A的偏移 */
#define ATIM3_COMPARE_CAPTURE_CH2A (0x4u) /*!< ATIM3_CCR2A相对于ATIM3_CCR0A的偏移 */
#define ATIM3_COMPARE_CAPTURE_CH2B (0x5u) /*!< ATIM3_CCR2B相对于ATIM3_CCR0A的偏移 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 Gate配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32GateFuncSelect; /*!< Gate比较、捕获功能选择 @ref ATIM3_Mode23_Gate_Func */
    uint32_t u32GateRiseCap;    /*!< GATE作为捕获功能时，上沿捕获有效控制 @ref ATIM3_Mode23_Gate_Func_Rising_Enable */
    uint32_t u32GateFallCap;    /*!< GATE作为捕获功能时，下沿捕获有效控制 @ref ATIM3_Mode23_Gate_Func_Falling_Enable */
} stc_atim3_m23_gate_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Gate_Func Gate比较、捕获功能选择
 * @{
 */
#define ATIM3_M23_M23CR_GATE_FUN_COMPARE (0x0u)                       /*!< 比较模式 */
#define ATIM3_M23_M23CR_GATE_FUN_CAPTURE (ATIM3_MODE23_M23CR_CSG_Msk) /*!< 捕获模式 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Gate_Func_Rising_Enable GATE作为捕获功能时，上沿捕获有效控制
 * @{
 */
#define ATIM3_M23_M23CR_GATE_CAP_RISE_DISABLE (0x0u)                       /*!< 上沿捕获无效 */
#define ATIM3_M23_M23CR_GATE_CAP_RISE_ENABLE  (ATIM3_MODE23_M23CR_CRG_Msk) /*!< 上沿捕获有效 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Gate_Func_Falling_Enable GATE作为捕获功能时，下沿捕获有效控制
 * @{
 */
#define ATIM3_M23_M23CR_GATE_CAP_FALL_DISABLE (0x0u)                       /*!< 下沿捕获无效 */
#define ATIM3_M23_M23CR_GATE_CAP_FALL_ENABLE  (ATIM3_MODE23_M23CR_CFG_Msk) /*!< 下沿捕获有效 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 主从触发 配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32MasterSlaveSelect; /*!< 主从模式选择 @ref ATIM3_Mode23_Master_Slaver */
    uint32_t u32MasterSrc;         /*!< 主模式触发源选择 @ref ATIM3_Mode23_Master_Source */
    uint32_t u32SlaveModeSelect;   /*!< 从模式选择 @ref ATIM3_Mode23_Slave_Func */
    uint32_t u32TsSelect;          /*!< 触发输入源选择 @ref ATIM3_Mode23_Trigger_Source */
} stc_atim3_m23_master_slave_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Master_Slaver 主从模式选择
 * @{
 */
#define ATIM3_M23_MSCR_MSM_SLAVE  (0x0u)                      /*!< 从模式 */
#define ATIM3_M23_MSCR_MSM_MASTER (ATIM3_MODE23_MSCR_MSM_Msk) /*!< 主模式 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Master_Source 主模式触发源选择
 * @{
 */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_UG      (0x0u)                              /*!< 软件更新UG，写CR.UG */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_CTEN    (0x1u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器使能CTEN */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_UEV     (0x2u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器事件更新UEV */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_CMPSO   (0x3u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 比较匹配选择输出CMPSO */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_OCREF0A (0x4u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器比较参数输出OCREF0A */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_OCREF1A (0x5u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器比较参数输出OCREF1A */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_OCREF2A (0x6u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器比较参数输出OCREF2A */
#define ATIM3_M23_MSCR_MMS_TRIG_SOURCE_OCREF0B (0x7u << ATIM3_MODE23_MSCR_MMS_Pos) /*!< 定时器比较参数输出OCREF0B */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Slave_Func 从模式选择
 * @{
 */
#define ATIM3_M23_MSCR_SMS_INTERNAL_CLK  (0x0u)                              /*!< 使用内部时钟 */
#define ATIM3_M23_MSCR_SMS_RESET         (0x1u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 复位功能 */
#define ATIM3_M23_MSCR_SMS_TRIG          (0x2u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 触发模式 */
#define ATIM3_M23_MSCR_SMS_EXTERNAL_CLK  (0x3u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 外部时钟模式 */
#define ATIM3_M23_MSCR_SMS_QUADRATURE_M1 (0x4u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 正交编码计数模式1 */
#define ATIM3_M23_MSCR_SMS_QUADRATURE_M2 (0x5u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 正交编码计数模式2 */
#define ATIM3_M23_MSCR_SMS_QUADRATURE_M3 (0x6u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 正交编码计数模式3 */
#define ATIM3_M23_MSCR_SMS_GATE          (0x7u << ATIM3_MODE23_MSCR_SMS_Pos) /*!< 门控功能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Trigger_Source 触发输入源选择
 * @{
 */
#define ATIM3_M23_MSCR_TS_ETFP      (0x0u)                             /*!< 端口ETR的滤波相位选择后的信号ETFP */
#define ATIM3_M23_MSCR_TS_ITR0      (0x1u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 内部互联信号 ITR0 */
#define ATIM3_M23_MSCR_TS_ITR1      (0x2u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 内部互联信号 ITR1 */
#define ATIM3_M23_MSCR_TS_ITR2      (0x3u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 内部互联信号 ITR2 */
#define ATIM3_M23_MSCR_TS_ITR3      (0x4u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 内部互联信号 ITR3 */
#define ATIM3_M23_MSCR_TS_CH0A_EDGE (0x5u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 端口CH0A的边沿信号 */
#define ATIM3_M23_MSCR_TS_IAFP      (0x6u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 端口CH0A的滤波相位选择后的信号IAFP */
#define ATIM3_M23_MSCR_TS_IBFP      (0x7u << ATIM3_MODE23_MSCR_TS_Pos) /*!< 端口CH0B的滤波相位选择后的信号IBFP */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_IA0_IN_Sel IA0 输入选择
 * @{
 */
#define ATIM3_M23_MSCR_IA0_CH0A       (0x0u)                       /*!< IA0选择CH0A */
#define ATIM3_M23_MSCR_IA0_CH012A_XOR (ATIM3_MODE23_MSCR_IA0S_Msk) /*!< CH0A,CH1A,CH2A的XOR的值 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_IB0_IN_Sel IB0 输入选择
 * @{
 */
#define ATIM3_M23_MSCR_IB0_CH0B      (0x0u)                       /*!<IB0选择CH0B */
#define ATIM3_M23_MSCR_IB0_TS_SOURCE (ATIM3_MODE23_MSCR_IB0S_Msk) /*!<IB0选择TS的源 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 CHxA通道比较、输出控制 配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32CHxCompareCap;       /*!< CHxA/CHxB比较/捕获功能选择 @ref ATIM3_Mode23_CH_Mode */
    uint32_t u32CHxCompareModeCtrl;  /*!< CHxA/CHxB通道比较控制 @ref ATIM3_Mode23_PWM_Comp_Mode */
    uint32_t u32CHxPolarity;         /*!< CHxA/CHxB输出极性控制 @ref ATIM3_Mode23_PWM_Polarity */
    uint32_t u32CHxCompareBufEn;     /*!< 比较A/B缓存功能 使能/禁止 @ref ATIM3_Mode23_CH_Buf_Enable */
    uint32_t u32CHxCompareIntSelect; /*!< CHxA/CHxB比较匹配中断选择 @ref ATIM3_Mode23_CHxA/B_Match_INT */
} stc_atim3_m23_compare_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_CH_Sel 通道序号
 * @{
 */
#define ATIM3_M23_OUTPUT_CHANNEL_CH0 (0x0u)
#define ATIM3_M23_OUTPUT_CHANNEL_CH1 (0x1u)
#define ATIM3_M23_OUTPUT_CHANNEL_CH2 (0x2u)
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_CH_Mode CHxA/CHxB比较/捕获功能选择
 * @{
 */
#define ATIM3_M23_CRCHx_CSA_CSB_COMPARE (0x0u)                       /*!< 比较模式 */
#define ATIM3_M23_CRCHx_CSA_CSB_CAPTURE (ATIM3_MODE23_CRCH0_CSA_Msk) /*!< 捕获模式 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_CH_Buf_Enable 比较A/B缓存功能 使能/禁止
 * @{
 */
#define ATIM3_M23_CRCHx_BUFEx_DISABLE (0x0u)                         /*!< 禁止 */
#define ATIM3_M23_CRCHx_BUFEx_ENABLE  (ATIM3_MODE23_CRCH0_BUFEA_Msk) /*!< 使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_CHxA/B_Match_INT CHxA/CHxB比较匹配中断选择
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_CHxA_Match_INT CHxA比较匹配中断选择
 * @{
 */
#define ATIM3_M23_M23CR_CISA_DISABLE_INT   (0x0u)                               /*!< 无匹配 */
#define ATIM3_M23_M23CR_CISA_RISE_INT      (0x1u << ATIM3_MODE23_M23CR_CIS_Pos) /*!< 上升沿匹配 */
#define ATIM3_M23_M23CR_CISA_FALL_INT      (0x2u << ATIM3_MODE23_M23CR_CIS_Pos) /*!< 下降沿匹配 */
#define ATIM3_M23_M23CR_CISA_RISE_FALL_INT (0x3u << ATIM3_MODE23_M23CR_CIS_Pos) /*!< 上升沿和下降沿匹配 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_CHxB_Match_INT CHxB比较匹配中断选择
 * @{
 */
#define ATIM3_M23_CRCHx_CISB_DISABLE_INT   (0x0u)                                /*!< 无匹配 */
#define ATIM3_M23_CRCHx_CISB_RISE_INT      (0x1u << ATIM3_MODE23_CRCH0_CISB_Pos) /*!< 上升沿匹配 */
#define ATIM3_M23_CRCHx_CISB_FALL_INT      (0x2u << ATIM3_MODE23_CRCH0_CISB_Pos) /*!< 下降沿匹配 */
#define ATIM3_M23_CRCHx_CISB_RISE_FALL_INT (0x3u << ATIM3_MODE23_CRCH0_CISB_Pos) /*!< 上升沿和下降沿匹配 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_PWM_Comp_Mode CHxA/CHxB通道比较控制
 * @{
 */
#define ATIM3_M23_FLTR_OCMxx_FORCE_LOW         (0x0u)                                      /*!< 强制为0低电平 */
#define ATIM3_M23_FLTR_OCMxx_FORCE_HIGH        (0x1u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< 强制为1高电平 */
#define ATIM3_M23_FLTR_OCMxx_COMP_FORCE_LOW    (0x2u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< 比较匹配时候强制为0低电平 */
#define ATIM3_M23_FLTR_OCMxx_COMP_FORCE_HIGH   (0x3u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< 比较匹配时候强制为1高电平 */
#define ATIM3_M23_FLTR_OCMxx_COMP_REVERSE      (0x4u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< 比较匹配时候翻转 */
#define ATIM3_M23_FLTR_OCMxx_COMP_ONE_PRD_HIGH (0x5u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< 比较匹配时候输出一个计数周期的高电平 */
#define ATIM3_M23_FLTR_OCMxx_PWM_MODE_1        (0x6u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PWM模式1 */
#define ATIM3_M23_FLTR_OCMxx_PWM_MODE_2        (0x7u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PWM模式2 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_PWM_Polarity CHxA/CHxB输出极性控制
 * @{
 */
#define ATIM3_M23_FLTR_CCPxx_NORMAL_IN_OUT  (0x0u)                        /*!< 正常输出 */
#define ATIM3_M23_FLTR_CCPxx_REVERSE_IN_OUT (ATIM3_MODE23_FLTR_CCPA0_Msk) /*!< 反向输出 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 CHA/CHB通道捕获、输入控制 配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32CHxCompareCap;    /*!< CHxA/CHxB比较/捕获功能选择 @ref ATIM3_Mode23_CH_Mode */
    uint32_t u32CHxCaptureSelect; /*!< CHxA/CHxB捕获边沿选择 @ref ATIM3_Mode23_Capture_Edge */
    uint32_t u32CHxInFlt;         /*!< CHxA/CHxB通道捕获滤波控制 @ref ATIM3_Mode23_Filter */
    uint32_t u32CHxPolarity;      /*!< CHxA/CHxB输入相位 @ref ATIM3_Mode23_PWM_Polarity */
} stc_atim3_m23_input_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Capture_Edge CRA_CFA(BKSA)& CRB_CFB(BKSB) CHxA/CHxB捕获边沿选择
 * @{
 */
#define ATIM3_M23_CRCHx_CRxCFx_CAPTURE_EDGE_DISABLE   (0x0u)                                        /*!< 禁止上升沿或下降沿捕获 */
#define ATIM3_M23_CRCHx_CRxCFx_CAPTURE_EDGE_RISE      (0x1u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 上升沿捕获使能  */
#define ATIM3_M23_CRCHx_CRxCFx_CAPTURE_EDGE_FALL      (0x2u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 下降沿捕获使能  */
#define ATIM3_M23_CRCHx_CRxCFx_CAPTURE_EDGE_RISE_FALL (0x3u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 上升沿和下降沿捕获使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Filter FLTAx/FLTBx/FLTET CHxB通道捕获滤波控制
 * @{
 */
#define ATIM3_M23_FLTR_FLTxx_NONE              (0x0u)                                      /*!< 无滤波 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV1_2 (0x1u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 2个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV1_4 (0x2u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 4个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV1_6 (0x3u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK 6个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV4_4 (0x4u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/4 4个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV4_5 (0x5u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/4 6个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV8_4 (0x6u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/8 4个连续有效 */
#define ATIM3_M23_FLTR_FLTxx_THREE_PCLK_DIV8_6 (0x7u << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos) /*!< PCLK/8 6个连续有效 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 ETR输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32ETRPolarity; /*!< ETR输入极性设置 @ref ATIM3_Mode23_Input_Polarity */
    uint32_t u32ETRFlt;      /*!< ETR滤波设置     @ref ATIM3_Mode23_Filter         */
} stc_atim3_m23_etr_input_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Input_Polarity ETR输入极性设置
 * @{
 */
#define ATIM3_M23_FLTR_ETP_NORMAL_IN  (0x0u)                      /*!< 正常输入 */
#define ATIM3_M23_FLTR_ETP_REVERSE_IN (ATIM3_MODE23_FLTR_ETP_Msk) /*!< 反向输入 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief ATIM3 刹车BK输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32EnBrake;       /*!< 刹车使能 @ref ATIM3_Mode23_Brake_Enable */
    uint32_t u32EnVCBrake;     /*!< 使能VC刹车 @ref ATIM3_Mode23_Brake_VC_Enable */
    uint32_t u32EnSafetyBk;    /*!< 使能safety刹车 @ref ATIM3_Mode23_Brake_Safe_Enable */
    uint32_t u32BrakePolarity; /*!< 刹车BK输入极性设置 @ref ATIM3_Mode23_Brake_Polarity */
    uint32_t u32BrakeFlt;      /*!< 刹车BK滤波设置 @ref ATIM3_Mode23_Filter */
} stc_atim3_m23_bk_input_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_Brake_Enable 刹车使能
 * @{
 */
#define ATIM3_M23_DTR_BKE_BRAKE_DISABLE (0x0u)                     /*!< 禁止 */
#define ATIM3_M23_DTR_BKE_BRAKE_ENABLE  (ATIM3_MODE23_DTR_BKE_Msk) /*!< 使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Brake_VC_Enable 使能VC刹车
 * @{
 */
#define ATIM3_M23_DTR_VCE_BRAKE_DISABLE (0x0u)                     /*!< 禁止 */
#define ATIM3_M23_DTR_VCE_BRAKE_ENABLE  (ATIM3_MODE23_DTR_VCE_Msk) /*!< 使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Brake_Safe_Enable 使能safety刹车
 * @{
 */
#define ATIM3_M23_DTR_SAFEEN_BRAKE_DISABLE (0x0u)                        /*!< 禁止 */
#define ATIM3_M23_DTR_SAFEEN_BRAKE_ENABLE  (ATIM3_MODE23_DTR_SAFEEN_Msk) /*!< 使能 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Brake_Port_Out_Level 刹车发生时端口电平及状态
 * @{
 */
#define ATIM3_M23_CRCHx_BKSA_BKSB_PORT_OUTPUT_HIZ  (0x0u)                                        /*!< 高阻态 */
#define ATIM3_M23_CRCHx_BKSA_BKSB_PORT_OUTPUT_KEEP (0x1u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 保持，无影响 */
#define ATIM3_M23_CRCHx_BKSA_BKSB_PORT_OUTPUT_LOW  (0x2u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 强制输出低电平 */
#define ATIM3_M23_CRCHx_BKSA_BKSB_PORT_OUTPUT_HIGH (0x3u << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos) /*!< 强制输出高电平 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_Brake_Polarity 刹车BK输入极性设置
 * @{
 */
#define ATIM3_M23_FLTR_BKP_NORMAL_IN  (0x0u)                      /*!< 正相 */
#define ATIM3_M23_FLTR_BKP_REVERSE_IN (ATIM3_MODE23_FLTR_BKP_Msk) /*!< 反相 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief 死区功能配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t bEnDeadTime;      /*!< 死区使能设置，FALSE: 禁止, TRUE: 使能 */
    uint32_t  u32DeadTimeValue; /*!< 8 bit 死区时间设置 */
} stc_atim3_m23_dt_init_t;

/**
 * @brief 触发ADC配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t bEnTrigADC;        /*!< 触发ADC全局控制，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnUevTrigADC;     /*!< 事件更新触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH0ACmpTrigADC; /*!< CH0A比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH0BCmpTrigADC; /*!< CH0B比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH1ACmpTrigADC; /*!< CH0A比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH1BCmpTrigADC; /*!< CH0B比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH2ACmpTrigADC; /*!< CH0A比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
    boolean_t bEnCH2BCmpTrigADC; /*!< CH0B比较匹配触发ADC，FALSE: 禁止, TRUE: 使能 */
} stc_atim3_m23_adc_trig_init_t;

/**
 * @brief 重复计数功能配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t u32EnUnderFlowMask; /*!< 下溢使能屏蔽 @ref ATIM3_Mode23_UND_Repeat_Cnt */
    uint32_t u32EnOverFLowMask;  /*!< 上溢使能屏蔽 @ref ATIM3_Mode23_OVF_Repeat_Cnt */
    uint32_t u32RepeatCountNum;  /*!< 8 bit重复计数次数设置 */
} stc_atim3_m23_rcr_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_UND_Repeat_Cnt Under Flow Repeat Count setting
 * @{
 */
#define ATIM3_M23_RCR_UND_INT_EVT_CNT_ENABLE (0x0u)                     /*!< 下溢出计数使能，RCR计算下溢出 */
#define ATIM3_M23_RCR_UND_INT_EVT_CNT_MASK   (ATIM3_MODE23_RCR_UND_Msk) /*!< 下溢出计数屏蔽，RCR不计算下溢出 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_OVF_Repeat_Cnt Over Flow Repeat Count setting
 * @{
 */
#define ATIM3_M23_RCR_OVF_INT_EVT_CNT_ENABLE (0x0u)                    /*!< 上溢出不屏蔽，RCR计算上溢出 */
#define ATIM3_M23_RCR_OVF_INT_EVT_CNT_MASK   (ATIM3_MODE23_RCR_OV_Msk) /*!< 上溢出屏蔽，RCR不计算上溢出 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ATIM3_MODE23_Global_Types ATIM3 Mode23全局类型定义
 * @{
 */

/**
 * @brief OCREF清除功能 配置结构体定义(模式23)
 */
typedef struct
{
    uint32_t  u32OCRefClearSrcSelect; /*!< OCREF清除源选择 @ref ATIM3_Mode23_OCREF_Clear_Source */
    boolean_t bOCSourceClearEn;       /*!< 来自OCCS的OCREF_Clear源是否使能清除OCREF输出,FALSE: 禁止, TRUE: 使能 */
} stc_atim3_m23_ocref_clr_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_Mode23_OCREF_Clear_Source OCREF清除源选择
 * @{
 */
#define ATIM3_M23_M23CR_OCCS_VC  (0x0u)                        /*!< 来自VC输出的OCREF_Clear */
#define ATIM3_M23_M23CR_OCCS_ETR (ATIM3_MODE23_M23CR_OCCS_Msk) /*!< 来自ETR端口滤波相位选择后的OCREF_Clear */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Mode23_Global_Macros ATIM3 Mode23全局宏定义
 * @{
 */

/**
 * @defgroup ATIM3_INT_Status_Flags     ATIM3 Mode0/1/2/3 Interrupt Status Flags
 * @{
 */
#define ATIM3_FLAG_UI      (ATIM3_MODE23_IFR_UIF)  /*!< Mode0/1:溢出中断标志；Mode2/3:事件更新中断标志 */
#define ATIM3_FLAG_PWC_CA0 (ATIM3_MODE23_IFR_CA0F) /*!< Mode1:脉冲宽度测量中断标志；Mode2/3:通道CH0A 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CA1     (ATIM3_MODE23_IFR_CA1F) /*!< Mode2/3:通道CH1A 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CA2     (ATIM3_MODE23_IFR_CA2F) /*!< Mode2/3:通道CH2A 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CB0     (ATIM3_MODE23_IFR_CB0F) /*!< Mode2/3:通道CH0B 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CB1     (ATIM3_MODE23_IFR_CB1F) /*!< Mode2/3:通道CH1B 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CB2     (ATIM3_MODE23_IFR_CB2F) /*!< Mode2/3:通道CH2B 发生捕获/比较匹配标志 */
#define ATIM3_FLAG_CA0E    (ATIM3_MODE23_IFR_CA0E) /*!< Mode2/3:通道CH0A 捕获数据丢失标志 */
#define ATIM3_FLAG_CA1E    (ATIM3_MODE23_IFR_CA1E) /*!< Mode2/3:通道CH1A 捕获数据丢失标志 */
#define ATIM3_FLAG_CA2E    (ATIM3_MODE23_IFR_CA2E) /*!< Mode2/3:通道CH2A 捕获数据丢失标志 */
#define ATIM3_FLAG_CB0E    (ATIM3_MODE23_IFR_CB0E) /*!< Mode2/3:通道CH0B 捕获数据丢失标志 */
#define ATIM3_FLAG_CB1E    (ATIM3_MODE23_IFR_CB1E) /*!< Mode2/3:通道CH1B 捕获数据丢失标志 */
#define ATIM3_FLAG_CB2E    (ATIM3_MODE23_IFR_CB2E) /*!< Mode2/3:通道CH2B 捕获数据丢失标志 */
#define ATIM3_FLAG_BI      (ATIM3_MODE23_IFR_BIF)  /*!< Mode2/3:刹车中断标志 */
#define ATIM3_FLAG_TI      (ATIM3_MODE23_IFR_TIF)  /*!< Mode2/3:触发中断标志 */
#define ATIM3_FLAG_OV      (ATIM3_MODE23_IFR_OVF)  /*!< Mode2/3:上溢出中断标志 */
#define ATIM3_FLAG_UND     (ATIM3_MODE23_IFR_UNDF) /*!< Mode2/3:下溢出中断标志 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode1_INT_Request ATIM3 Mode1 Interrupt Request
 * @{
 */
#define ATIM3_M1_INT_UI  (0x00000001u) /*!< 模式1 溢出中断 */
#define ATIM3_M1_INT_CA0 (0x00000002u) /*!< 模式1 脉宽测量完成中断 */
/**
 * @}
 */

/**
 * @defgroup ATIM3_Mode23_INT_Request ATIM3 Mode23 Interrupt Request
 * @{
 */
#define INTERRUPT_M23CR_ID   (0x80000000u)
#define INTERRUPT_CRCH0_ID   (0x08000000u)
#define INTERRUPT_CRCH1_ID   (0x04000000u)
#define INTERRUPT_CRCH2_ID   (0x02000000u)

#define INTERRUPT_M23CR_MASK (0x30180400u)
#define INTERRUPT_CRCH0_MASK (0x00000300u)
#define INTERRUPT_CRCH1_MASK (0x000000C0u)
#define INTERRUPT_CRCH2_MASK (0x00000030u)

#define ATIM3_M23_INT_UI     (INTERRUPT_M23CR_ID | ATIM3_MODE23_M23CR_UIE)            /*!< 模式23 溢出中断 */
#define ATIM3_M23_INT_BI     (INTERRUPT_M23CR_ID | ATIM3_MODE23_M23CR_BIE)            /*!< 模式23 刹车中断 */
#define ATIM3_M23_INT_TI     (INTERRUPT_M23CR_ID | ATIM3_MODE23_M23CR_TIE)            /*!< 模式23 触发中断 */
#define ATIM3_M23_INT_OV     (INTERRUPT_M23CR_ID | ATIM3_MODE23_M23CR_OVE)            /*!< 模式23 上溢中断 */
#define ATIM3_M23_INT_UND    (INTERRUPT_M23CR_ID | ATIM3_MODE23_M23CR_UNDE)           /*!< 模式23 下溢中断 */
#define ATIM3_M23_INT_CA0    (INTERRUPT_CRCH0_ID | ATIM3_MODE23_CRCH0_CIEA)           /*!< 模式23 比较捕获CH0A中断 */
#define ATIM3_M23_INT_CB0    (INTERRUPT_CRCH0_ID | ATIM3_MODE23_CRCH0_CIEB)           /*!< 模式23 比较捕获CH0B中断 */
#define ATIM3_M23_INT_CA1    (INTERRUPT_CRCH1_ID | (ATIM3_MODE23_CRCH1_CIEA >> 0x2u)) /*!< 模式23 比较捕获CH1A中断 */
#define ATIM3_M23_INT_CB1    (INTERRUPT_CRCH1_ID | (ATIM3_MODE23_CRCH1_CIEB >> 0x2u)) /*!< 模式23 比较捕获CH1B中断 */
#define ATIM3_M23_INT_CA2    (INTERRUPT_CRCH2_ID | (ATIM3_MODE23_CRCH2_CIEA >> 0x4u)) /*!< 模式23 比较捕获CH2A中断 */
#define ATIM3_M23_INT_CB2    (INTERRUPT_CRCH2_ID | (ATIM3_MODE23_CRCH2_CIEB >> 0x4u)) /*!< 模式23 比较捕获CH2B中断 */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义 模式0初始化及相关功能操作
 * @{
 */
void ATIM3_Mode0_Init(stc_atim3_mode0_init_t *pstcCfg); /* timer配置及初始化 */

void ATIM3_Mode0_Run(void);  /* timer 启动 */
void ATIM3_Mode0_Stop(void); /* timer 停止 */

void     ATIM3_Mode0_ARRSet(uint32_t u16Data);   /* 重载值设置 */
uint32_t ATIM3_Mode0_ARRGet(void);               /* 重载值获取 */
void     ATIM3_Mode0_Cnt16Set(uint32_t u16Data); /* 16位计数值设置 */
uint32_t ATIM3_Mode0_Cnt16Get(void);             /* 16位计数值获取 */
void     ATIM3_Mode0_Cnt32Set(uint32_t u32Data); /* 32位计数值设置 */
uint32_t ATIM3_Mode0_Cnt32Get(void);             /* 32位计数值获取 */

void ATIM3_Mode0_OutputEnable(void);  /*!< 模式0端口输出使能 */
void ATIM3_Mode0_OutputDisable(void); /*!< 模式0端口输出禁止 */
void ATIM3_Mode0_TOGEnable(void);     /*!< 模式0翻转使能 */
void ATIM3_Mode0_TOGDisable(void);    /*!< 模式0翻转禁止 */
/**
 * @}
 */

/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义 模式1初始化及相关功能操作
 * @{
 */
void ATIM3_Mode1_Init(stc_atim3_mode1_init_t *pstcCfg);            /* timer配置及初始化 */
void ATIM3_Mode1_InputConfig(stc_atim3_pwc_input_init_t *pstcCfg); /* PWC 输入配置 */
void ATIM3_Mode1_PWCEdgeSelect(uint32_t u32DetectEdgeSel);         /* PWC测量边沿起始结束选择 */

void ATIM3_Mode1_Run(void);  /* timer 启动 */
void ATIM3_Mode1_Stop(void); /* timer 停止 */

void     ATIM3_Mode1_Cnt16Set(uint32_t u16Data); /* 16位计数值设置 */
uint32_t ATIM3_Mode1_Cnt16Get(void);             /* 16位计数值获取 */

uint32_t ATIM3_Mode1_PWCCapValueGet(void); /* 脉冲宽度测量结果数值获取 */
/**
 * @}
 */

/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义 模式23初始化及相关功能操作
 * @{
 */
void ATIM3_Mode23_Init(stc_atim3_mode23_init_t *pstcCfg); /* timer配置及初始化 */
void ATIM3_Mode23_Run(void);                              /* timer启动/停止 */
void ATIM3_Mode23_Stop(void);                             /* timer启动/停止 */

void ATIM3_Mode23_ManualPWMOutputEnable(void);  /* PWM 手动 输出使能*/
void ATIM3_Mode23_ManualPWMOutputDisable(void); /* PWM 手动 输出禁止 */
void ATIM3_Mode23_AutoPWMOutputEnable(void);    /* PWM 自动 输出使能 */
void ATIM3_Mode23_AutoPWMOutputDisable(void);   /* PWM 自动 输出禁止 */

void     ATIM3_Mode23_ARRBufferEnable(void);    /* 重载值(周期)缓存功能使能*/
void     ATIM3_Mode23_ARRBufferDisable(void);   /* 重载值(周期)缓存功能禁止 */
void     ATIM3_Mode23_ARRSet(uint16_t u16Data); /* 重载值(周期)设置/获取 */
uint32_t ATIM3_Mode23_GetARR(void);
void     ATIM3_Mode23_Cnt16Set(uint16_t u16Data); /* 16位计数值设置/获取 */
uint32_t ATIM3_Mode23_Cnt16Get(void);

void     ATIM3_Mode23_ChannelCompareValueSet(uint32_t u32Channel, uint16_t u16Data); /* 比较捕获寄存器CCRxA/CCRxB/CCR3设置 */
uint32_t ATIM3_Mode23_ChannelCaptureValueGet(uint32_t u32Channel);                   /* 比较捕获寄存器CCRxA/CCRxB/CCR3读取 */
void     ATIM3_Mode23_GateFuncSel(stc_atim3_m23_gate_init_t *pstcCfg);               /* PWM互补输出模式下，GATE功能选择 */

void ATIM3_Mode23_MasterSlaveTrigSet(stc_atim3_m23_master_slave_init_t *pstcCfg); /* 主从触发配置 */
void ATIM3_Mode23_MSCRIA0Sel(uint32_t u32Ia0Sel);                                 /* 主从触发配置 */
void ATIM3_Mode23_MSCRIB0Sel(uint32_t u32Ib0Sel);                                 /* 主从触发配置 */

void ATIM3_Mode23_PortOutputCHxAConfig(uint32_t u32Channel, stc_atim3_m23_compare_init_t *pstcCfg); /* CHxA/CHxB比较输出通道控制 */
void ATIM3_Mode23_PortOutputCHxBConfig(uint32_t u32Channel, stc_atim3_m23_compare_init_t *pstcCfg); /* CHxA/CHxB比较输出通道控制 */
void ATIM3_Mode23_PortInputCHxAConfig(uint32_t u32Channel, stc_atim3_m23_input_init_t *pstcCfg);    /* CH0A/CH0B输入控制 */
void ATIM3_Mode23_PortInputCHxBConfig(uint32_t u32Channel, stc_atim3_m23_input_init_t *pstcCfg);    /* CH0A/CH0B输入控制 */

void ATIM3_Mode23_ETRInputConfig(stc_atim3_m23_etr_input_init_t *pstcCfg);                                    /* ERT输入控制 */
void ATIM3_Mode23_BrakeInputConfig(stc_atim3_m23_bk_input_init_t *pstcBkCfg);                                 /* 刹车BK输入控制 */
void ATIM3_Mode23_BrakePortStatusConfig(uint32_t u32Channel, uint32_t u32ChxaStatus, uint32_t u32ChxbStatus); /* 刹车BK输入控制 */
void ATIM3_Mode23_DTConfig(stc_atim3_m23_dt_init_t *pstcCfg);                                                 /* 死区功能 */
void ATIM3_Mode23_TrigADCConfig(stc_atim3_m23_adc_trig_init_t *pstcCfg);                                      /* 触发ADC控制 */
void ATIM3_Mode23_SetRepeatPeriod(stc_atim3_m23_rcr_init_t *pstcCfg);                                         /* 重复周期设置 */
void ATIM3_Mode23_OCRefClr(stc_atim3_m23_ocref_clr_init_t *pstcCfg);                                          /* OCREF清除功能 */

void ATIM3_Mode23_EnableCH0ASwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */
void ATIM3_Mode23_EnableCH0BSwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */
void ATIM3_Mode23_EnableCH1ASwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */
void ATIM3_Mode23_EnableCH1BSwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */
void ATIM3_Mode23_EnableCH2ASwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */
void ATIM3_Mode23_EnableCH2BSwTrigCaptureCompare(void); /* CHxA/CHxB捕获比较软件触发 */

void ATIM3_Mode23_EnableSoftwareUev(void);   /* 软件更新使能 */
void ATIM3_Mode23_EnableSoftwareTrig(void);  /* 软件触发使能 */
void ATIM3_Mode23_EnableSoftwareBrake(void); /* 软件刹车使能 */
/**
 * @}
 */

/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义 中断函数相关
 * @{
 */
boolean_t ATIM3_IntFlagGet(uint32_t u32InterruptFlagTypes);    /* 中断标志获取 */
void      ATIM3_IntFlagClear(uint32_t u32InterruptFlagTypes);  /* 中断标志清除 */
void      ATIM3_IntFlagClearAll(void);                         /* 所有中断标志清除 */
void      ATIM3_Mode0_IntEnable(void);                         /* 模式0中断使能 */
void      ATIM3_Mode0_IntDisable(void);                        /* 模式0中断禁止 */
void      ATIM3_Mode1_IntEnable(uint32_t u32InterruptTypes);   /* 模式1中断使能 */
void      ATIM3_Mode1_IntDisable(uint32_t u32InterruptTypes);  /* 模式1中断禁止 */
void      ATIM3_Mode23_IntEnable(uint32_t u32InterruptTypes);  /* 模式23中断使能 */
void      ATIM3_Mode23_IntDisable(uint32_t u32InterruptTypes); /* 模式23中断禁止 */
/**
 * @}
 */

/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义 结构体初始化函数相关
 * @{
 */
void ATIM3_Mode0_StcInit(stc_atim3_mode0_init_t *pstcInit);   /* 模式0结构体初始化 */
void ATIM3_Mode1_StcInit(stc_atim3_mode1_init_t *pstcInit);   /* 模式1结构体初始化 */
void ATIM3_Mode23_StcInit(stc_atim3_mode23_init_t *pstcInit); /* 模式23结构体初始化 */

void ATIM3_Mode1_InputStcInit(stc_atim3_pwc_input_init_t *pstcCfg);               /*模式1PWC输入配置初始化 */
void ATIM3_Mode23_MasterSlaveStcInit(stc_atim3_m23_master_slave_init_t *pstcCfg); /*模式23 主从触发配置初始化*/
void ATIM3_Mode23_CompareStcInit(stc_atim3_m23_compare_init_t *pstcCfg);          /*模式23 通道0/1/2 CHxB输出设置初始化*/
void ATIM3_Mode23_DTStcInit(stc_atim3_m23_dt_init_t *pstcCfg);                    /*模式23 死区功能初始化*/
void ATIM3_Mode23_ADCTrigStcInit(stc_atim3_m23_adc_trig_init_t *pstcCfg);         /*模式23 触发ADC控制初始化*/
void ATIM3_Mode23_InputStcInit(stc_atim3_m23_input_init_t *pstcCfg);              /*模式23 通道0/1/2 CHxA输入设置初始化*/
void ATIM3_Mode23_BKInputStcInit(stc_atim3_m23_bk_input_init_t *pstcCfg);         /*模式23 刹车BK输入控制初始化*/
void ATIM3_Mode23_RCRStcInit(stc_atim3_m23_rcr_init_t *pstcCfg);                  /*模式23 重复周期设置初始化*/

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

#endif /* __ATIM3_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
