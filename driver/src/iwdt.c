/**
 *******************************************************************************
 * @file  iwdt.c
 * @brief This file provides firmware functions to manage the IWDT
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
   2025-07-08       MADS            Modify IWDT_SR_PRSF_Msk to IWDT_SR_CRF_Msk
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024~2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "iwdt.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_IWDT IWDT模块驱动库
 * @brief IWDT Driver Library IWDT模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Local_Macros IWDT局部宏定义
 * @{
 */
/**
 * @defgroup IWDT_Key_Value_Define IWDT键值设置
 * @{
 */
#define IWDT_KEY_LOCK_RELEASE     (0x5555u) /*!< 解除写保护 */
#define IWDT_KEY_START_VALUE      (0xCCCCu) /*!< 启动IWDT计数器 */
#define IWDT_KEY_RELOAD_VALUE     (0xAAAAu) /*!< 重载IWDT计数器 */
#define IWDT_KEY_STOP_BYPASS_1234 (0x1234u) /*!< 依次写入0x1234和0x5678停止IWDT */
#define IWDT_KEY_STOP_BYPASS_5678 (0x5678u) /*!< 依次写入0x1234和0x5678停止IWDT */
/**
 * @}
 */

/**
 * @defgroup IWDT_Timeout IWDT超时时间
 * @{
 */
#define IWDT_TIMEOUT (0xFFFFu)
/**
 * @}
 */

/**
 * @}
 */
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
 * @defgroup IWDT_Global_Functions IWDT全局函数定义
 * @{
 */

/**
 * @brief  IWDT初始化
 * @param  [in] pstcIwdtInit IWDT初始化 @ref stc_iwdt_init_t
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t IWDT_Init(stc_iwdt_init_t *pstcIwdtInit)
{
    uint32_t u32Timeout;

    WRITE_REG32(IWDT->KR, IWDT_KEY_START_VALUE);
    WRITE_REG32(IWDT->KR, IWDT_KEY_LOCK_RELEASE);

    u32Timeout = IWDT_TIMEOUT;
    while (READ_REG32_BIT(IWDT->SR, IWDT_SR_CRF_Msk | IWDT_SR_ARRF_Msk | IWDT_SR_WINRF_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    WRITE_REG32(IWDT->CR, pstcIwdtInit->u32Action | pstcIwdtInit->u32Prescaler);
    u32Timeout = IWDT_TIMEOUT;
    while (READ_REG32_BIT(IWDT->SR, IWDT_SR_CRF_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    WRITE_REG32(IWDT->ARR, pstcIwdtInit->u32ArrCounter);
    u32Timeout = IWDT_TIMEOUT;
    while (READ_REG32_BIT(IWDT->SR, IWDT_SR_ARRF_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    if (pstcIwdtInit->u32Window < pstcIwdtInit->u32ArrCounter) /*!< 窗口看门狗模式 */
    {
        WRITE_REG32(IWDT->WINR, pstcIwdtInit->u32Window);
        u32Timeout = IWDT_TIMEOUT;
        while (READ_REG32_BIT(IWDT->SR, IWDT_SR_WINRF_Msk))
        {
            if (0 == u32Timeout--)
            {
                return ErrorTimeout;
            }
        }
    }

    else /*!< 独立看门狗模式 */
    {
        u32Timeout = IWDT_TIMEOUT;
        while (!READ_REG32_BIT(IWDT->SR, IWDT_SR_RUN_Msk))
        {
            if (0 == u32Timeout--)
            {
                return ErrorTimeout;
            }
        }
        WRITE_REG32(IWDT->KR, IWDT_KEY_RELOAD_VALUE);
    }

    return Ok;
}

/**
 * @brief  IWDT启动运行
 * @retval None
 */
void IWDT_Start(void)
{
    WRITE_REG32(IWDT->KR, IWDT_KEY_START_VALUE);
}

/**
 * @brief  IWDT停止运行
 * @retval None
 */
void IWDT_Stop(void)
{
    WRITE_REG32(IWDT->KR, IWDT_KEY_STOP_BYPASS_1234);
    WRITE_REG32(IWDT->KR, IWDT_KEY_STOP_BYPASS_5678);
}

/**
 * @brief  IWDT重载
 * @retval None
 */
void IWDT_Feed(void)
{
    WRITE_REG32(IWDT->KR, IWDT_KEY_RELOAD_VALUE);
}

/**
 * @brief  获取IWDT溢出状态标志
 * @retval boolean_t 溢出标志位
 *           - TRUE: 溢出
 *           - FALSE: 没有溢出
 */
boolean_t IWDT_OverFlagGet(void)
{
    return READ_REG32_BIT(IWDT->SR, IWDT_SR_OV_Msk) ? TRUE : FALSE;
}

/**
 * @brief  获取IWDT运行状态标志
 * @retval boolean_t 运行状态
 *           - TRUE: 正在运行
 *           - FALSE: 没有运行
 */
boolean_t IWDT_RunFlagGet(void)
{
    return READ_REG32_BIT(IWDT->SR, IWDT_SR_RUN_Msk) ? TRUE : FALSE;
}

/**
 * @brief  IWDT溢出标志清除
 * @retval None
 */
void IWDT_OverFlagClear(void)
{
    CLR_REG32(IWDT->SR);
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_iwdt_init_t
 * @retval None
 */
void IWDT_StcInit(stc_iwdt_init_t *pstcInit)
{
    pstcInit->u32Action     = IWDT_OVER_RST_SLEEPMODE_RUN;
    pstcInit->u32ArrCounter = 0xFFFu;
    pstcInit->u32Window     = 0xFFFu;
    pstcInit->u32Prescaler  = IWDT_RC10K_DIV_4;
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
