/**
 *******************************************************************************
 * @file  rtc.c
 * @brief This file provides firmware functions to manage the RTC
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "rtc.h"
#include "math.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RTC RTC模块驱动库
 * @brief RTC Driver Library RTC模块驱动库
 * @{
 */
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Local_Macros RTC局部宏定义
 * @{
 */
/**
 * @defgroup RTC_WPR_Value RTC WPR Value definition RTC WPR保护序列
 * @{
 */
#define RTC_UNLOCK_VALUE1 (0xCAu) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_UNLOCK_VALUE2 (0x53u) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_LOCK_VALUE    (0xFFu) /*!< 写入其他序列锁定寄存器写，除了WPR与ICR */
/**
 * @}
 */

/**
 * @defgroup RTC_Timeout RTC超时时间
 * @{
 */
#define RTC_TIMEOUT (0xFFFFu)
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
 * Local type definitions ('typedef')
 ******************************************************************************/
/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup RTC_Local_Variables RTC局部变量定义
 * @{
 */
/**
 * @brief  平年每个月最后一天日期表 BCD格式
 */
const static uint8_t au8CommonYearMonthEndDates[12] = {0x31, 0x28, 0x31, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x31};
/**
 * @}
 */
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
static en_result_t RTC_CheckBCDFormat(uint8_t u8Data, uint8_t u8Min, uint8_t u8Max);
static boolean_t   RTC_IsLeapYear(uint8_t u8Year);
/**
 * @}
 */
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup RTC_Local_Functions RTC局部函数定义
 * @{
 */

/**
 * @brief  BCD格式检查
 * @param  [in] u8Data BCD带检查数
 * @param  [in] u8Min BCD最小值
 * @param  [in] u8Max BCD最大值
 * @retval en_result_t
 *           - Ok: BCD格式正确
 *           - Error: BCD格式错误
 */
static en_result_t RTC_CheckBCDFormat(uint8_t u8Data, uint8_t u8Min, uint8_t u8Max)
{
    if (((u8Data & 0x0Fu) > 0x09u) || ((u8Data & 0xF0u) > 0x90u) || (u8Data > u8Max) || (u8Data < u8Min))
    {
        return Error;
    }
    return Ok;
}

/**
 * @brief  闰年判断
 * @param  [in] u8Year 2000年后的年份的十位和个位0~99
 * @retval boolean_t
 *           - TRUE: 是闰年
 *           - FALSE: 不是闰年
 */
static boolean_t RTC_IsLeapYear(uint8_t u8Year)
{
    uint16_t u16Year;
    u16Year = 2000u + u8Year;

    return (((u16Year % 4u == 0u) && (u16Year % 100u != 0u)) || (u16Year % 400u == 0u)) ? TRUE : FALSE;
}
/**
 * @}
 */
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup RTC_Global_Functions RTC全局函数定义
 * @{
 */

/**
 * @brief  RTC初始化
 * @param  [in] pstcRtcInit 初始化结构体指针 @ref stc_rtc_init_t
 * @retval en_result_t
 *           - Ok: 设置初始时间成功
 *           - Error: 设置初始时间失败
 */
en_result_t RTC_Init(stc_rtc_init_t *pstcRtcInit)
{
    CLR_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk);                                /* 计数停止 */
    MODIFY_REG32(RTC->CR0, RTC_CR0_AMPM_Msk, (uint32_t)pstcRtcInit->u8Format); /* 实时时钟小时的时制 */
    MODIFY_REG32(RTC->CR1, RTC_CR1_CKSEL_Msk, pstcRtcInit->u32ClockSelect);    /* 实时时钟RTC的时钟源 */

    if (Ok == RTC_DateTimeSet(&pstcRtcInit->stcRtcTime)) /* 设置初始时间 */
    {
        SET_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk); /* 计数开始 */
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  RTC写保护寄存器解锁
 * @retval None
 */
void RTC_Unlock(void)
{
    WRITE_REG32(RTC->WPR, RTC_UNLOCK_VALUE1);
    WRITE_REG32(RTC->WPR, RTC_UNLOCK_VALUE2);
}

/**
 * @brief  RTC写保护寄存器锁定
 * @retval None
 */
void RTC_Lock(void)
{
    WRITE_REG32(RTC->WPR, RTC_UNLOCK_VALUE1);
    WRITE_REG32(RTC->WPR, RTC_LOCK_VALUE);
}

/**
 * @brief  RTC使能
 * @retval None
 */
void RTC_Enable(void)
{
    SET_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk);
}

/**
 * @brief  RTC禁止
 * @retval None
 */
void RTC_Disable(void)
{
    CLR_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk);
}

/**
 * @brief  RTC计数器启动等待函数
 * @note   如启动RTC计数器后立即进入低功耗模式，进入低功耗模式之前需执行此函数，以确保RTC已启动完成
 * @retval en_result_t
 *           - Ok: 写入成功
 *           - ErrorTimeout: 操作超时
 */
en_result_t RTC_StartWait(void)
{
    uint32_t u32Timeout;

    SET_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);

    u32Timeout = RTC_TIMEOUT;
    while (RTC_CR1_WAITF_Msk != READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk)) /* 等待直到WAITF=1 */
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    CLR_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);

    u32Timeout = RTC_TIMEOUT;
    while (RTC_CR1_WAITF_Msk == READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk)) /* 等待直到WAITF=0 */
    {
        if (0x0u == u32Timeout--)
        {
            return ErrorTimeout;
        }
    }

    return Ok;
}

