/**
 *******************************************************************************
 * @file  interrupts_hc32l021.h
 * @brief This file contains all the functions prototypes of the interrupt driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-30       MADS            First version
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

#ifndef __INTERRUPTS_HC32L021_H__
#define __INTERRUPTS_HC32L021_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_INT INT模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup INT_Global_Types INT全局类型定义
 * @{
 */
/**
 * @brief 中断优先级数据类型定义
 */
typedef enum
{
    IrqPriorityLevel0 = 0x0u, /*!< 优先级0*/
    IrqPriorityLevel1 = 0x1u, /*!< 优先级1*/
    IrqPriorityLevel2 = 0x2u, /*!< 优先级2*/
    IrqPriorityLevel3 = 0x3u, /*!< 优先级3*/
} en_irq_priority_level_t;
/**
 * @}
 */

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
 * @addtogroup INT_Global_Functions INT全局函数定义
 * @{
 */
void EnableNvic(IRQn_Type enIrq, en_irq_priority_level_t enLevel, boolean_t bEn); /* 中断使能 */
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

#endif /* __INTERRUPTS_HC32L021_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
