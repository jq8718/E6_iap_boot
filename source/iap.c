/*******************************************************************************
 * @file  iap.c
 * @brief This file provides firmware functions of IAP for I2C Bootloader
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
   2026-06-20       Claude          Use boot_param state machine for I2C IAP
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
#include "boot_param.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/******************************************************************************
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
 * @brief  检查Boot参数区状态，判断是否需要升级APP程序
 * @retval None
 */
void IAP_UpdateCheck(void)
{
    stc_boot_param_t stcParam;

    BootParam_Read(&stcParam);

    /* First power-on or corrupted parameter area: initialize and try jumping to APP */
    if (stcParam.magic != BOOT_PARAM_MAGIC)
    {
        BootParam_Init();
        if (Ok == IAP_JumpToApp(APP_ADDR))
        {
            return;
        }
        return;
    }

    switch (stcParam.state)
    {
        case BOOT_PARAM_STATE_IMAGE_VALID:
            /* Image verified OK: try jumping to APP */
            if (Error == IAP_JumpToApp(APP_ADDR))
            {
                /* Jump failed — mark invalid and stay in bootloader for recovery */
                BootParam_WriteState(BOOT_PARAM_STATE_IMAGE_INVALID);
            }
            break;

        case BOOT_PARAM_STATE_EMPTY:
            /* No update metadata; try jumping to existing APP */
            if (Error == IAP_JumpToApp(APP_ADDR))
            {
                /* No valid APP: stay in bootloader */
            }
            break;

        case BOOT_PARAM_STATE_UPDATE_REQUEST:
        case BOOT_PARAM_STATE_IMAGE_PENDING:
        case BOOT_PARAM_STATE_IMAGE_INVALID:
        default:
            /* Stay in Bootloader and wait for host I2C commands */
            break;
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