/**
 * @brief  1Hz输出使能
 * @retval None
 */
void RTC_1HzEnable(void)
{
    SET_REG32_BIT(RTC->CR0, RTC_CR0_HZ1OE_Msk);
}

/**
 * @brief  1Hz输出禁止
 * @retval None
 */
void RTC_1HzDisable(void)
{
    CLR_REG32_BIT(RTC->CR0, RTC_CR0_HZ1OE_Msk);
}

/**
 * @brief  1Hz输出精度配置
 * @param  [in] u32Pricision  @ref RTC_1Hz_Pricision_Select
 * @retval None
 */
void RTC_1HzConfig(uint32_t u32Pricision)
{
    MODIFY_REG32(RTC->CR0, RTC_CR0_HZ1SEL_Msk, u32Pricision);
}

/**
 * @brief  设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX)
 * @param  [in] pstcPrd 根据结构体的定义设置PRDSEL、PRDS与PRDX @ref stc_rtc_prd_t
 * @note   设置产生周期中断的时间间隔PRDX，可设定的范围为0~63，对应0.5秒到32秒，步进为0.5秒
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_PrdConfig(stc_rtc_prd_t *pstcPrd)
{
    en_result_t enRet = Ok;
    MODIFY_REG32(RTC->CR0, RTC_CR0_PRDSEL_Msk, pstcPrd->u32PrdSelect);

    if (pstcPrd->u32PrdSelect == RTC_PRDSEL_PRDS)
    {
        MODIFY_REG32(RTC->CR0, RTC_CR0_PRDS_Msk, pstcPrd->u32Prds);
    }
    else if (pstcPrd->u32PrdSelect == RTC_PRDSEL_PRDX)
    {
        if (pstcPrd->u8Prdx >= 64u)
        {
            enRet = ErrorInvalidParameter;
            return enRet;
        }
        MODIFY_REG32(RTC->CR0, RTC_CR0_PRDX_Msk, (uint32_t)pstcPrd->u8Prdx << RTC_CR0_PRDX_Pos);
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }
    return enRet;
}

/**
 * @brief  闹钟使能
 * @param  [in] u32AlarmX 闹钟选择闹钟A或者闹钟B @ref RTC_Alarm_Channel_Select
 * @retval None
 */
void RTC_AlarmEnalbe(uint32_t u32AlarmX)
{
    if (RTC_ALM_CHA == u32AlarmX)
    {
        SET_REG32_BIT(RTC->CR2, RTC_CR2_ALMAE_Msk);
    }
    else if (RTC_ALM_CHB == u32AlarmX)
    {
        SET_REG32_BIT(RTC->CR2, RTC_CR2_ALMBE_Msk);
    }
    else
    {
        ;
    }
}

