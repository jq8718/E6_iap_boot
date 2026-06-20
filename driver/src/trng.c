/**
 *******************************************************************************
 * @file  trng.c
 * @brief This file provides firmware functions to manage the TRNG
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-10-10       MADS            First version
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
#include "trng.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_TRNG TRNG模块驱动库
 * @brief TRNG Driver Library TRNG模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TRNG_Local_Macros TRNG局部宏定义
 * @{
 */

/**
 * @defgroup TRNG_Load_Config TRNG装载新的初始值配置
 * @{
 */
#define TRNG_LOAD_DISABLE (0x0u)               /*!< 不装载新的初始值 */
#define TRNG_LOAD_ENABLE  (TRNG_MODE_LOAD_Msk) /*!< 装载新的初始值 */
/**
 * @}
 */

/**
 * @defgroup TRNG_FDBK_XOR_Config TRNG异或操作配置
 * @{
 */
#define TRNG_FDBK_XOR_DISABLE (0x0u)               /*!< 不进行异或操作 */
#define TRNG_FDBK_XOR_ENABLE  (TRNG_MODE_FDBK_Msk) /*!< 进行异或操作 */
/**
 * @}
 */

/**
 * @defgroup TRNG_Shift_Time TRNG反馈移位次数
 * @{
 */
#define TRNG_SHIFT_TIMES_0   (0x0u)                       /*!< 移位0次 */
#define TRNG_SHIFT_TIMES_8   (0x01u << TRNG_MODE_CNT_Pos) /*!< 移位8次 */
#define TRNG_SHIFT_TIMES_16  (0x02u << TRNG_MODE_CNT_Pos) /*!< 移位16次 */
#define TRNG_SHIFT_TIMES_32  (0x03u << TRNG_MODE_CNT_Pos) /*!< 移位32次 */
#define TRNG_SHIFT_TIMES_64  (0x04u << TRNG_MODE_CNT_Pos) /*!< 移位64次 */
#define TRNG_SHIFT_TIMES_128 (0x05u << TRNG_MODE_CNT_Pos) /*!< 移位128次 */
#define TRNG_SHIFT_TIMES_256 (0x06u << TRNG_MODE_CNT_Pos) /*!< 移位256次 */
/**
 * @}
 */

/**
 * @defgroup TRNG_Timeout TRNG超时时间
 * @{
 */
#define TRNG_TIMEOUT 0xFFFFu
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
 * @defgroup TRNG_Global_Functions TRNG全局函数定义
 * @{
 */

/**
 * @brief   随机数初始化(上电第一次生成随机数)
 * @retval  en_result_t
 *           - Ok: 写入成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t TRNG_Init(void)
{
    uint32_t u32Timeout;

    /* 生成64bits随机数(上电第一次) */
    SET_REG32_BIT(TRNG->CR, TRNG_CR_RNGCIR_EN_Msk);

    /* 模式配置0 */
    MODIFY_REG32(TRNG->MODE, TRNG_MODE_LOAD_Msk | TRNG_MODE_FDBK_Msk | TRNG_MODE_CNT_Msk, TRNG_LOAD_ENABLE | TRNG_FDBK_XOR_ENABLE | TRNG_SHIFT_TIMES_256);

    /* 生成随机数0 */
    SET_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk);
    u32Timeout = TRNG_TIMEOUT;
    while (READ_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    /* 模式配置1 */
    MODIFY_REG32(TRNG->MODE, TRNG_MODE_LOAD_Msk | TRNG_MODE_FDBK_Msk | TRNG_MODE_CNT_Msk, TRNG_LOAD_DISABLE | TRNG_FDBK_XOR_DISABLE | TRNG_SHIFT_TIMES_64);
    /* 生成随机数1 */
    SET_REG_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk);
    u32Timeout = TRNG_TIMEOUT;
    while (READ_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    /* 关闭随机源电路，节省功耗 */
    CLR_REG32_BIT(TRNG->CR, TRNG_CR_RNGCIR_EN_Msk);

    return Ok;
}

/**
 * @brief   生成随机数(非上电第一次生成随机数)
 * @retval  en_result_t
 *           - Ok: 写入成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t TRNG_Generate(void)
{
    uint32_t u32Timeout;

    /* 生成64bits随机数(非上电第一次生成) */
    SET_REG32_BIT(TRNG->CR, TRNG_CR_RNGCIR_EN_Msk);

    /* 模式配置0 */
    MODIFY_REG32(TRNG->MODE, TRNG_MODE_LOAD_Msk | TRNG_MODE_FDBK_Msk | TRNG_MODE_CNT_Msk, TRNG_LOAD_DISABLE | TRNG_FDBK_XOR_DISABLE | TRNG_SHIFT_TIMES_256);
    /* 生成随机数0 */
    SET_REG_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk);
    u32Timeout = TRNG_TIMEOUT;
    while (READ_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    /* 模式配置1 */
    MODIFY_REG32(TRNG->MODE, TRNG_MODE_FDBK_Msk | TRNG_MODE_CNT_Msk, TRNG_FDBK_XOR_DISABLE | TRNG_SHIFT_TIMES_64);
    /* 生成随机数1 */
    SET_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk);
    u32Timeout = TRNG_TIMEOUT;
    while (READ_REG32_BIT(TRNG->CR, TRNG_CR_RNG_RUN_Msk))
    {
        if (0 == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    /* 关闭随机源电路，节省功耗 */
    CLR_REG32_BIT(TRNG->CR, TRNG_CR_RNGCIR_EN_Msk);

    return Ok;
}

/**
 * @brief  随机数获取
 * @retval 低32位随机数
 */
uint32_t TRNG_Data0Get(void)
{
    return TRNG->DATA0;
}

/**
 * @brief  随机数获取
 * @retval 高32位随机数
 */
uint32_t TRNG_Data1Get(void)
{
    return TRNG->DATA1;
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
