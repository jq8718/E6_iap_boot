/**
 *******************************************************************************
 * @file  iwdt.h
 * @brief This file contains all the functions prototypes of the IWDT driver
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

#ifndef __IWDT_H__
#define __IWDT_H__

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
 * @addtogroup DDL_IWDT IWDT模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Types IWDT全局类型定义
 * @{
 */

/**
 * @brief  IWDT Init structure definition
 */
typedef struct
{
    uint32_t u32Action;     /*!< 看门狗休眠模式及溢出后动作配置 @ref IWDT_Over_Action */
    uint32_t u32Prescaler;  /*!< 看门狗计数时钟(RC10K)的分频 @ref IWDT_RC10K_Prescaler */
    uint32_t u32Window;     /*!< 看门狗窗口值配置,取值范围必须为：[0u ~ 0xFFFu] */
    uint32_t u32ArrCounter; /*!< 看门狗重载计数值配置,取值范围必须为：[0u ~ 0xFFFu] */
    /*!< u32Window < u32ArrCounter时, IWDT工作于窗口看门狗模式 */
    /*!< u32Window ≥ u32ArrCounter时, IWDT工作于独立看门狗模式 */
} stc_iwdt_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Macros IWDT全局宏定义
 * @{
 */

/**
 * @defgroup IWDT_Over_Action IWDT溢出中断/复位选择和SleepMode下运行/暂停选择
 * @{
 */
#define IWDT_OVER_RST_SLEEPMODE_RUN  (0x0u)                                        /*!< IWDT复位SleepMode运行 */
#define IWDT_OVER_RST_SLEEPMODE_STOP (IWDT_CR_PAUSE)                               /*!< IWDT复位SleepMode停止 */
#define IWDT_OVER_INT_SLEEPMODE_RUN  (IWDT_CR_ACTION | IWDT_CR_IE)                 /*!< IWDT中断SleepMode运行 */
#define IWDT_OVER_INT_SLEEPMODE_STOP (IWDT_CR_ACTION | IWDT_CR_IE | IWDT_CR_PAUSE) /*!< IWDT中断SleepMode停止 */
/**
 * @}
 */

/** @defgroup IWDT_RC10K_Prescaler IWDT分频选择
 * @{
 */
#define IWDT_RC10K_DIV_4   (0x0u)                    /*!< RC10K 4分频 */
#define IWDT_RC10K_DIV_8   (0x1u << IWDT_CR_PRS_Pos) /*!< RC10K 8分频 */
#define IWDT_RC10K_DIV_16  (0x2u << IWDT_CR_PRS_Pos) /*!< RC10K 16分频 */
#define IWDT_RC10K_DIV_32  (0x3u << IWDT_CR_PRS_Pos) /*!< RC10K 32分频 */
#define IWDT_RC10K_DIV_64  (0x4u << IWDT_CR_PRS_Pos) /*!< RC10K 64分频 */
#define IWDT_RC10K_DIV_128 (0x5u << IWDT_CR_PRS_Pos) /*!< RC10K 128分频 */
#define IWDT_RC10K_DIV_256 (0x6u << IWDT_CR_PRS_Pos) /*!< RC10K 256分频 */
#define IWDT_RC10K_DIV_512 (0x7u << IWDT_CR_PRS_Pos) /*!< RC10K 512分频 */
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
 * @addtogroup IWDT_Global_Functions IWDT全局函数定义
 * @{
 */
en_result_t IWDT_Init(stc_iwdt_init_t *pstcIwdtInit); /* IWDT初始化 */
void        IWDT_Start(void);                         /* IWDT启动运行 */
void        IWDT_Stop(void);                          /* IWDT停止运行 */
void        IWDT_Feed(void);                          /* IWDT喂狗 */

boolean_t IWDT_OverFlagGet(void);   /* 获取IWDT溢出状态标志 */
boolean_t IWDT_RunFlagGet(void);    /* 获取IWDT运行状态标志 */
void      IWDT_OverFlagClear(void); /* IWDT溢出标志位清零 */

void IWDT_StcInit(stc_iwdt_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __IWDT_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