/**
 * @brief  闹钟禁止
 * @param  [in] u32AlarmX 闹钟选择闹钟A或者闹钟B @ref RTC_Alarm_Channel_Select
 * @retval None
 */
void RTC_AlarmDisalbe(uint32_t u32AlarmX)
{
    if (RTC_ALM_CHA == u32AlarmX)
    {
        CLR_REG32_BIT(RTC->CR2, RTC_CR2_ALMAE_Msk);
    }
    else if (RTC_ALM_CHB == u32AlarmX)
    {
        CLR_REG32_BIT(RTC->CR2, RTC_CR2_ALMBE_Msk);
    }
    else
    {
        ;
    }
}

/**
 * @brief  RTC闹钟时间获取
 * @param  [in] u32AlarmX 闹钟选择闹钟A或者闹钟B @ref RTC_Alarm_Channel_Select
 * @param  [in] pstcAlarmTime 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval None
 */
void RTC_AlarmTimeGet(uint32_t u32AlarmX, stc_rtc_alarmtime_t *pstcAlarmTime)
{
    uint32_t u32RegAddr;
    uint8_t  u8Hour;

    if (RTC_ALM_CHA == u32AlarmX)
    {
        u32RegAddr = (uint32_t)&RTC->ALMA;
    }
    else
    {
        u32RegAddr = (uint32_t)&RTC->ALMB;
    }

    pstcAlarmTime->u8AlarmSecond    = (uint8_t)(((*(uint32_t *)u32RegAddr) & (RTC_ALMA_SECL_Msk | RTC_ALMA_SECH_Msk)) >> RTC_ALMA_SECL_Pos);
    pstcAlarmTime->u8AlarmMinute    = (uint8_t)(((*(uint32_t *)u32RegAddr) & (RTC_ALMA_MINL_Msk | RTC_ALMA_MINH_Msk)) >> RTC_ALMA_MINL_Pos);
    u8Hour                          = (uint8_t)(((*(uint32_t *)u32RegAddr) & (RTC_ALMA_HOURL_Msk | RTC_ALMA_HOURH_Msk)) >> RTC_ALMA_HOURL_Pos);
    pstcAlarmTime->u8AlarmDayOfWeek = (uint8_t)(((*(uint32_t *)u32RegAddr) & RTC_ALMA_WEEK_Msk) >> RTC_ALMA_WEEK_Pos);
    pstcAlarmTime->bAlarmMskHour    = ((*(uint32_t *)u32RegAddr) & RTC_ALMA_MSKH_Msk) ? TRUE : FALSE;
    pstcAlarmTime->bAlarmMskMinute  = ((*(uint32_t *)u32RegAddr) & RTC_ALMA_MSKM_Msk) ? TRUE : FALSE;
    pstcAlarmTime->bAlarmMskSecond  = ((*(uint32_t *)u32RegAddr) & RTC_ALMA_MSKS_Msk) ? TRUE : FALSE;

    if (RTC_FMT_24H == READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        pstcAlarmTime->u8AlarmHour = u8Hour;
    }
    else
    {
        pstcAlarmTime->u8AlarmHour = u8Hour & 0x1Fu;
        pstcAlarmTime->u8AmPm      = (u8Hour & 0x20u) ? 1u : 0u;
    }
}

/**
 * @brief  RTC闹钟设置
 * @param  [in] u32AlarmX 闹钟选择闹钟A或者闹钟B @ref RTC_Alarm_Channel_Select
 * @param  [in] pstcAlarmTime 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval en_result_t
 *         - Ok: 设置完成
 *         - ErrorInvalidParameter: 设置失败，时间BCD格式不符合
 */
