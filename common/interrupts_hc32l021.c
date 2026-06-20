/**
 *******************************************************************************
 * @file  interrupts_hc32l021.c
 * @brief This file provides firmware functions to manage the interrupts.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "interrupts_hc32l021.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_INT INT模块驱动库
 * @brief INT Driver Library INT模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup INT_Global_Functions INT全局函数定义
 * @{
 */

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
 * @defgroup INT_Weak_Functions 中断弱定义函数
 * @{
 */
__WEAK void SysTick_IRQHandler(void)
{
    ;
}
__WEAK void PortA_IRQHandler(void)
{
    ;
}
__WEAK void PortB_IRQHandler(void)
{
    ;
}
__WEAK void Atim3_IRQHandler(void)
{
    ;
}
__WEAK void LpUart0_IRQHandler(void)
{
    ;
}
__WEAK void LpUart1_IRQHandler(void)
{
    ;
}
__WEAK void Spi_IRQHandler(void)
{
    ;
}
__WEAK void Ctim0_IRQHandler(void)
{
    ;
}
__WEAK void Ctim1_IRQHandler(void)
{
    ;
}
__WEAK void Hsi2c_IRQHandler(void)
{
    ;
}
__WEAK void Iwdt_IRQHandler(void)
{
    ;
}
__WEAK void Rtc_IRQHandler(void)
{
    ;
}
__WEAK void Adc_IRQHandler(void)
{
    ;
}
__WEAK void Vc0_IRQHandler(void)
{
    ;
}
__WEAK void Vc1_IRQHandler(void)
{
    ;
}
__WEAK void Lvd_IRQHandler(void)
{
    ;
}
__WEAK void Flash_IRQHandler(void)
{
    ;
}
__WEAK void Ctrim_Clkdet_IRQHandler(void)
{
    ;
}
/**
 * @}
 */

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
 * @brief  NVIC SysTick 中断处理函数
 * @retval None
 */
void SysTick_Handler(void)
{
    SysTick_IRQHandler();
}

/**
 * @brief  GPIO PortA 中断处理函数
 * @retval None
 */
void PORTA_IRQHandler(void)
{
    PortA_IRQHandler();
}

/**
 * @brief  GPIO PortB 中断处理函数
 * @retval None
 */
void PORTB_IRQHandler(void)
{
    PortB_IRQHandler();
}

/**
 * @brief  ATIM3 中断处理函数
 * @retval None
 */
void ATIM3_IRQHandler(void)
{
    Atim3_IRQHandler();
}

/**
 * @brief  LPUART0 低功耗串口0 中断处理函数
 * @retval None
 */
void LPUART0_IRQHandler(void)
{
    LpUart0_IRQHandler();
}

/**
 * @brief  LPUART1 低功耗串口1 中断处理函数
 * @retval None
 */
void LPUART1_IRQHandler(void)
{
    LpUart1_IRQHandler();
}

/**
 * @brief  SPI 中断处理函数
 * @retval None
 */
void SPI_IRQHandler(void)
{
    Spi_IRQHandler();
}

/**
 * @brief  CTIM0 中断处理函数
 * @retval None
 */
void CTIM0_IRQHandler(void)
{
    Ctim0_IRQHandler();
}

/**
 * @brief  CTIM1 中断处理函数
 * @retval None
 */
void CTIM1_IRQHandler(void)
{
    Ctim1_IRQHandler();
}

/**
 * @brief  HSI2C 中断处理函数
 * @retval None
 */
void HSI2C_IRQHandler(void)
{
    Hsi2c_IRQHandler();
}

/**
 * @brief  IWDT 中断处理函数
 * @retval None
 */
void IWDT_IRQHandler(void)
{
    Iwdt_IRQHandler();
}

/**
 * @brief  RTC 中断处理函数
 * @retval None
 */
void RTC_IRQHandler(void)
{
    Rtc_IRQHandler();
}

/**
 * @brief  ADC 中断处理函数
 * @retval None
 */
void ADC_IRQHandler(void)
{
    Adc_IRQHandler();
}

/**
 * @brief  VC0 中断处理函数
 * @retval None
 */
void VC0_IRQHandler(void)
{
    Vc0_IRQHandler();
}

/**
 * @brief  VC1 中断处理函数
 * @retval None
 */
void VC1_IRQHandler(void)
{
    Vc1_IRQHandler();
}

/**
 * @brief  LVD 中断处理函数
 * @retval None
 */
void LVD_IRQHandler(void)
{
    Lvd_IRQHandler();
}

/**
 * @brief  FLASH 中断处理函数
 * @retval None
 */
void FLASH_IRQHandler(void)
{
    Flash_IRQHandler();
}

/**
 * @brief  CTRIM、CLKDET中断处理函数
 * @retval None
 */
void CTRIM_CLKDET_IRQHandler(void)
{
    Ctrim_Clkdet_IRQHandler();
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
