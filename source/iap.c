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

    BOOT_DBG_PRINT("BOOT: start\r\n");

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

    /* Parameter area not initialized */
    if (stcParam.magic != BOOT_PARAM_MAGIC)
    {
#if (BOOT_PARAM_AUTO_INIT == 1u)
        BootParam_Init();
#endif
        /* Stay in bootloader — parameter area must be pre-programmed */
        BOOT_DBG_PRINT("BOOT: magic mismatch, stay\r\n");
        return;
    }

    switch (stcParam.state)
    {
        case BOOT_PARAM_STATE_IMAGE_VALID:
            BOOT_DBG_PRINT("BOOT: IMAGE_VALID, jump\r\n");
            (void)IAP_JumpToApp(APP_ADDR);
            BOOT_DBG_PRINT("BOOT: jump failed\r\n");
            break;

        case BOOT_PARAM_STATE_UPDATE_REQUEST:
            BOOT_DBG_PRINT("BOOT: UPDATE_REQUEST, IAP mode\r\n");
            break;

        case BOOT_PARAM_STATE_IMAGE_PENDING:
            BOOT_DBG_PRINT("BOOT: IMAGE_PENDING, IAP mode\r\n");
            break;

        default:
            BOOT_DBG_PRINT("BOOT: unknown state\r\n");
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
    uint32_t u32StackTop     = *((__IO uint32_t *)u32Addr);        /* APP 栈顶地址 */
    uint32_t u32ResetHandler = *((__IO uint32_t *)(u32Addr + 4u)); /* APP ResetHandler */

    /* 栈顶地址有效性 */
    if ((u32StackTop <= SRAM_BASE) || (u32StackTop > (SRAM_BASE + RAM_SIZE)))
    {
        BOOT_DBG_PRINT("BOOT: bad SP\r\n");
        return Error;
    }

    /* ResetHandler 必须在 APP Flash 范围内，且为 Thumb 地址（LSB=1） */
    if ((u32ResetHandler < APP_ADDR) ||
        (u32ResetHandler >= (APP_ADDR + APP_MAX_SIZE)) ||
        ((u32ResetHandler & 0x1u) == 0u))
    {
        BOOT_DBG_PRINT("BOOT: bad ResetHandler\r\n");
        return Error;
    }

    BOOT_DBG_PRINT("BOOT: jumping\r\n");

    /* 配置跳转到用户程序复位中断入口 */
    u32JumpAddress       = u32ResetHandler;
    pfnJumpToApplication = (func_ptr_t)u32JumpAddress;
    /* 初始化用户程序的栈顶指针 */
    __set_MSP(u32StackTop);
    pfnJumpToApplication();

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
