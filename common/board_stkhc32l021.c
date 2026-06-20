/**
 *******************************************************************************
 * @file  board_stkhc32l021.c
 * @brief Source file for BSP functions.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-12-02       MADS            First version
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
#include "board_stkhc32l021.h"
#include "gpio.h"
#include "hc32l021.h"
#include "sysctrl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_STK STK模块驱动库
 * @brief STK Driver Library STK模块驱动库
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
 * @defgroup STK_Global_Functions STK全局函数定义
 * @brief STK Function Library STK功能函数库
 * @{
 */

/**
 * @brief  STK 按键初始化
 * @retval None
 */
void STK_UserKeyConfig(void)
{
    stc_gpio_init_t stcGpioInit = {0};

    GPIO_StcInit(&stcGpioInit);                 /* 结构体变量初始值初始化 */
    SYSCTRL_PeriphClockEnable(PeriphClockGpio); /* 打开GPIO外设时钟门控 */
    stcGpioInit.u32Mode   = GPIO_MD_INPUT;      /* 端口方向配置 */
    stcGpioInit.u32PullUp = GPIO_PULL_NONE;     /* 端口上拉配置 */
    stcGpioInit.u32Pin    = STK_USER_PIN;       /* 端口引脚配置 */
    GPIOA_Init(&stcGpioInit);                   /* GPIO 端口初始化 */
}

/**
 * @brief  STK LED初始化
 * @retval None
 */
void STK_LedConfig(void)
{
    stc_gpio_init_t stcGpioInit = {0};

    GPIO_StcInit(&stcGpioInit);                 /* 结构体变量初始值初始化 */
    SYSCTRL_PeriphClockEnable(PeriphClockGpio); /* 打开GPIO外设时钟门控 */
    stcGpioInit.u32Mode   = GPIO_MD_OUTPUT_PP;  /* 端口方向配置 */
    stcGpioInit.u32PullUp = GPIO_PULL_NONE;     /* 端口上拉配置 */
    stcGpioInit.u32Pin    = STK_LED_PIN;        /* 端口引脚配置 */
    GPIOA_Init(&stcGpioInit);                   /* GPIO 端口初始化 */
}

/**
 * @brief  获取芯片相关信息
 * @param  [in] pstcChipInfo 芯片信息结构体指针 @ref stc_stk_chip_info_t
 * @retval None
 */
void STK_ChipInfoGet(stc_stk_chip_info_t *pstcChipInfo)
{
    memcpy((void *)(&pstcChipInfo->u8UID[0]), (uint8_t *)0x001008B4, 10);
    pstcChipInfo->pcProductNum       = (char_t *)0x00100740u;
    pstcChipInfo->u32FlashSize       = *((uint32_t *)0x00100760u);
    pstcChipInfo->u32RamSize         = *((uint32_t *)0x00100764u);
    pstcChipInfo->u16FlashSectorSize = *((uint16_t *)0x00100768u);
    pstcChipInfo->u16PinCount        = *((uint16_t *)0x0010076Au);
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
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
