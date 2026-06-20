/*******************************************************************************
 * @file  interrupts_hc32l021.c
 * @brief This file provides firmware functions to manage the interrupts.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-30       MADS            First version
   2026-06-20       Claude          Use vector-table names directly, remove wrappers
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

/**
 * @brief  NVIC hardware fault 中断处理函数
 * @retval None
 */
void HardFault_Handler(void)
{
    volatile int32_t a = 0;

    while (0 == a)
    {
        ;
    }
}

/**
 * @defgroup INT_Weak_Functions 中断弱定义函数
 * @{
 */
__WEAK void SysTick_Handler(void)
{
    ;
}

__WEAK void PORTA_IRQHandler(void)
{
    ;
}

__WEAK void PORTB_IRQHandler(void)
{
    ;
}

__WEAK void ATIM3_IRQHandler(void)
{
    ;
}

__WEAK void LPUART0_IRQHandler(void)
{
    ;
}

__WEAK void LPUART1_IRQHandler(void)
{
    ;
}

__WEAK void SPI_IRQHandler(void)
{
    ;
}

__WEAK void CTIM0_IRQHandler(void)
{
    ;
}

__WEAK void CTIM1_IRQHandler(void)
{
    ;
}

__WEAK void HSI2C_IRQHandler(void)
{
    ;
}

__WEAK void IWDT_IRQHandler(void)
{
    ;
}

__WEAK void RTC_IRQHandler(void)
{
    ;
}

__WEAK void ADC_IRQHandler(void)
{
    ;
}

__WEAK void VC0_IRQHandler(void)
{
    ;
}

__WEAK void VC1_IRQHandler(void)
{
    ;
}

__WEAK void LVD_IRQHandler(void)
{
    ;
}

__WEAK void FLASH_IRQHandler(void)
{
    ;
}

__WEAK void CTRIM_CLKDET_IRQHandler(void)
{
    ;
}
/**
 * @}
 */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