en_result_t RTC_AlarmTimeSet(uint32_t u32AlarmX, stc_rtc_alarmtime_t *pstcAlarmTime)
{
    en_result_t enRet = Ok;

    uint32_t u32RegValue;
    uint32_t u32Hour;

    if (Ok != RTC_CheckBCDFormat(pstcAlarmTime->u8AlarmSecond, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }
    if (Ok != RTC_CheckBCDFormat(pstcAlarmTime->u8AlarmMinute, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }

    if (RTC_FMT_24H == READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        enRet   = RTC_CheckBCDFormat(pstcAlarmTime->u8AlarmHour, 0x00u, 0x23u); /* 24H */
        u32Hour = pstcAlarmTime->u8AlarmHour;
    }
    else
    {
        enRet   = RTC_CheckBCDFormat(pstcAlarmTime->u8AlarmHour & (~0x20u), 0x01u, 0x12u); /* 12H */
        u32Hour = pstcAlarmTime->u8AmPm ? (pstcAlarmTime->u8AlarmHour | 0x20u) : pstcAlarmTime->u8AlarmHour;
    }
    if (Ok != enRet)
    {
        return ErrorInvalidParameter;
    }

    u32RegValue = (((uint32_t)pstcAlarmTime->u8AlarmSecond << RTC_ALMA_SECL_Pos) | ((uint32_t)pstcAlarmTime->u8AlarmMinute << RTC_ALMA_MINL_Pos)
                   | ((uint32_t)u32Hour << RTC_ALMA_HOURL_Pos) | ((uint32_t)pstcAlarmTime->u8AlarmDayOfWeek << RTC_ALMA_WEEK_Pos)
                   | ((uint32_t)pstcAlarmTime->bAlarmMskSecond << RTC_ALMA_MSKS_Pos) | ((uint32_t)pstcAlarmTime->bAlarmMskMinute << RTC_ALMA_MSKM_Pos)
                   | ((uint32_t)pstcAlarmTime->bAlarmMskHour << RTC_ALMA_MSKH_Pos));

    if (RTC_ALM_CHA == u32AlarmX)
    {
        CLR_REG32_BIT(RTC->CR2, RTC_CR2_ALMAE_Msk); /* 闹钟禁止以后再设置闹钟时间 */
        WRITE_REG32(RTC->ALMA, u32RegValue);
    }
    else
    {
        CLR_REG32_BIT(RTC->CR2, RTC_CR2_ALMBE_Msk); /* 闹钟禁止以后再设置闹钟时间 */
        WRITE_REG32(RTC->ALMB, u32RegValue);
    }

    return Ok;
}

/**
 * @brief  RTC唤醒定时器使能
 * @retval None
 */
void RTC_WakeupTimerEnable(void)
{
    SET_REG32_BIT(RTC->CR2, RTC_CR2_WUTE_Msk);
}

/**
 * @brief  RTC唤醒定时器禁止
 * @retval None
 */
void RTC_WakeupTimerDisable(void)
{
    CLR_REG32_BIT(RTC->CR2, RTC_CR2_WUTE_Msk);
}

/**
 * @brief  RTC唤醒定时器时钟选择
 * @param  [in] u32Wucksel  @ref RTC_Wakeup_Timer_Clock_Select
 * @retval None
 */
void RTC_WakeupTimerClockSelect(uint32_t u32Wucksel)
{
    MODIFY_REG32(RTC->CR2, RTC_CR2_WUCKSEL_Msk, u32Wucksel);
}

/**
 * @brief  RTC唤醒定时器设置周期值
 * @param  [in] u16Cycle RTC唤醒定时器周期值 输入范围: 1~65536
 * @retval None
 */
void RTC_WakeupTimerCycleSet(uint32_t u32Cycle)
{
    MODIFY_REG32(RTC->WUTR, RTC_WUTR_ARR_Msk, (u32Cycle - 1u) << RTC_WUTR_ARR_Pos);
}

/**
 * @brief  RTC唤醒定时器获取周期值
 * @retval uint16_t RTC唤醒定时器周期值
 */
uint32_t RTC_WakeupTimerCycleGet(void)
{
    return READ_REG32(RTC->WUTR);
}

/**
 * @brief  RTC时间戳使能
 * @retval None
 */
void RTC_TimestampEnable(void)
{
    SET_REG32_BIT(RTC->CR2, RTC_CR2_TSE_Msk);
}

/**
 * @brief  RTC时间戳禁止
 * @retval None
 */
void RTC_TimestampDisable(void)
{
    CLR_REG32_BIT(RTC->CR2, RTC_CR2_TSE_Msk);
}

/**
 * @brief  RTC时间戳边沿选择
 * @param  [in] u32Edge RTC时间戳边沿选择 @ref RTC_Time_Stamp_Edge_Select
 * @retval None
 */
void RTC_TimestampEdgeSelect(uint32_t u32Edge)
{
    MODIFY_REG32(RTC->CR2, RTC_CR2_TSEDG_Msk, u32Edge);
}

/**
 * @brief  RTC时间戳时间读取
 * @param  [in] pstcTs RTC时间戳读取指针 @ref stc_rtc_ts_t
 * @retval None
 */
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs)
{
    uint8_t u8Hour;

    pstcTs->u8Second    = (uint8_t)((RTC->TSTR & (RTC_TSTR_SECL_Msk | RTC_TSTR_SECH_Msk)) >> RTC_TSTR_SECL_Pos);
    pstcTs->u8Minute    = (uint8_t)((RTC->TSTR & (RTC_TSTR_MINL_Msk | RTC_TSTR_MINH_Msk)) >> RTC_TSTR_MINL_Pos);
    u8Hour              = (uint8_t)((RTC->TSTR & (RTC_TSTR_HOURL_Msk | RTC_TSTR_HOURH_Msk)) >> RTC_TSTR_HOURL_Pos);
    pstcTs->u8DayOfWeek = (uint8_t)((RTC->TSDR & RTC_TSDR_WEEK_Msk) >> RTC_TSDR_WEEK_Pos);
    pstcTs->u8Day       = (uint8_t)((RTC->TSDR & (RTC_TSDR_DAYL_Msk | RTC_TSDR_DAYH_Msk)) >> RTC_TSDR_DAYL_Pos);
    pstcTs->u8Month     = (uint8_t)((RTC->TSDR & RTC_TSDR_MON_Msk) >> RTC_TSDR_MON_Pos);

    if (RTC_FMT_24H == READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        pstcTs->u8Hour = u8Hour;
    }
    else
    {
        pstcTs->u8Hour = u8Hour & 0x1Fu;
        pstcTs->u8AmPm = (u8Hour & 0x20u) ? 1u : 0u;
    }
}

/**
 * @brief  RTC读取中断标志
 * @param  [in] u32IntFlag RTC中断标记 @ref RTC_Flag_Select
 * @retval boolean_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t RTC_IntFlagGet(uint32_t u32IntFlag)
{
    return READ_REG32_BIT(RTC->IFR, u32IntFlag) ? TRUE : FALSE;
}

/**
 * @brief  RTC清除中断标志
 * @param  [in] u32IntFlag RTC中断标志 @ref RTC_Flag_Select
 * @retval None
 */
void RTC_IntFlagClear(uint32_t u32IntFlag)
{
    CLR_REG32_BIT(RTC->ICR, u32IntFlag);
}

/**
 * @brief  RTC中断使能
 * @param  [in] u32IntFlag RTC中断标记 @ref RTC_Int_Select
 * @retval None
 */
void RTC_IntEnable(uint32_t u32IntFlag)
{
    SET_REG32_BIT(RTC->IER, u32IntFlag);
}

/**
 * @brief  RTC中断禁用
 * @param  [in] u32IntFlag RTC中断标记 @ref RTC_Int_Select
 * @retval None
 */
void RTC_IntDisable(uint32_t u32IntFlag)
{
    CLR_REG32_BIT(RTC->IER, u32IntFlag);
}

/**
 * @brief  计算RTC误差补偿寄存器的值
 * @param  [in] f32CompUint: 补偿目标值，单位ppm
 * @param  [in] u16Csteps: 补偿精度选择 @ref RTC_Compen_Pricision_Select
 * @param  [out] pu16CompValue: 计算结果
 * @retval en_result_t
 *           - Ok: 计算成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CompValueCalculate(float32_t f32CompUint, uint16_t u16Csteps, uint16_t *pu16CompValue)
{
    uint16_t  u16Res  = 0;
    float32_t f32Temp = f32CompUint;

    /* 根据 u16Csteps 选择补偿精度 */
    if (u16Csteps == RTC_COMPEN_PRICISION_0P96PPM)
    {
        if ((f32CompUint < -274.66) || (f32CompUint > 212.67))
        {
            return ErrorInvalidParameter;
        }

        if (f32CompUint > -31.47125)
        {
            CLR_REG32_BIT(RTC->COMPEN, RTC_COMPEN_CSTEPS_Msk);
            f32Temp = 32 + (f32Temp / 0.9536743f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低9位 */
            u16Res &= 0x1FFu;
        }
        else
        {
            CLR_REG32_BIT(RTC->COMPEN, RTC_COMPEN_CSTEPS_Msk);
            f32Temp = 512 + ((f32Temp + 32 * 0.9536743f) / 0.9536743f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低9位 */
            u16Res &= 0x1FFu;
        }
    }

    else if (u16Csteps == RTC_COMPEN_PRICISION_0P06PPM)
    {
        if ((f32CompUint < -274.66) || (f32CompUint > 213.57))
        {
            return ErrorInvalidParameter;
        }

        if (f32CompUint > -30.51758)
        {
            SET_REG32_BIT(RTC->COMPEN, RTC_COMPEN_CSTEPS_Msk);
            f32Temp = 512 + (f32Temp / 0.0596046f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低13位 */
            u16Res &= 0x1FFFu;
        }
        else
        {
            SET_REG32_BIT(RTC->COMPEN, RTC_COMPEN_CSTEPS_Msk);
            f32Temp = 8192 + ((f32Temp + 512 * 0.0596046f) / 0.0596046f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低13位 */
            u16Res &= 0x1FFFu;
        }
    }

    else
    {
        return ErrorInvalidParameter;
    }

    *pu16CompValue = u16Res;

    return Ok;
}

/**
 * @brief  配置RTC的误差补偿寄存器
 * @param  [in] u16CompValue 对于0.96ppm精度：范围为0-511（即0x1FF）；对于0.06ppm精度：范围为0-8191（即0x1FFF）
 * @param  [in] u16Csteps 补偿精度选择 @ref RTC_Compen_Pricision_Select
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CompConfig(uint16_t u16CompValue, uint16_t u16Csteps)
{
    if (u16Csteps == RTC_COMPEN_PRICISION_0P96PPM)
    {
        if (u16CompValue > 0x1FFu)
        {
            return ErrorInvalidParameter;
        }

        MODIFY_REG32(RTC->COMPEN, RTC_COMPEN_CR_Msk, (uint32_t)u16CompValue << RTC_COMPEN_CR_Pos);
    }

    else if (u16Csteps == RTC_COMPEN_PRICISION_0P06PPM)
    {
        if (u16CompValue > 0x1FFFu)
        {
            return ErrorInvalidParameter;
        }

        MODIFY_REG32(RTC->COMPEN, RTC_COMPEN_CR_Msk, (uint32_t)u16CompValue << RTC_COMPEN_CR_Pos);
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  配置RTC的高速补偿精度参数
 * @param  [in] u32Hcomppara 补偿频率MHz @ref RTC_Hcomp_Parameter_Select
 * @note   0.06ppm补偿精度 建议配置补偿频率为32.768k的整数倍，范围为16-48M
 * @note   0.96ppm补偿精度 建议配置补偿频率为32.768k的整数倍，范围为4-48M
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_HcompConfig(uint32_t u32Hcomppara)
{
    if (u32Hcomppara > 0x2Eu)
    {
        return ErrorInvalidParameter;
    }

    MODIFY_REG32(RTC->HCOMP, RTC_HCOMP_PARA_Msk, (uint32_t)u32Hcomppara);

    return Ok;
}

/**
 * @brief  RTC时间误差补偿使能
 * @retval None
 */
void RTC_CompEnable(void)
{
    SET_REG32_BIT(RTC->COMPEN, RTC_COMPEN_EN_Msk);
}

/**
 * @brief  RTC时间误差补偿禁止
 * @retval None
 */
void RTC_CompDisable(void)
{
    CLR_REG32_BIT(RTC->COMPEN, RTC_COMPEN_EN_Msk);
}

/**
 * @brief  RTC获取时间
 * @param  [in] pstcDateTime 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval int32_t
 *           - Ok: 获取正常
 *           - ErrorTimeout: 超时错误
 */
en_result_t RTC_DateTimeRead(stc_rtc_time_t *pstcDateTime)
{
    uint32_t u32Timeout;

    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk))
    {
        SET_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);

        u32Timeout = RTC_TIMEOUT;
        while (RTC_CR1_WAITF_Msk != READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }

    pstcDateTime->u8Second = (uint8_t)RTC->SEC;
    pstcDateTime->u8Minute = (uint8_t)RTC->MIN;
    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        pstcDateTime->u8Hour = (uint8_t)RTC->HOUR;
    }
    else
    {
        pstcDateTime->u8Hour = (uint8_t)RTC->HOUR & 0x1Fu;
        pstcDateTime->u8AmPm = ((RTC->HOUR & 0x20u) ? 1u : 0u);
    }
    pstcDateTime->u8Day       = (uint8_t)RTC->DAY;
    pstcDateTime->u8DayOfWeek = (uint8_t)RTC->WEEK;
    pstcDateTime->u8Month     = (uint8_t)RTC->MON;
    pstcDateTime->u8Year      = (uint8_t)RTC->YEAR;

    CLR_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);

    u32Timeout = RTC_TIMEOUT;
    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk))
    {
        while (RTC_CR1_WAITF_Msk == READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }

    return Ok;
}

