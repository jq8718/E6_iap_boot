/**
 *******************************************************************************
 * @file  system_hc32l021.h
 * @brief Header file for SYSTEM functions
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-12-09       MADS            First version
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

#ifndef __SYSTEM_HC32L021_H__
#define __SYSTEM_HC32L021_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_SYSTEM SYSTEM模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSTEM_Global_Macros SYSTEM全局宏定义
 * @{
 */
#define HWWD_DISABLE (1)

/**
 * @brief Clock Setup macro definition
 *        - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 *        - 1: CLOCK_SETTING_CMSIS -
 */
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup SYSTEM_Global_Variables SYSTEM全局变量定义
 * @{
 */
extern uint32_t SystemCoreClock; /* System Clock Frequency (Core Clock) */
/**
 * @}
 */
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SYSTEM_Global_Functions SYSTEM全局函数定义
 * @{
 */
extern void SystemInit(void);            /* Initialize the system */
extern void SystemCoreClockUpdate(void); /* Update SystemCoreClock variable */
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

#endif /* __SYSTEM_HC32L021 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
