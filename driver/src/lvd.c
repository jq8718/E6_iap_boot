/**
 *******************************************************************************
 * @file  lvd.c
 * @brief This file provides firmware functions to manage the LVD
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lvd.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LVD LVD模块驱动库
 * @brief LVD Driver Library LVD模块驱动库
 * @{
 */
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup LVD_Global_Functions LVD全局函数定义
 * @{
 */

/**
 * @brief  LVD初始化
 * @param  [in] pstcLvdInit VC初始化配置结构体 @ref stc_lvd_init_t
 * @retval en_result_t
 *           - Ok: 初始化成功
 */
en_result_t LVD_Init(stc_lvd_init_t *pstcLvdInit)
{
    MODIFY_REG32(LVD->CR,
                 LVD_CR_ACT_Msk | LVD_CR_FTEN_Msk | LVD_CR_RTEN_Msk | LVD_CR_HTEN_Msk | LVD_CR_SOURCE_Msk | LVD_CR_VTDS_Msk | LVD_CR_DEBOUNCE_TIME_Msk
                     | LVD_CR_FLT_MODE_Msk,
                 pstcLvdInit->u32TriggerAction | pstcLvdInit->u32TriggerMode | pstcLvdInit->u32Src | pstcLvdInit->u32ThresholdVolt | pstcLvdInit->u32FilterTime
                     | pstcLvdInit->u32FilterMode);

    return Ok;
}

/**
 * @brief  LVD模块使能
 * @retval None
 */
void LVD_Enable(void)
{
    SET_REG_BIT(LVD->CR, LVD_CR_EN_Msk);
}

/**
 * @brief  LVD模块禁止
 * @retval None
 */
void LVD_Disable(void)
{
    CLR_REG_BIT(LVD->CR, LVD_CR_EN_Msk);
}

/**
 * @brief  LVD触发动作配置
 * @param  [in] u32TriggerMode 触发模式 @ref LVD_Trigger_Action_Select
 * @retval None
 */
void LVD_TriggerActionConfig(uint32_t u32TriggerAction)
{
    MODIFY_REG(LVD->CR, LVD_CR_ACT_Msk, u32TriggerAction);
}

/**
 * @brief  LVD中断触发模式配置
 * @param  [in] u32TriggerMode 触发模式 @ref LVD_Trigger_Mode_Select
 * @retval None
 */
void LVD_TriggerModeConfig(uint32_t u32TriggerMode)
{
    MODIFY_REG(LVD->CR, LVD_CR_HTEN_Msk | LVD_CR_RTEN_Msk | LVD_CR_FTEN_Msk, u32TriggerMode);
}

/**
 * @brief  LVD中断使能
 * @retval None
 */
void LVD_IntEnable(void)
{
    SET_REG_BIT(LVD->CR, LVD_CR_IE_Msk);
}

/**
 * @brief  LVD中断禁止
 * @retval None
 */
void LVD_IntDisable(void)
{
    CLR_REG_BIT(LVD->CR, LVD_CR_IE_Msk);
}

/**
 * @brief  获取LVD中断标志
 * @retval uint32_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t LVD_IntFlagGet(void)
{
    return READ_REG32_BIT(LVD->SR, LVD_SR_INTF_Msk) ? TRUE : FALSE;
}

/**
 * @brief  清除LVD中断标志
 * @retval None
 */
void LVD_IntFlagClear(void)
{
    CLR_REG_BIT(LVD->SR, LVD_SR_INTF_Msk);
}

/**
 * @brief  获取滤波后的信号电平
 * @retval uint32_t
 *           - TRUE: 滤波后的信号电平为高
 *           - FALSE: 滤波后的信号电平为低
 */
boolean_t LVD_FilterOutputGet(void)
{
    return READ_REG32_BIT(LVD->SR, LVD_SR_FLTV_Msk) ? TRUE : FALSE;
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_lvd_init_t
 * @retval None
 */
void LVD_StcInit(stc_lvd_init_t *pstcInit)
{
    pstcInit->u32TriggerAction = LVD_TRIG_ACT_INT;
    pstcInit->u32TriggerMode   = LVD_TRIG_MD_NONE;
    pstcInit->u32Src           = LVD_SRC_DVCC;
    pstcInit->u32ThresholdVolt = LVD_THRESHOLD_VOLT1P8V;
    pstcInit->u32FilterTime    = LVD_FILTER_TIME_NONE;
    pstcInit->u32FilterMode    = LVD_FILTER_MD_NFM;
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

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
