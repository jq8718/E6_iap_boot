/**
 *******************************************************************************
 * @file  rtc.h
 * @brief This file contains all the functions prototypes of the RTC driver
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

#ifndef __RTC_H__
#define __RTC_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_RTC RTC模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Types RTC全局类型定义
 * @{
 */

/**
 * @brief PRD中断周期类型配置
 */
typedef struct
{
    uint32_t u32PrdSelect; /*!< 时钟周期选择  @ref RTC_PRDSEL_Select */
    uint32_t u32Prds;      /*!< 设置产生中断的时间间隔  @ref RTC_PRDS_Select */
    uint8_t  u8Prdx;       /*!< 0~63,设置产生周期中断的时间间隔，(u8Prdx + 1)*0.5s */
} stc_rtc_prd_t;

/**
 * @brief 闹钟时间配置
 */
typedef struct
{
    uint8_t   u8AmPm;           /*!< 上午下午选择，仅12小时制时需要 @ref RTC_AMPM_Select */
    uint8_t   u8AlarmSecond;    /*!< 闹钟秒钟 BCD码 */
    uint8_t   u8AlarmMinute;    /*!< 闹钟分钟 BCD码 */
    uint8_t   u8AlarmHour;      /*!< 闹钟小时 BCD码 */
    uint8_t   u8AlarmDayOfWeek; /*!< 闹钟星期选择 @ref RTC_AlarmDayOfWeek_Select */
    boolean_t bAlarmMskHour;    /*!< 闹钟小时屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与时位无关 */
    boolean_t bAlarmMskMinute;  /*!< 闹钟分屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与分位无关 */
    boolean_t bAlarmMskSecond;  /*!< 闹钟秒屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与秒位无关 */
} stc_rtc_alarmtime_t;

/**
 * @brief 时间戳配置
 */
typedef struct
{
    uint8_t u8AmPm;      /*!< 上午下午选择，仅12小时制时需要 @ref RTC_AMPM_Select */
    uint8_t u8Second;    /*!< 时间：秒 BCD码 */
    uint8_t u8Minute;    /*!< 时间：分 BCD码 */
    uint8_t u8Hour;      /*!< 时间：时 BCD码 */
    uint8_t u8DayOfWeek; /*!< 时间：周 BCD码 */
    uint8_t u8Day;       /*!< 时间：日 BCD码 */
    uint8_t u8Month;     /*!< 时间：月 BCD码 */
} stc_rtc_ts_t;

/**
 * @brief RTC时钟年、月、日、时、分、秒读写结构
 */
typedef struct
{
    uint8_t u8AmPm;      /*!< 上午下午选择，仅12小时制时需要 @ref RTC_AMPM_Select */
    uint8_t u8Second;    /*!< 时间：秒 BCD码 */
    uint8_t u8Minute;    /*!< 时间：分 BCD码 */
    uint8_t u8Hour;      /*!< 时间：时 BCD码 */
    uint8_t u8DayOfWeek; /*!< 时间：周 BCD码 */
    uint8_t u8Day;       /*!< 时间：日 BCD码 */
    uint8_t u8Month;     /*!< 时间：月 BCD码 */
    uint8_t u8Year;      /*!< 时间：年 BCD码 */
} stc_rtc_time_t;

/**
 * @brief RTC配置结构体
 */
