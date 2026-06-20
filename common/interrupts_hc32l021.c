/*******************************************************************************
 * @file  interrupts_hc32l021.c
 * @brief This file provides firmware functions to manage the interrupts.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-30       MADS            First version
   2026-06-20       Claude          Use startup-supplied weak handlers
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "interrupts_hc32l021.h"

/*******************************************************************************
 * Global function definitions
 ******************************************************************************/
/**
 * @brief  NVIC 中断使能
 * @param  [in] enIrq 中断号枚举类型 @ref IRQn_Type
 * @param  [in] enLevel 中断优先级枚举类型 @ref en_irq_priority_level_t
 * @param  [in] bEn 中断开关 @ref boolean_t
 * @retval None
 */
void EnableNvic(IRQn_Type enIrq, en_irq_priority_level_t enLevel, boolean_t bEn)
{
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, enLevel);
    if (TRUE == bEn)
    {
        NVIC_EnableIRQ(enIrq);
    }
    else
    {
        NVIC_DisableIRQ(enIrq);
    }
}

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