/**
 * @brief  向RTC时间寄存器写入时间
 * @param  [in] pstcDateTime 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval en_result_t
 *           - Ok: 写入正常
 *           - ErrorInvalidParameter: 参数错误
 *           - ErrorTimeout: 时间溢出错误
 */
en_result_t RTC_DateTimeSet(stc_rtc_time_t *pstcDateTime)
{
    en_result_t enRet = Ok;
    uint32_t    u32Timeout;
    uint8_t     u8MonthIndex;

    if (Ok != RTC_CheckBCDFormat(pstcDateTime->u8Second, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }
    if (Ok != RTC_CheckBCDFormat(pstcDateTime->u8Minute, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }
    if (Ok != RTC_CheckBCDFormat(pstcDateTime->u8Month, 0x01u, 0x12u))
    {
        return ErrorInvalidParameter;
    }
    if (Ok != RTC_CheckBCDFormat(pstcDateTime->u8Year, 0x00u, 0x99u))
    {
        return ErrorInvalidParameter;
    }
    if (Ok != RTC_CheckBCDFormat(pstcDateTime->u8DayOfWeek, 0x00u, 0x06u))
    {
        return ErrorInvalidParameter;
    }
    u8MonthIndex = ((pstcDateTime->u8Month & 0x10U) ? 10u : 0u) + (pstcDateTime->u8Month & 0x0Fu) - 1u;
    if (pstcDateTime->u8Month == 0x02u)
    {
        if (RTC_IsLeapYear(pstcDateTime->u8Year))
        {
            enRet = RTC_CheckBCDFormat(pstcDateTime->u8Day, 0x01u, 0x29u); /*!< 闰年2月 */
        }
        else
        {
            enRet = RTC_CheckBCDFormat(pstcDateTime->u8Day, 0x01u, 0x28u); /*!< 平年2月 */
        }
    }
    else
    {
        enRet = RTC_CheckBCDFormat(pstcDateTime->u8Day, 0x01u, au8CommonYearMonthEndDates[u8MonthIndex]);
    }
    if (Ok != enRet)
    {
        return ErrorInvalidParameter;
    }
    if (RTC_FMT_24H == READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        enRet = RTC_CheckBCDFormat(pstcDateTime->u8Hour, 0x00u, 0x23u); /*!< 24H */
    }
    else
    {
        enRet = RTC_CheckBCDFormat(pstcDateTime->u8Hour & (~0x20u), 0x01u, 0x12u); /*!< 12H */
    }
    if (Ok != enRet)
    {
        return ErrorInvalidParameter;
    }

    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk))
    {
        SET_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);
        u32Timeout = RTC_TIMEOUT;
        while (RTC_CR1_WAITF_Msk != READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }
    WRITE_REG32(RTC->SEC, (uint32_t)pstcDateTime->u8Second);
    WRITE_REG32(RTC->MIN, (uint32_t)pstcDateTime->u8Minute);
    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk))
    {
        WRITE_REG32(RTC->HOUR, (uint32_t)pstcDateTime->u8Hour); /*!< 24H */
    }
    else
    {
        WRITE_REG32(RTC->HOUR, (uint32_t)pstcDateTime->u8Hour | ((uint32_t)pstcDateTime->u8AmPm << 5u)); /*!< 12H */
    }
    WRITE_REG32(RTC->DAY, (uint32_t)pstcDateTime->u8Day);
    WRITE_REG32(RTC->MON, (uint32_t)pstcDateTime->u8Month);
    WRITE_REG32(RTC->YEAR, (uint32_t)pstcDateTime->u8Year);
    WRITE_REG32(RTC->WEEK, (uint32_t)pstcDateTime->u8DayOfWeek);

    CLR_REG32_BIT(RTC->CR1, RTC_CR1_WAIT_Msk);

    u32Timeout = RTC_TIMEOUT;
    if (READ_REG32_BIT(RTC->CR0, RTC_CR0_START_Msk))
    {
        while (RTC_CR1_WAITF_Msk == READ_REG32_BIT(RTC->CR1, RTC_CR1_WAITF_Msk))
        {
            if (0x0u == u32Timeout--)
            {
                return ErrorTimeout; /* 等待超时 */
            }
        }
    }

    enRet = Ok;
    return enRet;
}

