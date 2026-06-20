/**
 *******************************************************************************
 * @file  lvd.h
 * @brief This file contains all the functions prototypes of the LVD driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
   2025-09-12       MADS            Modify lvd source avcc to dvcc
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

#ifndef __LVD_H__
#define __LVD_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LVD LVD模块驱动库
 * @{
 */
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup LVD_Global_Types LVD全局类型定义
 * @{
 */

/**
 * @brief  LVD初始化配置结构体
 */
typedef struct
{
    uint32_t u32TriggerAction; /*!< 触发动作选择  @ref LVD_Trigger_Action_Select */
    uint32_t u32TriggerMode;   /*!< 触发模式选择  @ref LVD_Trigger_Mode_Select */
    uint32_t u32Src;           /*!< 监测源选择  @ref LVD_Source_Select */
    uint32_t u32ThresholdVolt; /*!< 阈值电压选择  @ref LVD_Threshold_Volt_Select */
    uint32_t u32FilterTime;    /*!< 数字滤波时间选择  @ref LVD_Filter_Time_Select */
    uint32_t u32FilterMode;    /*!< 滤波器模式选择 @ref LVD_Filter_Mode_Select*/
} stc_lvd_init_t;
/**
 * @}
 */
/******************************************************************************
 * Global definitions
 ******************************************************************************/
/**
 * @defgroup LVD_Global_Macros LVD全局宏定义
 * @{
 */

/** @defgroup LVD_Trigger_Action_Select 触发动作选择
 * @{
 */
#define LVD_TRIG_ACT_INT   (0x0u)           /*!< NVIC中断 */
#define LVD_TRIG_ACT_RESET (LVD_CR_ACT_Msk) /*!< 系统复位 */
/**
 * @}
 */

/**
 * @defgroup LVD_Trigger_Mode_Select 触发模式选择
 * @{
 */
#define LVD_TRIG_MD_NONE    (0x0u)            /*!< 无触发 */
#define LVD_TRIG_MD_FALLING (LVD_CR_FTEN_Msk) /*!< 下降沿触发 */
#define LVD_TRIG_MD_RISING  (LVD_CR_RTEN_Msk) /*!< 上升沿触发 */
#define LVD_TRIG_MD_HIGH    (LVD_CR_HTEN_Msk) /*!< 高电平触发 */
/**
 * @}
 */

/**
 * @defgroup LVD_Source_Select 输入监测源选择
 * @{
 */
#define LVD_SRC_DVCC (0x0u)                      /*!< DVCC电压 */
#define LVD_SRC_PA03 (0x1u << LVD_CR_SOURCE_Pos) /*!< PA03 */
#define LVD_SRC_PA10 (0x2u << LVD_CR_SOURCE_Pos) /*!< PA10 */
/**
 * @}
 */

/**
 * @defgroup LVD_Threshold_Volt_Select 阈值电压选择
 * @{
 */
#define LVD_THRESHOLD_VOLT1P8V (0x0u)                    /*!< 1.8V */
#define LVD_THRESHOLD_VOLT2P0V (0x1u << LVD_CR_VTDS_Pos) /*!< 2.0V */
#define LVD_THRESHOLD_VOLT2P2V (0x2u << LVD_CR_VTDS_Pos) /*!< 2.2V */
#define LVD_THRESHOLD_VOLT2P4V (0x3u << LVD_CR_VTDS_Pos) /*!< 2.4V */
#define LVD_THRESHOLD_VOLT2P6V (0x4u << LVD_CR_VTDS_Pos) /*!< 2.6V */
#define LVD_THRESHOLD_VOLT2P8V (0x5u << LVD_CR_VTDS_Pos) /*!< 2.8V */
#define LVD_THRESHOLD_VOLT3P0V (0x6u << LVD_CR_VTDS_Pos) /*!< 3.0V */
#define LVD_THRESHOLD_VOLT3P2V (0x7u << LVD_CR_VTDS_Pos) /*!< 3.2V */
#define LVD_THRESHOLD_VOLT3P4V (0x8u << LVD_CR_VTDS_Pos) /*!< 3.4V */
#define LVD_THRESHOLD_VOLT3P6V (0x9u << LVD_CR_VTDS_Pos) /*!< 3.6V */
#define LVD_THRESHOLD_VOLT3P8V (0xAu << LVD_CR_VTDS_Pos) /*!< 3.8V */
#define LVD_THRESHOLD_VOLT4P0V (0xBu << LVD_CR_VTDS_Pos) /*!< 4.0V */
#define LVD_THRESHOLD_VOLT4P2V (0xCu << LVD_CR_VTDS_Pos) /*!< 4.2V */
#define LVD_THRESHOLD_VOLT4P4V (0xDu << LVD_CR_VTDS_Pos) /*!< 4.4V */
#define LVD_THRESHOLD_VOLT4P6V (0xEu << LVD_CR_VTDS_Pos) /*!< 4.6V */
#define LVD_THRESHOLD_VOLT4P8V (0xFu << LVD_CR_VTDS_Pos) /*!< 4.8V */
/**
 * @}
 */

/**
 * @defgroup LVD_Filter_Time_Select 数字滤波时间选择
 * @{
 */
#define LVD_FILTER_TIME_NONE      (0x0u)                             /*!< 数字滤波无效 */
#define LVD_FILTER_TIME_2CYCLE    (0x1u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 2个滤波时钟周期 */
#define LVD_FILTER_TIME_4CYCLE    (0x2u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 4个滤波时钟周期 */
#define LVD_FILTER_TIME_8CYCLE    (0x3u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 8个滤波时钟周期 */
#define LVD_FILTER_TIME_16CYCLE   (0x4u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 16个滤波时钟周期 */
#define LVD_FILTER_TIME_32CYCLE   (0x5u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 32个滤波时钟周期 */
#define LVD_FILTER_TIME_64CYCLE   (0x6u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 64个滤波时钟周期 */
#define LVD_FILTER_TIME_128CYCLE  (0x7u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 128个滤波时钟周期 */
#define LVD_FILTER_TIME_256CYCLE  (0x8u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 256个滤波时钟周期 */
#define LVD_FILTER_TIME_512CYCLE  (0x9u << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 512个滤波时钟周期 */
#define LVD_FILTER_TIME_1024CYCLE (0xAu << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 1024个滤波时钟周期 */
#define LVD_FILTER_TIME_2048CYCLE (0xBu << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 2048个滤波时钟周期 */
#define LVD_FILTER_TIME_4096CYCLE (0xCu << LVD_CR_DEBOUNCE_TIME_Pos) /*!< 4096个滤波时钟周期 */
/**
 * @}
 */

/**
 * @defgroup LVD_Filter_Mode_Select 滤波器模式选择
 * @{
 */
#define LVD_FILTER_MD_NFM (0x0u)                        /*!< 普通滤波模式 Normal Filter Mode */
#define LVD_FILTER_MD_PFM (0x1u << LVD_CR_FLT_MODE_Pos) /*!< 滤峰模式 Peak Filter Mode */
#define LVD_FILTER_MD_VFM (0x2u << LVD_CR_FLT_MODE_Pos) /*!< 滤谷模式 Valley Filter Mode */
#define LVD_FILTER_MD_SFM (0x3u << LVD_CR_FLT_MODE_Pos) /*!< 滤刺模式 Spike Filter Mode */
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
 * @addtogroup LVD_Global_Functions LVD全局函数定义
 * @{
 */
en_result_t LVD_Init(stc_lvd_init_t *pstcLvdInit); /* LVD初始化 */
void        LVD_Enable(void);                      /* LVD模块使能 */
void        LVD_Disable(void);                     /* LVD模块禁止 */

void      LVD_TriggerActionConfig(uint32_t u32TriggerAction); /* LVD触发动作配置 */
void      LVD_TriggerModeConfig(uint32_t u32TriggerMode);     /* LVD触发模式配置 */
void      LVD_IntEnable(void);                                /* LVD中断使能 */
void      LVD_IntDisable(void);                               /* LVD中断禁止 */
boolean_t LVD_IntFlagGet(void);                               /* 获取LVD中断标志 */
void      LVD_IntFlagClear(void);                             /* 清除LVD中断标志 */

boolean_t LVD_FilterOutputGet(void); /* 获取滤波后的信号电平 */

void LVD_StcInit(stc_lvd_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __LVD_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
