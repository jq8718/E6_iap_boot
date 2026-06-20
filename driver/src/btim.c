/**
 *******************************************************************************
 * @file  btim.c
 * @brief This file provides firmware functions to manage the BTIM
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-18       MADS            First version
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
#include "btim.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_BTIM BTIM模块驱动库
 * @brief BTIM Driver Library BTIM模块驱动库
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
 * @defgroup BTIM_Global_Functions BTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器BTIMx的初始化配置
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] pstcInitConfig 初始化BTIMx的结构体 @ref stc_btim_init_t
 * @retval en_result_t
 *           - Ok 配置成功
 *           - ErrorInvalidParameter 无效参数
 */
en_result_t BTIM_Init(BTIM_TypeDef *BTIMx, stc_btim_init_t *pstcInitConfig)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_OST_Msk | BTIM_CR_MD_Msk | BTIM_CR_PRS_Msk | BTIM_CR_TOGEN_Msk | BTIM_CR_TRS_Msk | BTIM_CR_ETP_Msk,
                 pstcInitConfig->u32Mode | pstcInitConfig->u32OneShotEn | pstcInitConfig->u32Prescaler | pstcInitConfig->u32ToggleEn
                     | pstcInitConfig->u32TriggerSrc | pstcInitConfig->u32ExternInputPolarity);

    MODIFY_REG32(BTIMx->ARR, BTIM_ARR_ARR_Msk, (uint16_t)pstcInitConfig->u32AutoReloadValue);

    return Ok;
}

/**
 * @brief  设定BTIMx计数器计数值
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u16CountValue 16bit 计数值
 * @retval None
 */
void BTIM_CounterSet(BTIM_TypeDef *BTIMx, uint16_t u16CountValue)
{
    WRITE_REG32(BTIMx->CNT, (uint32_t)u16CountValue);
}

/**
 * @brief  获取BTIMx计数器计数值
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @retval uint32_t BTIMx计数器计数值
 */
uint32_t BTIM_CounterGet(BTIM_TypeDef *BTIMx)
{
    return READ_REG32_BIT(BTIMx->CNT, BTIM_CNT_CNT_Msk);
}

/**
 * @brief  设定BTIMx重载寄存器的值
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u16AutoReload 重载值
 * @retval None
 */
void BTIM_AutoReloadSet(BTIM_TypeDef *BTIMx, uint16_t u16AutoReload)
{
    WRITE_REG32(BTIMx->ARR, (uint32_t)u16AutoReload);
}

/**
 * @brief  开启定时器BTIMx模块
 * @param  [in] BTIMx BTIM结构体变量 @ref BTIM_TypeDef
 * @retval  None
 */
void BTIM_Enable(BTIM_TypeDef *BTIMx)
{
    SET_REG32_BIT(BTIMx->CR, BTIM_CR_CEN_Msk);
}

/**
 * @brief  禁止定时器BTIMx模块
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @retval  None
 */
void BTIM_Disable(BTIM_TypeDef *BTIMx)
{
    CLR_REG32_BIT(BTIMx->CR, BTIM_CR_CEN_Msk);
}

/**
 * @brief  设定定时器BTIMx工作模式
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32Mode 选择BTIM工作模式 @ref BTIM_Mode_Select
 * @retval None
 */
void BTIM_ModeSet(BTIM_TypeDef *BTIMx, uint32_t u32Mode)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_MD_Msk, u32Mode);
}

/**
 * @brief  定时器BTIMx TOG输出使能，TOGP和TOGN输出相位相反的信号
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @retval None
 */
void BTIM_ToggleEnable(BTIM_TypeDef *BTIMx)
{
    SET_REG32_BIT(BTIMx->CR, BTIM_CR_TOGEN_Msk);
}

/**
 * @brief  定时器BTIMx TOG输出禁止，TOGP和TOGN同时输出0
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @retval None
 */
void BTIM_ToggleDisable(BTIM_TypeDef *BTIMx)
{
    CLR_REG32_BIT(BTIMx->CR, BTIM_CR_TOGEN_Msk);
}

/**
 * @brief  定时器BTIMx模块 计数时钟预除频
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32CounterClockDiv 计数时钟预分频选择 @ref BTIM_Clock_Div
 * @retval None
 */
void BTIM_CounterClockDivSet(BTIM_TypeDef *BTIMx, uint32_t u32CounterClockDiv)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_PRS_Msk, u32CounterClockDiv);
}

