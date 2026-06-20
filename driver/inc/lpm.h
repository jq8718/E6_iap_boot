/**
 *******************************************************************************
 * @file  lpm.h
 * @brief This file contains all the functions prototypes of the
 *        LPM(Low Power Mode) driver library
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

#ifndef __LPM_H__
#define __LPM_H__

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
 * @addtogroup DDL_LPM LPM模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup LPM_Global_Functions LPM全局函数定义
 * @{
 */
void LPM_GotoSleep(boolean_t bOnExit);     /* 进入普通休眠模式 */
void LPM_GotoDeepSleep(boolean_t bOnExit); /* 进入深度休眠模式 */
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

#endif /* __LPM_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
