/**
 *******************************************************************************
 * @file  atim3.c
 * @brief This file provides firmware functions to manage the ADC
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
#include "atim3.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ATIM3 ATIM3模块驱动库
 * @brief ATIM3 Driver Library ADC模块驱动库
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
 * @defgroup ATIM3_Global_Functions ATIM3全局函数定义
 * @{
 */

/**
 * @brief  ATIM3 初始化配置(模式0)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_mode0_init_t
 * @retval None
 */
void ATIM3_Mode0_Init(stc_atim3_mode0_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE0->M0CR,
               ATIM3_MODE0_M0CR_MODE | ATIM3_MODE0_M0CR_GATEP | ATIM3_MODE0_M0CR_GATE | ATIM3_MODE0_M0CR_PRS | ATIM3_MODE0_M0CR_TOGEN | ATIM3_MODE0_M0CR_CT
                   | ATIM3_MODE0_M0CR_MD,
               pstcCfg->u32WorkMode | pstcCfg->u32GatePolar | pstcCfg->u32EnGate | pstcCfg->u32PRS | pstcCfg->u32EnTog | pstcCfg->u32CountClockSelect
                   | pstcCfg->u32CountMode);
}

/**
 * @brief  ATIM3 模式0 启动运行
 * @retval None
 */
void ATIM3_Mode0_Run(void)
{
    SET_REG_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_CTEN);
}

/**
 * @brief  ATIM3 模式0 停止运行
 * @retval None
 */
void ATIM3_Mode0_Stop(void)
{
    CLR_REG_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_CTEN);
}

/**
 * @brief  ATIM3 模式0 重载值设置
 * @param  [in] u16Data 16bits重载值
 * @retval None
 */