/**
 * @brief  设定BTIMx计数模式 单次\连续计数模式
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32OneShotMode 单次\连续计数模式 @ref BTIM_OneShot_Continue_Select
 * @retval None
 */
void BTIM_OneShotSet(BTIM_TypeDef *BTIMx, uint32_t u32OneShotMode)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_OST_Msk, BTIM_ONESHOT_COUNTER);
}

/**
 * @brief  设定定时器BTIMx触发源
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32TriggerSrc 选择BTIM触发源 @ref BTIM_Trigger_Src_Select
 * @retval None
 */
void BTIM_TriggerSrcSet(BTIM_TypeDef *BTIMx, uint32_t u32TriggerSrc)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_TRS_Msk, u32TriggerSrc);
}

/**
 * @brief  设定定时器BTIMx外部输入ETR极性设定
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32ExternInputPolarity 外部输入ETR极性 @ref BTIM_ETR_Input_Polarity
 * @retval None
 */
void BTIM_ExternInputPolaritySet(BTIM_TypeDef *BTIMx, uint32_t u32ExternInputPolarity)
{
    MODIFY_REG32(BTIMx->CR, BTIM_CR_ETP_Msk, u32ExternInputPolarity);
}

/**
 * @brief  BTIMx中断使能
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32Int 中断使能禁止定义 @ref  BTIM_Int_Select
 * @retval None
 */
void BTIM_IntEnable(BTIM_TypeDef *BTIMx, uint32_t u32Int)
{
    SET_REG32_BIT(BTIMx->IER, u32Int);
}

/**
 * @brief  BTIMx中断禁止
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32Int 中断使能禁止定义 @ref  BTIM_Int_Select
 * @retval None
 */
void BTIM_IntDisable(BTIM_TypeDef *BTIMx, uint32_t u32Int)
{
    CLR_REG32_BIT(BTIMx->IER, u32Int);
}

/**
 * @brief  获取BTIMx中断标志
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32IntFlag  中断置起标志定义  @ref  BTIM_Flag_Select
 * @retval boolean_t
 *           - TRUE 已置起
 *           - FALSE 未置起
 */
boolean_t BTIM_IntFlagGet(BTIM_TypeDef *BTIMx, uint32_t u32IntFlag)
{
    return READ_REG32_BIT(BTIMx->IFR, u32IntFlag) ? TRUE : FALSE;
}

/**
 * @brief  清除BTIMx中断标志位
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32IntClearFlag 中断清零标志定义 @ref  BTIM_Flag_Select
 * @retval None
 */
void BTIM_IntFlagClear(BTIM_TypeDef *BTIMx, uint32_t u32IntClearFlag)
{
    CLR_REG32_BIT(BTIMx->ICR, u32IntClearFlag);
}

/**
 * @brief  获取复合BTIM中断标志
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32IntFlag 中断标志 @ref BTIM_All_Int_Flag
 * @retval boolean_t
 *           - TRUE: 已置起
 *           - FALSE: 未置起
 */
boolean_t BTIM_AifrFlagGet(BTIM_TypeDef *BTIMx, uint32_t u32IntFlag)
{
    return READ_REG32_BIT(BTIMx->AIFR, u32IntFlag) ? TRUE : FALSE;
}

/**
 * @brief  清除复合BTIM中断标志位
 * @param  [in] BTIMx BTIM单元名宏定义 @ref BTIM_TypeDef
 * @param  [in] u32IntClearFlag 中断清零标志 @ref BTIM_All_Int_Flag
 * @retval None
 */
void BTIM_AicrFlagClear(BTIM_TypeDef *BTIMx, uint32_t u32IntClearFlag)
{
    CLR_REG32_BIT(BTIMx->AICR, u32IntClearFlag);
}

/**
 * @brief  BTIM结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_btim_init_t
 * @retval None
 */
void BTIM_StcInit(stc_btim_init_t *pstcInit)
{
    pstcInit->u32Mode                = BTIM_MD_PCLK;
    pstcInit->u32OneShotEn           = BTIM_CONTINUOUS_COUNTER;
    pstcInit->u32Prescaler           = BTIM_COUNTER_CLK_DIV1;
    pstcInit->u32ToggleEn            = BTIM_TOGGLE_DISABLE;
    pstcInit->u32TriggerSrc          = BTIM_TRIG_SRC_ETR;
    pstcInit->u32ExternInputPolarity = BTIM_ETR_POLARITY_NORMAL;
    pstcInit->u32AutoReloadValue     = 0xFFFFu;
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
