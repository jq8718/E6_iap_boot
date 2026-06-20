/**
 *******************************************************************************
 * @file  ctrim.h
 * @brief This file contains all the functions prototypes of the CTRIM driver
 *        library
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

#ifndef __CTRIM_H__
#define __CTRIM_H__

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
 * @addtogroup DDL_CTRIM CTRIM模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Types CTRIM全局类型定义
 * @{
 */

/**
 * @brief  CTRIM 自动校准 配置结构体定义
 */
typedef struct
{
    uint32_t u32Mode;            /*!< 校准模式  @ref CTRIM_Mode_Select */
    uint32_t u32AccurateClock;   /*!< 精确时钟源选择  @ref CTRIM_Accurate_clock_Select */
    uint32_t u32RefClockDiv;     /*!< 参考时钟分频  @ref CTRIM_REF_Clock_Div_Select */
    uint32_t u32OneShot;         /*!< 校准模式，实时校准或单次校准  @ref CTRIM_One_Shot_Select */
    uint32_t u32InitStep;        /*!< TRIM初始步进量  @ref CTRIM_Init_Step_Select */
    uint32_t u32ExternFilter;    /*!< 外部输入管脚滤波配置  @ref CTRIM_ETR_Clock_Filter_Select */
    uint16_t u16ReloadValue;     /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
    uint16_t u16CountErrorLimit; /*!< 误差允许值  取值范围 0x0 ~ 0xFFF */
} stc_ctrim_calib_init_t;

/**
 * @brief  CTRIM 定时器 配置结构体定义
 */
