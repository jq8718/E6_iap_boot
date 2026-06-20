/**
 *******************************************************************************
 * @file  trng.h
 * @brief This file contains all the functions prototypes of the TRNG driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
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

#ifndef __TRNG_H__
#define __TRNG_H__

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
 * @addtogroup DDL_TRNG TRNG模块驱动库
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
 * @addtogroup TRNG_Global_Functions TRNG全局函数定义
 * @{
 */
en_result_t TRNG_Init(void);     /* 随机数初始化(上电第一次生成随机数） */
en_result_t TRNG_Generate(void); /* 生成随机数（非上电第一次生成随机数） */

uint32_t TRNG_Data0Get(void); /* 获取低32bits随机数（执行随机数初始化或生成随机数函数后可使用该函数获取随机数值） */
uint32_t TRNG_Data1Get(void); /* 获取高32bits随机数（执行随机数初始化或生成随机数函数后可使用该函数获取随机数值） */
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

#endif /* __TRNG_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