void ATIM3_Mode0_ARRSet(uint32_t u16Data)
{
    WRITE_REG(ATIM3_MODE0->ARR, (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式0 获取重载值
 * @retval uint32_t 16bits重载值
 */
uint32_t ATIM3_Mode0_ARRGet(void)
{
    return ((READ_REG(ATIM3_MODE0->ARR)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式0 16位计数器初值设置
 * @param  [in] u16Data CNT 16位初值
 * @retval None
 */
void ATIM3_Mode0_Cnt16Set(uint32_t u16Data)
{
    WRITE_REG(ATIM3_MODE0->CNT, (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式0 16位计数值获取
 * @retval uint32_t 16bits计数值
 */
uint32_t ATIM3_Mode0_Cnt16Get(void)
{
    return ((READ_REG(ATIM3_MODE0->CNT)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式0 32位计数器初值设置
 * @param  [in] u32Data 32位初值
 * @retval None
 */
void ATIM3_Mode0_Cnt32Set(uint32_t u32Data)
{
    WRITE_REG(ATIM3_MODE0->CNT32, u32Data);
}

/**
 * @brief  ATIM3 模式0 32位计数值获取
 * @retval uint32_t 32bits计数值
 */
uint32_t ATIM3_Mode0_Cnt32Get(void)
{
    return (READ_REG(ATIM3_MODE0->CNT32));
}

/**
 * @brief  ATIM3 模式0端口输出使能
 * @retval None
 */
void ATIM3_Mode0_OutputEnable(void)
{
    SET_REG32_BIT(ATIM3_MODE0->DTR, ATIM3_MODE0_DTR_MOE);
}
/**
 * @brief  ATIM3 模式0端口输出禁止
 * @retval None
 */
void ATIM3_Mode0_OutputDisable(void)
{
    CLR_REG16_BIT(ATIM3_MODE0->DTR, ATIM3_MODE0_DTR_MOE);
}

/**
 * @brief  ATIM3 模式0翻转使能
 * @retval None
 */
void ATIM3_Mode0_TOGEnable(void)
{
    SET_REG32_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_TOGEN);
}

/**
 * @brief  ATIM3 模式0翻转禁止
 * @retval None
 */
void ATIM3_Mode0_TOGDisable(void)
{
    CLR_REG32_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_TOGEN);
}
/**
 * @brief  ATIM3 模式1 初始化配置
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_mode1_init_t
 * @retval None
 */
void ATIM3_Mode1_Init(stc_atim3_mode1_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_MODE | ATIM3_MODE1_M1CR_PRS | ATIM3_MODE1_M1CR_CT | ATIM3_MODE1_M1CR_ONESHOT,
               pstcCfg->u32WorkMode | pstcCfg->u32PRS | pstcCfg->u32CountClockSelect | pstcCfg->u32ShotMode);
}

/**
 * @brief  ATIM3 模式1 PWC 输入配置
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_pwc_input_init_t
 * @retval None
 */
void ATIM3_Mode1_InputConfig(stc_atim3_pwc_input_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE1->MSCR, ATIM3_MODE1_MSCR_TS | ATIM3_MODE1_MSCR_IA0S | ATIM3_MODE1_MSCR_IB0S,
               pstcCfg->u32IA0Select | pstcCfg->u32IB0Select | pstcCfg->u32TsSelect);

    if (ATIM3_M1_FLTR_FLTA0_B0_ET_NONE != pstcCfg->u32FltIA0)
    {
        SET_REG_BIT(ATIM3_MODE1->CR0, ATIM3_MODE1_CR0_CSA);
    }
    if (ATIM3_M1_FLTR_FLTA0_B0_ET_NONE != pstcCfg->u32FltIB0)
    {
        SET_REG_BIT(ATIM3_MODE1->CR0, ATIM3_MODE1_CR0_CSB);
    }

    MODIFY_REG(ATIM3_MODE1->FLTR, ATIM3_MODE1_FLTR_FLTA0 | ATIM3_MODE1_FLTR_FLTB0 | ATIM3_MODE1_FLTR_FLTET | ATIM3_MODE1_FLTR_ETP,
               pstcCfg->u32FltIA0 | (pstcCfg->u32FltIB0 << ATIM3_MODE1_FLTR_FLTB0_Pos) | (pstcCfg->u32FltETR << ATIM3_MODE1_FLTR_FLTET_Pos) | pstcCfg->u32ETR);
}

/**
 * @brief  ATIM3 模式1 PWC测量边沿起始结束选择(周期)
 * @param  [in] u32DetectEdgeSel 测量起始和结束边沿选择 @ref ATIM3_Mode1_PWC_Start_End_Edge
 * @retval None
 */
void ATIM3_Mode1_PWCEdgeSelect(uint32_t u32DetectEdgeSel)
{
    MODIFY_REG(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_EDG2ND | ATIM3_MODE1_M1CR_EDG1ST, u32DetectEdgeSel);
}

/**
 * @brief  ATIM3 模式1 启动运行
 * @retval None
 */
void ATIM3_Mode1_Run(void)
{
    SET_REG_BIT(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_CTEN);
}

/**
 * @brief  ATIM3 模式1 停止运行
 * @retval None
 */
void ATIM3_Mode1_Stop(void)
{
    CLR_REG_BIT(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_CTEN);
}

/**
 * @brief  ATIM3 模式1 16位计数器初值设置
 * @param  [in] u16Data CNT 16位初值
 * @retval None
 */
void ATIM3_Mode1_Cnt16Set(uint32_t u16Data)
{
    WRITE_REG(ATIM3_MODE1->CNT, (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式1 16位计数值获取
 * @retval uint32_t 16bits计数值
 */
uint32_t ATIM3_Mode1_Cnt16Get(void)
{
    return ((READ_REG(ATIM3_MODE1->CNT)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式1 脉冲宽度测量结果数值获取
 * @retval uint32_t 16bits脉冲宽度测量结果
 */
uint32_t ATIM3_Mode1_PWCCapValueGet(void)
{
    return ((READ_REG(ATIM3_MODE1->CCR0A)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式23 初始化配置
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_mode23_init_t
 * @retval None
 */
void ATIM3_Mode23_Init(stc_atim3_mode23_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->M23CR,
               ATIM3_MODE23_M23CR_MODE | ATIM3_MODE23_M23CR_DIR | ATIM3_MODE23_M23CR_PRS | ATIM3_MODE23_M23CR_CT | ATIM3_MODE23_M23CR_COMP
                   | ATIM3_MODE23_M23CR_PWM2S | ATIM3_MODE23_M23CR_ONESHOT | ATIM3_MODE23_M23CR_URS,
               pstcCfg->u32WorkMode | pstcCfg->u32CountDir | pstcCfg->u32PRS | pstcCfg->u32CountClockSelect | pstcCfg->u32PWMTypeSelect
                   | pstcCfg->u32PWM2sSelect | pstcCfg->u32ShotMode | pstcCfg->u32URSSelect);
}

/**
 * @brief  ATIM3 模式23 启动运行
 * @retval None
 */
void ATIM3_Mode23_Run(void)
{
    SET_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_CTEN);
}

/**
 * @brief  ATIM3 模式23 停止运行
 * @retval None
 */
void ATIM3_Mode23_Stop(void)
{
    CLR_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_CTEN);
}

/**
 * @brief  ATIM3 模式23 手动PWM输出使能
 * @retval None
 */
void ATIM3_Mode23_ManualPWMOutputEnable(void)
{
    SET_REG_BIT(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_MOE);
}

/**
 * @brief  ATIM3 模式23 手动PWM输出禁止
 * @retval None
 */
void ATIM3_Mode23_ManualPWMOutputDisable(void)
{
    CLR_REG_BIT(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_MOE);
}

/**
 * @brief  ATIM3 模式23 自动PWM输出使能
 * @retval None
 */
void ATIM3_Mode23_AutoPWMOutputEnable(void)
{
    SET_REG_BIT(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_AOE);
}

/**
 * @brief  ATIM3 模式23 自动PWM输出禁止
 * @retval None
 */
void ATIM3_Mode23_AutoPWMOutputDisable(void)
{
    CLR_REG_BIT(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_AOE);
}

/**
 * @brief  ATIM3 模式23 重载(周期)缓存使能
 * @retval None
 */
void ATIM3_Mode23_ARRBufferEnable(void)
{
    SET_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_BUFPEN);
}

/**
 * @brief  ATIM3 模式23 重载(周期)缓存禁止
 * @retval None
 */
void ATIM3_Mode23_ARRBufferDisable(void)
{
    CLR_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_BUFPEN);
}

/**
 * @brief  ATIM3 模式23 重载值设置
 * @param  [in] u16Data 16bits重载值
 * @retval None
 */
void ATIM3_Mode23_ARRSet(uint16_t u16Data)
{
    WRITE_REG(ATIM3_MODE23->ARR, (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式23 重载值获取
 * @retval uint32_t: 16bit重载值
 */
uint32_t ATIM3_Mode23_GetARR(void)
{
    return ((READ_REG(ATIM3_MODE23->ARR)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式23 16位计数器初值设置
 * @param  [in] u16Data 16位初值
 * @retval None
 */
void ATIM3_Mode23_Cnt16Set(uint16_t u16Data)
{
    WRITE_REG(ATIM3_MODE23->CNT, (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式23 16位计数值获取
 * @retval uint32_t: 16bits计数值
 */
uint32_t ATIM3_Mode23_Cnt16Get(void)
{
    return ((READ_REG(ATIM3_MODE23->CNT)) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式23 通道CHxA/CHxB比较值设置(CCRxA/CCRxB/CCR)
 * @param  [in] u32Channel ATIM3 通道 @ref ATIM3_Mode23_CCRxx_Channel
 * @param  [in] u16Data CCRxA/CCRxB 16位比较值
 * @retval None
 */
void ATIM3_Mode23_ChannelCompareValueSet(uint32_t u32Channel, uint16_t u16Data)
{
    WRITE_REG(*(&ATIM3_MODE23->CCR0A + u32Channel), (u16Data & 0xFFFFu));
}

/**
 * @brief  ATIM3 模式23 通道CHxA/CHxB捕获值读取、CCR3寄存器值读取(CCRxA/CCRxB/CCR3)
 * @param  [in] u32Channel ATIM3 通道 @ref ATIM3_Mode23_CCRxx_Channel
 * @retval uint32_t 16 bits CCRxA/CCRxB捕获值
 */
uint32_t ATIM3_Mode23_ChannelCaptureValueGet(uint32_t u32Channel)
{
    return ((READ_REG(*(&ATIM3_MODE23->CCR0A + u32Channel))) & 0xFFFFu);
}

/**
 * @brief  ATIM3 模式23 PWM互补输出模式下，GATE功能选择,只有在PWM互补输出时有效
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_gate_init_t
 * @retval None
 */
void ATIM3_Mode23_GateFuncSel(stc_atim3_m23_gate_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_CSG | ATIM3_MODE23_M23CR_CRG | ATIM3_MODE23_M23CR_CFG,
               pstcCfg->u32GateFuncSelect | pstcCfg->u32GateRiseCap | pstcCfg->u32GateFallCap);
}

/**
 * @brief  ATIM3 模式23 主从触发配置
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_master_slave_init_t
 * @retval None
 */
void ATIM3_Mode23_MasterSlaveTrigSet(stc_atim3_m23_master_slave_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->MSCR, ATIM3_MODE23_MSCR_MSM | ATIM3_MODE23_MSCR_MMS | ATIM3_MODE23_MSCR_SMS | ATIM3_MODE23_MSCR_TS,
               pstcCfg->u32MasterSlaveSelect | pstcCfg->u32MasterSrc | pstcCfg->u32SlaveModeSelect | pstcCfg->u32TsSelect);
}

/**
 * @brief  ATIM3 模式23 IA0输入选择
 * @param  [in] u32Ia0Sel CH0A输入通道选择 @ref ATIM3_Mode23_IA0_IN_Sel
 * @retval None
 */
void ATIM3_Mode23_MSCRIA0Sel(uint32_t u32Ia0Sel)
{
    MODIFY_REG(ATIM3_MODE23->MSCR, ATIM3_MODE23_MSCR_IA0S, u32Ia0Sel);
}

/**
 * @brief  ATIM3 模式23 IB0输入选择
 * @param  [in] u32Ib0Sel CH0B输入通道选择 @ref ATIM3_Mode23_IB0_IN_Sel
 * @retval None
 */
void ATIM3_Mode23_MSCRIB0Sel(uint32_t u32Ib0Sel)
{
    MODIFY_REG(ATIM3_MODE23->MSCR, ATIM3_MODE23_MSCR_IB0S, u32Ib0Sel);
}

/**
 * @brief  ATIM3 模式23 通道0/1/2 CHxA输出设置
 * @param  [in] u32Channel 通道序号 @ref ATIM3_Mode23_CH_Sel
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_compare_init_t
 * @retval None
 */
void ATIM3_Mode23_PortOutputCHxAConfig(uint32_t u32Channel, stc_atim3_m23_compare_init_t *pstcCfg)
{
    MODIFY_REG(*(&ATIM3_MODE23->CRCH0 + u32Channel), ATIM3_MODE23_CRCH0_CSA | ATIM3_MODE23_CRCH0_BUFEA,
               pstcCfg->u32CHxCompareCap | pstcCfg->u32CHxCompareBufEn);

    MODIFY_REG(ATIM3_MODE23->FLTR,
               (ATIM3_MODE23_FLTR_OCMA0_FLTA0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (ATIM3_MODE23_FLTR_CCPA0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)),
               (pstcCfg->u32CHxCompareModeCtrl << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (pstcCfg->u32CHxPolarity << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)));

    MODIFY_REG(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_CIS, pstcCfg->u32CHxCompareIntSelect);
}

/**
 * @brief  ATIM3 模式23 通道0/1/2 CHxB输出设置
 * @param  [in] u32Channel 通道序号 @ref ATIM3_Mode23_CH_Sel
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_compare_init_t
 * @retval None
 */
void ATIM3_Mode23_PortOutputCHxBConfig(uint32_t u32Channel, stc_atim3_m23_compare_init_t *pstcCfg)
{
    MODIFY_REG(*(&ATIM3_MODE23->CRCH0 + u32Channel), ATIM3_MODE23_CRCH0_CSB | ATIM3_MODE23_CRCH0_BUFEB | ATIM3_MODE23_CRCH0_CISB,
               (pstcCfg->u32CHxCompareCap << 1) | (pstcCfg->u32CHxCompareBufEn << 1) | pstcCfg->u32CHxCompareIntSelect);

    MODIFY_REG(ATIM3_MODE23->FLTR,
               (ATIM3_MODE23_FLTR_OCMB0_FLTB0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (ATIM3_MODE23_FLTR_CCPB0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)),
               (pstcCfg->u32CHxCompareModeCtrl << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos + ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos))
                   | (pstcCfg->u32CHxPolarity << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos + ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos)));
}

/**
 * @brief  ATIM3 模式23 通道0/1/2 CHxA输入设置
 * @param  [in] u32Channel 通道序号 @ref ATIM3_Mode23_CH_Sel
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_input_init_t
 * @retval None
 */
void ATIM3_Mode23_PortInputCHxAConfig(uint32_t u32Channel, stc_atim3_m23_input_init_t *pstcCfg)
{
    MODIFY_REG(*(&ATIM3_MODE23->CRCH0 + u32Channel), ATIM3_MODE23_CRCH0_CSA | ATIM3_MODE23_CRCH0_CFA_CRA_BKSA,
               pstcCfg->u32CHxCompareCap | pstcCfg->u32CHxCaptureSelect);

    MODIFY_REG(ATIM3_MODE23->FLTR,
               (ATIM3_MODE23_FLTR_OCMA0_FLTA0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (ATIM3_MODE23_FLTR_CCPA0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)),
               (pstcCfg->u32CHxInFlt << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (pstcCfg->u32CHxPolarity << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)));
}

/**
 * @brief  ATIM3 模式23 通道0/1/2 CHxB输入设置
 * @param  [in] u32Channel 通道序号 @ref ATIM3_Mode23_CH_Sel
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_input_init_t
 * @retval None
 */
void ATIM3_Mode23_PortInputCHxBConfig(uint32_t u32Channel, stc_atim3_m23_input_init_t *pstcCfg)
{
    MODIFY_REG(*(&ATIM3_MODE23->CRCH0 + u32Channel), ATIM3_MODE23_CRCH0_CSB | ATIM3_MODE23_CRCH0_CFB_CRB_BKSB,
               (pstcCfg->u32CHxCompareCap << 1) | (pstcCfg->u32CHxCaptureSelect << ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Msk));

    MODIFY_REG(ATIM3_MODE23->FLTR,
               (ATIM3_MODE23_FLTR_OCMB0_FLTB0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos))
                   | (ATIM3_MODE23_FLTR_CCPB0 << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)),
               (pstcCfg->u32CHxInFlt << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos + ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos))
                   | (pstcCfg->u32CHxPolarity << (u32Channel * ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos + ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos)));
}

/**
 * @brief  ATIM3 模式23 ERT输入控制
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_etr_input_init_t
 * @retval None
 */
void ATIM3_Mode23_ETRInputConfig(stc_atim3_m23_etr_input_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->FLTR, ATIM3_MODE23_FLTR_ETP | ATIM3_MODE23_FLTR_FLTET,
               pstcCfg->u32ETRPolarity | (pstcCfg->u32ETRFlt << ATIM3_MODE23_FLTR_FLTET_Pos));
}

/**
 * @brief  ATIM3 模式23 刹车BK输入控制
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_bk_input_init_t
 * @retval None
 */
void ATIM3_Mode23_BrakeInputConfig(stc_atim3_m23_bk_input_init_t *pstcBkCfg)
{
    MODIFY_REG(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_BKE | ATIM3_MODE23_DTR_VCE | ATIM3_MODE23_DTR_SAFEEN,
               pstcBkCfg->u32EnBrake | pstcBkCfg->u32EnVCBrake | pstcBkCfg->u32EnSafetyBk);

    MODIFY_REG(ATIM3_MODE23->FLTR, ATIM3_MODE23_FLTR_BKP | ATIM3_MODE23_FLTR_FLTBK,
               pstcBkCfg->u32BrakePolarity | (pstcBkCfg->u32BrakeFlt << ATIM3_MODE23_FLTR_FLTBK_Pos));
}

/**
 * @brief  ATIM3 模式23 刹车BK端口状态控制
 * @param  [in] u32Channel    通道序号 @ref ATIM3_Mode23_CH_Sel
 * @param  [in] u32ChxaStatus CHxA端口 @ref ATIM3_Mode23_Brake_Port_Out_Level
 * @param  [in] u32ChxbStatus CHxB端口 @ref ATIM3_Mode23_Brake_Port_Out_Level
 * @retval None
 */
void ATIM3_Mode23_BrakePortStatusConfig(uint32_t u32Channel, uint32_t u32ChxaStatus, uint32_t u32ChxbStatus)
{
    MODIFY_REG(*(&ATIM3_MODE23->CRCH0 + u32Channel), ATIM3_MODE23_CRCH0_CFA_CRA_BKSA | ATIM3_MODE23_CRCH0_CFB_CRB_BKSB,
               u32ChxaStatus | (u32ChxbStatus << ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Msk));
}

/**
 * @brief  ATIM3 模式23 死区功能
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_dt_init_t
 * @retval None
 */
void ATIM3_Mode23_DTConfig(stc_atim3_m23_dt_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->DTR, ATIM3_MODE23_DTR_DTEN | ATIM3_MODE23_DTR_DTR,
               (((uint32_t)pstcCfg->bEnDeadTime) << ATIM3_MODE23_DTR_DTEN_Pos) | (pstcCfg->u32DeadTimeValue & 0xFF));
}

/**
 * @brief  ATIM3 模式23 触发ADC控制
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_adc_trig_init_t
 * @retval None
 */
void ATIM3_Mode23_TrigADCConfig(stc_atim3_m23_adc_trig_init_t *pstcCfg)
{
    MODIFY_REG(
        ATIM3_MODE23->ADTR,
        ATIM3_MODE23_ADTR_ADTE | ATIM3_MODE23_ADTR_UEVE | ATIM3_MODE23_ADTR_CMA0E | ATIM3_MODE23_ADTR_CMA1E | ATIM3_MODE23_ADTR_CMA2E | ATIM3_MODE23_ADTR_CMB0E
            | ATIM3_MODE23_ADTR_CMB1E | ATIM3_MODE23_ADTR_CMB2E,
        ((uint32_t)pstcCfg->bEnTrigADC) << ATIM3_MODE23_ADTR_ADTE_Pos | ((uint32_t)pstcCfg->bEnUevTrigADC) << ATIM3_MODE23_ADTR_UEVE_Pos
            | ((uint32_t)pstcCfg->bEnCH0ACmpTrigADC) << ATIM3_MODE23_ADTR_CMA0E_Pos | ((uint32_t)pstcCfg->bEnCH0BCmpTrigADC) << ATIM3_MODE23_ADTR_CMB0E_Pos
            | ((uint32_t)pstcCfg->bEnCH1ACmpTrigADC) << ATIM3_MODE23_ADTR_CMA1E_Pos | ((uint32_t)pstcCfg->bEnCH1BCmpTrigADC) << ATIM3_MODE23_ADTR_CMB1E_Pos
            | ((uint32_t)pstcCfg->bEnCH2ACmpTrigADC) << ATIM3_MODE23_ADTR_CMA2E_Pos | ((uint32_t)pstcCfg->bEnCH2BCmpTrigADC) << ATIM3_MODE23_ADTR_CMB2E_Pos);
}

/**
 * @brief  ATIM3 模式23 重复周期设置
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_rcr_init_t
 * @retval None
 */
void ATIM3_Mode23_SetRepeatPeriod(stc_atim3_m23_rcr_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->RCR, ATIM3_MODE23_RCR_UND | ATIM3_MODE23_RCR_OV | ATIM3_MODE23_RCR_RCR,
               pstcCfg->u32EnUnderFlowMask | pstcCfg->u32EnOverFLowMask | pstcCfg->u32RepeatCountNum);
}

/**
 * @brief  ATIM3 模式23 OCREF清除功能
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_atim3_m23_ocref_clr_init_t
 * @retval None
 */
void ATIM3_Mode23_OCRefClr(stc_atim3_m23_ocref_clr_init_t *pstcCfg)
{
    MODIFY_REG(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_OCCE | ATIM3_MODE23_M23CR_OCCS,
               ((uint32_t)pstcCfg->u32OCRefClearSrcSelect) << ATIM3_MODE23_M23CR_OCCE_Pos | pstcCfg->u32OCRefClearSrcSelect);
}

/**
 * @brief  ATIM3 模式23 CH0A通道0A捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH0ASwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH0, ATIM3_MODE23_CRCH0_CCGA);
}

/**
 * @brief  ATIM3 模式23 CH0B通道0B捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH0BSwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH0, ATIM3_MODE23_CRCH0_CCGB);
}

/**
 * @brief  ATIM3 模式23 CH1A通道1A捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH1ASwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH1, ATIM3_MODE23_CRCH1_CCGA);
}

/**
 * @brief  ATIM3 模式23 CH1B通道1B捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH1BSwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH1, ATIM3_MODE23_CRCH1_CCGB);
}

/**
 * @brief  ATIM3 模式23 CH2A通道2A捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH2ASwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH2, ATIM3_MODE23_CRCH2_CCGA);
}

/**
 * @brief  ATIM3 模式23 CH2B通道2B捕获比较软件触发
 * @retval None
 */
void ATIM3_Mode23_EnableCH2BSwTrigCaptureCompare(void)
{
    SET_REG_BIT(ATIM3_MODE23->CRCH2, ATIM3_MODE23_CRCH2_CCGB);
}

/**
 * @brief  ATIM3 模式23 软件更新使能
 * @retval None
 */
void ATIM3_Mode23_EnableSoftwareUev(void)
{
    SET_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_UG);
}

/**
 * @brief  ATIM3 模式23 软件触发使能
 * @retval None
 */
void ATIM3_Mode23_EnableSoftwareTrig(void)
{
    SET_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_TG);
}

/**
 * @brief  ATIM3 模式23 软件刹车使能
 * @retval None
 */
void ATIM3_Mode23_EnableSoftwareBrake(void)
{
    SET_REG_BIT(ATIM3_MODE23->M23CR, ATIM3_MODE23_M23CR_BG);
}

/**
 * @brief  ATIM3 模式23 获取模式0/1/2/3 中断标志
 * @param  u32InterruptFlagTypes ATIMx中断标志类型 @ref ATIM3_INT_Status_Flags
 * @retval boolean_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t ATIM3_IntFlagGet(uint32_t u32InterruptFlagTypes)
{
    return READ_REG32_BIT(ATIM3_MODE23->IFR, u32InterruptFlagTypes) ? TRUE : FALSE;
}

/**
 * @brief  ATIM3 模式23 清除模式0/1/2/3 中断标志
 * @param  u32InterruptFlagTypes ATIMx中断标志类型 @ref ATIM3_INT_Status_Flags
 * @retval None
 */
void ATIM3_IntFlagClear(uint32_t u32InterruptFlagTypes)
{
    CLR_REG_BIT(ATIM3_MODE23->ICLR, u32InterruptFlagTypes);
}

/**
 * @brief  ATIM3 模式23 中断所有标志清除
 * @retval None
 */
void ATIM3_IntFlagClearAll(void)
{
    CLR_REG_BIT(ATIM3_MODE23->ICLR, 0x7FFFDu);
}

/**
 * @brief  ATIM3 模式0 中断使能
 * @retval None
 */
void ATIM3_Mode0_IntEnable(void)
{
    SET_REG_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_UIE);
}

/**
 * @brief  ATIM3 模式0 中断禁止
 * @retval None
 */
void ATIM3_Mode0_IntDisable(void)
{
    CLR_REG_BIT(ATIM3_MODE0->M0CR, ATIM3_MODE0_M0CR_UIE);
}

/**
 * @brief  ATIM3 模式1 中断使能
 * @param  u32InterruptTypes 中断类型 @ref ATIM3_Mode1_INT_Request
 * @retval None
 */
void ATIM3_Mode1_IntEnable(uint32_t u32InterruptTypes)
{
    if (u32InterruptTypes & ATIM3_M1_INT_UI)
    {
        SET_REG_BIT(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_UIE);
    }
    if (u32InterruptTypes & ATIM3_M1_INT_CA0)
    {
        SET_REG_BIT(ATIM3_MODE1->CR0, ATIM3_MODE1_CR0_CIEA);
    }
}

/**
 * @brief  ATIM3 模式1 中断禁止
 * @param  u32InterruptTypes 中断类型 @ref ATIM3_Mode1_INT_Request
 * @retval None
 */
void ATIM3_Mode1_IntDisable(uint32_t u32InterruptTypes)
{
    if (u32InterruptTypes & ATIM3_M1_INT_UI)
    {
        CLR_REG_BIT(ATIM3_MODE1->M1CR, ATIM3_MODE1_M1CR_UIE);
    }
    if (u32InterruptTypes & ATIM3_M1_INT_CA0)
    {
        CLR_REG_BIT(ATIM3_MODE1->CR0, ATIM3_MODE1_CR0_CIEA);
    }
}

/**
 * @brief  ATIM3 模式23 中断使能
 * @param  u32InterruptTypes 中断类型 @ref ATIM3_Mode23_INT_Request
 * @retval None
 */
void ATIM3_Mode23_IntEnable(uint32_t u32InterruptTypes)
{
    uint32_t u32Types = 0;

    if (INTERRUPT_M23CR_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_M23CR_MASK;
        SET_REG_BIT(ATIM3_MODE23->M23CR, u32Types);
    }

    if (INTERRUPT_CRCH0_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH0_MASK;
        SET_REG_BIT(ATIM3_MODE23->CRCH0, u32Types);
    }

    if (INTERRUPT_CRCH1_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH1_MASK;
        SET_REG_BIT(ATIM3_MODE23->CRCH1, u32Types << 2);
    }

    if (INTERRUPT_CRCH2_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH2_MASK;
        SET_REG_BIT(ATIM3_MODE23->CRCH2, u32Types << 4);
    }
}

/**
 * @brief  ATIM3 模式23 中断禁止
 * @param  u32InterruptTypes 中断类型 @ref ATIM3_Mode23_INT_Request
 * @retval None
 */
void ATIM3_Mode23_IntDisable(uint32_t u32InterruptTypes)
{
    uint32_t u32Types = 0;

    if (INTERRUPT_M23CR_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_M23CR_MASK;
        CLR_REG_BIT(ATIM3_MODE23->M23CR, u32Types);
    }

    if (INTERRUPT_CRCH0_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH0_MASK;
        CLR_REG_BIT(ATIM3_MODE23->CRCH0, u32Types);
    }

    if (INTERRUPT_CRCH1_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH1_MASK;
        CLR_REG_BIT(ATIM3_MODE23->CRCH1, u32Types << 2);
    }

    if (INTERRUPT_CRCH2_ID & u32InterruptTypes)
    {
        u32Types = u32InterruptTypes & INTERRUPT_CRCH2_MASK;
        CLR_REG_BIT(ATIM3_MODE23->CRCH2, u32Types << 4);
    }
}

/**
 * @brief  模式0结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_atim3_mode0_init_t
 * @retval None
 */
void ATIM3_Mode0_StcInit(stc_atim3_mode0_init_t *pstcInit)
{
    pstcInit->u32WorkMode         = ATIM3_M0_M0CR_WORK_MODE_TIMER;
    pstcInit->u32CountClockSelect = ATIM3_M0_M0CR_CT_PCLK;
    pstcInit->u32CountMode        = ATIM3_M0_M0CR_MD_32BIT_FREE;
    pstcInit->u32PRS              = ATIM3_M0_M0CR_ATIM3CLK_PRS1;
    pstcInit->u32EnTog            = ATIM3_M0_M0CR_TOG_ON;
    pstcInit->u32EnGate           = ATIM3_M0_M0CR_GATE_OFF;
    pstcInit->u32GatePolar        = ATIM3_M0_M0CR_GATE_POLAR_HIGH;
}
/**
 * @brief  模式1结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_atim3_mode1_init_t
 * @retval None
 */
void ATIM3_Mode1_StcInit(stc_atim3_mode1_init_t *pstcInit)
{
    pstcInit->u32WorkMode         = ATIM3_M1_M1CR_WORK_MODE_PWC;
    pstcInit->u32PRS              = ATIM3_M1_M1CR_ATIM3CLK_PRS1;
    pstcInit->u32CountClockSelect = ATIM3_M1_M1CR_CT_PCLK;
    pstcInit->u32ShotMode         = ATIM3_M1_M1CR_SHOT_CYCLE;
}
/**
 * @brief  模式23结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_atim3_mode23_init_t
 * @retval None
 */
void ATIM3_Mode23_StcInit(stc_atim3_mode23_init_t *pstcInit)
{
    pstcInit->u32WorkMode         = ATIM3_M0_M0CR_WORK_MODE_TIMER;
    pstcInit->u32CountDir         = ATIM3_M23_M23CR_DIR_UP_CNT;
    pstcInit->u32PRS              = ATIM3_M23_M23CR_ATIM3CLK_PRS1;
    pstcInit->u32CountClockSelect = ATIM3_M23_M23CR_CT_PCLK;
    pstcInit->u32PWMTypeSelect    = ATIM3_M23_M23CR_COMP_PWM_INDEPT;
    pstcInit->u32PWM2sSelect      = ATIM3_M23_M23CR_PWM2S_COMPARE_SINGLE_POINT;
    pstcInit->u32ShotMode         = ATIM3_M23_M23CR_SHOT_CYCLE;
    pstcInit->u32URSSelect        = ATIM3_M23_M23CR_URS_OV_UND_UG_RST;
}

/**
 * @brief  模式1 PWC输入配置初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_pwc_input_init_t
 * @retval None
 */
void ATIM3_Mode1_InputStcInit(stc_atim3_pwc_input_init_t *pstcCfg)
{
    pstcCfg->u32TsSelect  = ATIM3_M1_MSCR_TS_ETR;
    pstcCfg->u32IA0Select = ATIM3_M1_MSCR_IA0S_CH0A;
    pstcCfg->u32IB0Select = ATIM3_M1_MSCR_IB0S_CH0B;
    pstcCfg->u32ETR       = ATIM3_M1_FLTR_ETP_POLARITY_POSITIVE;
    pstcCfg->u32FltETR    = ATIM3_M1_FLTR_FLTA0_B0_ET_NONE;
    pstcCfg->u32FltIA0    = ATIM3_M1_FLTR_FLTA0_B0_ET_NONE;
    pstcCfg->u32FltIB0    = ATIM3_M1_FLTR_FLTA0_B0_ET_NONE;
}

/**
 * @brief  模式23 主从触发配置初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_master_slave_init_t
 * @retval None
 */
void ATIM3_Mode23_MasterSlaveStcInit(stc_atim3_m23_master_slave_init_t *pstcCfg)
{
    pstcCfg->u32MasterSlaveSelect = ATIM3_M23_MSCR_MSM_SLAVE;
    pstcCfg->u32MasterSrc         = ATIM3_M23_MSCR_MMS_TRIG_SOURCE_UG;
    pstcCfg->u32SlaveModeSelect   = ATIM3_M23_MSCR_SMS_INTERNAL_CLK;
    pstcCfg->u32TsSelect          = ATIM3_M23_MSCR_TS_ETFP;
}

/**
 * @brief  模式23 通道0/1/2 CHxB输出设置初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_compare_init_t
 * @retval None
 */
void ATIM3_Mode23_CompareStcInit(stc_atim3_m23_compare_init_t *pstcCfg)
{
    pstcCfg->u32CHxCompareCap       = ATIM3_M23_CRCHx_CSA_CSB_COMPARE;
    pstcCfg->u32CHxCompareModeCtrl  = ATIM3_M23_FLTR_OCMxx_FORCE_LOW;
    pstcCfg->u32CHxPolarity         = ATIM3_M23_FLTR_CCPxx_NORMAL_IN_OUT;
    pstcCfg->u32CHxCompareBufEn     = ATIM3_M23_CRCHx_BUFEx_DISABLE;
    pstcCfg->u32CHxCompareIntSelect = ATIM3_M23_M23CR_CISA_DISABLE_INT;
}

/**
 * @brief  模式23 触发ADC控制初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_adc_trig_init_t
 * @retval None
 */
void ATIM3_Mode23_ADCTrigStcInit(stc_atim3_m23_adc_trig_init_t *pstcCfg)
{
    pstcCfg->bEnTrigADC        = FALSE;
    pstcCfg->bEnUevTrigADC     = FALSE;
    pstcCfg->bEnCH0ACmpTrigADC = FALSE;
    pstcCfg->bEnCH0BCmpTrigADC = FALSE;
    pstcCfg->bEnCH1ACmpTrigADC = FALSE;
    pstcCfg->bEnCH1BCmpTrigADC = FALSE;
    pstcCfg->bEnCH2ACmpTrigADC = FALSE;
    pstcCfg->bEnCH2BCmpTrigADC = FALSE;
}

/**
 * @brief  模式23 通道0/1/2 CHxA输入设置初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_input_init_t
 * @retval None
 */
void ATIM3_Mode23_InputStcInit(stc_atim3_m23_input_init_t *pstcCfg)
{
    pstcCfg->u32CHxCompareCap    = ATIM3_M23_CRCHx_CSA_CSB_COMPARE;
    pstcCfg->u32CHxCaptureSelect = ATIM3_M23_CRCHx_CRxCFx_CAPTURE_EDGE_DISABLE;
    pstcCfg->u32CHxInFlt         = ATIM3_M23_FLTR_FLTxx_NONE;
    pstcCfg->u32CHxPolarity      = ATIM3_M23_FLTR_CCPxx_NORMAL_IN_OUT;
}

/**
 * @brief  模式23 死区功能初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_dt_init_t
 * @retval None
 */
void ATIM3_Mode23_DTStcInit(stc_atim3_m23_dt_init_t *pstcCfg)
{
    pstcCfg->bEnDeadTime      = FALSE;
    pstcCfg->u32DeadTimeValue = 0;
}

/**
 * @brief  模式23 重复周期设置初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_rcr_init_t
 * @retval None
 */
void ATIM3_Mode23_RCRStcInit(stc_atim3_m23_rcr_init_t *pstcCfg)
{
    pstcCfg->u32EnUnderFlowMask = ATIM3_M23_RCR_OVF_INT_EVT_CNT_ENABLE;
    pstcCfg->u32EnOverFLowMask  = ATIM3_M23_RCR_UND_INT_EVT_CNT_ENABLE;
    pstcCfg->u32RepeatCountNum  = 0;
}

/**
 * @brief  模式23 刹车BK输入控制初始化
 * @param  [in] pstcCfg 初始化结构体 @ref stc_atim3_m23_bk_input_init_t
 * @retval None
 */
void ATIM3_Mode23_BKInputStcInit(stc_atim3_m23_bk_input_init_t *pstcCfg)
{
    pstcCfg->u32EnBrake       = ATIM3_M23_DTR_BKE_BRAKE_DISABLE;
    pstcCfg->u32EnVCBrake     = ATIM3_M23_DTR_VCE_BRAKE_DISABLE;
    pstcCfg->u32EnSafetyBk    = ATIM3_M23_DTR_SAFEEN_BRAKE_DISABLE;
    pstcCfg->u32BrakePolarity = ATIM3_M23_FLTR_BKP_NORMAL_IN;
    pstcCfg->u32BrakeFlt      = ATIM3_M23_FLTR_FLTxx_NONE;
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
