/**
 *******************************************************************************
 * @file  ddl.c
 * @brief This file provides firmware functions to manage the DDL
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
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
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DDL DDL模块驱动库
 * @brief DDL Common Functions共通API
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
 * @defgroup DDL_Global_Functions DDL全局函数定义
 * @{
 */

/**
 * @brief  log2数学函数
 * @param  [in] u32Value 32位无符号输入值
 * @retval uint32_t 32位无符号结果
 */
uint32_t Log2(uint32_t u32Value)
{
    uint32_t u32V1 = 0;

    if (0u == u32Value)
    {
        return 0;
    }

    while (u32Value > 1u)
    {
        u32V1++;
        u32Value /= 2;
    }

    return u32V1;
}

/**
 * @brief  memory清零函数
 * @param  [in] pu8StartAddr 起始地址
 * @param  [in] u32Count 清零长度，以字节为单位
 * @retval None
 */
void DDL_MemoryClear(void *pu8StartAddr, uint32_t u32Count)
{
    uint8_t *pu8Addr = (uint8_t *)pu8StartAddr;

    if (NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}

/**
 * @brief  1ms延时函数
 * @param  [in] u32Count 延时时长，单位1ms
 * @retval None
 */
void DDL_Delay1ms(uint32_t u32Count)
{
    uint32_t u32ValueNow = 0, u32ValueCount = 0;
    uint32_t u32ValueEnd = (u32Count * (SystemCoreClock / 1000));

    uint32_t u32ValueStart = SysTick->VAL;
    while (1)
    {
        u32ValueNow = SysTick->VAL;

        if (u32ValueNow != u32ValueStart)
        {
            if (u32ValueNow < u32ValueStart)
            {
                u32ValueCount += u32ValueStart - u32ValueNow;
            }
            else
            {
                u32ValueCount += SysTick->LOAD - u32ValueNow + u32ValueStart;
            }
            u32ValueStart = u32ValueNow;
            if (u32ValueCount >= u32ValueEnd)
            {
                break;
            }
        }
    }
}

/**
 * @brief  100us延时函数
 * @param  [in] u32Count 延时时长，单位100us
 * @retval None
 */
void DDL_Delay100us(uint32_t u32Count)
{
    uint32_t u32ValueNow = 0, u32ValueCount = 0;
    uint32_t u32ValueEnd = (u32Count * (SystemCoreClock / 10000));

    uint32_t u32ValueStart = SysTick->VAL;
    while (1)
    {
        u32ValueNow = SysTick->VAL;

        if (u32ValueNow != u32ValueStart)
        {
            if (u32ValueNow < u32ValueStart)
            {
                u32ValueCount += u32ValueStart - u32ValueNow;
            }
            else
            {
                u32ValueCount += SysTick->LOAD - u32ValueNow + u32ValueStart;
            }

            u32ValueStart = u32ValueNow;

            if (u32ValueCount >= u32ValueEnd)
            {
                break;
            }
        }
    }
}

/**
 * @brief  10us延时函数
 * @param  [in] u32Count 延时时长，单位10us
 * @retval None
 */
void DDL_Delay10us(uint32_t u32Count)
{
    uint32_t u32ValueNow = 0, u32ValueCount = 0;

    uint32_t u32ValueStart = SysTick->VAL;
    while (1)
    {
        u32ValueNow = SysTick->VAL;

        if (u32ValueNow != u32ValueStart)
        {
            if (u32ValueNow < u32ValueStart)
            {
                u32ValueCount += u32ValueStart - u32ValueNow;
            }
            else
            {
                u32ValueCount += SysTick->LOAD - u32ValueNow + u32ValueStart;
            }

            u32ValueStart = u32ValueNow;

            if (u32ValueCount >= (u32Count * (SystemCoreClock / 100000)))
            {
                break;
            }
        }
    }
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
