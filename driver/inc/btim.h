/**
 *******************************************************************************
 * @file  btim.h
 * @brief This file contains all the functions prototypes of the BTIM driver
 *        library
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

#ifndef __BTIM_H__
#define __BTIM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_BTIM BTIM模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup BTIM_Global_Types BTIM全局类型定义
 * @{
 */

/**
 * @brief BTIMx 初始化配置的结构体
 */
typedef struct
{
    uint32_t u32Mode;                /*!< 工作模式：内部时钟计数、外部输入计数、触发模式、门控模式 @ref BTIM_Mode_Select */
    uint32_t u32OneShotEn;           /*!< 定时器计数模式选择：连续计数模式或单次计数模式 @ref BTIM_OneShot_Continue_Select */
    uint32_t u32Prescaler;           /*!< 计数器输入信号分频 @ref BTIM_Clock_Div */
    uint32_t u32ToggleEn;            /*!< Toggle_N和Toggle_P输出使能 @ref BTIM_Toggle_Output_Control */
    uint32_t u32TriggerSrc;          /*!< 触发源选择，外部管脚ETR或者上一级BTIM溢出 @ref BTIM_Trigger_Src_Select */
    uint32_t u32ExternInputPolarity; /*!< 外部输入极性选择 @ref BTIM_ETR_Input_Polarity */
    uint32_t u32AutoReloadValue;     /*!< 配置重载寄存器的值，数据范围：0x0000 ~ 0xFFFF */
} stc_btim_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup BTIM_Global_Macros BTIM全局宏定义
 * @{
 */

/** @defgroup BTIM_Mode_Select BTIM工作模式配置
 * @{
 */
#define BTIM_MD_PCLK   (0x0u)                   /*!< 定时器模式 */
#define BTIM_MD_EXTERN (0x1u << BTIM_CR_MD_Pos) /*!< 计数器模式 */
#define BTIM_MD_TRIG   (0x2u << BTIM_CR_MD_Pos) /*!< 触发启动模式 */
#define BTIM_MD_GATE   (0x3u << BTIM_CR_MD_Pos) /*!< 门控模式 */
/**
 * @}
 */

/** @defgroup BTIM_OneShot_Continue_Select BTIM单次/连续计数模式
 * @{
 */
#define BTIM_CONTINUOUS_COUNTER (0x0u)            /*!< 连续计数模式 */
#define BTIM_ONESHOT_COUNTER    (BTIM_CR_OST_Msk) /*!< 单次模式 */
/**
 * @}
 */

/** @defgroup BTIM_Clock_Div BTIM预分频器分频系数配置
 * @{
 */
#define BTIM_COUNTER_CLK_DIV1     (0x0u)                    /*!<BTIM  Div 1*/
#define BTIM_COUNTER_CLK_DIV2     (0x1u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 2*/
#define BTIM_COUNTER_CLK_DIV4     (0x2u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 4*/
#define BTIM_COUNTER_CLK_DIV8     (0x3u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 8*/
#define BTIM_COUNTER_CLK_DIV16    (0x4u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 16*/
#define BTIM_COUNTER_CLK_DIV32    (0x5u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 32*/
#define BTIM_COUNTER_CLK_DIV64    (0x6u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 64*/
#define BTIM_COUNTER_CLK_DIV128   (0x7u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 128*/
#define BTIM_COUNTER_CLK_DIV256   (0x8u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 256*/
#define BTIM_COUNTER_CLK_DIV512   (0x9u << BTIM_CR_PRS_Pos) /*!<BTIM  Div 512*/
#define BTIM_COUNTER_CLK_DIV1024  (0xAu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 1024*/
#define BTIM_COUNTER_CLK_DIV2048  (0xBu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 2048*/
#define BTIM_COUNTER_CLK_DIV4096  (0xCu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 4096*/
#define BTIM_COUNTER_CLK_DIV8192  (0xDu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 8192*/
#define BTIM_COUNTER_CLK_DIV16384 (0xEu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 16384*/
#define BTIM_COUNTER_CLK_DIV32768 (0xFu << BTIM_CR_PRS_Pos) /*!<BTIM  Div 32768*/
/**
 * @}
 */

/** @defgroup BTIM_Toggle_Output_Control BTIM TOG管脚输出使能控制
 * @{
 */
#define BTIM_TOGGLE_DISABLE (0x0u)              /*!< TOG禁止，输出电平为0 */
#define BTIM_TOGGLE_ENABLE  (BTIM_CR_TOGEN_Msk) /*!< TOG输出使能，电平反相 */
/**
 * @}
 */

/** @defgroup BTIM_Trigger_Src_Select BTIM触发源选择
 * @{
 */
#define BTIM_TRIG_SRC_ETR (0x0u)                    /*!< 外部管脚TER作为计数器触发源，或门控 */
#define BTIM_TRIG_SRC_ITR (0x1u << BTIM_CR_TRS_Pos) /*!< 上一级BTIM溢出信号,门控模式下不建议选此源作为门控信号 */
/**
 * @}
 */

/** @defgroup BTIM_ETR_Input_Polarity BTIM外部管脚输入的ETR信号极性选择
 * @{
 */
#define BTIM_ETR_POLARITY_NORMAL   (0x0u)            /*!< 外部输入ETR不反向(触发模式上沿触发,门控模式低电平停止计数) */
#define BTIM_ETR_POLARITY_INVERTED (BTIM_CR_ETP_Msk) /*!< 外部输入ETR反向(触发模式下沿触发,门控模式高电平停止计数) */
/**
 * @}
 */

/** @defgroup BTIM_Int_Select BTIM中断中断使能控制
 * @{
 */
#define BTIM_INT_UI (BTIM_IER_UI_Msk) /*!< 溢出中断使能控制 */
#define BTIM_INT_TI (BTIM_IER_TI_Msk) /*!< 触发中断使能控制 */
/**
 * @}
 */

/** @defgroup BTIM_Flag_Select BTIM中断标志选择
 * @{
 */
#define BTIM_FLAG_UI (BTIM_IFR_UI_Msk) /*!< 溢出中断标志 */
#define BTIM_FLAG_TI (BTIM_IFR_TI_Msk) /*!< 触发中断标志 */
/**
 * @}
 */

/** @defgroup BTIM_All_Int_Flag BTIM复合中断标志
 * @{
 */
#define BTIM03_AIT_FLAG_UI (BTIM_AIFR_UI03_Msk) /*!< BTIM0或BTIM3溢出中断标志 */
#define BTIM03_AIT_FLAG_TI (BTIM_AIFR_TI03_Msk) /*!< BTIM0或BTIM3触发中断标志 */
#define BTIM14_AIT_FLAG_UI (BTIM_AIFR_UI14_Msk) /*!< BTIM1或BTIM4溢出中断标志 */
#define BTIM14_AIT_FLAG_TI (BTIM_AIFR_TI14_Msk) /*!< BTIM1或BTIM4触发中断标志 */
#define BTIM25_AIT_FLAG_UI (BTIM_AIFR_UI25_Msk) /*!< BTIM2或BTIM5溢出中断标志 */
#define BTIM25_AIT_FLAG_TI (BTIM_AIFR_TI25_Msk) /*!< BTIM2或BTIM5触发中断标志 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup BTIM_Global_Functions BTIM全局函数定义
 * @{
 */
en_result_t BTIM_Init(BTIM_TypeDef *BTIMx, stc_btim_init_t *pstcInitConfig); /* 定时器BTIMx的初始化配置 */

void     BTIM_CounterSet(BTIM_TypeDef *BTIMx, uint16_t u16CountValue); /* 设定BTIMx计数器计数值 */
uint32_t BTIM_CounterGet(BTIM_TypeDef *BTIMx);                         /* 获取BTIMx计数器计数值 */

void BTIM_AutoReloadSet(BTIM_TypeDef *BTIMx, uint16_t u16AutoReload); /* 设定BTIMx重载寄存器的值 */

void BTIM_Enable(BTIM_TypeDef *BTIMx);  /* 开启定时器BTIMx模块 */
void BTIM_Disable(BTIM_TypeDef *BTIMx); /* 禁止定时器BTIMx模块 */

void BTIM_ModeSet(BTIM_TypeDef *BTIMx, uint32_t u32Mode); /* 设定定时器BTIMx工作模式 */

void BTIM_ToggleEnable(BTIM_TypeDef *BTIMx);  /* 定时器BTIMx TOG输出使能 */
void BTIM_ToggleDisable(BTIM_TypeDef *BTIMx); /* 定时器BTIMx TOG输出禁止 */

void BTIM_CounterClockDivSet(BTIM_TypeDef *BTIMx, uint32_t u32CounterClockDiv); /* 定时器BTIMx模块 计数时钟预除频 */

void BTIM_OneShotSet(BTIM_TypeDef *BTIMx, uint32_t u32OneShotMode); /* 设定BTIMx计数模式 单次\连续计数模式 */

void BTIM_TriggerSrcSet(BTIM_TypeDef *BTIMx, uint32_t u32TriggerSrc); /* 设定定时器BTIMx触发源 */

void BTIM_ExternInputPolaritySet(BTIM_TypeDef *BTIMx, uint32_t u32ExternInputPolarity); /* 设定定时器BTIMx外部输入ETR极性设定 */

void BTIM_IntEnable(BTIM_TypeDef *BTIMx, uint32_t u32Int);  /* BTIMx中断使能 */
void BTIM_IntDisable(BTIM_TypeDef *BTIMx, uint32_t u32Int); /* BTIMx中断禁止 */

boolean_t BTIM_IntFlagGet(BTIM_TypeDef *BTIMx, uint32_t u32IntFlag);        /* 获取BTIMx中断标志 */
void      BTIM_IntFlagClear(BTIM_TypeDef *BTIMx, uint32_t u32IntClearFlag); /* 清除BTIMx中断标志位 */

boolean_t BTIM_AifrFlagGet(BTIM_TypeDef *BTIMx, uint32_t u32IntFlag);        /* 获取AIFR复合BTIM中断标志 */
void      BTIM_AicrFlagClear(BTIM_TypeDef *BTIMx, uint32_t u32IntClearFlag); /* 清除AICR复合BTIM中断标志位 */

void BTIM_StcInit(stc_btim_init_t *pstcInit); /* 结构体初始化 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BTIM_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