/**
 * @brief  读取RTC当前的时间格式
 * @retval en_result_t
 *           - TRUE: 24小时制
 *           - FALSE: 12小时制
 */
boolean_t RTC_FormatGet(void)
{
    return READ_REG32_BIT(RTC->CR0, RTC_CR0_AMPM_Msk) ? TRUE : FALSE;
}

/**
 * @brief  RTC配置结构体初始化
 * @retval None
 */
void RTC_RtcStcInit(stc_rtc_init_t *pstcInit)
{
    pstcInit->u32ClockSelect         = RTC_CLK_XTL;
    pstcInit->u8Format               = RTC_FMT_12H;
    pstcInit->stcRtcTime.u8Second    = 0x0u;
    pstcInit->stcRtcTime.u8Minute    = 0x0u;
    pstcInit->stcRtcTime.u8Hour      = 0x1u;
    pstcInit->stcRtcTime.u8Day       = 0x1u;
    pstcInit->stcRtcTime.u8DayOfWeek = 0x0u;
    pstcInit->stcRtcTime.u8Month     = 0x1u;
    pstcInit->stcRtcTime.u8Year      = 0x0u;
}

/**
 * @brief  RTC中断周期类型配置结构体初始化
 * @retval None
 */
void RTC_PrdStcInit(stc_rtc_prd_t *pstcInit)
{
    pstcInit->u32PrdSelect = RTC_PRDSEL_PRDS;
    pstcInit->u32Prds      = RTC_PRDS_NONE;
    pstcInit->u8Prdx       = 0x0u;
}

/**
 * @brief  RTC闹钟时间配置结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_rtc_init_t
 * @retval None
 */
void RTC_AlarmStcInit(stc_rtc_alarmtime_t *pstcInit)
{
    pstcInit->u8AmPm           = RTC_AMPM_AM;
    pstcInit->u8AlarmSecond    = 0x0u;
    pstcInit->bAlarmMskSecond  = FALSE;
    pstcInit->u8AlarmMinute    = 0x0u;
    pstcInit->bAlarmMskMinute  = FALSE;
    pstcInit->u8AlarmHour      = 0x0u;
    pstcInit->bAlarmMskHour    = FALSE;
    pstcInit->u8AlarmDayOfWeek = RTC_ALMWEEK_NONE;
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
 *****************************************************************************/