typedef struct
{
    uint32_t u32Clock;        /*!< 时钟源选择  @ref CTRIM_Accurate_clock_Select */
    uint32_t u32ClockDiv;     /*!< 时钟分频  @ref CTRIM_REF_Clock_Div_Select */
    uint32_t u32ExternFilter; /*!< 外部输入管脚滤波配置  @ref CTRIM_ETR_Clock_Filter_Select */
    uint32_t u16ReloadValue;  /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
} stc_ctrim_timer_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Macros CTRIM全局宏定义
 * @{
 */

/**
 * @defgroup CTRIM_Mode_Select  工作模式选择
 * @{
 */
#define CTRIM_AUTO_CALIB_MD_RC48M (CTRIM_CR1_AUTO_Msk)                              /*!< RC48M校准模式，CR0.SRC需选择低速精准时钟 */
#define CTRIM_AUTO_CALIB_MD_RCL   ((0x1u << CTRIM_CR1_MD_Pos) | CTRIM_CR1_AUTO_Msk) /*!< RCL校准模式，CR0.SRC需选择高速精准时钟 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_Accurate_clock_Select  精确时钟源选择
 * @{
 */
#define CTRIM_ACCURATE_CLOCK_ETR   (0x0u)                      /*!< ETR */
#define CTRIM_ACCURATE_CLOCK_XTL   (0x2u << CTRIM_CR0_SRC_Pos) /*!< XTL */
#define CTRIM_ACCURATE_CLOCK_PCLK  (0x3u << CTRIM_CR0_SRC_Pos) /*!< PCLK */
#define CTRIM_ACCURATE_CLOCK_RCL   (0x4u << CTRIM_CR0_SRC_Pos) /*!< RCL */
#define CTRIM_ACCURATE_CLOCK_RC48M (0x5u << CTRIM_CR0_SRC_Pos) /*!< RC48M */
/**
 * @}
 */

/**
 * @defgroup CTRIM_REF_Clock_Div_Select  参考时钟预分频配置
 * @{
 */
#define CTRIM_REF_CLOCK_DIV2     (0x1u << CTRIM_CR1_PRS_Pos) /*!< DIV2 */
#define CTRIM_REF_CLOCK_DIV4     (0x2u << CTRIM_CR1_PRS_Pos) /*!< DIV4 */
#define CTRIM_REF_CLOCK_DIV8     (0x3u << CTRIM_CR1_PRS_Pos) /*!< DIV8 */
#define CTRIM_REF_CLOCK_DIV16    (0x4u << CTRIM_CR1_PRS_Pos) /*!< DIV16 */
#define CTRIM_REF_CLOCK_DIV32    (0x5u << CTRIM_CR1_PRS_Pos) /*!< DIV32 */
#define CTRIM_REF_CLOCK_DIV64    (0x6u << CTRIM_CR1_PRS_Pos) /*!< DIV64 */
#define CTRIM_REF_CLOCK_DIV128   (0x7u << CTRIM_CR1_PRS_Pos) /*!< DIV128 */
#define CTRIM_REF_CLOCK_DIV256   (0x8u << CTRIM_CR1_PRS_Pos) /*!< DIV256 */
#define CTRIM_REF_CLOCK_DIV512   (0x9u << CTRIM_CR1_PRS_Pos) /*!< DIV512 */
#define CTRIM_REF_CLOCK_DIV1024  (0xAu << CTRIM_CR1_PRS_Pos) /*!< DIV1024 */
#define CTRIM_REF_CLOCK_DIV2048  (0xBu << CTRIM_CR1_PRS_Pos) /*!< DIV2048 */
#define CTRIM_REF_CLOCK_DIV4096  (0xCu << CTRIM_CR1_PRS_Pos) /*!< DIV4096 */
#define CTRIM_REF_CLOCK_DIV8192  (0xDu << CTRIM_CR1_PRS_Pos) /*!< DIV8192 */
#define CTRIM_REF_CLOCK_DIV16384 (0xEu << CTRIM_CR1_PRS_Pos) /*!< DIV16384 */
#define CTRIM_REF_CLOCK_DIV32768 (0xFu << CTRIM_CR1_PRS_Pos) /*!< DIV32768 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_One_Shot_Select  校准模式配置
 * @{
 */
#define CTRIM_ONE_SHOT_REPETITIVE (0x0u)              /*!< 实时校准模式 */
#define CTRIM_ONE_SHOT_SINGLE     (CTRIM_CR1_OST_Msk) /*!< 单次校准模式 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_Init_Step_Select  TRIM初始步进量选择
 * @{
 */
#define CTRIM_INIT_STEP_2    (0x1u << CTRIM_CR0_STEP_Pos) /*!< STEP_2 */
#define CTRIM_INIT_STEP_8    (0x2u << CTRIM_CR0_STEP_Pos) /*!< STEP_8 */
#define CTRIM_INIT_STEP_16   (0x0u)                       /*!< STEP_16 */
#define CTRIM_INIT_STEP_32   (0x3u << CTRIM_CR0_STEP_Pos) /*!< STEP_32 */
#define CTRIM_INIT_STEP_128  (0x4u << CTRIM_CR0_STEP_Pos) /*!< STEP_128 */
#define CTRIM_INIT_STEP_256  (0x5u << CTRIM_CR0_STEP_Pos) /*!< STEP_256 */
#define CTRIM_INIT_STEP_512  (0x6u << CTRIM_CR0_STEP_Pos) /*!< STEP_512 */
#define CTRIM_INIT_STEP_1024 (0x7u << CTRIM_CR0_STEP_Pos) /*!< STEP_1024 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_ETR_Clock_Filter_Select  外部管脚输入时钟滤波配置
 * @{
 */
#define CTRIM_ETR_CLK_FLT_NONE          (0x0u)                         /*!< NONE */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC2 (0x1u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV1CYC2 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC4 (0x2u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV1CYC4 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC6 (0x3u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV1CYC6 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV4CYC4 (0x4u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV4CYC4 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV4CYC6 (0x5u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV4CYC6 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV8CYC4 (0x6u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV8CYC4 */
#define CTRIM_ETR_CLK_FLT_PCLK_DIV8CYC6 (0x7u << CTRIM_CR0_ETRFLT_Pos) /*!< PCLK_DIV8CYC6 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_Int_Select  中断控制位使能选择
 * @{
 */
#define CTRIM_INT_UD   (CTRIM_IER_UD_Msk)   /*!< 误差计数器下溢 中断 */
#define CTRIM_INT_END  (CTRIM_IER_END_Msk)  /*!< 自动Trim结束 中断 */
#define CTRIM_INT_PS   (CTRIM_IER_PS_Msk)   /*!< 误差计数器完成(一次计数) 中断 */
#define CTRIM_INT_MISS (CTRIM_IER_MISS_Msk) /*!< 计数失败(在GCLK的一个周期内，误差计数器已计数到ARR) 中断 */
#define CTRIM_INT_OV   (CTRIM_IER_OV_Msk)   /*!< TrimCode溢出(TrimCode已调整到0或者0x1FF) 中断 */
#define CTRIM_INT_OK   (CTRIM_IER_OK_Msk)   /*!< 自动Trim结果在范围内 中断 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_Flag_Select  中断标志位选择
 * @{
 */
#define CTRIM_FLAG_UD   (CTRIM_ISR_UD_Msk)   /*!< 误差计数器下溢 标志 */
#define CTRIM_FLAG_END  (CTRIM_ISR_END_Msk)  /*!< 自动Trim结束 标志 */
#define CTRIM_FLAG_PS   (CTRIM_ISR_PS_Msk)   /*!< 误差计数器完成(一次计数) 标志 */
#define CTRIM_FLAG_MISS (CTRIM_ISR_MISS_Msk) /*!< 计数失败(在GCLK的一个周期内，误差计数器已计数到ARR) 标志 */
#define CTRIM_FLAG_OV   (CTRIM_ISR_OV_Msk)   /*!< TrimCode溢出(TrimCode已调整到0或者0x1FF) 标志 */
#define CTRIM_FLAG_OK   (CTRIM_ISR_OK_Msk)   /*!< Trim完成时精度满足FLIM要求 标志 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_ARR_Count_Dir  误差计数器计数方向
 * @{
 */
#define CTRIM_ARR_COUNT_DIR_INCREASE (0x0u)              /*!< 递增计数，RC48M输出频率高于目标频率，或RCL输出频率低于目标频率 */
#define CTRIM_ARR_COUNT_DIR_DECREASE (CTRIM_ISR_DIR_Msk) /*!< 递减计数，RC48M输出频率低于目标频率，或RCL输出频率高于目标频率 */
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
 * @addtogroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */
en_result_t CTRIM_CalibInit(stc_ctrim_calib_init_t *pstcInitConfig); /* CTRIM时钟校准初始化配置 */

en_result_t CTRIM_TimerInit(stc_ctrim_timer_init_t *pstcInitConfig); /* CTRIM时钟功能初始化配置 */

uint32_t CTRIM_CounterGet(void); /* CTRIM获取误差计数器计数值 */

void CTRIM_AutoReloadSet(uint32_t u32AutoReload); /* CTRIM设定自动装载寄存器的值 */

void CTRIM_InitStepSet(uint32_t u32TrimStep); /* CTRIM TRIM初始步进量配置 */

void CTRIM_ExternClockFilterSet(uint32_t u32ExternClockFilter); /* CTRIM 外部管脚输入时钟滤波配置 */

void CTRIM_AccurateClockSet(uint32_t u32ClockSrc); /* CTRIM精确时钟源选择 */

void CTRIM_ModeSet(uint32_t u32Mode); /* CTRIM工作模式配置 */

void CTRIM_RefClockDivSet(uint32_t u32RefClockDiv); /* CTRIM参考时钟预分频配置 */

void CTRIM_OneShotSet(uint32_t u32OneShotMode); /* CTRIM校准模式配置 */

uint32_t CTRIM_ARRCoutDirGet(void); /* CTRIM获取误差计数器计数方向 */
uint32_t CTRIM_TrimCodeGet(void);   /* CTRIM获取TrimCode值 */

uint32_t CTRIM_CountErrorCaptureGet(void);                 /* CTRIM获取计数误差捕获值 */
void     CTRIM_CountErrorLimitSet(uint16_t u16ErrorLimit); /* CTRIM设置误差允许值 */

void CTRIM_Enable(void);  /* CTRIM开启模块 */
void CTRIM_Disable(void); /* CTRIM禁止模块 */

void CTRIM_IntEnable(uint32_t u32Int);  /* CTRIM中断使能 */
void CTRIM_IntDisable(uint32_t u32Int); /* CTRIM中断禁止 */

boolean_t CTRIM_FlagGet(uint32_t u32Flag);   /* CTRIM获取状态标志 */
void      CTRIM_FlagClear(uint32_t u32Flag); /* CTRIM清除状态标志 */
void      CTRIM_FlagClearALL(void);          /* CTRIM清除所有标志*/

void CTRIM_CalibStcInit(stc_ctrim_calib_init_t *pstcInit); /* CTRIM校准结构体初始化 */
void CTRIM_TimerStcInit(stc_ctrim_timer_init_t *pstcInit); /* CTRIM定时器结构体初始化 */
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

#endif /* __CTRIM_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