typedef struct
{
    uint8_t        u8Format;       /*!< 12h制或24h制方式选择 @ref RTC_Format_Select */
    uint32_t       u32ClockSelect; /*!< RTC时钟选择 @ref RTC_Clock_Select */
    stc_rtc_time_t stcRtcTime;     /*!< 要写入时间寄存器的时间 */
} stc_rtc_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Macros RTC全局宏定义
 * @{
 */

/**
 * @defgroup RTC_Format_Select 12h制或24h制方式选择
 * @{
 */
#define RTC_FMT_12H (0x0u)             /*!< 12小时制 */
#define RTC_FMT_24H (RTC_CR0_AMPM_Msk) /*!< 24小时制 */
/**
 * @}
 */

/**
 * @defgroup RTC_AMPM_Select 上午下午选择
 * @{
 */
#define RTC_AMPM_AM (0x0u) /*!< 上午 */
#define RTC_AMPM_PM (0x1u) /*!< 下午 */
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Select RTC时钟选择
 * @{
 */
#define RTC_CLK_XTL (0x0u)                      /*!< 外部低速时钟XTL  32.768k */
#define RTC_CLK_RCL (0x2u << RTC_CR1_CKSEL_Pos) /*!< 内部低速时钟RCL */
/**
 * @}
 */

/**
 * @defgroup RTC_PRDSEL_Select 周期中断选择
 * @{
 */
#define RTC_PRDSEL_PRDS (0x0u)               /*!< 使用PRDS所设定的周期中断事件间隔 */
#define RTC_PRDSEL_PRDX (RTC_CR0_PRDSEL_Msk) /*!< 使用PRDX所设定的周期中断事件间隔 */
/**
 * @}
 */

/**
 * @defgroup RTC_PRDS_Select RTC周期中断的时间间隔选择
 * @{
 */
#define RTC_PRDS_NONE   (0x0u) /*!< 无周期中断 */
#define RTC_PRDS_0P5S   (0x1u) /*!< 0.5s */
#define RTC_PRDS_1SEC   (0x2u) /*!< 1s */
#define RTC_PRDS_1MIN   (0x3u) /*!< 1分钟 */
#define RTC_PRDS_1HOUR  (0x4u) /*!< 1小时 */
#define RTC_PRDS_1DAY   (0x5u) /*!< 1天 */
#define RTC_PRDS_1MONTH (0x6u) /*!< 1月 */
/**
 * @}
 */

/**
 * @defgroup RTC_1Hz_Pricision_Select 1Hz普通精度与高精度输出选择
 * @{
 */
#define RTC_1HZ_NORMAL_PRICISION (0x0u)               /*!< 普通精度1Hz输出 */
#define RTC_1HZ_HIGH_PRICISION   (RTC_CR0_HZ1SEL_Msk) /*!< 高精度1Hz输出 */
/**
 * @}
 */

/**
 * @defgroup RTC_Alarm_Channel_Select RTC闹钟通道选择
 * @{
 */
#define RTC_ALM_CHA (0x0u) /*!< 闹钟A */
#define RTC_ALM_CHB (0x4u) /*!< 闹钟B */
/**
 * @}
 */

/**
 * @defgroup RTC_Wakeup_Timer_Clock_Select RTC唤醒定时器时钟选择
 * @{
 */
#define RTC_WUTR_DIV2    (0x0u)                        /*!< RTC/2 */
#define RTC_WUTR_DIV4    (0x1u << RTC_CR2_WUCKSEL_Pos) /*!< RTC/4 */
#define RTC_WUTR_DIV8    (0x2u << RTC_CR2_WUCKSEL_Pos) /*!< RTC/8 */
#define RTC_WUTR_DIV16   (0x3u << RTC_CR2_WUCKSEL_Pos) /*!< RTC/16 */
#define RTC_WUTR_SECDIV1 (0x4u << RTC_CR2_WUCKSEL_Pos) /*!< RTC_SEC/1 */
#define RTC_WUTR_SECDIV2 (0x5u << RTC_CR2_WUCKSEL_Pos) /*!< RTC_SEC/2 */
#define RTC_WUTR_SECDIV4 (0x6u << RTC_CR2_WUCKSEL_Pos) /*!< RTC_SEC/4 */
#define RTC_WUTR_SECDIV8 (0x7u << RTC_CR2_WUCKSEL_Pos) /*!< RTC_SEC/8 */
/**
 * @}
 */

/**
 * @defgroup RTC_Time_Stamp_Edge_Select RTC时间戳边沿选择
 * @{
 */
#define RTC_TS_EDGE_RISING  (0x0u)              /*!< 上升沿 */
#define RTC_TS_EDGE_FALLING (RTC_CR2_TSEDG_Msk) /*!< 下降沿 */
/**
 * @}
 */

/**
 * @defgroup RTC_Compen_Pricision_Select RTC时钟误差补偿精度选择
 * @{
 */
#define RTC_COMPEN_PRICISION_0P96PPM (0x0u)                  /*!< 补偿精度0.96ppm */
#define RTC_COMPEN_PRICISION_0P06PPM (RTC_COMPEN_CSTEPS_Msk) /*!< 补偿精度0.06ppm */
/**
 * @}
 */

/**
 * @defgroup RTC_AlarmDayOfWeek_Select RTC闹钟周内选择
 * @{
 */
#define RTC_ALMWEEK_SUNDAY    (0x01u) /*!< 周日 */
#define RTC_ALMWEEK_MONDAY    (0x02u) /*!< 周一 */
#define RTC_ALMWEEK_TUESDAY   (0x04u) /*!< 周二 */
#define RTC_ALMWEEK_WEDNESDAY (0x08u) /*!< 周三 */
#define RTC_ALMWEEK_THURSDAY  (0x10u) /*!< 周四 */
#define RTC_ALMWEEK_FRIDAY    (0x20u) /*!< 周五 */
#define RTC_ALMWEEK_SATURDAY  (0x40u) /*!< 周六 */
#define RTC_ALMWEEK_ALL       (0x7Fu) /*!< 一周全选 */
#define RTC_ALMWEEK_NONE      (0x0u)  /*!< None */
/**
 * @}
 */

/**
 * @defgroup RTC_Hcomp_Parameter_Select RTC高速补偿精度参数频率选择
 * @{
 */
#define RTC_HCOMP_PARA_4M  (0x04u << RTC_HCOMP_PARA_Pos) /*!< 4M补偿频率 */
#define RTC_HCOMP_PARA_6M  (0x06u << RTC_HCOMP_PARA_Pos) /*!< 6M补偿频率 */
#define RTC_HCOMP_PARA_8M  (0x08u << RTC_HCOMP_PARA_Pos) /*!< 8M补偿频率 */
#define RTC_HCOMP_PARA_12M (0x0Cu << RTC_HCOMP_PARA_Pos) /*!< 12M补偿频率 */
#define RTC_HCOMP_PARA_16M (0x0Fu << RTC_HCOMP_PARA_Pos) /*!< 16M补偿频率 */
#define RTC_HCOMP_PARA_20M (0x13u << RTC_HCOMP_PARA_Pos) /*!< 20M补偿频率 */
#define RTC_HCOMP_PARA_24M (0x17u << RTC_HCOMP_PARA_Pos) /*!< 24M补偿频率 */
#define RTC_HCOMP_PARA_32M (0x1Fu << RTC_HCOMP_PARA_Pos) /*!< 32M补偿频率 */
#define RTC_HCOMP_PARA_48M (0x2Eu << RTC_HCOMP_PARA_Pos) /*!< 48M补偿频率 */
/**
 * @}
 */

/**
 * @defgroup RTC_Int_Select RTC中断控制位使能选择
 * @{
 */
#define RTC_INT_ALMA (RTC_IER_ALMA_Msk)                                                                        /*!< 闹钟A中断使能 */
#define RTC_INT_ALMB (RTC_IER_ALMB_Msk)                                                                        /*!< 闹钟B中断使能 */
#define RTC_INT_WU   (RTC_IER_WU_Msk)                                                                          /*!< 定时中断使能 */
#define RTC_INT_TS   (RTC_IER_TS_Msk)                                                                          /*!< 时间戳中断使能 */
#define RTC_INT_PRD  (RTC_IER_PRD_Msk)                                                                         /*!< 周期中断使能 */
#define RTC_INT_ALL  (RTC_IER_ALMA_Msk | RTC_IER_ALMB_Msk | RTC_IER_WU_Msk | RTC_IER_TS_Msk | RTC_IER_PRD_Msk) /*!< 所有中断使能 */
/**
 * @}
 */

/**
 * @defgroup RTC_Flag_Select RTC中断标志位选择
 * @{
 */
#define RTC_FLAG_ALMA (RTC_IFR_ALMA_Msk)                                                                                           /*!< 闹钟A中断标志 */
#define RTC_FLAG_ALMB (RTC_IFR_ALMB_Msk)                                                                                           /*!< 闹钟B中断标志 */
#define RTC_FLAG_WU   (RTC_IFR_WU_Msk)                                                                                             /*!< 定时中断标志 */
#define RTC_FLAG_TS   (RTC_IFR_TS_Msk)                                                                                             /*!< 时间戳中断标志 */
#define RTC_FLAG_TSOV (RTC_IFR_TSOV_Msk)                                                                                           /*!< 时间戳溢出标志 */
#define RTC_FLAG_PRD  (RTC_IFR_PRD_Msk)                                                                                            /*!< 周期中断标志 */
#define RTC_FLAG_ALL  (RTC_IFR_ALMA_Msk | RTC_IFR_ALMB_Msk | RTC_IFR_WU_Msk | RTC_IFR_TS_Msk | RTC_IFR_TSOV_Msk | RTC_IFR_PRD_Msk) /*!< 所有中断标志 */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup RTC_Global_Functions RTC全局函数定义
 * @{
 */

en_result_t RTC_Init(stc_rtc_init_t *pstcRtcInit); /* RTC初始化 */
void        RTC_Unlock(void);                      /* RTC写保护寄存器解锁 */
void        RTC_Lock(void);                        /* RTC写保护寄存器锁定 */
void        RTC_Enable(void);                      /* RTC使能 */
void        RTC_Disable(void);                     /* RTC禁止 */

en_result_t RTC_DateTimeSet(stc_rtc_time_t *pstcDateTime);  /* 向RTC时间寄存器写入时间 */
en_result_t RTC_DateTimeRead(stc_rtc_time_t *pstcDateTime); /* RTC获取时间 */

void RTC_1HzConfig(uint32_t u32Pricision); /* RTC的1Hz输出精度配置 */
void RTC_1HzEnable(void);                  /* RTC的1Hz输出使能 */
void RTC_1HzDisable(void);                 /* RTC的1Hz输出禁止 */

en_result_t RTC_StartWait(void); /* RTC计数器启动等待函数 */

en_result_t RTC_PrdConfig(stc_rtc_prd_t *pstcPrd); /* 设置周期中断的类型及其所选类型的时间 */

void        RTC_AlarmEnalbe(uint32_t u32AlarmX);                                      /* 闹钟使能 */
void        RTC_AlarmDisalbe(uint32_t u32AlarmX);                                     /* 闹钟禁止 */
void        RTC_AlarmTimeGet(uint32_t u32AlarmX, stc_rtc_alarmtime_t *pstcAlarmTime); /* RTC闹钟中断时间获取 */
en_result_t RTC_AlarmTimeSet(uint32_t u32AlarmX, stc_rtc_alarmtime_t *pstcAlarmTime); /* RTC闹钟设置 */

void     RTC_WakeupTimerEnable(void);                     /* RTC唤醒定时器使能 */
void     RTC_WakeupTimerDisable(void);                    /* RTC唤醒定时器禁止 */
void     RTC_WakeupTimerClockSelect(uint32_t u32Wucksel); /* RTC唤醒定时器时钟选择 */
void     RTC_WakeupTimerCycleSet(uint32_t u32Cycle);      /* RTC唤醒定时器设置周期值 */
uint32_t RTC_WakeupTimerCycleGet(void);                   /* RTC唤醒定时器获取周期值 */

void RTC_TimestampEnable(void);                 /* RTC时间戳使能 */
void RTC_TimestampDisable(void);                /* RTC时间戳禁止 */
void RTC_TimestampEdgeSelect(uint32_t u32Edge); /* RTC时间戳边沿选择 */
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs);    /* RTC时间戳时间读取 */

boolean_t RTC_IntFlagGet(uint32_t u32IntFlag);   /* RTC读取中断标志 */
void      RTC_IntFlagClear(uint32_t u32IntFlag); /* RTC清除中断标志 */
void      RTC_IntEnable(uint32_t u32IntFlag);    /* RTC中断使能 */
void      RTC_IntDisable(uint32_t u32IntFlag);   /* RTC中断禁用 */

en_result_t RTC_CompValueCalculate(float32_t f32CompUint, uint16_t u16Csteps, uint16_t *pu16CompValue); /* 计算RTC误差补偿寄存器的值 */
en_result_t RTC_CompConfig(uint16_t u16CompValue, uint16_t u16Csteps);                                  /* 配置RTC的误差补偿寄存器 */
void        RTC_CompEnable(void);                                                                       /* RTC时间误差补偿使能 */
void        RTC_CompDisable(void);                                                                      /* RTC时间误差补偿禁止 */
en_result_t RTC_HcompConfig(uint32_t u32Hcomppara);                                                     /* 配置RTC的高速补偿精度参数 */

boolean_t RTC_FormatGet(void); /* 读取RTC当前的时间格式 */

void RTC_RtcStcInit(stc_rtc_init_t *pstcInit);        /* RTC配置结构体初始化 */
void RTC_PrdStcInit(stc_rtc_prd_t *pstcInit);         /* RTC中断周期类型配置结构体初始化 */
void RTC_AlarmStcInit(stc_rtc_alarmtime_t *pstcInit); /* RTC闹钟时间配置结构体初始化 */
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

#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
