/**
 *******************************************************************************
 * @file  iap.c
 * @brief This file provides firmware functions of IAP
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "iap.h"
#include "config_hc32l021.h"
#include "modem.h"
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
static en_result_t IAP_JumpToApp(uint32_t u32Addr);
static void        IAP_ResetConfig(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint32_t   u32JumpAddress;
static func_ptr_t pfnJumpToApplication;
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  IAP初始化
 * @retval None
 */
void IAP_Init(void)
{
    HC32_PeriModuleInit();
    MODEM_RamInit();
}

/**
 * @brief  IAP APP程序升级主函数
 * @retval None
 */
void IAP_Main(void)
{
    en_result_t enRet;

    while (1)
    {
        enRet = MODEM_Process(); /* APP程序更新处理 */

        if (Ok == enRet)
        {
            IAP_ResetConfig();                    /* 复位所有外设模块 */
            if (Error == IAP_JumpToApp(APP_ADDR)) /* 如果跳转失败 */
            {
                while (1)
                    ;
            }
        }
    }
}

/**
 * @brief  检查BootPara标记区数据值，判断是否需要升级APP程序
 * @retval None
 */
void IAP_UpdateCheck(void)
{
    uint32_t u32AppFlag;

    u32AppFlag = *(__IO uint32_t *)BOOT_PARA_ADDR; /* 读出BootLoader para区标记值 */
    if (APP_FLAG != u32AppFlag)                    /* 如果标记值不等于APP_FLAG,表示不需要升级APP程序 */
    {
        IAP_JumpToApp(APP_ADDR); /* 直接跳转至APP */
    }
}

/**
 * @brief  IAP跳转函数
 * @param  [in] u32Addr APP 首地址
 * @retval en_result_t
 *           - Error: 跳转错误
 */
static en_result_t IAP_JumpToApp(uint32_t u32Addr)
{
    uint32_t u32StackTop = *((__IO uint32_t *)u32Addr); /* 读取APP程序栈顶地址 */

    /* 判断栈顶地址有效性 */
    if ((u32StackTop > SRAM_BASE) && (u32StackTop <= (SRAM_BASE + RAM_SIZE)))
    {
        /* 配置跳转到用户程序复位中断入口 */
        u32JumpAddress       = *(__IO uint32_t *)(u32Addr + 4);
        pfnJumpToApplication = (func_ptr_t)u32JumpAddress;
        /* 初始化用户程序的栈顶指针 */
        __set_MSP(*(__IO uint32_t *)u32Addr);
        pfnJumpToApplication();
    }

    return Error;
}

/**
 * @brief  BootLoader复位配置
 * @retval None
 */
static void IAP_ResetConfig(void)
{
    HC32_PeriModuleDeInit();
}

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
