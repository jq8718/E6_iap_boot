/**
 *******************************************************************************
 * @file  gpio.c
 * @brief This file contains all the functions prototypes of the GPIO driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-04       MADS            First version
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
#include "gpio.h"
/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO模块驱动库
 * @brief GPIOx Driver Library GPIO模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Macros GPIO局部宏定义
 * @{
 */
/**
 * @defgroup GPIO_Value_Define GPIO模式值设置
 * @{
 */
#define GPIO_MD_MSK         (0x000Fu) /*!< 端口模式Mask值 */
#define GPIO_MD_OD_MSK      (0x00F0u) /*!< 端口开漏模式Mask值 */
#define GPIO_MD_EXT_INT_MSK (0x0F00u) /*!< 外部中断模式Mask值 */

#define GPIO_INPUT          (0x0001u) /*!< 端口模式_输入 */
#define GPIO_OUTPUT         (0x0002u) /*!< 端口模式_输出 */
#define GPIO_ANALOG         (0x0004u) /*!< 端口模式_模拟 */
#define GPIO_EXT_INT        (0x0F00u) /*!< 端口外部中断  */
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
 * @defgroup GPIO_Global_Func GPIO全局函数定义
 * @{
 */

/**
 * @brief  GPIO初始化
 * @param  [in] GPIOx  端口类型 @ref GPIO_TypeDef
 * @param  [in] pstcGpioConfig 配置结构体指针 @ref stc_gpio_init_t
 * @retval None
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, stc_gpio_init_t *pstcGpioInit)
{
    if (GPIOx != GPIOB)
    {
        /* INPUT */
        if (GPIO_INPUT == (pstcGpioInit->u32Mode & GPIO_MD_MSK))
        {
            SET_REG_BIT(GPIOx->DIR, pstcGpioInit->u32Pin);
        }

        /* OUTPUT */
        if (GPIO_OUTPUT == (pstcGpioInit->u32Mode & GPIO_MD_MSK))
        {
            /* Set Initial Output Value */
            if (pstcGpioInit->bOutputValue != FALSE)
            {
                SET_REG_BIT(GPIOx->OUT, pstcGpioInit->u32Pin);
            }
            else
            {
                CLR_REG_BIT(GPIOx->OUT, pstcGpioInit->u32Pin);
            }

            /* OPENDRAIN or PUSH-PULL */
            if (pstcGpioInit->u32Mode & GPIO_MD_OD_MSK)
            {
                SET_REG_BIT(GPIOx->OD, pstcGpioInit->u32Pin);
            }
            else
            {
                CLR_REG_BIT(GPIOx->OD, pstcGpioInit->u32Pin);
            }

            /* Set Direction as Output*/
            CLR_REG_BIT(GPIOx->DIR, pstcGpioInit->u32Pin);
        }

        /* ANALOG */
        if (GPIO_ANALOG == (pstcGpioInit->u32Mode & GPIO_MD_MSK))
        {
            SET_REG_BIT(GPIOx->ADS, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->ADS, pstcGpioInit->u32Pin);
        }

        /* PULL */
        if (GPIO_PULL_UP == pstcGpioInit->u32PullUp)
        {
            SET_REG_BIT(GPIOx->PU, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->PU, pstcGpioInit->u32Pin);
        }
    }

    /* External Interrupt */
    if (GPIO_EXT_INT == (pstcGpioInit->u32Mode & GPIO_MD_EXT_INT_MSK))
    {
        if (pstcGpioInit->u32ExternInt & GPIO_EXTI_RISING)
        {
            SET_REG_BIT(GPIOx->RIE, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->RIE, pstcGpioInit->u32Pin);
        }

        if (pstcGpioInit->u32ExternInt & GPIO_EXTI_FALLING)
        {
            SET_REG_BIT(GPIOx->FIE, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->FIE, pstcGpioInit->u32Pin);
        }

        if (pstcGpioInit->u32ExternInt & GPIO_EXTI_HIGH)
        {
            SET_REG_BIT(GPIOx->HIE, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->HIE, pstcGpioInit->u32Pin);
        }

        if (pstcGpioInit->u32ExternInt & GPIO_EXTI_LOW)
        {
            SET_REG_BIT(GPIOx->LIE, pstcGpioInit->u32Pin);
        }
        else
        {
            CLR_REG_BIT(GPIOx->LIE, pstcGpioInit->u32Pin);
        }
    }
}

/**
 * @brief  中断状态获取
 * @param  [in] GPIOx 端口类型 @ref GPIO_TypeDef
 * @param  [in] u32Pin 引脚类型 @ref GPIO_Pins_Define
 * @retval boolean_t
 *           - TRUE  中断标志置位
 *           - FALSE  中断标志未置位
 */
boolean_t GPIO_IntFlagGet(GPIO_TypeDef *GPIOx, uint32_t u32Pin)
{
    return READ_REG_BIT(GPIOx->STAT, u32Pin) ? TRUE : FALSE;
}

/**
 * @brief  中断状态清除
 * @param  [in] GPIOx 端口类型 @ref GPIO_TypeDef
 * @param  [in] u32Pin 引脚类型 @ref GPIO_Pins_Define
 * @retval None
 */
void GPIO_IntFlagClear(GPIO_TypeDef *GPIOx, uint32_t u32Pin)
{
    CLR_REG_BIT(GPIOx->ICLR, u32Pin);
}

/**
 * @brief  GPIO结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_gpio_init_t
 * @retval None
 */
void GPIO_StcInit(stc_gpio_init_t *pstcInit)
{
    pstcInit->u32Pin       = 0x0u;
    pstcInit->u32Mode      = GPIO_MD_ANALOG;
    pstcInit->u32PullUp    = GPIO_PULL_NONE;
    pstcInit->u32ExternInt = GPIO_EXTI_NONE;
    pstcInit->bOutputValue = FALSE;
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
