/**
*******************************************************************************
* @file  hc32l021.h
* @brief Headerfile for HC32L021 series MCU
@verbatim
Change Logs:
Date             Author          Notes
2025-09-08       MADS            First version
@endverbatim
*******************************************************************************
* Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
*
* This software component is licensed by XHSC under BSD 3-Clause license
* (the "License"); You may not use this file except in compliance with the
* License. You may obtain a copy of the License at:
*                    opensource.org/licenses/BSD-3-Clause
*
*******************************************************************************
*/

#ifndef __HC32L021_H__
#define __HC32L021_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Configuration of the Cortex-M0+ Processor and Core Peripherals
******************************************************************************/
#define __CM0PLUS_REV                  1            /*!< Core revision r0p1                                                    */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __VTOR_PRESENT                 1            /*!< Vector table register supported                                       */
#define __NVIC_PRIO_BITS               2            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

/******************************************************************************
* Interrupt Number Definition
******************************************************************************/
typedef enum IRQn
{
    Reset_IRQn              = -15,    /*!<   1  Reset Vector, invoked on Power up and warm reset                                  */
    NonMaskableInt_IRQn     = -14,    /*!<   2  Non maskable Interrupt, cannot be stopped or preempted                            */
    HardFault_IRQn          = -13,    /*!<   3  Hard Fault, all classes of Fault                                                  */
    SVCall_IRQn             =  -5,    /*!<  11  System Service Call via SVC instruction                                           */
    PendSV_IRQn             =  -2,    /*!<  14  Pendable request for system service                                               */
    SysTick_IRQn            =  -1,    /*!<  15  System Tick Timer                                                                 */
    
    PORTA_IRQn          = 0 ,
    PORTB_IRQn          = 1 ,
    ATIM3_IRQn          = 5 ,
    LPUART0_IRQn        = 8 ,
    LPUART1_IRQn        = 9 ,
    SPI_IRQn            = 10,
    CTIM0_IRQn          = 14,
    CTIM1_IRQn          = 15,
    HSI2C_IRQn          = 18,
    IWDT_IRQn           = 22,
    RTC_IRQn            = 23,
    ADC_IRQn            = 24,
    VC0_IRQn            = 26,
    VC1_IRQn            = 27,
    LVD_IRQn            = 28,
    FLASH_IRQn          = 30,
    CTRIM_CLKDET_IRQn   = 31,
    
} IRQn_Type;

#include <core_cm0plus.h>
#include <stdint.h>

#define SUCCESS         (0)
#define ERROR           (-1)

#ifndef NULL
#define NULL            (0)
#endif

/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CLKDIV                    : 2;
    uint32_t RESERVED4                      : 5;
    __IO uint32_t REF                       : 1;
    uint32_t RESERVED10                     : 2;
    __IO uint32_t IBSEL                     : 2;
    uint32_t RESERVED14                     : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     : 1;
    __IO uint32_t SAM                       : 4;
    uint32_t RESERVED21                     :10;
    __IO uint32_t RSV                       : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 4;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t CH1MUX                    : 4;
    uint32_t RESERVED9                      : 1;
    __IO uint32_t CH2MUX                    : 4;
    uint32_t RESERVED14                     : 1;
    __IO uint32_t CH3MUX                    : 4;
    uint32_t RESERVED19                     :12;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr0_field_t;

typedef struct
{
    __IO uint32_t CNT                       : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult3_field_t;

typedef struct
{
    __IO uint32_t SQRIF                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t SQRIC                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_icr_field_t;

typedef struct
{
    __IO uint32_t EXT_TRIG_EN               : 4;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_adc_exttrigger_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrstart_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_atim3_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_atim3_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    __IO uint32_t OCMA1_FLTA1               : 3;
    __IO uint32_t CCPA1                     : 1;
    __IO uint32_t OCMB1_FLTB1               : 3;
    __IO uint32_t CCPB1                     : 1;
    __IO uint32_t OCMA2_FLTA2               : 3;
    __IO uint32_t CCPA2                     : 1;
    __IO uint32_t OCMB2_FLTB2               : 3;
    __IO uint32_t CCPB2                     : 1;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_atim3_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    __IO uint32_t CMA1E                     : 1;
    __IO uint32_t CMA2E                     : 1;
    __IO uint32_t CMB0E                     : 1;
    __IO uint32_t CMB1E                     : 1;
    __IO uint32_t CMB2E                     : 1;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    uint32_t RESERVED10                     : 2;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    uint32_t RESERVED10                     : 2;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_crch1_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    uint32_t RESERVED10                     : 2;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_crch2_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t CCR1A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr1a_field_t;

typedef struct
{
    __IO uint32_t CCR1B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr1b_field_t;

typedef struct
{
    __IO uint32_t CCR2A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr2a_field_t;

typedef struct
{
    __IO uint32_t CCR2B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3_mode23_ccr2b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_btim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_btim_cnt_field_t;

typedef struct
{
    __IO uint32_t CEN                       : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    __IO uint32_t TRS                       : 2;
    __IO uint32_t ETP                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_btim_cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_ier_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_icr_field_t;

typedef struct
{
    __IO uint32_t UI03                      : 1;
    __IO uint32_t TI03                      : 1;
    __IO uint32_t UI14                      : 1;
    __IO uint32_t TI14                      : 1;
    __IO uint32_t UI25                      : 1;
    __IO uint32_t TI25                      : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_btim_aifr_field_t;

typedef struct
{
    __IO uint32_t UI03                      : 1;
    __IO uint32_t TI03                      : 1;
    __IO uint32_t UI14                      : 1;
    __IO uint32_t TI14                      : 1;
    __IO uint32_t UI25                      : 1;
    __IO uint32_t TI25                      : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_btim_aicr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cnt_field_t;

typedef struct
{
    __IO uint32_t STEP                      : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t ETRFLT                    : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t SRC                       : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr0_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t AUTO                      : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr1_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_ier_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_isr_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_icr_field_t;

typedef struct
{
    __IO uint32_t FCAP                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_fcap_field_t;

typedef struct
{
    __IO uint32_t TVAL                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_tval_field_t;

typedef struct
{
    __IO uint32_t FLIM                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_flim_field_t;

typedef struct
{
    __IO uint32_t OP                        : 2;
    __IO uint32_t WAIT                      : 2;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t IE                        : 2;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t DPSTB_EN                  : 1;
    __IO uint32_t CONTP                     : 1;
    __IO uint32_t RO                        : 1;
    __IO uint32_t RSV                       :20;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
    __IO uint32_t RSV                       :16;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock0_field_t;

typedef struct
{
    __IO uint32_t LOCK_ST                   : 2;
    __IO uint32_t RSV                       :30;
} stc_flash_lock_st_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pin15_sel_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_dir_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_in_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_out_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_ads_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_bset_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_bclr_field_t;

typedef struct
{
    __IO uint32_t BCLRPIN00                 : 1;
    __IO uint32_t BCLRPIN01                 : 1;
    __IO uint32_t BCLRPIN02                 : 1;
    __IO uint32_t BCLRPIN03                 : 1;
    __IO uint32_t BCLRPIN04                 : 1;
    __IO uint32_t BCLRPIN05                 : 1;
    __IO uint32_t BCLRPIN06                 : 1;
    __IO uint32_t BCLRPIN07                 : 1;
    __IO uint32_t BCLRPIN08                 : 1;
    __IO uint32_t BCLRPIN09                 : 1;
    __IO uint32_t BCLRPIN10                 : 1;
    __IO uint32_t BCLRPIN11                 : 1;
    __IO uint32_t BCLRPIN12                 : 1;
    __IO uint32_t BCLRPIN13                 : 1;
    __IO uint32_t BCLRPIN14                 : 1;
    __IO uint32_t BCLRPIN15                 : 1;
    __IO uint32_t BSETPIN00                 : 1;
    __IO uint32_t BSETPIN01                 : 1;
    __IO uint32_t BSETPIN02                 : 1;
    __IO uint32_t BSETPIN03                 : 1;
    __IO uint32_t BSETPIN04                 : 1;
    __IO uint32_t BSETPIN05                 : 1;
    __IO uint32_t BSETPIN06                 : 1;
    __IO uint32_t BSETPIN07                 : 1;
    __IO uint32_t BSETPIN08                 : 1;
    __IO uint32_t BSETPIN09                 : 1;
    __IO uint32_t BSETPIN10                 : 1;
    __IO uint32_t BSETPIN11                 : 1;
    __IO uint32_t BSETPIN12                 : 1;
    __IO uint32_t BSETPIN13                 : 1;
    __IO uint32_t BSETPIN14                 : 1;
    __IO uint32_t BSETPIN15                 : 1;
} stc_gpio_bsetclr_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pu_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_od_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_hie_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_lie_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_rie_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_fie_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_stat_field_t;

typedef struct
{
    __IO uint32_t PIN00                     : 1;
    __IO uint32_t PIN01                     : 1;
    __IO uint32_t PIN02                     : 1;
    __IO uint32_t PIN03                     : 1;
    __IO uint32_t PIN04                     : 1;
    __IO uint32_t PIN05                     : 1;
    __IO uint32_t PIN06                     : 1;
    __IO uint32_t PIN07                     : 1;
    __IO uint32_t PIN08                     : 1;
    __IO uint32_t PIN09                     : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :14;
    __IO uint32_t IR_POL                    : 1;
    __IO uint32_t HSI2C_LSEL                : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_ctrl1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t TCLK_SEL                  : 2;
    __IO uint32_t TCLK_DIV                  : 2;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_ctrl2_field_t;

typedef struct
{
    __IO uint32_t CTIM0_E                   : 2;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t CTIM1_E                   : 2;
    uint32_t RESERVED5                      : 4;
    __IO uint32_t ATIM3_E                   : 3;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_times_field_t;

typedef struct
{
    __IO uint32_t CTIM0_C0                  : 2;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t CTIM1_C0                  : 2;
    uint32_t RESERVED5                      : 4;
    __IO uint32_t ATIM3_C0A                 : 2;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_timcps_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t PB0FLT_EN                 : 1;
    __IO uint32_t PA8FLT_EN                 : 1;
    __IO uint32_t PA0FLT_EN                 : 1;
    __IO uint32_t FCLK_DIV                  : 2;
    __IO uint32_t FCLK_SEL                  : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_fltcfg_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cnt_field_t;

typedef struct
{
    __IO uint32_t CC0M                      : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t CC1M                      : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t CC2M                      : 3;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t CC3M                      : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cmmr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t ETRFLT                    : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cr1_field_t;

typedef struct
{
    __IO uint32_t CEN                       : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    __IO uint32_t TRS                       : 2;
    __IO uint32_t ETP                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cr0_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    uint32_t RESERVED6                      : 4;
    __IO uint32_t OVTRAD                    : 1;
    __IO uint32_t C0TRAD                    : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ier_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_gtim_icr_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr0_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr1_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr2_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr3_field_t;

typedef struct
{
    __IO uint32_t MEN                       : 1;
    __IO uint32_t RST                       : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t DBGEN                     : 1;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcr_field_t;

typedef struct
{
    __IO uint32_t TDF                       : 1;
    __IO uint32_t RDF                       : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t EPF                       : 1;
    __IO uint32_t SDF                       : 1;
    __IO uint32_t NDF                       : 1;
    __IO uint32_t ALF                       : 1;
    __IO uint32_t FEF                       : 1;
    __IO uint32_t PLTF                      : 1;
    __IO uint32_t DMF                       : 1;
    uint32_t RESERVED15                     : 9;
    __IO uint32_t MBF                       : 1;
    __IO uint32_t BBF                       : 1;
    uint32_t RESERVED26                     : 5;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_msr_field_t;

typedef struct
{
    __IO uint32_t TDIE                      : 1;
    __IO uint32_t RDIE                      : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t EPIE                      : 1;
    __IO uint32_t SDIE                      : 1;
    __IO uint32_t NDIE                      : 1;
    __IO uint32_t ALIE                      : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t PLTIE                     : 1;
    __IO uint32_t DMIE                      : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t EPC                       : 1;
    __IO uint32_t SDC                       : 1;
    __IO uint32_t NDC                       : 1;
    __IO uint32_t ALC                       : 1;
    __IO uint32_t FEC                       : 1;
    __IO uint32_t PLTC                      : 1;
    __IO uint32_t DMC                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mscr_field_t;

typedef struct
{
    __IO uint32_t PRESCALE                  : 3;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t AUTOSTOP                  : 1;
    __IO uint32_t IGNACK                    : 1;
    __IO uint32_t TIMECFG                   : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t RDMO                      : 1;
    __IO uint32_t MATCFG                    : 3;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcfgr1_field_t;

typedef struct
{
    __IO uint32_t BUSIDLE                   :12;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t FILTSCL                   : 4;
    uint32_t RESERVED20                     : 3;
    __IO uint32_t FILTBPSCL                 : 1;
    __IO uint32_t FILTSDA                   : 4;
    uint32_t RESERVED28                     : 3;
    __IO uint32_t FILTBPSDA                 : 1;
} stc_hsi2c_mcfgr2_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t PINLOW                    :12;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcfgr3_field_t;

typedef struct
{
    __IO uint32_t CLKLO                     : 6;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CLKHI                     : 6;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t SETHOLD                   : 6;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t DATAVD                    : 6;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mccr0_field_t;

typedef struct
{
    __IO uint32_t CLKLO                     : 6;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CLKHI                     : 6;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t SETHOLD                   : 6;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t DATAVD                    : 6;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mccr1_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t CMD                       : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mtdr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      : 6;
    __IO uint32_t RXEMPTY                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mrdr_field_t;

typedef struct
{
    __IO uint32_t MATCH0                    : 8;
    uint32_t RESERVED8                      : 8;
    __IO uint32_t MATCH1                    : 8;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mdmr_field_t;

typedef struct
{
    __IO uint32_t SEN                       : 1;
    __IO uint32_t RST                       : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr0_field_t;

typedef struct
{
    __IO uint32_t TDF                       : 1;
    __IO uint32_t RDF                       : 1;
    __IO uint32_t AVF                       : 1;
    __IO uint32_t TAF                       : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t RSF                       : 1;
    __IO uint32_t SDF                       : 1;
    __IO uint32_t BEF                       : 1;
    __IO uint32_t FEF                       : 1;
    __IO uint32_t AM0F                      : 1;
    __IO uint32_t AM1F                      : 1;
    __IO uint32_t GCF                       : 1;
    __IO uint32_t SARF                      : 1;
    uint32_t RESERVED16                     : 8;
    __IO uint32_t SBF                       : 1;
    __IO uint32_t BBF                       : 1;
    uint32_t RESERVED26                     : 5;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_ssr_field_t;

typedef struct
{
    __IO uint32_t TDIE                      : 1;
    __IO uint32_t RDIE                      : 1;
    __IO uint32_t AVIE                      : 1;
    __IO uint32_t TAIE                      : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t RSIE                      : 1;
    __IO uint32_t SDIE                      : 1;
    __IO uint32_t BEIE                      : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t AM0IE                     : 1;
    __IO uint32_t AM1IE                     : 1;
    __IO uint32_t GCIE                      : 1;
    __IO uint32_t SARIE                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t RSC                       : 1;
    __IO uint32_t SDC                       : 1;
    __IO uint32_t BEC                       : 1;
    __IO uint32_t FEC                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sscr_field_t;

typedef struct
{
    __IO uint32_t ADRSTALL                  : 1;
    __IO uint32_t RXSTALL                   : 1;
    __IO uint32_t TXDSTALL                  : 1;
    __IO uint32_t ACKSTALL                  : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t GCEN                      : 1;
    __IO uint32_t SAEN                      : 1;
    __IO uint32_t TXCFG                     : 1;
    __IO uint32_t RXCFG                     : 1;
    __IO uint32_t IGNACK                    : 1;
    __IO uint32_t HSMEN                     : 1;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t ADDRMODE                  : 3;
    uint32_t RESERVED19                     :12;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr1_field_t;

typedef struct
{
    __IO uint32_t CLKHOLD                   : 4;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t DATAVD                    : 6;
    __IO uint32_t FILTEN                    : 1;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t FILTSCL                   : 4;
    __IO uint32_t FILTSDA                   : 4;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr2_field_t;

typedef struct
{
    __IO uint32_t TXNACK                    : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_star_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_stdr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      : 6;
    __IO uint32_t REMP                      : 1;
    __IO uint32_t SOF                       : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_srdr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR0                     :10;
    uint32_t RESERVED11                     : 6;
    __IO uint32_t ADDR1                     :10;
    uint32_t RESERVED27                     : 4;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_saddr_field_t;

typedef struct
{
    __IO uint32_t RADDR                     :11;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t ANV                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sasr_field_t;

typedef struct
{
    __IO uint32_t KR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_kr_field_t;

typedef struct
{
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t ACTION                    : 1;
    __IO uint32_t PAUSE                     : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_arr_field_t;

typedef struct
{
    __IO uint32_t CRF                       : 1;
    __IO uint32_t ARRF                      : 1;
    __IO uint32_t WINRF                     : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t RUN                       : 1;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_sr_field_t;

typedef struct
{
    __IO uint32_t WINR                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_winr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t DATA8                     : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RCIE                      : 1;
    __IO uint32_t TCIE                      : 1;
    __IO uint32_t B8CONT                    : 2;
    __IO uint32_t REN                       : 1;
    __IO uint32_t ADRDET                    : 1;
    __IO uint32_t SM                        : 2;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t OVER                      : 2;
    __IO uint32_t SCLKSEL                   : 2;
    __IO uint32_t PEIE                      : 1;
    __IO uint32_t STOPBIT                   : 2;
    uint32_t RESERVED16                     : 2;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t CTSIE                     : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t HDSEL                     : 1;
    uint32_t RESERVED23                     : 8;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scon_field_t;

typedef struct
{
    __IO uint32_t ADDR                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saddr_field_t;

typedef struct
{
    __IO uint32_t MASK                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saden_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    __IO uint32_t CTS                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_isr_field_t;

typedef struct
{
    __IO uint32_t RCCF                      : 1;
    __IO uint32_t TCCF                      : 1;
    __IO uint32_t FECF                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PECF                      : 1;
    __IO uint32_t CTSIFCF                   : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_icr_field_t;

typedef struct
{
    __IO uint32_t SCNT                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scnt_field_t;

typedef struct
{
    __IO uint32_t BSEL                      : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_bsel_field_t;

typedef struct
{
    __IO uint32_t MODU                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_modu_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE                    : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t DEBOUNCE_TIME             : 4;
    __IO uint32_t FTEN                      : 1;
    __IO uint32_t RTEN                      : 1;
    __IO uint32_t HTEN                      : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     : 1;
    __IO uint32_t FLT_MODE                  : 2;
    uint32_t RESERVED19                     :12;
    __IO uint32_t RSV                       : 1;
} stc_lvd_cr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FLTV                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_lvd_sr_field_t;

typedef struct
{
    __IO uint32_t PRDS                      : 3;
    __IO uint32_t AMPM                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t HZ1OE                     : 1;
    __IO uint32_t HZ1SEL                    : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t PRDX                      : 6;
    __IO uint32_t PRDSEL                    : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr0_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 1;
    __IO uint32_t WAITF                     : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t CKSEL                     : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr1_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_sec_field_t;

typedef struct
{
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_min_field_t;

typedef struct
{
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_hour_field_t;

typedef struct
{
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_rtc_week_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_day_field_t;

typedef struct
{
    __IO uint32_t MON                       : 5;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_rtc_mon_field_t;

typedef struct
{
    __IO uint32_t YEARL                     : 4;
    __IO uint32_t YEARH                     : 4;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_year_field_t;

typedef struct
{
    __IO uint32_t CR                        :13;
    uint32_t RESERVED13                     : 1;
    __IO uint32_t CSTEPS                    : 1;
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_compen_field_t;

typedef struct
{
    __IO uint32_t PARA                      : 6;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_hcomp_field_t;

typedef struct
{
    __IO uint32_t WUCKSEL                   : 3;
    __IO uint32_t TSEDG                     : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t TSE                       : 1;
    __IO uint32_t WUTE                      : 1;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t ALMAE                     : 1;
    __IO uint32_t ALMBE                     : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr2_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_alma_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_almb_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 9;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tstr_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t MON                       : 5;
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tsdr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wutr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ier_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ifr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_icr_field_t;

typedef struct
{
    __IO uint32_t WPR                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wpr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t BRR                       : 3;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    __IO uint32_t LSBF                      : 1;
    __IO uint32_t WIDTH                     : 4;
    __IO uint32_t SSM                       : 1;
    __IO uint32_t CM                        : 2;
    __IO uint32_t SMP                       : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr0_field_t;

typedef struct
{
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t RXNEIE                    : 1;
    __IO uint32_t SSFIE                     : 1;
    __IO uint32_t SSRIE                     : 1;
    __IO uint32_t UDFIE                     : 1;
    __IO uint32_t OVFIE                     : 1;
    __IO uint32_t SSERRIE                   : 1;
    __IO uint32_t MODFIE                    : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr1_field_t;

typedef struct
{
    __IO uint32_t HDOE                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_hdoe_field_t;

typedef struct
{
    __IO uint32_t SSI                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_ssi_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t SSLVL                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_spi_sr_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_icr_field_t;

typedef struct
{
    __IO uint32_t DR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_dr_field_t;

typedef struct
{
    __IO uint32_t RC48M_EN                  : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t RCL_EN                    : 1;
    __IO uint32_t XTL_EN                    : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t CLKSW                     : 3;
    __IO uint32_t HCLK_PRS                  : 3;
    uint32_t RESERVED11                     : 4;
    __IO uint32_t WAKEUP_BYRC48M            : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl0_field_t;

typedef struct
{
    __IO uint32_t RESET_USE_IO              : 1;
    __IO uint32_t EXTH_EN                   : 1;
    __IO uint32_t EXTL_EN                   : 1;
    __IO uint32_t XTL_ALWAYS_ON             : 1;
    __IO uint32_t CLOCK_FAULT_EN            : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t LOCKUP_EN                 : 1;
    __IO uint32_t SPI_PCTRL                 : 1;
    __IO uint32_t SWD_USE_IO                : 1;
    __IO uint32_t CTIMER0_FUN_SEL           : 1;
    __IO uint32_t CTIMER1_FUN_SEL           : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl1_field_t;

typedef struct
{
    __IO uint32_t SYSCTRL2                  :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl2_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t TRIMF                     : 6;
    __IO uint32_t TRIMC                     : 8;
    __IO uint32_t FSEL                      : 2;
    uint32_t RESERVED18                     :13;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_rc48m_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    uint32_t RESERVED10                     : 2;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t MSEL                      : 1;
    uint32_t RESERVED17                     :14;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rcl_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t AMP_SEL                   : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    __IO uint32_t DETIE                     : 1;
    __IO uint32_t DETTIME                   : 1;
    __IO uint32_t DETEN                     : 1;
    __IO uint32_t FAULT_STATE               : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xtl_cr_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR15V                    : 1;
    __IO uint32_t LVD_FLAG                  : 1;
    __IO uint32_t IWDT_FLAG                 : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_reset_flag_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t LPUART0_EN                : 1;
    __IO uint32_t LPUART1_EN                : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t SPI_EN                    : 1;
    uint32_t RESERVED7                      : 4;
    __IO uint32_t ATIM3_EN                  : 1;
    uint32_t RESERVED12                     : 3;
    __IO uint32_t IWDT_EN                   : 1;
    __IO uint32_t ADC_EN                    : 1;
    __IO uint32_t VC_EN                     : 1;
    __IO uint32_t TRNG_EN                   : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC_EN                    : 1;
    uint32_t RESERVED21                     : 7;
    __IO uint32_t GPIO_EN                   : 1;
    uint32_t RESERVED29                     : 1;
    __IO uint32_t HSI2C_EN                  : 1;
    __IO uint32_t FLASH_EN                  : 1;
} stc_sysctrl_peri_clken0_field_t;

typedef struct
{
    __IO uint32_t CTIM0_EN                  : 1;
    __IO uint32_t CTIM1_EN                  : 1;
    __IO uint32_t CTRIM_EN                  : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_peri_clken1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t LPUART0_RST               : 1;
    __IO uint32_t LPUART1_RST               : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t SPI_RST                   : 1;
    uint32_t RESERVED7                      : 4;
    __IO uint32_t ATIM3_RST                 : 1;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t ADC_RST                   : 1;
    __IO uint32_t VC_RST                    : 1;
    __IO uint32_t TRNG_RST                  : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC_RST                   : 1;
    uint32_t RESERVED21                     : 7;
    __IO uint32_t GPIO_RST                  : 1;
    uint32_t RESERVED29                     : 1;
    __IO uint32_t HSI2C_RST                 : 1;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_peri_reset0_field_t;

typedef struct
{
    __IO uint32_t CTIM0_RST                 : 1;
    __IO uint32_t CTIM1_RST                 : 1;
    __IO uint32_t CTRIM_RST                 : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_peri_reset1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t IWDT_DEBUG                : 1;
    __IO uint32_t RTC_DEBUG                 : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t ATIM3_DEBUG               : 1;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t CTIM0_DEBUG               : 1;
    __IO uint32_t CTIM1_DEBUG               : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_debug_active_field_t;

typedef struct
{
    __IO uint32_t RNGCIR_EN                 : 1;
    __IO uint32_t RNG_RUN                   : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_trng_cr_field_t;

typedef struct
{
    __IO uint32_t LOAD                      : 1;
    __IO uint32_t FDBK                      : 1;
    __IO uint32_t CNT                       : 3;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_trng_mode_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_trng_data0_field_t;

typedef struct
{
    __IO uint32_t DATA1                     :32;
} stc_trng_data1_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BIAS                      : 2;
    __IO uint32_t HYS                       : 2;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_cr0_field_t;

typedef struct
{
    __IO uint32_t PSEL                      : 4;
    __IO uint32_t NSEL                      : 4;
    __IO uint32_t FLTTIME                   : 4;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
    __IO uint32_t FLTCLK                    : 1;
    __IO uint32_t FLT_MODE                  : 2;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_cr1_field_t;

typedef struct
{
    __IO uint32_t POL                       : 1;
    uint32_t RESERVED1                      : 3;
    __IO uint32_t ATIM3CLR                  : 1;
    __IO uint32_t ATIMBK                    : 1;
    __IO uint32_t WINDOW                    : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BLANK                     : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_cr2_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FLTV                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_sr_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BIAS                      : 2;
    __IO uint32_t HYS                       : 2;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_cr0_field_t;

typedef struct
{
    __IO uint32_t PSEL                      : 4;
    __IO uint32_t NSEL                      : 4;
    __IO uint32_t FLTTIME                   : 4;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
    __IO uint32_t FLTCLK                    : 1;
    __IO uint32_t FLT_MODE                  : 2;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_cr1_field_t;

typedef struct
{
    __IO uint32_t POL                       : 1;
    uint32_t RESERVED1                      : 3;
    __IO uint32_t ATIM3CLR                  : 1;
    __IO uint32_t ATIMBK                    : 1;
    __IO uint32_t WINDOW                    : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BLANK                     : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_cr2_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FLTV                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_sr_field_t;

typedef struct
{
    __IO uint32_t TRIM0                     : 4;
    __IO uint32_t TRIM1                     : 4;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_vc_trim_field_t;


typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CR0;
        stc_adc_cr0_field_t CR0_f;
    };
    uint8_t RESERVED1[56];
    union
    {
        __IO uint32_t SQR0;
        stc_adc_sqr0_field_t SQR0_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t SQR1;
        stc_adc_sqr1_field_t SQR1_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t SQRRESULT0;
        stc_adc_sqrresult0_field_t SQRRESULT0_f;
    };
    union
    {
        __IO uint32_t SQRRESULT1;
        stc_adc_sqrresult1_field_t SQRRESULT1_f;
    };
    union
    {
        __IO uint32_t SQRRESULT2;
        stc_adc_sqrresult2_field_t SQRRESULT2_f;
    };
    union
    {
        __IO uint32_t SQRRESULT3;
        stc_adc_sqrresult3_field_t SQRRESULT3_f;
    };
    uint8_t RESERVED7[80];
    union
    {
        __IO uint32_t IFR;
        stc_adc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_adc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t EXTTRIGGER;
        stc_adc_exttrigger_field_t EXTTRIGGER_f;
    };
    uint8_t RESERVED10[8];
    union
    {
        __IO uint32_t SQRSTART;
        stc_adc_sqrstart_field_t SQRSTART_f;
    };
}ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_atim3_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_atim3_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_atim3_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_atim3_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atim3_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atim3_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_atim3_mode0_dtr_field_t DTR_f;
    };
}ATIM3_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_atim3_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_atim3_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atim3_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atim3_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_atim3_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_atim3_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_atim3_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_atim3_mode1_ccr0a_field_t CCR0A_f;
    };
}ATIM3_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_atim3_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_atim3_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_atim3_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atim3_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atim3_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_atim3_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_atim3_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_atim3_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_atim3_mode23_crch0_field_t CRCH0_f;
    };
    union
    {
        __IO uint32_t CRCH1;
        stc_atim3_mode23_crch1_field_t CRCH1_f;
    };
    union
    {
        __IO uint32_t CRCH2;
        stc_atim3_mode23_crch2_field_t CRCH2_f;
    };
    union
    {
        __IO uint32_t DTR;
        stc_atim3_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_atim3_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_atim3_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_atim3_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_atim3_mode23_ccr0b_field_t CCR0B_f;
    };
    union
    {
        __IO uint32_t CCR1A;
        stc_atim3_mode23_ccr1a_field_t CCR1A_f;
    };
    union
    {
        __IO uint32_t CCR1B;
        stc_atim3_mode23_ccr1b_field_t CCR1B_f;
    };
    union
    {
        __IO uint32_t CCR2A;
        stc_atim3_mode23_ccr2a_field_t CCR2A_f;
    };
    union
    {
        __IO uint32_t CCR2B;
        stc_atim3_mode23_ccr2b_field_t CCR2B_f;
    };
}ATIM3_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_btim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_btim_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[8];
    union
    {
        __IO uint32_t CR;
        stc_btim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_btim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_btim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_btim_icr_field_t ICR_f;
    };
    uint8_t RESERVED6[40];
    union
    {
        __IO uint32_t AIFR;
        stc_btim_aifr_field_t AIFR_f;
    };
    union
    {
        __IO uint32_t AICR;
        stc_btim_aicr_field_t AICR_f;
    };
}BTIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_ctrim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_ctrim_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR0;
        stc_ctrim_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_ctrim_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_ctrim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_ctrim_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_ctrim_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t FCAP;
        stc_ctrim_fcap_field_t FCAP_f;
    };
    union
    {
        __IO uint32_t TVAL;
        stc_ctrim_tval_field_t TVAL_f;
    };
    union
    {
        __IO uint32_t FLIM;
        stc_ctrim_flim_field_t FLIM_f;
    };
}CTRIM_TypeDef;

typedef struct
{
    uint8_t RESERVED0[32];
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_flash_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    union
    {
        __IO uint32_t SLOCK0;
        stc_flash_slock0_field_t SLOCK0_f;
    };
    uint8_t RESERVED5[56];
    union
    {
        __IO uint32_t LOCK_ST;
        stc_flash_lock_st_field_t LOCK_ST_f;
    };
}FLASH_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t PIN00_SEL;
        stc_gpio_pin00_sel_field_t PIN00_SEL_f;
    };
    union
    {
        __IO uint32_t PIN01_SEL;
        stc_gpio_pin01_sel_field_t PIN01_SEL_f;
    };
    union
    {
        __IO uint32_t PIN02_SEL;
        stc_gpio_pin02_sel_field_t PIN02_SEL_f;
    };
    union
    {
        __IO uint32_t PIN03_SEL;
        stc_gpio_pin03_sel_field_t PIN03_SEL_f;
    };
    union
    {
        __IO uint32_t PIN04_SEL;
        stc_gpio_pin04_sel_field_t PIN04_SEL_f;
    };
    union
    {
        __IO uint32_t PIN05_SEL;
        stc_gpio_pin05_sel_field_t PIN05_SEL_f;
    };
    union
    {
        __IO uint32_t PIN06_SEL;
        stc_gpio_pin06_sel_field_t PIN06_SEL_f;
    };
    union
    {
        __IO uint32_t PIN07_SEL;
        stc_gpio_pin07_sel_field_t PIN07_SEL_f;
    };
    union
    {
        __IO uint32_t PIN08_SEL;
        stc_gpio_pin08_sel_field_t PIN08_SEL_f;
    };
    union
    {
        __IO uint32_t PIN09_SEL;
        stc_gpio_pin09_sel_field_t PIN09_SEL_f;
    };
    union
    {
        __IO uint32_t PIN10_SEL;
        stc_gpio_pin10_sel_field_t PIN10_SEL_f;
    };
    union
    {
        __IO uint32_t PIN11_SEL;
        stc_gpio_pin11_sel_field_t PIN11_SEL_f;
    };
    union
    {
        __IO uint32_t PIN12_SEL;
        stc_gpio_pin12_sel_field_t PIN12_SEL_f;
    };
    union
    {
        __IO uint32_t PIN13_SEL;
        stc_gpio_pin13_sel_field_t PIN13_SEL_f;
    };
    union
    {
        __IO uint32_t PIN14_SEL;
        stc_gpio_pin14_sel_field_t PIN14_SEL_f;
    };
    union
    {
        __IO uint32_t PIN15_SEL;
        stc_gpio_pin15_sel_field_t PIN15_SEL_f;
    };
    uint8_t RESERVED16[192];
    union
    {
        __IO uint32_t DIR;
        stc_gpio_dir_field_t DIR_f;
    };
    union
    {
        __IO uint32_t IN;
        stc_gpio_in_field_t IN_f;
    };
    union
    {
        __IO uint32_t OUT;
        stc_gpio_out_field_t OUT_f;
    };
    union
    {
        __IO uint32_t ADS;
        stc_gpio_ads_field_t ADS_f;
    };
    union
    {
        __IO uint32_t BSET;
        stc_gpio_bset_field_t BSET_f;
    };
    union
    {
        __IO uint32_t BCLR;
        stc_gpio_bclr_field_t BCLR_f;
    };
    union
    {
        __IO uint32_t BSETCLR;
        stc_gpio_bsetclr_field_t BSETCLR_f;
    };
    uint8_t RESERVED23[4];
    union
    {
        __IO uint32_t PU;
        stc_gpio_pu_field_t PU_f;
    };
    uint8_t RESERVED24[8];
    union
    {
        __IO uint32_t OD;
        stc_gpio_od_field_t OD_f;
    };
    union
    {
        __IO uint32_t HIE;
        stc_gpio_hie_field_t HIE_f;
    };
    union
    {
        __IO uint32_t LIE;
        stc_gpio_lie_field_t LIE_f;
    };
    union
    {
        __IO uint32_t RIE;
        stc_gpio_rie_field_t RIE_f;
    };
    union
    {
        __IO uint32_t FIE;
        stc_gpio_fie_field_t FIE_f;
    };
    uint8_t RESERVED29[192];
    union
    {
        __IO uint32_t STAT;
        stc_gpio_stat_field_t STAT_f;
    };
    uint8_t RESERVED30[12];
    union
    {
        __IO uint32_t ICLR;
        stc_gpio_iclr_field_t ICLR_f;
    };
}GPIO_TypeDef;

typedef struct
{
    uint8_t RESERVED0[772];
    union
    {
        __IO uint32_t CTRL1;
        stc_gpioaux_ctrl1_field_t CTRL1_f;
    };
    union
    {
        __IO uint32_t CTRL2;
        stc_gpioaux_ctrl2_field_t CTRL2_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t TIMES;
        stc_gpioaux_times_field_t TIMES_f;
    };
    union
    {
        __IO uint32_t TIMCPS;
        stc_gpioaux_timcps_field_t TIMCPS_f;
    };
    uint8_t RESERVED4[24];
    union
    {
        __IO uint32_t FLTCFG;
        stc_gpioaux_fltcfg_field_t FLTCFG_f;
    };
}GPIOAUX_TypeDef;

typedef struct
{
    uint8_t RESERVED0[768];
    union
    {
        __IO uint32_t ARR;
        stc_gtim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_gtim_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CMMR;
        stc_gtim_cmmr_field_t CMMR_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_gtim_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR0;
        stc_gtim_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_gtim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_gtim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_gtim_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t CCR0;
        stc_gtim_ccr0_field_t CCR0_f;
    };
    union
    {
        __IO uint32_t CCR1;
        stc_gtim_ccr1_field_t CCR1_f;
    };
    union
    {
        __IO uint32_t CCR2;
        stc_gtim_ccr2_field_t CCR2_f;
    };
    union
    {
        __IO uint32_t CCR3;
        stc_gtim_ccr3_field_t CCR3_f;
    };
}GTIM_TypeDef;

typedef struct
{
    uint8_t RESERVED0[16];
    union
    {
        __IO uint32_t MCR;
        stc_hsi2c_mcr_field_t MCR_f;
    };
    union
    {
        __IO uint32_t MSR;
        stc_hsi2c_msr_field_t MSR_f;
    };
    union
    {
        __IO uint32_t MIER;
        stc_hsi2c_mier_field_t MIER_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_hsi2c_mscr_field_t MSCR_f;
    };
    uint8_t RESERVED4[4];
    union
    {
        __IO uint32_t MCFGR1;
        stc_hsi2c_mcfgr1_field_t MCFGR1_f;
    };
    union
    {
        __IO uint32_t MCFGR2;
        stc_hsi2c_mcfgr2_field_t MCFGR2_f;
    };
    union
    {
        __IO uint32_t MCFGR3;
        stc_hsi2c_mcfgr3_field_t MCFGR3_f;
    };
    union
    {
        __IO uint32_t MCCR0;
        stc_hsi2c_mccr0_field_t MCCR0_f;
    };
    union
    {
        __IO uint32_t MCCR1;
        stc_hsi2c_mccr1_field_t MCCR1_f;
    };
    union
    {
        __IO uint32_t MTDR;
        stc_hsi2c_mtdr_field_t MTDR_f;
    };
    union
    {
        __IO uint32_t MRDR;
        stc_hsi2c_mrdr_field_t MRDR_f;
    };
    union
    {
        __IO uint32_t MDMR;
        stc_hsi2c_mdmr_field_t MDMR_f;
    };
    uint8_t RESERVED12[204];
    union
    {
        __IO uint32_t SCR0;
        stc_hsi2c_scr0_field_t SCR0_f;
    };
    union
    {
        __IO uint32_t SSR;
        stc_hsi2c_ssr_field_t SSR_f;
    };
    union
    {
        __IO uint32_t SIER;
        stc_hsi2c_sier_field_t SIER_f;
    };
    union
    {
        __IO uint32_t SSCR;
        stc_hsi2c_sscr_field_t SSCR_f;
    };
    union
    {
        __IO uint32_t SCR1;
        stc_hsi2c_scr1_field_t SCR1_f;
    };
    union
    {
        __IO uint32_t SCR2;
        stc_hsi2c_scr2_field_t SCR2_f;
    };
    union
    {
        __IO uint32_t STAR;
        stc_hsi2c_star_field_t STAR_f;
    };
    union
    {
        __IO uint32_t STDR;
        stc_hsi2c_stdr_field_t STDR_f;
    };
    union
    {
        __IO uint32_t SRDR;
        stc_hsi2c_srdr_field_t SRDR_f;
    };
    uint8_t RESERVED21[12];
    union
    {
        __IO uint32_t SADDR;
        stc_hsi2c_saddr_field_t SADDR_f;
    };
    uint8_t RESERVED22[12];
    union
    {
        __IO uint32_t SASR;
        stc_hsi2c_sasr_field_t SASR_f;
    };
}HSI2C_TypeDef;

typedef struct
{
    uint8_t RESERVED0[128];
    union
    {
        __IO uint32_t KR;
        stc_iwdt_kr_field_t KR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_iwdt_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_iwdt_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_iwdt_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t WINR;
        stc_iwdt_winr_field_t WINR_f;
    };
}IWDT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_lpuart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_lpuart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_lpuart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_lpuart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_lpuart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_lpuart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t SCNT;
        stc_lpuart_scnt_field_t SCNT_f;
    };
    union
    {
        __IO uint32_t BSEL;
        stc_lpuart_bsel_field_t BSEL_f;
    };
    union
    {
        __IO uint32_t MODU;
        stc_lpuart_modu_field_t MODU_f;
    };
}LPUART_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_lvd_sr_field_t SR_f;
    };
}LVD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_rtc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_rtc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SEC;
        stc_rtc_sec_field_t SEC_f;
    };
    union
    {
        __IO uint32_t MIN;
        stc_rtc_min_field_t MIN_f;
    };
    union
    {
        __IO uint32_t HOUR;
        stc_rtc_hour_field_t HOUR_f;
    };
    union
    {
        __IO uint32_t WEEK;
        stc_rtc_week_field_t WEEK_f;
    };
    union
    {
        __IO uint32_t DAY;
        stc_rtc_day_field_t DAY_f;
    };
    union
    {
        __IO uint32_t MON;
        stc_rtc_mon_field_t MON_f;
    };
    union
    {
        __IO uint32_t YEAR;
        stc_rtc_year_field_t YEAR_f;
    };
    uint8_t RESERVED9[12];
    union
    {
        __IO uint32_t COMPEN;
        stc_rtc_compen_field_t COMPEN_f;
    };
    union
    {
        __IO uint32_t HCOMP;
        stc_rtc_hcomp_field_t HCOMP_f;
    };
    uint8_t RESERVED11[4];
    union
    {
        __IO uint32_t CR2;
        stc_rtc_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t ALMA;
        stc_rtc_alma_field_t ALMA_f;
    };
    union
    {
        __IO uint32_t ALMB;
        stc_rtc_almb_field_t ALMB_f;
    };
    union
    {
        __IO uint32_t TSTR;
        stc_rtc_tstr_field_t TSTR_f;
    };
    union
    {
        __IO uint32_t TSDR;
        stc_rtc_tsdr_field_t TSDR_f;
    };
    union
    {
        __IO uint32_t WUTR;
        stc_rtc_wutr_field_t WUTR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_rtc_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_rtc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_rtc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t WPR;
        stc_rtc_wpr_field_t WPR_f;
    };
}RTC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_spi_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_spi_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t HDOE;
        stc_spi_hdoe_field_t HDOE_f;
    };
    union
    {
        __IO uint32_t SSI;
        stc_spi_ssi_field_t SSI_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_spi_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_spi_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t DR;
        stc_spi_dr_field_t DR_f;
    };
}SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SYSCTRL0;
        stc_sysctrl_sysctrl0_field_t SYSCTRL0_f;
    };
    union
    {
        __IO uint32_t SYSCTRL1;
        stc_sysctrl_sysctrl1_field_t SYSCTRL1_f;
    };
    union
    {
        __IO uint32_t SYSCTRL2;
        stc_sysctrl_sysctrl2_field_t SYSCTRL2_f;
    };
    union
    {
        __IO uint32_t RC48M_CR;
        stc_sysctrl_rc48m_cr_field_t RC48M_CR_f;
    };
    uint8_t RESERVED4[4];
    union
    {
        __IO uint32_t RCL_CR;
        stc_sysctrl_rcl_cr_field_t RCL_CR_f;
    };
    union
    {
        __IO uint32_t XTL_CR;
        stc_sysctrl_xtl_cr_field_t XTL_CR_f;
    };
    union
    {
        __IO uint32_t RESET_FLAG;
        stc_sysctrl_reset_flag_field_t RESET_FLAG_f;
    };
    union
    {
        __IO uint32_t PERI_CLKEN0;
        stc_sysctrl_peri_clken0_field_t PERI_CLKEN0_f;
    };
    union
    {
        __IO uint32_t PERI_CLKEN1;
        stc_sysctrl_peri_clken1_field_t PERI_CLKEN1_f;
    };
    union
    {
        __IO uint32_t PERI_RESET0;
        stc_sysctrl_peri_reset0_field_t PERI_RESET0_f;
    };
    union
    {
        __IO uint32_t PERI_RESET1;
        stc_sysctrl_peri_reset1_field_t PERI_RESET1_f;
    };
    uint8_t RESERVED11[8];
    union
    {
        __IO uint32_t DEBUG_ACTIVE;
        stc_sysctrl_debug_active_field_t DEBUG_ACTIVE_f;
    };
}SYSCTRL_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_trng_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t MODE;
        stc_trng_mode_field_t MODE_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t DATA0;
        stc_trng_data0_field_t DATA0_f;
    };
    union
    {
        __IO uint32_t DATA1;
        stc_trng_data1_field_t DATA1_f;
    };
}TRNG_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t VC0_CR0;
        stc_vc_vc0_cr0_field_t VC0_CR0_f;
    };
    union
    {
        __IO uint32_t VC0_CR1;
        stc_vc_vc0_cr1_field_t VC0_CR1_f;
    };
    union
    {
        __IO uint32_t VC0_CR2;
        stc_vc_vc0_cr2_field_t VC0_CR2_f;
    };
    union
    {
        __IO uint32_t VC0_SR;
        stc_vc_vc0_sr_field_t VC0_SR_f;
    };
    union
    {
        __IO uint32_t VC1_CR0;
        stc_vc_vc1_cr0_field_t VC1_CR0_f;
    };
    union
    {
        __IO uint32_t VC1_CR1;
        stc_vc_vc1_cr1_field_t VC1_CR1_f;
    };
    union
    {
        __IO uint32_t VC1_CR2;
        stc_vc_vc1_cr2_field_t VC1_CR2_f;
    };
    union
    {
        __IO uint32_t VC1_SR;
        stc_vc_vc1_sr_field_t VC1_SR_f;
    };
    union
    {
        __IO uint32_t VC_TRIM;
        stc_vc_trim_field_t VC_TRIM_f;
    };
}VC_TypeDef;



#define PERIPH_BASE                        (0x40000000UL)
#define ADC_BASE                               (PERIPH_BASE + 0x00002400UL)
#define ATIM3_MODE0_BASE                       (PERIPH_BASE + 0x00009800UL)
#define ATIM3_MODE1_BASE                       (PERIPH_BASE + 0x00009800UL)
#define ATIM3_MODE23_BASE                      (PERIPH_BASE + 0x00009800UL)
#define BTIM0_BASE                             (PERIPH_BASE + 0x00001800UL)
#define BTIM1_BASE                             (PERIPH_BASE + 0x00001900UL)
#define BTIM2_BASE                             (PERIPH_BASE + 0x00001A00UL)
#define BTIM3_BASE                             (PERIPH_BASE + 0x00001C00UL)
#define BTIM4_BASE                             (PERIPH_BASE + 0x00001D00UL)
#define BTIM5_BASE                             (PERIPH_BASE + 0x00001E00UL)
#define CTRIM_BASE                             (PERIPH_BASE + 0x00009000UL)
#define FLASH_BASE                             (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE                             (PERIPH_BASE + 0x00020C00UL)
#define GPIOAUX_BASE                           (PERIPH_BASE + 0x00020C00UL)
#define GPIOB_BASE                             (PERIPH_BASE + 0x00020C40UL)
#define GTIM0_BASE                             (PERIPH_BASE + 0x00001800UL)
#define GTIM1_BASE                             (PERIPH_BASE + 0x00001C00UL)
#define HSI2C_BASE                             (PERIPH_BASE + 0x0000BC00UL)
#define IWDT_BASE                              (PERIPH_BASE + 0x00001000UL)
#define LPUART0_BASE                           (PERIPH_BASE + 0x00000000UL)
#define LPUART1_BASE                           (PERIPH_BASE + 0x00008000UL)
#define LVD_BASE                               (PERIPH_BASE + 0x00002C00UL)
#define RTC_BASE                               (PERIPH_BASE + 0x00001400UL)
#define SPI_BASE                               (PERIPH_BASE + 0x00000800UL)
#define SYSCTRL_BASE                           (PERIPH_BASE + 0x00021800UL)
#define TRNG_BASE                              (PERIPH_BASE + 0x00008C00UL)
#define VC_BASE                                (PERIPH_BASE + 0x00002800UL)


#define ADC                                    ((ADC_TypeDef *)0x40002400UL)
#define ATIM3_MODE0                            ((ATIM3_MODE0_TypeDef *)0x40009800UL)
#define ATIM3_MODE1                            ((ATIM3_MODE1_TypeDef *)0x40009800UL)
#define ATIM3_MODE23                           ((ATIM3_MODE23_TypeDef *)0x40009800UL)
#define BTIM0                                  ((BTIM_TypeDef *)0x40001800UL)
#define BTIM1                                  ((BTIM_TypeDef *)0x40001900UL)
#define BTIM2                                  ((BTIM_TypeDef *)0x40001A00UL)
#define BTIM3                                  ((BTIM_TypeDef *)0x40001C00UL)
#define BTIM4                                  ((BTIM_TypeDef *)0x40001D00UL)
#define BTIM5                                  ((BTIM_TypeDef *)0x40001E00UL)
#define CTRIM                                  ((CTRIM_TypeDef *)0x40009000UL)
#define FLASH                                  ((FLASH_TypeDef *)0x40020000UL)
#define GPIOA                                  ((GPIO_TypeDef *)0x40020C00UL)
#define GPIOAUX                                ((GPIOAUX_TypeDef *)0x40020C00UL)
#define GPIOB                                  ((GPIO_TypeDef *)0x40020C40UL)
#define GTIM0                                  ((GTIM_TypeDef *)0x40001800UL)
#define GTIM1                                  ((GTIM_TypeDef *)0x40001C00UL)
#define HSI2C                                  ((HSI2C_TypeDef *)0x4000BC00UL)
#define IWDT                                   ((IWDT_TypeDef *)0x40001000UL)
#define LPUART0                                ((LPUART_TypeDef *)0x40000000UL)
#define LPUART1                                ((LPUART_TypeDef *)0x40008000UL)
#define LVD                                    ((LVD_TypeDef *)0x40002C00UL)
#define RTC                                    ((RTC_TypeDef *)0x40001400UL)
#define SPI                                    ((SPI_TypeDef *)0x40000800UL)
#define SYSCTRL                                ((SYSCTRL_TypeDef *)0x40021800UL)
#define TRNG                                   ((TRNG_TypeDef *)0x40008C00UL)
#define VC                                     ((VC_TypeDef *)0x40002800UL)


//********************    Bits Define For Peripheral ADC    ********************//
// ADC_CR0
#define ADC_CR0_EN_Pos                                      (0U)
#define ADC_CR0_EN_Msk                                      (0x1UL << ADC_CR0_EN_Pos)
#define ADC_CR0_EN                                          ADC_CR0_EN_Msk
#define ADC_CR0_CLKDIV_Pos                                  (2U)
#define ADC_CR0_CLKDIV_Msk                                  (0x3UL << ADC_CR0_CLKDIV_Pos)
#define ADC_CR0_CLKDIV                                      ADC_CR0_CLKDIV_Msk
#define ADC_CR0_REF_Pos                                     (9U)
#define ADC_CR0_REF_Msk                                     (0x1UL << ADC_CR0_REF_Pos)
#define ADC_CR0_REF                                         ADC_CR0_REF_Msk
#define ADC_CR0_IBSEL_Pos                                   (12U)
#define ADC_CR0_IBSEL_Msk                                   (0x3UL << ADC_CR0_IBSEL_Pos)
#define ADC_CR0_IBSEL                                       ADC_CR0_IBSEL_Msk
#define ADC_CR0_IE_Pos                                      (15U)
#define ADC_CR0_IE_Msk                                      (0x1UL << ADC_CR0_IE_Pos)
#define ADC_CR0_IE                                          ADC_CR0_IE_Msk
#define ADC_CR0_SAM_Pos                                     (17U)
#define ADC_CR0_SAM_Msk                                     (0xFUL << ADC_CR0_SAM_Pos)
#define ADC_CR0_SAM                                         ADC_CR0_SAM_Msk

// ADC_SQR0
#define ADC_SQR0_CH0MUX_Pos                                 (0U)
#define ADC_SQR0_CH0MUX_Msk                                 (0xFUL << ADC_SQR0_CH0MUX_Pos)
#define ADC_SQR0_CH0MUX                                     ADC_SQR0_CH0MUX_Msk
#define ADC_SQR0_CH1MUX_Pos                                 (5U)
#define ADC_SQR0_CH1MUX_Msk                                 (0xFUL << ADC_SQR0_CH1MUX_Pos)
#define ADC_SQR0_CH1MUX                                     ADC_SQR0_CH1MUX_Msk
#define ADC_SQR0_CH2MUX_Pos                                 (10U)
#define ADC_SQR0_CH2MUX_Msk                                 (0xFUL << ADC_SQR0_CH2MUX_Pos)
#define ADC_SQR0_CH2MUX                                     ADC_SQR0_CH2MUX_Msk
#define ADC_SQR0_CH3MUX_Pos                                 (15U)
#define ADC_SQR0_CH3MUX_Msk                                 (0xFUL << ADC_SQR0_CH3MUX_Pos)
#define ADC_SQR0_CH3MUX                                     ADC_SQR0_CH3MUX_Msk

// ADC_SQR1
#define ADC_SQR1_CNT_Pos                                    (0U)
#define ADC_SQR1_CNT_Msk                                    (0x3UL << ADC_SQR1_CNT_Pos)
#define ADC_SQR1_CNT                                        ADC_SQR1_CNT_Msk

// ADC_SQRRESULT0
#define ADC_SQRRESULT0_RESULT_Pos                           (0U)
#define ADC_SQRRESULT0_RESULT_Msk                           (0xFFFUL << ADC_SQRRESULT0_RESULT_Pos)
#define ADC_SQRRESULT0_RESULT                               ADC_SQRRESULT0_RESULT_Msk

// ADC_SQRRESULT1
#define ADC_SQRRESULT1_RESULT_Pos                           (0U)
#define ADC_SQRRESULT1_RESULT_Msk                           (0xFFFUL << ADC_SQRRESULT1_RESULT_Pos)
#define ADC_SQRRESULT1_RESULT                               ADC_SQRRESULT1_RESULT_Msk

// ADC_SQRRESULT2
#define ADC_SQRRESULT2_RESULT_Pos                           (0U)
#define ADC_SQRRESULT2_RESULT_Msk                           (0xFFFUL << ADC_SQRRESULT2_RESULT_Pos)
#define ADC_SQRRESULT2_RESULT                               ADC_SQRRESULT2_RESULT_Msk

// ADC_SQRRESULT3
#define ADC_SQRRESULT3_RESULT_Pos                           (0U)
#define ADC_SQRRESULT3_RESULT_Msk                           (0xFFFUL << ADC_SQRRESULT3_RESULT_Pos)
#define ADC_SQRRESULT3_RESULT                               ADC_SQRRESULT3_RESULT_Msk

// ADC_IFR
#define ADC_IFR_SQRIF_Pos                                   (0U)
#define ADC_IFR_SQRIF_Msk                                   (0x1UL << ADC_IFR_SQRIF_Pos)
#define ADC_IFR_SQRIF                                       ADC_IFR_SQRIF_Msk

// ADC_ICR
#define ADC_ICR_SQRIC_Pos                                   (0U)
#define ADC_ICR_SQRIC_Msk                                   (0x1UL << ADC_ICR_SQRIC_Pos)
#define ADC_ICR_SQRIC                                       ADC_ICR_SQRIC_Msk

// ADC_EXTTRIGGER
#define ADC_EXTTRIGGER_EXT_TRIG_EN_Pos                      (0U)
#define ADC_EXTTRIGGER_EXT_TRIG_EN_Msk                      (0xFUL << ADC_EXTTRIGGER_EXT_TRIG_EN_Pos)
#define ADC_EXTTRIGGER_EXT_TRIG_EN                          ADC_EXTTRIGGER_EXT_TRIG_EN_Msk

// ADC_SQRSTART
#define ADC_SQRSTART_START_Pos                              (0U)
#define ADC_SQRSTART_START_Msk                              (0x1UL << ADC_SQRSTART_START_Pos)
#define ADC_SQRSTART_START                                  ADC_SQRSTART_START_Msk



//********************    Bits Define For Peripheral ATIM3_MODE0    ********************//
// ATIM3_MODE0_ARR
#define ATIM3_MODE0_ARR_ARR_Pos                             (0U)
#define ATIM3_MODE0_ARR_ARR_Msk                             (0xFFFFUL << ATIM3_MODE0_ARR_ARR_Pos)
#define ATIM3_MODE0_ARR_ARR                                 ATIM3_MODE0_ARR_ARR_Msk

// ATIM3_MODE0_CNT
#define ATIM3_MODE0_CNT_CNT_Pos                             (0U)
#define ATIM3_MODE0_CNT_CNT_Msk                             (0xFFFFUL << ATIM3_MODE0_CNT_CNT_Pos)
#define ATIM3_MODE0_CNT_CNT                                 ATIM3_MODE0_CNT_CNT_Msk

// ATIM3_MODE0_CNT32
#define ATIM3_MODE0_CNT32_CNT32_Pos                         (0U)
#define ATIM3_MODE0_CNT32_CNT32_Msk                         (0xFFFFFFFFUL << ATIM3_MODE0_CNT32_CNT32_Pos)
#define ATIM3_MODE0_CNT32_CNT32                             ATIM3_MODE0_CNT32_CNT32_Msk

// ATIM3_MODE0_M0CR
#define ATIM3_MODE0_M0CR_CTEN_Pos                           (0U)
#define ATIM3_MODE0_M0CR_CTEN_Msk                           (0x1UL << ATIM3_MODE0_M0CR_CTEN_Pos)
#define ATIM3_MODE0_M0CR_CTEN                               ATIM3_MODE0_M0CR_CTEN_Msk
#define ATIM3_MODE0_M0CR_MD_Pos                             (1U)
#define ATIM3_MODE0_M0CR_MD_Msk                             (0x1UL << ATIM3_MODE0_M0CR_MD_Pos)
#define ATIM3_MODE0_M0CR_MD                                 ATIM3_MODE0_M0CR_MD_Msk
#define ATIM3_MODE0_M0CR_CT_Pos                             (2U)
#define ATIM3_MODE0_M0CR_CT_Msk                             (0x1UL << ATIM3_MODE0_M0CR_CT_Pos)
#define ATIM3_MODE0_M0CR_CT                                 ATIM3_MODE0_M0CR_CT_Msk
#define ATIM3_MODE0_M0CR_TOGEN_Pos                          (3U)
#define ATIM3_MODE0_M0CR_TOGEN_Msk                          (0x1UL << ATIM3_MODE0_M0CR_TOGEN_Pos)
#define ATIM3_MODE0_M0CR_TOGEN                              ATIM3_MODE0_M0CR_TOGEN_Msk
#define ATIM3_MODE0_M0CR_PRS_Pos                            (4U)
#define ATIM3_MODE0_M0CR_PRS_Msk                            (0x7UL << ATIM3_MODE0_M0CR_PRS_Pos)
#define ATIM3_MODE0_M0CR_PRS                                ATIM3_MODE0_M0CR_PRS_Msk
#define ATIM3_MODE0_M0CR_GATE_Pos                           (8U)
#define ATIM3_MODE0_M0CR_GATE_Msk                           (0x1UL << ATIM3_MODE0_M0CR_GATE_Pos)
#define ATIM3_MODE0_M0CR_GATE                               ATIM3_MODE0_M0CR_GATE_Msk
#define ATIM3_MODE0_M0CR_GATEP_Pos                          (9U)
#define ATIM3_MODE0_M0CR_GATEP_Msk                          (0x1UL << ATIM3_MODE0_M0CR_GATEP_Pos)
#define ATIM3_MODE0_M0CR_GATEP                              ATIM3_MODE0_M0CR_GATEP_Msk
#define ATIM3_MODE0_M0CR_UIE_Pos                            (10U)
#define ATIM3_MODE0_M0CR_UIE_Msk                            (0x1UL << ATIM3_MODE0_M0CR_UIE_Pos)
#define ATIM3_MODE0_M0CR_UIE                                ATIM3_MODE0_M0CR_UIE_Msk
#define ATIM3_MODE0_M0CR_MODE_Pos                           (12U)
#define ATIM3_MODE0_M0CR_MODE_Msk                           (0x3UL << ATIM3_MODE0_M0CR_MODE_Pos)
#define ATIM3_MODE0_M0CR_MODE                               ATIM3_MODE0_M0CR_MODE_Msk

// ATIM3_MODE0_IFR
#define ATIM3_MODE0_IFR_UIF_Pos                             (0U)
#define ATIM3_MODE0_IFR_UIF_Msk                             (0x1UL << ATIM3_MODE0_IFR_UIF_Pos)
#define ATIM3_MODE0_IFR_UIF                                 ATIM3_MODE0_IFR_UIF_Msk

// ATIM3_MODE0_ICLR
#define ATIM3_MODE0_ICLR_UIF_Pos                            (0U)
#define ATIM3_MODE0_ICLR_UIF_Msk                            (0x1UL << ATIM3_MODE0_ICLR_UIF_Pos)
#define ATIM3_MODE0_ICLR_UIF                                ATIM3_MODE0_ICLR_UIF_Msk

// ATIM3_MODE0_DTR
#define ATIM3_MODE0_DTR_MOE_Pos                             (12U)
#define ATIM3_MODE0_DTR_MOE_Msk                             (0x1UL << ATIM3_MODE0_DTR_MOE_Pos)
#define ATIM3_MODE0_DTR_MOE                                 ATIM3_MODE0_DTR_MOE_Msk



//********************    Bits Define For Peripheral ATIM3_MODE1    ********************//
// ATIM3_MODE1_CNT
#define ATIM3_MODE1_CNT_CNT_Pos                             (0U)
#define ATIM3_MODE1_CNT_CNT_Msk                             (0xFFFFUL << ATIM3_MODE1_CNT_CNT_Pos)
#define ATIM3_MODE1_CNT_CNT                                 ATIM3_MODE1_CNT_CNT_Msk

// ATIM3_MODE1_M1CR
#define ATIM3_MODE1_M1CR_CTEN_Pos                           (0U)
#define ATIM3_MODE1_M1CR_CTEN_Msk                           (0x1UL << ATIM3_MODE1_M1CR_CTEN_Pos)
#define ATIM3_MODE1_M1CR_CTEN                               ATIM3_MODE1_M1CR_CTEN_Msk
#define ATIM3_MODE1_M1CR_CT_Pos                             (2U)
#define ATIM3_MODE1_M1CR_CT_Msk                             (0x1UL << ATIM3_MODE1_M1CR_CT_Pos)
#define ATIM3_MODE1_M1CR_CT                                 ATIM3_MODE1_M1CR_CT_Msk
#define ATIM3_MODE1_M1CR_PRS_Pos                            (4U)
#define ATIM3_MODE1_M1CR_PRS_Msk                            (0x7UL << ATIM3_MODE1_M1CR_PRS_Pos)
#define ATIM3_MODE1_M1CR_PRS                                ATIM3_MODE1_M1CR_PRS_Msk
#define ATIM3_MODE1_M1CR_EDG1ST_Pos                         (8U)
#define ATIM3_MODE1_M1CR_EDG1ST_Msk                         (0x1UL << ATIM3_MODE1_M1CR_EDG1ST_Pos)
#define ATIM3_MODE1_M1CR_EDG1ST                             ATIM3_MODE1_M1CR_EDG1ST_Msk
#define ATIM3_MODE1_M1CR_EDG2ND_Pos                         (9U)
#define ATIM3_MODE1_M1CR_EDG2ND_Msk                         (0x1UL << ATIM3_MODE1_M1CR_EDG2ND_Pos)
#define ATIM3_MODE1_M1CR_EDG2ND                             ATIM3_MODE1_M1CR_EDG2ND_Msk
#define ATIM3_MODE1_M1CR_UIE_Pos                            (10U)
#define ATIM3_MODE1_M1CR_UIE_Msk                            (0x1UL << ATIM3_MODE1_M1CR_UIE_Pos)
#define ATIM3_MODE1_M1CR_UIE                                ATIM3_MODE1_M1CR_UIE_Msk
#define ATIM3_MODE1_M1CR_MODE_Pos                           (12U)
#define ATIM3_MODE1_M1CR_MODE_Msk                           (0x3UL << ATIM3_MODE1_M1CR_MODE_Pos)
#define ATIM3_MODE1_M1CR_MODE                               ATIM3_MODE1_M1CR_MODE_Msk
#define ATIM3_MODE1_M1CR_ONESHOT_Pos                        (14U)
#define ATIM3_MODE1_M1CR_ONESHOT_Msk                        (0x1UL << ATIM3_MODE1_M1CR_ONESHOT_Pos)
#define ATIM3_MODE1_M1CR_ONESHOT                            ATIM3_MODE1_M1CR_ONESHOT_Msk

// ATIM3_MODE1_IFR
#define ATIM3_MODE1_IFR_UIF_Pos                             (0U)
#define ATIM3_MODE1_IFR_UIF_Msk                             (0x1UL << ATIM3_MODE1_IFR_UIF_Pos)
#define ATIM3_MODE1_IFR_UIF                                 ATIM3_MODE1_IFR_UIF_Msk
#define ATIM3_MODE1_IFR_CA0F_Pos                            (2U)
#define ATIM3_MODE1_IFR_CA0F_Msk                            (0x1UL << ATIM3_MODE1_IFR_CA0F_Pos)
#define ATIM3_MODE1_IFR_CA0F                                ATIM3_MODE1_IFR_CA0F_Msk

// ATIM3_MODE1_ICLR
#define ATIM3_MODE1_ICLR_UIF_Pos                            (0U)
#define ATIM3_MODE1_ICLR_UIF_Msk                            (0x1UL << ATIM3_MODE1_ICLR_UIF_Pos)
#define ATIM3_MODE1_ICLR_UIF                                ATIM3_MODE1_ICLR_UIF_Msk
#define ATIM3_MODE1_ICLR_CA0F_Pos                           (2U)
#define ATIM3_MODE1_ICLR_CA0F_Msk                           (0x1UL << ATIM3_MODE1_ICLR_CA0F_Pos)
#define ATIM3_MODE1_ICLR_CA0F                               ATIM3_MODE1_ICLR_CA0F_Msk

// ATIM3_MODE1_MSCR
#define ATIM3_MODE1_MSCR_TS_Pos                             (5U)
#define ATIM3_MODE1_MSCR_TS_Msk                             (0x7UL << ATIM3_MODE1_MSCR_TS_Pos)
#define ATIM3_MODE1_MSCR_TS                                 ATIM3_MODE1_MSCR_TS_Msk
#define ATIM3_MODE1_MSCR_IA0S_Pos                           (11U)
#define ATIM3_MODE1_MSCR_IA0S_Msk                           (0x1UL << ATIM3_MODE1_MSCR_IA0S_Pos)
#define ATIM3_MODE1_MSCR_IA0S                               ATIM3_MODE1_MSCR_IA0S_Msk
#define ATIM3_MODE1_MSCR_IB0S_Pos                           (12U)
#define ATIM3_MODE1_MSCR_IB0S_Msk                           (0x1UL << ATIM3_MODE1_MSCR_IB0S_Pos)
#define ATIM3_MODE1_MSCR_IB0S                               ATIM3_MODE1_MSCR_IB0S_Msk

// ATIM3_MODE1_FLTR
#define ATIM3_MODE1_FLTR_FLTA0_Pos                          (0U)
#define ATIM3_MODE1_FLTR_FLTA0_Msk                          (0x7UL << ATIM3_MODE1_FLTR_FLTA0_Pos)
#define ATIM3_MODE1_FLTR_FLTA0                              ATIM3_MODE1_FLTR_FLTA0_Msk
#define ATIM3_MODE1_FLTR_FLTB0_Pos                          (4U)
#define ATIM3_MODE1_FLTR_FLTB0_Msk                          (0x7UL << ATIM3_MODE1_FLTR_FLTB0_Pos)
#define ATIM3_MODE1_FLTR_FLTB0                              ATIM3_MODE1_FLTR_FLTB0_Msk
#define ATIM3_MODE1_FLTR_FLTET_Pos                          (28U)
#define ATIM3_MODE1_FLTR_FLTET_Msk                          (0x7UL << ATIM3_MODE1_FLTR_FLTET_Pos)
#define ATIM3_MODE1_FLTR_FLTET                              ATIM3_MODE1_FLTR_FLTET_Msk
#define ATIM3_MODE1_FLTR_ETP_Pos                            (31U)
#define ATIM3_MODE1_FLTR_ETP_Msk                            (0x1UL << ATIM3_MODE1_FLTR_ETP_Pos)
#define ATIM3_MODE1_FLTR_ETP                                ATIM3_MODE1_FLTR_ETP_Msk

// ATIM3_MODE1_CR0
#define ATIM3_MODE1_CR0_CSA_Pos                             (4U)
#define ATIM3_MODE1_CR0_CSA_Msk                             (0x1UL << ATIM3_MODE1_CR0_CSA_Pos)
#define ATIM3_MODE1_CR0_CSA                                 ATIM3_MODE1_CR0_CSA_Msk
#define ATIM3_MODE1_CR0_CSB_Pos                             (5U)
#define ATIM3_MODE1_CR0_CSB_Msk                             (0x1UL << ATIM3_MODE1_CR0_CSB_Pos)
#define ATIM3_MODE1_CR0_CSB                                 ATIM3_MODE1_CR0_CSB_Msk
#define ATIM3_MODE1_CR0_CIEA_Pos                            (8U)
#define ATIM3_MODE1_CR0_CIEA_Msk                            (0x1UL << ATIM3_MODE1_CR0_CIEA_Pos)
#define ATIM3_MODE1_CR0_CIEA                                ATIM3_MODE1_CR0_CIEA_Msk

// ATIM3_MODE1_CCR0A
#define ATIM3_MODE1_CCR0A_CCR0A_Pos                         (0U)
#define ATIM3_MODE1_CCR0A_CCR0A_Msk                         (0xFFFFUL << ATIM3_MODE1_CCR0A_CCR0A_Pos)
#define ATIM3_MODE1_CCR0A_CCR0A                             ATIM3_MODE1_CCR0A_CCR0A_Msk



//********************    Bits Define For Peripheral ATIM3_MODE23    ********************//
// ATIM3_MODE23_ARR
#define ATIM3_MODE23_ARR_ARR_Pos                            (0U)
#define ATIM3_MODE23_ARR_ARR_Msk                            (0xFFFFUL << ATIM3_MODE23_ARR_ARR_Pos)
#define ATIM3_MODE23_ARR_ARR                                ATIM3_MODE23_ARR_ARR_Msk

// ATIM3_MODE23_CNT
#define ATIM3_MODE23_CNT_CNT_Pos                            (0U)
#define ATIM3_MODE23_CNT_CNT_Msk                            (0xFFFFUL << ATIM3_MODE23_CNT_CNT_Pos)
#define ATIM3_MODE23_CNT_CNT                                ATIM3_MODE23_CNT_CNT_Msk

// ATIM3_MODE23_M23CR
#define ATIM3_MODE23_M23CR_CTEN_Pos                         (0U)
#define ATIM3_MODE23_M23CR_CTEN_Msk                         (0x1UL << ATIM3_MODE23_M23CR_CTEN_Pos)
#define ATIM3_MODE23_M23CR_CTEN                             ATIM3_MODE23_M23CR_CTEN_Msk
#define ATIM3_MODE23_M23CR_COMP_Pos                         (1U)
#define ATIM3_MODE23_M23CR_COMP_Msk                         (0x1UL << ATIM3_MODE23_M23CR_COMP_Pos)
#define ATIM3_MODE23_M23CR_COMP                             ATIM3_MODE23_M23CR_COMP_Msk
#define ATIM3_MODE23_M23CR_CT_Pos                           (2U)
#define ATIM3_MODE23_M23CR_CT_Msk                           (0x1UL << ATIM3_MODE23_M23CR_CT_Pos)
#define ATIM3_MODE23_M23CR_CT                               ATIM3_MODE23_M23CR_CT_Msk
#define ATIM3_MODE23_M23CR_PWM2S_Pos                        (3U)
#define ATIM3_MODE23_M23CR_PWM2S_Msk                        (0x1UL << ATIM3_MODE23_M23CR_PWM2S_Pos)
#define ATIM3_MODE23_M23CR_PWM2S                            ATIM3_MODE23_M23CR_PWM2S_Msk
#define ATIM3_MODE23_M23CR_PRS_Pos                          (4U)
#define ATIM3_MODE23_M23CR_PRS_Msk                          (0x7UL << ATIM3_MODE23_M23CR_PRS_Pos)
#define ATIM3_MODE23_M23CR_PRS                              ATIM3_MODE23_M23CR_PRS_Msk
#define ATIM3_MODE23_M23CR_BUFPEN_Pos                       (7U)
#define ATIM3_MODE23_M23CR_BUFPEN_Msk                       (0x1UL << ATIM3_MODE23_M23CR_BUFPEN_Pos)
#define ATIM3_MODE23_M23CR_BUFPEN                           ATIM3_MODE23_M23CR_BUFPEN_Msk
#define ATIM3_MODE23_M23CR_CRG_Pos                          (8U)
#define ATIM3_MODE23_M23CR_CRG_Msk                          (0x1UL << ATIM3_MODE23_M23CR_CRG_Pos)
#define ATIM3_MODE23_M23CR_CRG                              ATIM3_MODE23_M23CR_CRG_Msk
#define ATIM3_MODE23_M23CR_CFG_Pos                          (9U)
#define ATIM3_MODE23_M23CR_CFG_Msk                          (0x1UL << ATIM3_MODE23_M23CR_CFG_Pos)
#define ATIM3_MODE23_M23CR_CFG                              ATIM3_MODE23_M23CR_CFG_Msk
#define ATIM3_MODE23_M23CR_UIE_Pos                          (10U)
#define ATIM3_MODE23_M23CR_UIE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_UIE_Pos)
#define ATIM3_MODE23_M23CR_UIE                              ATIM3_MODE23_M23CR_UIE_Msk
#define ATIM3_MODE23_M23CR_UDE_Pos                          (11U)
#define ATIM3_MODE23_M23CR_UDE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_UDE_Pos)
#define ATIM3_MODE23_M23CR_UDE                              ATIM3_MODE23_M23CR_UDE_Msk
#define ATIM3_MODE23_M23CR_MODE_Pos                         (12U)
#define ATIM3_MODE23_M23CR_MODE_Msk                         (0x3UL << ATIM3_MODE23_M23CR_MODE_Pos)
#define ATIM3_MODE23_M23CR_MODE                             ATIM3_MODE23_M23CR_MODE_Msk
#define ATIM3_MODE23_M23CR_ONESHOT_Pos                      (14U)
#define ATIM3_MODE23_M23CR_ONESHOT_Msk                      (0x1UL << ATIM3_MODE23_M23CR_ONESHOT_Pos)
#define ATIM3_MODE23_M23CR_ONESHOT                          ATIM3_MODE23_M23CR_ONESHOT_Msk
#define ATIM3_MODE23_M23CR_CSG_Pos                          (15U)
#define ATIM3_MODE23_M23CR_CSG_Msk                          (0x1UL << ATIM3_MODE23_M23CR_CSG_Pos)
#define ATIM3_MODE23_M23CR_CSG                              ATIM3_MODE23_M23CR_CSG_Msk
#define ATIM3_MODE23_M23CR_OCCS_Pos                         (16U)
#define ATIM3_MODE23_M23CR_OCCS_Msk                         (0x1UL << ATIM3_MODE23_M23CR_OCCS_Pos)
#define ATIM3_MODE23_M23CR_OCCS                             ATIM3_MODE23_M23CR_OCCS_Msk
#define ATIM3_MODE23_M23CR_URS_Pos                          (17U)
#define ATIM3_MODE23_M23CR_URS_Msk                          (0x1UL << ATIM3_MODE23_M23CR_URS_Pos)
#define ATIM3_MODE23_M23CR_URS                              ATIM3_MODE23_M23CR_URS_Msk
#define ATIM3_MODE23_M23CR_TDE_Pos                          (18U)
#define ATIM3_MODE23_M23CR_TDE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_TDE_Pos)
#define ATIM3_MODE23_M23CR_TDE                              ATIM3_MODE23_M23CR_TDE_Msk
#define ATIM3_MODE23_M23CR_TIE_Pos                          (19U)
#define ATIM3_MODE23_M23CR_TIE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_TIE_Pos)
#define ATIM3_MODE23_M23CR_TIE                              ATIM3_MODE23_M23CR_TIE_Msk
#define ATIM3_MODE23_M23CR_BIE_Pos                          (20U)
#define ATIM3_MODE23_M23CR_BIE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_BIE_Pos)
#define ATIM3_MODE23_M23CR_BIE                              ATIM3_MODE23_M23CR_BIE_Msk
#define ATIM3_MODE23_M23CR_CIS_Pos                          (21U)
#define ATIM3_MODE23_M23CR_CIS_Msk                          (0x3UL << ATIM3_MODE23_M23CR_CIS_Pos)
#define ATIM3_MODE23_M23CR_CIS                              ATIM3_MODE23_M23CR_CIS_Msk
#define ATIM3_MODE23_M23CR_OCCE_Pos                         (23U)
#define ATIM3_MODE23_M23CR_OCCE_Msk                         (0x1UL << ATIM3_MODE23_M23CR_OCCE_Pos)
#define ATIM3_MODE23_M23CR_OCCE                             ATIM3_MODE23_M23CR_OCCE_Msk
#define ATIM3_MODE23_M23CR_TG_Pos                           (24U)
#define ATIM3_MODE23_M23CR_TG_Msk                           (0x1UL << ATIM3_MODE23_M23CR_TG_Pos)
#define ATIM3_MODE23_M23CR_TG                               ATIM3_MODE23_M23CR_TG_Msk
#define ATIM3_MODE23_M23CR_UG_Pos                           (25U)
#define ATIM3_MODE23_M23CR_UG_Msk                           (0x1UL << ATIM3_MODE23_M23CR_UG_Pos)
#define ATIM3_MODE23_M23CR_UG                               ATIM3_MODE23_M23CR_UG_Msk
#define ATIM3_MODE23_M23CR_BG_Pos                           (26U)
#define ATIM3_MODE23_M23CR_BG_Msk                           (0x1UL << ATIM3_MODE23_M23CR_BG_Pos)
#define ATIM3_MODE23_M23CR_BG                               ATIM3_MODE23_M23CR_BG_Msk
#define ATIM3_MODE23_M23CR_DIR_Pos                          (27U)
#define ATIM3_MODE23_M23CR_DIR_Msk                          (0x1UL << ATIM3_MODE23_M23CR_DIR_Pos)
#define ATIM3_MODE23_M23CR_DIR                              ATIM3_MODE23_M23CR_DIR_Msk
#define ATIM3_MODE23_M23CR_OVE_Pos                          (28U)
#define ATIM3_MODE23_M23CR_OVE_Msk                          (0x1UL << ATIM3_MODE23_M23CR_OVE_Pos)
#define ATIM3_MODE23_M23CR_OVE                              ATIM3_MODE23_M23CR_OVE_Msk
#define ATIM3_MODE23_M23CR_UNDE_Pos                         (29U)
#define ATIM3_MODE23_M23CR_UNDE_Msk                         (0x1UL << ATIM3_MODE23_M23CR_UNDE_Pos)
#define ATIM3_MODE23_M23CR_UNDE                             ATIM3_MODE23_M23CR_UNDE_Msk

// ATIM3_MODE23_IFR
#define ATIM3_MODE23_IFR_UIF_Pos                            (0U)
#define ATIM3_MODE23_IFR_UIF_Msk                            (0x1UL << ATIM3_MODE23_IFR_UIF_Pos)
#define ATIM3_MODE23_IFR_UIF                                ATIM3_MODE23_IFR_UIF_Msk
#define ATIM3_MODE23_IFR_CA0F_Pos                           (2U)
#define ATIM3_MODE23_IFR_CA0F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA0F_Pos)
#define ATIM3_MODE23_IFR_CA0F                               ATIM3_MODE23_IFR_CA0F_Msk
#define ATIM3_MODE23_IFR_CA1F_Pos                           (3U)
#define ATIM3_MODE23_IFR_CA1F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA1F_Pos)
#define ATIM3_MODE23_IFR_CA1F                               ATIM3_MODE23_IFR_CA1F_Msk
#define ATIM3_MODE23_IFR_CA2F_Pos                           (4U)
#define ATIM3_MODE23_IFR_CA2F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA2F_Pos)
#define ATIM3_MODE23_IFR_CA2F                               ATIM3_MODE23_IFR_CA2F_Msk
#define ATIM3_MODE23_IFR_CB0F_Pos                           (5U)
#define ATIM3_MODE23_IFR_CB0F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB0F_Pos)
#define ATIM3_MODE23_IFR_CB0F                               ATIM3_MODE23_IFR_CB0F_Msk
#define ATIM3_MODE23_IFR_CB1F_Pos                           (6U)
#define ATIM3_MODE23_IFR_CB1F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB1F_Pos)
#define ATIM3_MODE23_IFR_CB1F                               ATIM3_MODE23_IFR_CB1F_Msk
#define ATIM3_MODE23_IFR_CB2F_Pos                           (7U)
#define ATIM3_MODE23_IFR_CB2F_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB2F_Pos)
#define ATIM3_MODE23_IFR_CB2F                               ATIM3_MODE23_IFR_CB2F_Msk
#define ATIM3_MODE23_IFR_CA0E_Pos                           (8U)
#define ATIM3_MODE23_IFR_CA0E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA0E_Pos)
#define ATIM3_MODE23_IFR_CA0E                               ATIM3_MODE23_IFR_CA0E_Msk
#define ATIM3_MODE23_IFR_CA1E_Pos                           (9U)
#define ATIM3_MODE23_IFR_CA1E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA1E_Pos)
#define ATIM3_MODE23_IFR_CA1E                               ATIM3_MODE23_IFR_CA1E_Msk
#define ATIM3_MODE23_IFR_CA2E_Pos                           (10U)
#define ATIM3_MODE23_IFR_CA2E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CA2E_Pos)
#define ATIM3_MODE23_IFR_CA2E                               ATIM3_MODE23_IFR_CA2E_Msk
#define ATIM3_MODE23_IFR_CB0E_Pos                           (11U)
#define ATIM3_MODE23_IFR_CB0E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB0E_Pos)
#define ATIM3_MODE23_IFR_CB0E                               ATIM3_MODE23_IFR_CB0E_Msk
#define ATIM3_MODE23_IFR_CB1E_Pos                           (12U)
#define ATIM3_MODE23_IFR_CB1E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB1E_Pos)
#define ATIM3_MODE23_IFR_CB1E                               ATIM3_MODE23_IFR_CB1E_Msk
#define ATIM3_MODE23_IFR_CB2E_Pos                           (13U)
#define ATIM3_MODE23_IFR_CB2E_Msk                           (0x1UL << ATIM3_MODE23_IFR_CB2E_Pos)
#define ATIM3_MODE23_IFR_CB2E                               ATIM3_MODE23_IFR_CB2E_Msk
#define ATIM3_MODE23_IFR_BIF_Pos                            (14U)
#define ATIM3_MODE23_IFR_BIF_Msk                            (0x1UL << ATIM3_MODE23_IFR_BIF_Pos)
#define ATIM3_MODE23_IFR_BIF                                ATIM3_MODE23_IFR_BIF_Msk
#define ATIM3_MODE23_IFR_TIF_Pos                            (15U)
#define ATIM3_MODE23_IFR_TIF_Msk                            (0x1UL << ATIM3_MODE23_IFR_TIF_Pos)
#define ATIM3_MODE23_IFR_TIF                                ATIM3_MODE23_IFR_TIF_Msk
#define ATIM3_MODE23_IFR_OVF_Pos                            (16U)
#define ATIM3_MODE23_IFR_OVF_Msk                            (0x1UL << ATIM3_MODE23_IFR_OVF_Pos)
#define ATIM3_MODE23_IFR_OVF                                ATIM3_MODE23_IFR_OVF_Msk
#define ATIM3_MODE23_IFR_UNDF_Pos                           (17U)
#define ATIM3_MODE23_IFR_UNDF_Msk                           (0x1UL << ATIM3_MODE23_IFR_UNDF_Pos)
#define ATIM3_MODE23_IFR_UNDF                               ATIM3_MODE23_IFR_UNDF_Msk

// ATIM3_MODE23_ICLR
#define ATIM3_MODE23_ICLR_UIF_Pos                           (0U)
#define ATIM3_MODE23_ICLR_UIF_Msk                           (0x1UL << ATIM3_MODE23_ICLR_UIF_Pos)
#define ATIM3_MODE23_ICLR_UIF                               ATIM3_MODE23_ICLR_UIF_Msk
#define ATIM3_MODE23_ICLR_CA0F_Pos                          (2U)
#define ATIM3_MODE23_ICLR_CA0F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA0F_Pos)
#define ATIM3_MODE23_ICLR_CA0F                              ATIM3_MODE23_ICLR_CA0F_Msk
#define ATIM3_MODE23_ICLR_CA1F_Pos                          (3U)
#define ATIM3_MODE23_ICLR_CA1F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA1F_Pos)
#define ATIM3_MODE23_ICLR_CA1F                              ATIM3_MODE23_ICLR_CA1F_Msk
#define ATIM3_MODE23_ICLR_CA2F_Pos                          (4U)
#define ATIM3_MODE23_ICLR_CA2F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA2F_Pos)
#define ATIM3_MODE23_ICLR_CA2F                              ATIM3_MODE23_ICLR_CA2F_Msk
#define ATIM3_MODE23_ICLR_CB0F_Pos                          (5U)
#define ATIM3_MODE23_ICLR_CB0F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB0F_Pos)
#define ATIM3_MODE23_ICLR_CB0F                              ATIM3_MODE23_ICLR_CB0F_Msk
#define ATIM3_MODE23_ICLR_CB1F_Pos                          (6U)
#define ATIM3_MODE23_ICLR_CB1F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB1F_Pos)
#define ATIM3_MODE23_ICLR_CB1F                              ATIM3_MODE23_ICLR_CB1F_Msk
#define ATIM3_MODE23_ICLR_CB2F_Pos                          (7U)
#define ATIM3_MODE23_ICLR_CB2F_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB2F_Pos)
#define ATIM3_MODE23_ICLR_CB2F                              ATIM3_MODE23_ICLR_CB2F_Msk
#define ATIM3_MODE23_ICLR_CA0E_Pos                          (8U)
#define ATIM3_MODE23_ICLR_CA0E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA0E_Pos)
#define ATIM3_MODE23_ICLR_CA0E                              ATIM3_MODE23_ICLR_CA0E_Msk
#define ATIM3_MODE23_ICLR_CA1E_Pos                          (9U)
#define ATIM3_MODE23_ICLR_CA1E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA1E_Pos)
#define ATIM3_MODE23_ICLR_CA1E                              ATIM3_MODE23_ICLR_CA1E_Msk
#define ATIM3_MODE23_ICLR_CA2E_Pos                          (10U)
#define ATIM3_MODE23_ICLR_CA2E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CA2E_Pos)
#define ATIM3_MODE23_ICLR_CA2E                              ATIM3_MODE23_ICLR_CA2E_Msk
#define ATIM3_MODE23_ICLR_CB0E_Pos                          (11U)
#define ATIM3_MODE23_ICLR_CB0E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB0E_Pos)
#define ATIM3_MODE23_ICLR_CB0E                              ATIM3_MODE23_ICLR_CB0E_Msk
#define ATIM3_MODE23_ICLR_CB1E_Pos                          (12U)
#define ATIM3_MODE23_ICLR_CB1E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB1E_Pos)
#define ATIM3_MODE23_ICLR_CB1E                              ATIM3_MODE23_ICLR_CB1E_Msk
#define ATIM3_MODE23_ICLR_CB2E_Pos                          (13U)
#define ATIM3_MODE23_ICLR_CB2E_Msk                          (0x1UL << ATIM3_MODE23_ICLR_CB2E_Pos)
#define ATIM3_MODE23_ICLR_CB2E                              ATIM3_MODE23_ICLR_CB2E_Msk
#define ATIM3_MODE23_ICLR_BIF_Pos                           (14U)
#define ATIM3_MODE23_ICLR_BIF_Msk                           (0x1UL << ATIM3_MODE23_ICLR_BIF_Pos)
#define ATIM3_MODE23_ICLR_BIF                               ATIM3_MODE23_ICLR_BIF_Msk
#define ATIM3_MODE23_ICLR_TIF_Pos                           (15U)
#define ATIM3_MODE23_ICLR_TIF_Msk                           (0x1UL << ATIM3_MODE23_ICLR_TIF_Pos)
#define ATIM3_MODE23_ICLR_TIF                               ATIM3_MODE23_ICLR_TIF_Msk
#define ATIM3_MODE23_ICLR_OVF_Pos                           (16U)
#define ATIM3_MODE23_ICLR_OVF_Msk                           (0x1UL << ATIM3_MODE23_ICLR_OVF_Pos)
#define ATIM3_MODE23_ICLR_OVF                               ATIM3_MODE23_ICLR_OVF_Msk
#define ATIM3_MODE23_ICLR_UNDF_Pos                          (17U)
#define ATIM3_MODE23_ICLR_UNDF_Msk                          (0x1UL << ATIM3_MODE23_ICLR_UNDF_Pos)
#define ATIM3_MODE23_ICLR_UNDF                              ATIM3_MODE23_ICLR_UNDF_Msk

// ATIM3_MODE23_MSCR
#define ATIM3_MODE23_MSCR_MMS_Pos                           (0U)
#define ATIM3_MODE23_MSCR_MMS_Msk                           (0x7UL << ATIM3_MODE23_MSCR_MMS_Pos)
#define ATIM3_MODE23_MSCR_MMS                               ATIM3_MODE23_MSCR_MMS_Msk
#define ATIM3_MODE23_MSCR_MSM_Pos                           (4U)
#define ATIM3_MODE23_MSCR_MSM_Msk                           (0x1UL << ATIM3_MODE23_MSCR_MSM_Pos)
#define ATIM3_MODE23_MSCR_MSM                               ATIM3_MODE23_MSCR_MSM_Msk
#define ATIM3_MODE23_MSCR_TS_Pos                            (5U)
#define ATIM3_MODE23_MSCR_TS_Msk                            (0x7UL << ATIM3_MODE23_MSCR_TS_Pos)
#define ATIM3_MODE23_MSCR_TS                                ATIM3_MODE23_MSCR_TS_Msk
#define ATIM3_MODE23_MSCR_SMS_Pos                           (8U)
#define ATIM3_MODE23_MSCR_SMS_Msk                           (0x7UL << ATIM3_MODE23_MSCR_SMS_Pos)
#define ATIM3_MODE23_MSCR_SMS                               ATIM3_MODE23_MSCR_SMS_Msk
#define ATIM3_MODE23_MSCR_IA0S_Pos                          (11U)
#define ATIM3_MODE23_MSCR_IA0S_Msk                          (0x1UL << ATIM3_MODE23_MSCR_IA0S_Pos)
#define ATIM3_MODE23_MSCR_IA0S                              ATIM3_MODE23_MSCR_IA0S_Msk
#define ATIM3_MODE23_MSCR_IB0S_Pos                          (12U)
#define ATIM3_MODE23_MSCR_IB0S_Msk                          (0x1UL << ATIM3_MODE23_MSCR_IB0S_Pos)
#define ATIM3_MODE23_MSCR_IB0S                              ATIM3_MODE23_MSCR_IB0S_Msk

// ATIM3_MODE23_FLTR
#define ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos                   (0U)
#define ATIM3_MODE23_FLTR_OCMA0_FLTA0_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMA0_FLTA0_Pos)
#define ATIM3_MODE23_FLTR_OCMA0_FLTA0                       ATIM3_MODE23_FLTR_OCMA0_FLTA0_Msk
#define ATIM3_MODE23_FLTR_CCPA0_Pos                         (3U)
#define ATIM3_MODE23_FLTR_CCPA0_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPA0_Pos)
#define ATIM3_MODE23_FLTR_CCPA0                             ATIM3_MODE23_FLTR_CCPA0_Msk
#define ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos                   (4U)
#define ATIM3_MODE23_FLTR_OCMB0_FLTB0_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMB0_FLTB0_Pos)
#define ATIM3_MODE23_FLTR_OCMB0_FLTB0                       ATIM3_MODE23_FLTR_OCMB0_FLTB0_Msk
#define ATIM3_MODE23_FLTR_CCPB0_Pos                         (7U)
#define ATIM3_MODE23_FLTR_CCPB0_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPB0_Pos)
#define ATIM3_MODE23_FLTR_CCPB0                             ATIM3_MODE23_FLTR_CCPB0_Msk
#define ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos                   (8U)
#define ATIM3_MODE23_FLTR_OCMA1_FLTA1_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMA1_FLTA1_Pos)
#define ATIM3_MODE23_FLTR_OCMA1_FLTA1                       ATIM3_MODE23_FLTR_OCMA1_FLTA1_Msk
#define ATIM3_MODE23_FLTR_CCPA1_Pos                         (11U)
#define ATIM3_MODE23_FLTR_CCPA1_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPA1_Pos)
#define ATIM3_MODE23_FLTR_CCPA1                             ATIM3_MODE23_FLTR_CCPA1_Msk
#define ATIM3_MODE23_FLTR_OCMB1_FLTB1_Pos                   (12U)
#define ATIM3_MODE23_FLTR_OCMB1_FLTB1_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMB1_FLTB1_Pos)
#define ATIM3_MODE23_FLTR_OCMB1_FLTB1                       ATIM3_MODE23_FLTR_OCMB1_FLTB1_Msk
#define ATIM3_MODE23_FLTR_CCPB1_Pos                         (15U)
#define ATIM3_MODE23_FLTR_CCPB1_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPB1_Pos)
#define ATIM3_MODE23_FLTR_CCPB1                             ATIM3_MODE23_FLTR_CCPB1_Msk
#define ATIM3_MODE23_FLTR_OCMA2_FLTA2_Pos                   (16U)
#define ATIM3_MODE23_FLTR_OCMA2_FLTA2_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMA2_FLTA2_Pos)
#define ATIM3_MODE23_FLTR_OCMA2_FLTA2                       ATIM3_MODE23_FLTR_OCMA2_FLTA2_Msk
#define ATIM3_MODE23_FLTR_CCPA2_Pos                         (19U)
#define ATIM3_MODE23_FLTR_CCPA2_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPA2_Pos)
#define ATIM3_MODE23_FLTR_CCPA2                             ATIM3_MODE23_FLTR_CCPA2_Msk
#define ATIM3_MODE23_FLTR_OCMB2_FLTB2_Pos                   (20U)
#define ATIM3_MODE23_FLTR_OCMB2_FLTB2_Msk                   (0x7UL << ATIM3_MODE23_FLTR_OCMB2_FLTB2_Pos)
#define ATIM3_MODE23_FLTR_OCMB2_FLTB2                       ATIM3_MODE23_FLTR_OCMB2_FLTB2_Msk
#define ATIM3_MODE23_FLTR_CCPB2_Pos                         (23U)
#define ATIM3_MODE23_FLTR_CCPB2_Msk                         (0x1UL << ATIM3_MODE23_FLTR_CCPB2_Pos)
#define ATIM3_MODE23_FLTR_CCPB2                             ATIM3_MODE23_FLTR_CCPB2_Msk
#define ATIM3_MODE23_FLTR_FLTBK_Pos                         (24U)
#define ATIM3_MODE23_FLTR_FLTBK_Msk                         (0x7UL << ATIM3_MODE23_FLTR_FLTBK_Pos)
#define ATIM3_MODE23_FLTR_FLTBK                             ATIM3_MODE23_FLTR_FLTBK_Msk
#define ATIM3_MODE23_FLTR_BKP_Pos                           (27U)
#define ATIM3_MODE23_FLTR_BKP_Msk                           (0x1UL << ATIM3_MODE23_FLTR_BKP_Pos)
#define ATIM3_MODE23_FLTR_BKP                               ATIM3_MODE23_FLTR_BKP_Msk
#define ATIM3_MODE23_FLTR_FLTET_Pos                         (28U)
#define ATIM3_MODE23_FLTR_FLTET_Msk                         (0x7UL << ATIM3_MODE23_FLTR_FLTET_Pos)
#define ATIM3_MODE23_FLTR_FLTET                             ATIM3_MODE23_FLTR_FLTET_Msk
#define ATIM3_MODE23_FLTR_ETP_Pos                           (31U)
#define ATIM3_MODE23_FLTR_ETP_Msk                           (0x1UL << ATIM3_MODE23_FLTR_ETP_Pos)
#define ATIM3_MODE23_FLTR_ETP                               ATIM3_MODE23_FLTR_ETP_Msk

// ATIM3_MODE23_ADTR
#define ATIM3_MODE23_ADTR_UEVE_Pos                          (0U)
#define ATIM3_MODE23_ADTR_UEVE_Msk                          (0x1UL << ATIM3_MODE23_ADTR_UEVE_Pos)
#define ATIM3_MODE23_ADTR_UEVE                              ATIM3_MODE23_ADTR_UEVE_Msk
#define ATIM3_MODE23_ADTR_CMA0E_Pos                         (1U)
#define ATIM3_MODE23_ADTR_CMA0E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMA0E_Pos)
#define ATIM3_MODE23_ADTR_CMA0E                             ATIM3_MODE23_ADTR_CMA0E_Msk
#define ATIM3_MODE23_ADTR_CMA1E_Pos                         (2U)
#define ATIM3_MODE23_ADTR_CMA1E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMA1E_Pos)
#define ATIM3_MODE23_ADTR_CMA1E                             ATIM3_MODE23_ADTR_CMA1E_Msk
#define ATIM3_MODE23_ADTR_CMA2E_Pos                         (3U)
#define ATIM3_MODE23_ADTR_CMA2E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMA2E_Pos)
#define ATIM3_MODE23_ADTR_CMA2E                             ATIM3_MODE23_ADTR_CMA2E_Msk
#define ATIM3_MODE23_ADTR_CMB0E_Pos                         (4U)
#define ATIM3_MODE23_ADTR_CMB0E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMB0E_Pos)
#define ATIM3_MODE23_ADTR_CMB0E                             ATIM3_MODE23_ADTR_CMB0E_Msk
#define ATIM3_MODE23_ADTR_CMB1E_Pos                         (5U)
#define ATIM3_MODE23_ADTR_CMB1E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMB1E_Pos)
#define ATIM3_MODE23_ADTR_CMB1E                             ATIM3_MODE23_ADTR_CMB1E_Msk
#define ATIM3_MODE23_ADTR_CMB2E_Pos                         (6U)
#define ATIM3_MODE23_ADTR_CMB2E_Msk                         (0x1UL << ATIM3_MODE23_ADTR_CMB2E_Pos)
#define ATIM3_MODE23_ADTR_CMB2E                             ATIM3_MODE23_ADTR_CMB2E_Msk
#define ATIM3_MODE23_ADTR_ADTE_Pos                          (7U)
#define ATIM3_MODE23_ADTR_ADTE_Msk                          (0x1UL << ATIM3_MODE23_ADTR_ADTE_Pos)
#define ATIM3_MODE23_ADTR_ADTE                              ATIM3_MODE23_ADTR_ADTE_Msk

// ATIM3_MODE23_CRCH0
#define ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos                 (0U)
#define ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Msk                 (0x3UL << ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Pos)
#define ATIM3_MODE23_CRCH0_CFA_CRA_BKSA                     ATIM3_MODE23_CRCH0_CFA_CRA_BKSA_Msk
#define ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Pos                 (2U)
#define ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Msk                 (0x3UL << ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Pos)
#define ATIM3_MODE23_CRCH0_CFB_CRB_BKSB                     ATIM3_MODE23_CRCH0_CFB_CRB_BKSB_Msk
#define ATIM3_MODE23_CRCH0_CSA_Pos                          (4U)
#define ATIM3_MODE23_CRCH0_CSA_Msk                          (0x1UL << ATIM3_MODE23_CRCH0_CSA_Pos)
#define ATIM3_MODE23_CRCH0_CSA                              ATIM3_MODE23_CRCH0_CSA_Msk
#define ATIM3_MODE23_CRCH0_CSB_Pos                          (5U)
#define ATIM3_MODE23_CRCH0_CSB_Msk                          (0x1UL << ATIM3_MODE23_CRCH0_CSB_Pos)
#define ATIM3_MODE23_CRCH0_CSB                              ATIM3_MODE23_CRCH0_CSB_Msk
#define ATIM3_MODE23_CRCH0_BUFEA_Pos                        (6U)
#define ATIM3_MODE23_CRCH0_BUFEA_Msk                        (0x1UL << ATIM3_MODE23_CRCH0_BUFEA_Pos)
#define ATIM3_MODE23_CRCH0_BUFEA                            ATIM3_MODE23_CRCH0_BUFEA_Msk
#define ATIM3_MODE23_CRCH0_BUFEB_Pos                        (7U)
#define ATIM3_MODE23_CRCH0_BUFEB_Msk                        (0x1UL << ATIM3_MODE23_CRCH0_BUFEB_Pos)
#define ATIM3_MODE23_CRCH0_BUFEB                            ATIM3_MODE23_CRCH0_BUFEB_Msk
#define ATIM3_MODE23_CRCH0_CIEA_Pos                         (8U)
#define ATIM3_MODE23_CRCH0_CIEA_Msk                         (0x1UL << ATIM3_MODE23_CRCH0_CIEA_Pos)
#define ATIM3_MODE23_CRCH0_CIEA                             ATIM3_MODE23_CRCH0_CIEA_Msk
#define ATIM3_MODE23_CRCH0_CIEB_Pos                         (9U)
#define ATIM3_MODE23_CRCH0_CIEB_Msk                         (0x1UL << ATIM3_MODE23_CRCH0_CIEB_Pos)
#define ATIM3_MODE23_CRCH0_CIEB                             ATIM3_MODE23_CRCH0_CIEB_Msk
#define ATIM3_MODE23_CRCH0_CISB_Pos                         (12U)
#define ATIM3_MODE23_CRCH0_CISB_Msk                         (0x3UL << ATIM3_MODE23_CRCH0_CISB_Pos)
#define ATIM3_MODE23_CRCH0_CISB                             ATIM3_MODE23_CRCH0_CISB_Msk
#define ATIM3_MODE23_CRCH0_CCGA_Pos                         (14U)
#define ATIM3_MODE23_CRCH0_CCGA_Msk                         (0x1UL << ATIM3_MODE23_CRCH0_CCGA_Pos)
#define ATIM3_MODE23_CRCH0_CCGA                             ATIM3_MODE23_CRCH0_CCGA_Msk
#define ATIM3_MODE23_CRCH0_CCGB_Pos                         (15U)
#define ATIM3_MODE23_CRCH0_CCGB_Msk                         (0x1UL << ATIM3_MODE23_CRCH0_CCGB_Pos)
#define ATIM3_MODE23_CRCH0_CCGB                             ATIM3_MODE23_CRCH0_CCGB_Msk

// ATIM3_MODE23_CRCH1
#define ATIM3_MODE23_CRCH1_CFA_CRA_BKSA_Pos                 (0U)
#define ATIM3_MODE23_CRCH1_CFA_CRA_BKSA_Msk                 (0x3UL << ATIM3_MODE23_CRCH1_CFA_CRA_BKSA_Pos)
#define ATIM3_MODE23_CRCH1_CFA_CRA_BKSA                     ATIM3_MODE23_CRCH1_CFA_CRA_BKSA_Msk
#define ATIM3_MODE23_CRCH1_CFB_CRB_BKSB_Pos                 (2U)
#define ATIM3_MODE23_CRCH1_CFB_CRB_BKSB_Msk                 (0x3UL << ATIM3_MODE23_CRCH1_CFB_CRB_BKSB_Pos)
#define ATIM3_MODE23_CRCH1_CFB_CRB_BKSB                     ATIM3_MODE23_CRCH1_CFB_CRB_BKSB_Msk
#define ATIM3_MODE23_CRCH1_CSA_Pos                          (4U)
#define ATIM3_MODE23_CRCH1_CSA_Msk                          (0x1UL << ATIM3_MODE23_CRCH1_CSA_Pos)
#define ATIM3_MODE23_CRCH1_CSA                              ATIM3_MODE23_CRCH1_CSA_Msk
#define ATIM3_MODE23_CRCH1_CSB_Pos                          (5U)
#define ATIM3_MODE23_CRCH1_CSB_Msk                          (0x1UL << ATIM3_MODE23_CRCH1_CSB_Pos)
#define ATIM3_MODE23_CRCH1_CSB                              ATIM3_MODE23_CRCH1_CSB_Msk
#define ATIM3_MODE23_CRCH1_BUFEA_Pos                        (6U)
#define ATIM3_MODE23_CRCH1_BUFEA_Msk                        (0x1UL << ATIM3_MODE23_CRCH1_BUFEA_Pos)
#define ATIM3_MODE23_CRCH1_BUFEA                            ATIM3_MODE23_CRCH1_BUFEA_Msk
#define ATIM3_MODE23_CRCH1_BUFEB_Pos                        (7U)
#define ATIM3_MODE23_CRCH1_BUFEB_Msk                        (0x1UL << ATIM3_MODE23_CRCH1_BUFEB_Pos)
#define ATIM3_MODE23_CRCH1_BUFEB                            ATIM3_MODE23_CRCH1_BUFEB_Msk
#define ATIM3_MODE23_CRCH1_CIEA_Pos                         (8U)
#define ATIM3_MODE23_CRCH1_CIEA_Msk                         (0x1UL << ATIM3_MODE23_CRCH1_CIEA_Pos)
#define ATIM3_MODE23_CRCH1_CIEA                             ATIM3_MODE23_CRCH1_CIEA_Msk
#define ATIM3_MODE23_CRCH1_CIEB_Pos                         (9U)
#define ATIM3_MODE23_CRCH1_CIEB_Msk                         (0x1UL << ATIM3_MODE23_CRCH1_CIEB_Pos)
#define ATIM3_MODE23_CRCH1_CIEB                             ATIM3_MODE23_CRCH1_CIEB_Msk
#define ATIM3_MODE23_CRCH1_CISB_Pos                         (12U)
#define ATIM3_MODE23_CRCH1_CISB_Msk                         (0x3UL << ATIM3_MODE23_CRCH1_CISB_Pos)
#define ATIM3_MODE23_CRCH1_CISB                             ATIM3_MODE23_CRCH1_CISB_Msk
#define ATIM3_MODE23_CRCH1_CCGA_Pos                         (14U)
#define ATIM3_MODE23_CRCH1_CCGA_Msk                         (0x1UL << ATIM3_MODE23_CRCH1_CCGA_Pos)
#define ATIM3_MODE23_CRCH1_CCGA                             ATIM3_MODE23_CRCH1_CCGA_Msk
#define ATIM3_MODE23_CRCH1_CCGB_Pos                         (15U)
#define ATIM3_MODE23_CRCH1_CCGB_Msk                         (0x1UL << ATIM3_MODE23_CRCH1_CCGB_Pos)
#define ATIM3_MODE23_CRCH1_CCGB                             ATIM3_MODE23_CRCH1_CCGB_Msk

// ATIM3_MODE23_CRCH2
#define ATIM3_MODE23_CRCH2_CFA_CRA_BKSA_Pos                 (0U)
#define ATIM3_MODE23_CRCH2_CFA_CRA_BKSA_Msk                 (0x3UL << ATIM3_MODE23_CRCH2_CFA_CRA_BKSA_Pos)
#define ATIM3_MODE23_CRCH2_CFA_CRA_BKSA                     ATIM3_MODE23_CRCH2_CFA_CRA_BKSA_Msk
#define ATIM3_MODE23_CRCH2_CFB_CRB_BKSB_Pos                 (2U)
#define ATIM3_MODE23_CRCH2_CFB_CRB_BKSB_Msk                 (0x3UL << ATIM3_MODE23_CRCH2_CFB_CRB_BKSB_Pos)
#define ATIM3_MODE23_CRCH2_CFB_CRB_BKSB                     ATIM3_MODE23_CRCH2_CFB_CRB_BKSB_Msk
#define ATIM3_MODE23_CRCH2_CSA_Pos                          (4U)
#define ATIM3_MODE23_CRCH2_CSA_Msk                          (0x1UL << ATIM3_MODE23_CRCH2_CSA_Pos)
#define ATIM3_MODE23_CRCH2_CSA                              ATIM3_MODE23_CRCH2_CSA_Msk
#define ATIM3_MODE23_CRCH2_CSB_Pos                          (5U)
#define ATIM3_MODE23_CRCH2_CSB_Msk                          (0x1UL << ATIM3_MODE23_CRCH2_CSB_Pos)
#define ATIM3_MODE23_CRCH2_CSB                              ATIM3_MODE23_CRCH2_CSB_Msk
#define ATIM3_MODE23_CRCH2_BUFEA_Pos                        (6U)
#define ATIM3_MODE23_CRCH2_BUFEA_Msk                        (0x1UL << ATIM3_MODE23_CRCH2_BUFEA_Pos)
#define ATIM3_MODE23_CRCH2_BUFEA                            ATIM3_MODE23_CRCH2_BUFEA_Msk
#define ATIM3_MODE23_CRCH2_BUFEB_Pos                        (7U)
#define ATIM3_MODE23_CRCH2_BUFEB_Msk                        (0x1UL << ATIM3_MODE23_CRCH2_BUFEB_Pos)
#define ATIM3_MODE23_CRCH2_BUFEB                            ATIM3_MODE23_CRCH2_BUFEB_Msk
#define ATIM3_MODE23_CRCH2_CIEA_Pos                         (8U)
#define ATIM3_MODE23_CRCH2_CIEA_Msk                         (0x1UL << ATIM3_MODE23_CRCH2_CIEA_Pos)
#define ATIM3_MODE23_CRCH2_CIEA                             ATIM3_MODE23_CRCH2_CIEA_Msk
#define ATIM3_MODE23_CRCH2_CIEB_Pos                         (9U)
#define ATIM3_MODE23_CRCH2_CIEB_Msk                         (0x1UL << ATIM3_MODE23_CRCH2_CIEB_Pos)
#define ATIM3_MODE23_CRCH2_CIEB                             ATIM3_MODE23_CRCH2_CIEB_Msk
#define ATIM3_MODE23_CRCH2_CISB_Pos                         (12U)
#define ATIM3_MODE23_CRCH2_CISB_Msk                         (0x3UL << ATIM3_MODE23_CRCH2_CISB_Pos)
#define ATIM3_MODE23_CRCH2_CISB                             ATIM3_MODE23_CRCH2_CISB_Msk
#define ATIM3_MODE23_CRCH2_CCGA_Pos                         (14U)
#define ATIM3_MODE23_CRCH2_CCGA_Msk                         (0x1UL << ATIM3_MODE23_CRCH2_CCGA_Pos)
#define ATIM3_MODE23_CRCH2_CCGA                             ATIM3_MODE23_CRCH2_CCGA_Msk
#define ATIM3_MODE23_CRCH2_CCGB_Pos                         (15U)
#define ATIM3_MODE23_CRCH2_CCGB_Msk                         (0x1UL << ATIM3_MODE23_CRCH2_CCGB_Pos)
#define ATIM3_MODE23_CRCH2_CCGB                             ATIM3_MODE23_CRCH2_CCGB_Msk

// ATIM3_MODE23_DTR
#define ATIM3_MODE23_DTR_DTR_Pos                            (0U)
#define ATIM3_MODE23_DTR_DTR_Msk                            (0xFFUL << ATIM3_MODE23_DTR_DTR_Pos)
#define ATIM3_MODE23_DTR_DTR                                ATIM3_MODE23_DTR_DTR_Msk
#define ATIM3_MODE23_DTR_BKSEL_Pos                          (8U)
#define ATIM3_MODE23_DTR_BKSEL_Msk                          (0x1UL << ATIM3_MODE23_DTR_BKSEL_Pos)
#define ATIM3_MODE23_DTR_BKSEL                              ATIM3_MODE23_DTR_BKSEL_Msk
#define ATIM3_MODE23_DTR_DTEN_Pos                           (9U)
#define ATIM3_MODE23_DTR_DTEN_Msk                           (0x1UL << ATIM3_MODE23_DTR_DTEN_Pos)
#define ATIM3_MODE23_DTR_DTEN                               ATIM3_MODE23_DTR_DTEN_Msk
#define ATIM3_MODE23_DTR_BKE_Pos                            (10U)
#define ATIM3_MODE23_DTR_BKE_Msk                            (0x1UL << ATIM3_MODE23_DTR_BKE_Pos)
#define ATIM3_MODE23_DTR_BKE                                ATIM3_MODE23_DTR_BKE_Msk
#define ATIM3_MODE23_DTR_AOE_Pos                            (11U)
#define ATIM3_MODE23_DTR_AOE_Msk                            (0x1UL << ATIM3_MODE23_DTR_AOE_Pos)
#define ATIM3_MODE23_DTR_AOE                                ATIM3_MODE23_DTR_AOE_Msk
#define ATIM3_MODE23_DTR_MOE_Pos                            (12U)
#define ATIM3_MODE23_DTR_MOE_Msk                            (0x1UL << ATIM3_MODE23_DTR_MOE_Pos)
#define ATIM3_MODE23_DTR_MOE                                ATIM3_MODE23_DTR_MOE_Msk
#define ATIM3_MODE23_DTR_SAFEEN_Pos                         (13U)
#define ATIM3_MODE23_DTR_SAFEEN_Msk                         (0x1UL << ATIM3_MODE23_DTR_SAFEEN_Pos)
#define ATIM3_MODE23_DTR_SAFEEN                             ATIM3_MODE23_DTR_SAFEEN_Msk
#define ATIM3_MODE23_DTR_VCE_Pos                            (14U)
#define ATIM3_MODE23_DTR_VCE_Msk                            (0x1UL << ATIM3_MODE23_DTR_VCE_Pos)
#define ATIM3_MODE23_DTR_VCE                                ATIM3_MODE23_DTR_VCE_Msk

// ATIM3_MODE23_RCR
#define ATIM3_MODE23_RCR_RCR_Pos                            (0U)
#define ATIM3_MODE23_RCR_RCR_Msk                            (0xFFUL << ATIM3_MODE23_RCR_RCR_Pos)
#define ATIM3_MODE23_RCR_RCR                                ATIM3_MODE23_RCR_RCR_Msk
#define ATIM3_MODE23_RCR_OV_Pos                             (8U)
#define ATIM3_MODE23_RCR_OV_Msk                             (0x1UL << ATIM3_MODE23_RCR_OV_Pos)
#define ATIM3_MODE23_RCR_OV                                 ATIM3_MODE23_RCR_OV_Msk
#define ATIM3_MODE23_RCR_UND_Pos                            (9U)
#define ATIM3_MODE23_RCR_UND_Msk                            (0x1UL << ATIM3_MODE23_RCR_UND_Pos)
#define ATIM3_MODE23_RCR_UND                                ATIM3_MODE23_RCR_UND_Msk

// ATIM3_MODE23_ARRDM
#define ATIM3_MODE23_ARRDM_ARRDM_Pos                        (0U)
#define ATIM3_MODE23_ARRDM_ARRDM_Msk                        (0xFFFFUL << ATIM3_MODE23_ARRDM_ARRDM_Pos)
#define ATIM3_MODE23_ARRDM_ARRDM                            ATIM3_MODE23_ARRDM_ARRDM_Msk

// ATIM3_MODE23_CCR0A
#define ATIM3_MODE23_CCR0A_CCR0A_Pos                        (0U)
#define ATIM3_MODE23_CCR0A_CCR0A_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR0A_CCR0A_Pos)
#define ATIM3_MODE23_CCR0A_CCR0A                            ATIM3_MODE23_CCR0A_CCR0A_Msk

// ATIM3_MODE23_CCR0B
#define ATIM3_MODE23_CCR0B_CCR0B_Pos                        (0U)
#define ATIM3_MODE23_CCR0B_CCR0B_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR0B_CCR0B_Pos)
#define ATIM3_MODE23_CCR0B_CCR0B                            ATIM3_MODE23_CCR0B_CCR0B_Msk

// ATIM3_MODE23_CCR1A
#define ATIM3_MODE23_CCR1A_CCR1A_Pos                        (0U)
#define ATIM3_MODE23_CCR1A_CCR1A_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR1A_CCR1A_Pos)
#define ATIM3_MODE23_CCR1A_CCR1A                            ATIM3_MODE23_CCR1A_CCR1A_Msk

// ATIM3_MODE23_CCR1B
#define ATIM3_MODE23_CCR1B_CCR1B_Pos                        (0U)
#define ATIM3_MODE23_CCR1B_CCR1B_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR1B_CCR1B_Pos)
#define ATIM3_MODE23_CCR1B_CCR1B                            ATIM3_MODE23_CCR1B_CCR1B_Msk

// ATIM3_MODE23_CCR2A
#define ATIM3_MODE23_CCR2A_CCR2A_Pos                        (0U)
#define ATIM3_MODE23_CCR2A_CCR2A_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR2A_CCR2A_Pos)
#define ATIM3_MODE23_CCR2A_CCR2A                            ATIM3_MODE23_CCR2A_CCR2A_Msk

// ATIM3_MODE23_CCR2B
#define ATIM3_MODE23_CCR2B_CCR2B_Pos                        (0U)
#define ATIM3_MODE23_CCR2B_CCR2B_Msk                        (0xFFFFUL << ATIM3_MODE23_CCR2B_CCR2B_Pos)
#define ATIM3_MODE23_CCR2B_CCR2B                            ATIM3_MODE23_CCR2B_CCR2B_Msk



//********************    Bits Define For Peripheral BTIM    ********************//
// BTIM_ARR
#define BTIM_ARR_ARR_Pos                                    (0U)
#define BTIM_ARR_ARR_Msk                                    (0xFFFFUL << BTIM_ARR_ARR_Pos)
#define BTIM_ARR_ARR                                        BTIM_ARR_ARR_Msk

// BTIM_CNT
#define BTIM_CNT_CNT_Pos                                    (0U)
#define BTIM_CNT_CNT_Msk                                    (0xFFFFUL << BTIM_CNT_CNT_Pos)
#define BTIM_CNT_CNT                                        BTIM_CNT_CNT_Msk

// BTIM_CR
#define BTIM_CR_CEN_Pos                                     (0U)
#define BTIM_CR_CEN_Msk                                     (0x1UL << BTIM_CR_CEN_Pos)
#define BTIM_CR_CEN                                         BTIM_CR_CEN_Msk
#define BTIM_CR_MD_Pos                                      (1U)
#define BTIM_CR_MD_Msk                                      (0x3UL << BTIM_CR_MD_Pos)
#define BTIM_CR_MD                                          BTIM_CR_MD_Msk
#define BTIM_CR_TOGEN_Pos                                   (3U)
#define BTIM_CR_TOGEN_Msk                                   (0x1UL << BTIM_CR_TOGEN_Pos)
#define BTIM_CR_TOGEN                                       BTIM_CR_TOGEN_Msk
#define BTIM_CR_PRS_Pos                                     (4U)
#define BTIM_CR_PRS_Msk                                     (0xFUL << BTIM_CR_PRS_Pos)
#define BTIM_CR_PRS                                         BTIM_CR_PRS_Msk
#define BTIM_CR_OST_Pos                                     (8U)
#define BTIM_CR_OST_Msk                                     (0x1UL << BTIM_CR_OST_Pos)
#define BTIM_CR_OST                                         BTIM_CR_OST_Msk
#define BTIM_CR_TRS_Pos                                     (9U)
#define BTIM_CR_TRS_Msk                                     (0x3UL << BTIM_CR_TRS_Pos)
#define BTIM_CR_TRS                                         BTIM_CR_TRS_Msk
#define BTIM_CR_ETP_Pos                                     (11U)
#define BTIM_CR_ETP_Msk                                     (0x1UL << BTIM_CR_ETP_Pos)
#define BTIM_CR_ETP                                         BTIM_CR_ETP_Msk

// BTIM_IER
#define BTIM_IER_UI_Pos                                     (0U)
#define BTIM_IER_UI_Msk                                     (0x1UL << BTIM_IER_UI_Pos)
#define BTIM_IER_UI                                         BTIM_IER_UI_Msk
#define BTIM_IER_TI_Pos                                     (1U)
#define BTIM_IER_TI_Msk                                     (0x1UL << BTIM_IER_TI_Pos)
#define BTIM_IER_TI                                         BTIM_IER_TI_Msk

// BTIM_IFR
#define BTIM_IFR_UI_Pos                                     (0U)
#define BTIM_IFR_UI_Msk                                     (0x1UL << BTIM_IFR_UI_Pos)
#define BTIM_IFR_UI                                         BTIM_IFR_UI_Msk
#define BTIM_IFR_TI_Pos                                     (1U)
#define BTIM_IFR_TI_Msk                                     (0x1UL << BTIM_IFR_TI_Pos)
#define BTIM_IFR_TI                                         BTIM_IFR_TI_Msk

// BTIM_ICR
#define BTIM_ICR_UI_Pos                                     (0U)
#define BTIM_ICR_UI_Msk                                     (0x1UL << BTIM_ICR_UI_Pos)
#define BTIM_ICR_UI                                         BTIM_ICR_UI_Msk
#define BTIM_ICR_TI_Pos                                     (1U)
#define BTIM_ICR_TI_Msk                                     (0x1UL << BTIM_ICR_TI_Pos)
#define BTIM_ICR_TI                                         BTIM_ICR_TI_Msk

// BTIM_AIFR
#define BTIM_AIFR_UI03_Pos                                  (0U)
#define BTIM_AIFR_UI03_Msk                                  (0x1UL << BTIM_AIFR_UI03_Pos)
#define BTIM_AIFR_UI03                                      BTIM_AIFR_UI03_Msk
#define BTIM_AIFR_TI03_Pos                                  (1U)
#define BTIM_AIFR_TI03_Msk                                  (0x1UL << BTIM_AIFR_TI03_Pos)
#define BTIM_AIFR_TI03                                      BTIM_AIFR_TI03_Msk
#define BTIM_AIFR_UI14_Pos                                  (2U)
#define BTIM_AIFR_UI14_Msk                                  (0x1UL << BTIM_AIFR_UI14_Pos)
#define BTIM_AIFR_UI14                                      BTIM_AIFR_UI14_Msk
#define BTIM_AIFR_TI14_Pos                                  (3U)
#define BTIM_AIFR_TI14_Msk                                  (0x1UL << BTIM_AIFR_TI14_Pos)
#define BTIM_AIFR_TI14                                      BTIM_AIFR_TI14_Msk
#define BTIM_AIFR_UI25_Pos                                  (4U)
#define BTIM_AIFR_UI25_Msk                                  (0x1UL << BTIM_AIFR_UI25_Pos)
#define BTIM_AIFR_UI25                                      BTIM_AIFR_UI25_Msk
#define BTIM_AIFR_TI25_Pos                                  (5U)
#define BTIM_AIFR_TI25_Msk                                  (0x1UL << BTIM_AIFR_TI25_Pos)
#define BTIM_AIFR_TI25                                      BTIM_AIFR_TI25_Msk

// BTIM_AICR
#define BTIM_AICR_UI03_Pos                                  (0U)
#define BTIM_AICR_UI03_Msk                                  (0x1UL << BTIM_AICR_UI03_Pos)
#define BTIM_AICR_UI03                                      BTIM_AICR_UI03_Msk
#define BTIM_AICR_TI03_Pos                                  (1U)
#define BTIM_AICR_TI03_Msk                                  (0x1UL << BTIM_AICR_TI03_Pos)
#define BTIM_AICR_TI03                                      BTIM_AICR_TI03_Msk
#define BTIM_AICR_UI14_Pos                                  (2U)
#define BTIM_AICR_UI14_Msk                                  (0x1UL << BTIM_AICR_UI14_Pos)
#define BTIM_AICR_UI14                                      BTIM_AICR_UI14_Msk
#define BTIM_AICR_TI14_Pos                                  (3U)
#define BTIM_AICR_TI14_Msk                                  (0x1UL << BTIM_AICR_TI14_Pos)
#define BTIM_AICR_TI14                                      BTIM_AICR_TI14_Msk
#define BTIM_AICR_UI25_Pos                                  (4U)
#define BTIM_AICR_UI25_Msk                                  (0x1UL << BTIM_AICR_UI25_Pos)
#define BTIM_AICR_UI25                                      BTIM_AICR_UI25_Msk
#define BTIM_AICR_TI25_Pos                                  (5U)
#define BTIM_AICR_TI25_Msk                                  (0x1UL << BTIM_AICR_TI25_Pos)
#define BTIM_AICR_TI25                                      BTIM_AICR_TI25_Msk



//********************    Bits Define For Peripheral CTRIM    ********************//
// CTRIM_ARR
#define CTRIM_ARR_ARR_Pos                                   (0U)
#define CTRIM_ARR_ARR_Msk                                   (0xFFFFUL << CTRIM_ARR_ARR_Pos)
#define CTRIM_ARR_ARR                                       CTRIM_ARR_ARR_Msk

// CTRIM_CNT
#define CTRIM_CNT_CNT_Pos                                   (0U)
#define CTRIM_CNT_CNT_Msk                                   (0xFFFFUL << CTRIM_CNT_CNT_Pos)
#define CTRIM_CNT_CNT                                       CTRIM_CNT_CNT_Msk

// CTRIM_CR0
#define CTRIM_CR0_STEP_Pos                                  (0U)
#define CTRIM_CR0_STEP_Msk                                  (0x7UL << CTRIM_CR0_STEP_Pos)
#define CTRIM_CR0_STEP                                      CTRIM_CR0_STEP_Msk
#define CTRIM_CR0_ETRFLT_Pos                                (4U)
#define CTRIM_CR0_ETRFLT_Msk                                (0x7UL << CTRIM_CR0_ETRFLT_Pos)
#define CTRIM_CR0_ETRFLT                                    CTRIM_CR0_ETRFLT_Msk
#define CTRIM_CR0_SRC_Pos                                   (8U)
#define CTRIM_CR0_SRC_Msk                                   (0x7UL << CTRIM_CR0_SRC_Pos)
#define CTRIM_CR0_SRC                                       CTRIM_CR0_SRC_Msk

// CTRIM_CR1
#define CTRIM_CR1_EN_Pos                                    (0U)
#define CTRIM_CR1_EN_Msk                                    (0x1UL << CTRIM_CR1_EN_Pos)
#define CTRIM_CR1_EN                                        CTRIM_CR1_EN_Msk
#define CTRIM_CR1_MD_Pos                                    (1U)
#define CTRIM_CR1_MD_Msk                                    (0x3UL << CTRIM_CR1_MD_Pos)
#define CTRIM_CR1_MD                                        CTRIM_CR1_MD_Msk
#define CTRIM_CR1_AUTO_Pos                                  (3U)
#define CTRIM_CR1_AUTO_Msk                                  (0x1UL << CTRIM_CR1_AUTO_Pos)
#define CTRIM_CR1_AUTO                                      CTRIM_CR1_AUTO_Msk
#define CTRIM_CR1_PRS_Pos                                   (4U)
#define CTRIM_CR1_PRS_Msk                                   (0xFUL << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS                                       CTRIM_CR1_PRS_Msk
#define CTRIM_CR1_OST_Pos                                   (8U)
#define CTRIM_CR1_OST_Msk                                   (0x1UL << CTRIM_CR1_OST_Pos)
#define CTRIM_CR1_OST                                       CTRIM_CR1_OST_Msk

// CTRIM_IER
#define CTRIM_IER_UD_Pos                                    (0U)
#define CTRIM_IER_UD_Msk                                    (0x1UL << CTRIM_IER_UD_Pos)
#define CTRIM_IER_UD                                        CTRIM_IER_UD_Msk
#define CTRIM_IER_END_Pos                                   (1U)
#define CTRIM_IER_END_Msk                                   (0x1UL << CTRIM_IER_END_Pos)
#define CTRIM_IER_END                                       CTRIM_IER_END_Msk
#define CTRIM_IER_PS_Pos                                    (2U)
#define CTRIM_IER_PS_Msk                                    (0x1UL << CTRIM_IER_PS_Pos)
#define CTRIM_IER_PS                                        CTRIM_IER_PS_Msk
#define CTRIM_IER_MISS_Pos                                  (3U)
#define CTRIM_IER_MISS_Msk                                  (0x1UL << CTRIM_IER_MISS_Pos)
#define CTRIM_IER_MISS                                      CTRIM_IER_MISS_Msk
#define CTRIM_IER_OV_Pos                                    (4U)
#define CTRIM_IER_OV_Msk                                    (0x1UL << CTRIM_IER_OV_Pos)
#define CTRIM_IER_OV                                        CTRIM_IER_OV_Msk
#define CTRIM_IER_OK_Pos                                    (5U)
#define CTRIM_IER_OK_Msk                                    (0x1UL << CTRIM_IER_OK_Pos)
#define CTRIM_IER_OK                                        CTRIM_IER_OK_Msk

// CTRIM_ISR
#define CTRIM_ISR_UD_Pos                                    (0U)
#define CTRIM_ISR_UD_Msk                                    (0x1UL << CTRIM_ISR_UD_Pos)
#define CTRIM_ISR_UD                                        CTRIM_ISR_UD_Msk
#define CTRIM_ISR_END_Pos                                   (1U)
#define CTRIM_ISR_END_Msk                                   (0x1UL << CTRIM_ISR_END_Pos)
#define CTRIM_ISR_END                                       CTRIM_ISR_END_Msk
#define CTRIM_ISR_PS_Pos                                    (2U)
#define CTRIM_ISR_PS_Msk                                    (0x1UL << CTRIM_ISR_PS_Pos)
#define CTRIM_ISR_PS                                        CTRIM_ISR_PS_Msk
#define CTRIM_ISR_MISS_Pos                                  (3U)
#define CTRIM_ISR_MISS_Msk                                  (0x1UL << CTRIM_ISR_MISS_Pos)
#define CTRIM_ISR_MISS                                      CTRIM_ISR_MISS_Msk
#define CTRIM_ISR_OV_Pos                                    (4U)
#define CTRIM_ISR_OV_Msk                                    (0x1UL << CTRIM_ISR_OV_Pos)
#define CTRIM_ISR_OV                                        CTRIM_ISR_OV_Msk
#define CTRIM_ISR_OK_Pos                                    (5U)
#define CTRIM_ISR_OK_Msk                                    (0x1UL << CTRIM_ISR_OK_Pos)
#define CTRIM_ISR_OK                                        CTRIM_ISR_OK_Msk
#define CTRIM_ISR_DIR_Pos                                   (6U)
#define CTRIM_ISR_DIR_Msk                                   (0x1UL << CTRIM_ISR_DIR_Pos)
#define CTRIM_ISR_DIR                                       CTRIM_ISR_DIR_Msk

// CTRIM_ICR
#define CTRIM_ICR_UD_Pos                                    (0U)
#define CTRIM_ICR_UD_Msk                                    (0x1UL << CTRIM_ICR_UD_Pos)
#define CTRIM_ICR_UD                                        CTRIM_ICR_UD_Msk
#define CTRIM_ICR_END_Pos                                   (1U)
#define CTRIM_ICR_END_Msk                                   (0x1UL << CTRIM_ICR_END_Pos)
#define CTRIM_ICR_END                                       CTRIM_ICR_END_Msk
#define CTRIM_ICR_PS_Pos                                    (2U)
#define CTRIM_ICR_PS_Msk                                    (0x1UL << CTRIM_ICR_PS_Pos)
#define CTRIM_ICR_PS                                        CTRIM_ICR_PS_Msk
#define CTRIM_ICR_MISS_Pos                                  (3U)
#define CTRIM_ICR_MISS_Msk                                  (0x1UL << CTRIM_ICR_MISS_Pos)
#define CTRIM_ICR_MISS                                      CTRIM_ICR_MISS_Msk
#define CTRIM_ICR_OV_Pos                                    (4U)
#define CTRIM_ICR_OV_Msk                                    (0x1UL << CTRIM_ICR_OV_Pos)
#define CTRIM_ICR_OV                                        CTRIM_ICR_OV_Msk
#define CTRIM_ICR_OK_Pos                                    (5U)
#define CTRIM_ICR_OK_Msk                                    (0x1UL << CTRIM_ICR_OK_Pos)
#define CTRIM_ICR_OK                                        CTRIM_ICR_OK_Msk

// CTRIM_FCAP
#define CTRIM_FCAP_FCAP_Pos                                 (0U)
#define CTRIM_FCAP_FCAP_Msk                                 (0xFFFFUL << CTRIM_FCAP_FCAP_Pos)
#define CTRIM_FCAP_FCAP                                     CTRIM_FCAP_FCAP_Msk

// CTRIM_TVAL
#define CTRIM_TVAL_TVAL_Pos                                 (0U)
#define CTRIM_TVAL_TVAL_Msk                                 (0xFFFFUL << CTRIM_TVAL_TVAL_Pos)
#define CTRIM_TVAL_TVAL                                     CTRIM_TVAL_TVAL_Msk

// CTRIM_FLIM
#define CTRIM_FLIM_FLIM_Pos                                 (0U)
#define CTRIM_FLIM_FLIM_Msk                                 (0xFFFUL << CTRIM_FLIM_FLIM_Pos)
#define CTRIM_FLIM_FLIM                                     CTRIM_FLIM_FLIM_Msk



//********************    Bits Define For Peripheral FLASH    ********************//
// FLASH_CR
#define FLASH_CR_OP_Pos                                     (0U)
#define FLASH_CR_OP_Msk                                     (0x3UL << FLASH_CR_OP_Pos)
#define FLASH_CR_OP                                         FLASH_CR_OP_Msk
#define FLASH_CR_WAIT_Pos                                   (2U)
#define FLASH_CR_WAIT_Msk                                   (0x3UL << FLASH_CR_WAIT_Pos)
#define FLASH_CR_WAIT                                       FLASH_CR_WAIT_Msk
#define FLASH_CR_BUSY_Pos                                   (4U)
#define FLASH_CR_BUSY_Msk                                   (0x1UL << FLASH_CR_BUSY_Pos)
#define FLASH_CR_BUSY                                       FLASH_CR_BUSY_Msk
#define FLASH_CR_IE_Pos                                     (5U)
#define FLASH_CR_IE_Msk                                     (0x3UL << FLASH_CR_IE_Pos)
#define FLASH_CR_IE                                         FLASH_CR_IE_Msk
#define FLASH_CR_DPSTB_EN_Pos                               (9U)
#define FLASH_CR_DPSTB_EN_Msk                               (0x1UL << FLASH_CR_DPSTB_EN_Pos)
#define FLASH_CR_DPSTB_EN                                   FLASH_CR_DPSTB_EN_Msk
#define FLASH_CR_CONTP_Pos                                  (10U)
#define FLASH_CR_CONTP_Msk                                  (0x1UL << FLASH_CR_CONTP_Pos)
#define FLASH_CR_CONTP                                      FLASH_CR_CONTP_Msk
#define FLASH_CR_RO_Pos                                     (11U)
#define FLASH_CR_RO_Msk                                     (0x1UL << FLASH_CR_RO_Pos)
#define FLASH_CR_RO                                         FLASH_CR_RO_Msk

// FLASH_IFR
#define FLASH_IFR_PC_Pos                                    (0U)
#define FLASH_IFR_PC_Msk                                    (0x1UL << FLASH_IFR_PC_Pos)
#define FLASH_IFR_PC                                        FLASH_IFR_PC_Msk
#define FLASH_IFR_PROT_Pos                                  (1U)
#define FLASH_IFR_PROT_Msk                                  (0x1UL << FLASH_IFR_PROT_Pos)
#define FLASH_IFR_PROT                                      FLASH_IFR_PROT_Msk

// FLASH_ICLR
#define FLASH_ICLR_PC_Pos                                   (0U)
#define FLASH_ICLR_PC_Msk                                   (0x1UL << FLASH_ICLR_PC_Pos)
#define FLASH_ICLR_PC                                       FLASH_ICLR_PC_Msk
#define FLASH_ICLR_PROT_Pos                                 (1U)
#define FLASH_ICLR_PROT_Msk                                 (0x1UL << FLASH_ICLR_PROT_Pos)
#define FLASH_ICLR_PROT                                     FLASH_ICLR_PROT_Msk

// FLASH_BYPASS
#define FLASH_BYPASS_BYSEQ_Pos                              (0U)
#define FLASH_BYPASS_BYSEQ_Msk                              (0xFFFFUL << FLASH_BYPASS_BYSEQ_Pos)
#define FLASH_BYPASS_BYSEQ                                  FLASH_BYPASS_BYSEQ_Msk

// FLASH_SLOCK0
#define FLASH_SLOCK0_SLOCK_Pos                              (0U)
#define FLASH_SLOCK0_SLOCK_Msk                              (0xFFFFFFFFUL << FLASH_SLOCK0_SLOCK_Pos)
#define FLASH_SLOCK0_SLOCK                                  FLASH_SLOCK0_SLOCK_Msk

// FLASH_LOCK_ST
#define FLASH_LOCK_ST_LOCK_ST_Pos                           (0U)
#define FLASH_LOCK_ST_LOCK_ST_Msk                           (0x3UL << FLASH_LOCK_ST_LOCK_ST_Pos)
#define FLASH_LOCK_ST_LOCK_ST                               FLASH_LOCK_ST_LOCK_ST_Msk



//********************    Bits Define For Peripheral GPIO    ********************//
// GPIO_PIN00_SEL
#define GPIO_PIN00_SEL_SEL_Pos                              (0U)
#define GPIO_PIN00_SEL_SEL_Msk                              (0x7UL << GPIO_PIN00_SEL_SEL_Pos)
#define GPIO_PIN00_SEL_SEL                                  GPIO_PIN00_SEL_SEL_Msk

// GPIO_PIN01_SEL
#define GPIO_PIN01_SEL_SEL_Pos                              (0U)
#define GPIO_PIN01_SEL_SEL_Msk                              (0x7UL << GPIO_PIN01_SEL_SEL_Pos)
#define GPIO_PIN01_SEL_SEL                                  GPIO_PIN01_SEL_SEL_Msk

// GPIO_PIN02_SEL
#define GPIO_PIN02_SEL_SEL_Pos                              (0U)
#define GPIO_PIN02_SEL_SEL_Msk                              (0x7UL << GPIO_PIN02_SEL_SEL_Pos)
#define GPIO_PIN02_SEL_SEL                                  GPIO_PIN02_SEL_SEL_Msk

// GPIO_PIN03_SEL
#define GPIO_PIN03_SEL_SEL_Pos                              (0U)
#define GPIO_PIN03_SEL_SEL_Msk                              (0x7UL << GPIO_PIN03_SEL_SEL_Pos)
#define GPIO_PIN03_SEL_SEL                                  GPIO_PIN03_SEL_SEL_Msk

// GPIO_PIN04_SEL
#define GPIO_PIN04_SEL_SEL_Pos                              (0U)
#define GPIO_PIN04_SEL_SEL_Msk                              (0x7UL << GPIO_PIN04_SEL_SEL_Pos)
#define GPIO_PIN04_SEL_SEL                                  GPIO_PIN04_SEL_SEL_Msk

// GPIO_PIN05_SEL
#define GPIO_PIN05_SEL_SEL_Pos                              (0U)
#define GPIO_PIN05_SEL_SEL_Msk                              (0x7UL << GPIO_PIN05_SEL_SEL_Pos)
#define GPIO_PIN05_SEL_SEL                                  GPIO_PIN05_SEL_SEL_Msk

// GPIO_PIN06_SEL
#define GPIO_PIN06_SEL_SEL_Pos                              (0U)
#define GPIO_PIN06_SEL_SEL_Msk                              (0x7UL << GPIO_PIN06_SEL_SEL_Pos)
#define GPIO_PIN06_SEL_SEL                                  GPIO_PIN06_SEL_SEL_Msk

// GPIO_PIN07_SEL
#define GPIO_PIN07_SEL_SEL_Pos                              (0U)
#define GPIO_PIN07_SEL_SEL_Msk                              (0x7UL << GPIO_PIN07_SEL_SEL_Pos)
#define GPIO_PIN07_SEL_SEL                                  GPIO_PIN07_SEL_SEL_Msk

// GPIO_PIN08_SEL
#define GPIO_PIN08_SEL_SEL_Pos                              (0U)
#define GPIO_PIN08_SEL_SEL_Msk                              (0x7UL << GPIO_PIN08_SEL_SEL_Pos)
#define GPIO_PIN08_SEL_SEL                                  GPIO_PIN08_SEL_SEL_Msk

// GPIO_PIN09_SEL
#define GPIO_PIN09_SEL_SEL_Pos                              (0U)
#define GPIO_PIN09_SEL_SEL_Msk                              (0x7UL << GPIO_PIN09_SEL_SEL_Pos)
#define GPIO_PIN09_SEL_SEL                                  GPIO_PIN09_SEL_SEL_Msk

// GPIO_PIN10_SEL
#define GPIO_PIN10_SEL_SEL_Pos                              (0U)
#define GPIO_PIN10_SEL_SEL_Msk                              (0x7UL << GPIO_PIN10_SEL_SEL_Pos)
#define GPIO_PIN10_SEL_SEL                                  GPIO_PIN10_SEL_SEL_Msk

// GPIO_PIN11_SEL
#define GPIO_PIN11_SEL_SEL_Pos                              (0U)
#define GPIO_PIN11_SEL_SEL_Msk                              (0x7UL << GPIO_PIN11_SEL_SEL_Pos)
#define GPIO_PIN11_SEL_SEL                                  GPIO_PIN11_SEL_SEL_Msk

// GPIO_PIN12_SEL
#define GPIO_PIN12_SEL_SEL_Pos                              (0U)
#define GPIO_PIN12_SEL_SEL_Msk                              (0x7UL << GPIO_PIN12_SEL_SEL_Pos)
#define GPIO_PIN12_SEL_SEL                                  GPIO_PIN12_SEL_SEL_Msk

// GPIO_PIN13_SEL
#define GPIO_PIN13_SEL_SEL_Pos                              (0U)
#define GPIO_PIN13_SEL_SEL_Msk                              (0x7UL << GPIO_PIN13_SEL_SEL_Pos)
#define GPIO_PIN13_SEL_SEL                                  GPIO_PIN13_SEL_SEL_Msk

// GPIO_PIN14_SEL
#define GPIO_PIN14_SEL_SEL_Pos                              (0U)
#define GPIO_PIN14_SEL_SEL_Msk                              (0x7UL << GPIO_PIN14_SEL_SEL_Pos)
#define GPIO_PIN14_SEL_SEL                                  GPIO_PIN14_SEL_SEL_Msk

// GPIO_PIN15_SEL
#define GPIO_PIN15_SEL_SEL_Pos                              (0U)
#define GPIO_PIN15_SEL_SEL_Msk                              (0x7UL << GPIO_PIN15_SEL_SEL_Pos)
#define GPIO_PIN15_SEL_SEL                                  GPIO_PIN15_SEL_SEL_Msk

// GPIO_DIR
#define GPIO_DIR_PIN00_Pos                                  (0U)
#define GPIO_DIR_PIN00_Msk                                  (0x1UL << GPIO_DIR_PIN00_Pos)
#define GPIO_DIR_PIN00                                      GPIO_DIR_PIN00_Msk
#define GPIO_DIR_PIN01_Pos                                  (1U)
#define GPIO_DIR_PIN01_Msk                                  (0x1UL << GPIO_DIR_PIN01_Pos)
#define GPIO_DIR_PIN01                                      GPIO_DIR_PIN01_Msk
#define GPIO_DIR_PIN02_Pos                                  (2U)
#define GPIO_DIR_PIN02_Msk                                  (0x1UL << GPIO_DIR_PIN02_Pos)
#define GPIO_DIR_PIN02                                      GPIO_DIR_PIN02_Msk
#define GPIO_DIR_PIN03_Pos                                  (3U)
#define GPIO_DIR_PIN03_Msk                                  (0x1UL << GPIO_DIR_PIN03_Pos)
#define GPIO_DIR_PIN03                                      GPIO_DIR_PIN03_Msk
#define GPIO_DIR_PIN04_Pos                                  (4U)
#define GPIO_DIR_PIN04_Msk                                  (0x1UL << GPIO_DIR_PIN04_Pos)
#define GPIO_DIR_PIN04                                      GPIO_DIR_PIN04_Msk
#define GPIO_DIR_PIN05_Pos                                  (5U)
#define GPIO_DIR_PIN05_Msk                                  (0x1UL << GPIO_DIR_PIN05_Pos)
#define GPIO_DIR_PIN05                                      GPIO_DIR_PIN05_Msk
#define GPIO_DIR_PIN06_Pos                                  (6U)
#define GPIO_DIR_PIN06_Msk                                  (0x1UL << GPIO_DIR_PIN06_Pos)
#define GPIO_DIR_PIN06                                      GPIO_DIR_PIN06_Msk
#define GPIO_DIR_PIN07_Pos                                  (7U)
#define GPIO_DIR_PIN07_Msk                                  (0x1UL << GPIO_DIR_PIN07_Pos)
#define GPIO_DIR_PIN07                                      GPIO_DIR_PIN07_Msk
#define GPIO_DIR_PIN08_Pos                                  (8U)
#define GPIO_DIR_PIN08_Msk                                  (0x1UL << GPIO_DIR_PIN08_Pos)
#define GPIO_DIR_PIN08                                      GPIO_DIR_PIN08_Msk
#define GPIO_DIR_PIN09_Pos                                  (9U)
#define GPIO_DIR_PIN09_Msk                                  (0x1UL << GPIO_DIR_PIN09_Pos)
#define GPIO_DIR_PIN09                                      GPIO_DIR_PIN09_Msk
#define GPIO_DIR_PIN10_Pos                                  (10U)
#define GPIO_DIR_PIN10_Msk                                  (0x1UL << GPIO_DIR_PIN10_Pos)
#define GPIO_DIR_PIN10                                      GPIO_DIR_PIN10_Msk
#define GPIO_DIR_PIN11_Pos                                  (11U)
#define GPIO_DIR_PIN11_Msk                                  (0x1UL << GPIO_DIR_PIN11_Pos)
#define GPIO_DIR_PIN11                                      GPIO_DIR_PIN11_Msk
#define GPIO_DIR_PIN12_Pos                                  (12U)
#define GPIO_DIR_PIN12_Msk                                  (0x1UL << GPIO_DIR_PIN12_Pos)
#define GPIO_DIR_PIN12                                      GPIO_DIR_PIN12_Msk
#define GPIO_DIR_PIN13_Pos                                  (13U)
#define GPIO_DIR_PIN13_Msk                                  (0x1UL << GPIO_DIR_PIN13_Pos)
#define GPIO_DIR_PIN13                                      GPIO_DIR_PIN13_Msk
#define GPIO_DIR_PIN14_Pos                                  (14U)
#define GPIO_DIR_PIN14_Msk                                  (0x1UL << GPIO_DIR_PIN14_Pos)
#define GPIO_DIR_PIN14                                      GPIO_DIR_PIN14_Msk
#define GPIO_DIR_PIN15_Pos                                  (15U)
#define GPIO_DIR_PIN15_Msk                                  (0x1UL << GPIO_DIR_PIN15_Pos)
#define GPIO_DIR_PIN15                                      GPIO_DIR_PIN15_Msk

// GPIO_IN
#define GPIO_IN_PIN00_Pos                                   (0U)
#define GPIO_IN_PIN00_Msk                                   (0x1UL << GPIO_IN_PIN00_Pos)
#define GPIO_IN_PIN00                                       GPIO_IN_PIN00_Msk
#define GPIO_IN_PIN01_Pos                                   (1U)
#define GPIO_IN_PIN01_Msk                                   (0x1UL << GPIO_IN_PIN01_Pos)
#define GPIO_IN_PIN01                                       GPIO_IN_PIN01_Msk
#define GPIO_IN_PIN02_Pos                                   (2U)
#define GPIO_IN_PIN02_Msk                                   (0x1UL << GPIO_IN_PIN02_Pos)
#define GPIO_IN_PIN02                                       GPIO_IN_PIN02_Msk
#define GPIO_IN_PIN03_Pos                                   (3U)
#define GPIO_IN_PIN03_Msk                                   (0x1UL << GPIO_IN_PIN03_Pos)
#define GPIO_IN_PIN03                                       GPIO_IN_PIN03_Msk
#define GPIO_IN_PIN04_Pos                                   (4U)
#define GPIO_IN_PIN04_Msk                                   (0x1UL << GPIO_IN_PIN04_Pos)
#define GPIO_IN_PIN04                                       GPIO_IN_PIN04_Msk
#define GPIO_IN_PIN05_Pos                                   (5U)
#define GPIO_IN_PIN05_Msk                                   (0x1UL << GPIO_IN_PIN05_Pos)
#define GPIO_IN_PIN05                                       GPIO_IN_PIN05_Msk
#define GPIO_IN_PIN06_Pos                                   (6U)
#define GPIO_IN_PIN06_Msk                                   (0x1UL << GPIO_IN_PIN06_Pos)
#define GPIO_IN_PIN06                                       GPIO_IN_PIN06_Msk
#define GPIO_IN_PIN07_Pos                                   (7U)
#define GPIO_IN_PIN07_Msk                                   (0x1UL << GPIO_IN_PIN07_Pos)
#define GPIO_IN_PIN07                                       GPIO_IN_PIN07_Msk
#define GPIO_IN_PIN08_Pos                                   (8U)
#define GPIO_IN_PIN08_Msk                                   (0x1UL << GPIO_IN_PIN08_Pos)
#define GPIO_IN_PIN08                                       GPIO_IN_PIN08_Msk
#define GPIO_IN_PIN09_Pos                                   (9U)
#define GPIO_IN_PIN09_Msk                                   (0x1UL << GPIO_IN_PIN09_Pos)
#define GPIO_IN_PIN09                                       GPIO_IN_PIN09_Msk
#define GPIO_IN_PIN10_Pos                                   (10U)
#define GPIO_IN_PIN10_Msk                                   (0x1UL << GPIO_IN_PIN10_Pos)
#define GPIO_IN_PIN10                                       GPIO_IN_PIN10_Msk
#define GPIO_IN_PIN11_Pos                                   (11U)
#define GPIO_IN_PIN11_Msk                                   (0x1UL << GPIO_IN_PIN11_Pos)
#define GPIO_IN_PIN11                                       GPIO_IN_PIN11_Msk
#define GPIO_IN_PIN12_Pos                                   (12U)
#define GPIO_IN_PIN12_Msk                                   (0x1UL << GPIO_IN_PIN12_Pos)
#define GPIO_IN_PIN12                                       GPIO_IN_PIN12_Msk
#define GPIO_IN_PIN13_Pos                                   (13U)
#define GPIO_IN_PIN13_Msk                                   (0x1UL << GPIO_IN_PIN13_Pos)
#define GPIO_IN_PIN13                                       GPIO_IN_PIN13_Msk
#define GPIO_IN_PIN14_Pos                                   (14U)
#define GPIO_IN_PIN14_Msk                                   (0x1UL << GPIO_IN_PIN14_Pos)
#define GPIO_IN_PIN14                                       GPIO_IN_PIN14_Msk
#define GPIO_IN_PIN15_Pos                                   (15U)
#define GPIO_IN_PIN15_Msk                                   (0x1UL << GPIO_IN_PIN15_Pos)
#define GPIO_IN_PIN15                                       GPIO_IN_PIN15_Msk

// GPIO_OUT
#define GPIO_OUT_PIN00_Pos                                  (0U)
#define GPIO_OUT_PIN00_Msk                                  (0x1UL << GPIO_OUT_PIN00_Pos)
#define GPIO_OUT_PIN00                                      GPIO_OUT_PIN00_Msk
#define GPIO_OUT_PIN01_Pos                                  (1U)
#define GPIO_OUT_PIN01_Msk                                  (0x1UL << GPIO_OUT_PIN01_Pos)
#define GPIO_OUT_PIN01                                      GPIO_OUT_PIN01_Msk
#define GPIO_OUT_PIN02_Pos                                  (2U)
#define GPIO_OUT_PIN02_Msk                                  (0x1UL << GPIO_OUT_PIN02_Pos)
#define GPIO_OUT_PIN02                                      GPIO_OUT_PIN02_Msk
#define GPIO_OUT_PIN03_Pos                                  (3U)
#define GPIO_OUT_PIN03_Msk                                  (0x1UL << GPIO_OUT_PIN03_Pos)
#define GPIO_OUT_PIN03                                      GPIO_OUT_PIN03_Msk
#define GPIO_OUT_PIN04_Pos                                  (4U)
#define GPIO_OUT_PIN04_Msk                                  (0x1UL << GPIO_OUT_PIN04_Pos)
#define GPIO_OUT_PIN04                                      GPIO_OUT_PIN04_Msk
#define GPIO_OUT_PIN05_Pos                                  (5U)
#define GPIO_OUT_PIN05_Msk                                  (0x1UL << GPIO_OUT_PIN05_Pos)
#define GPIO_OUT_PIN05                                      GPIO_OUT_PIN05_Msk
#define GPIO_OUT_PIN06_Pos                                  (6U)
#define GPIO_OUT_PIN06_Msk                                  (0x1UL << GPIO_OUT_PIN06_Pos)
#define GPIO_OUT_PIN06                                      GPIO_OUT_PIN06_Msk
#define GPIO_OUT_PIN07_Pos                                  (7U)
#define GPIO_OUT_PIN07_Msk                                  (0x1UL << GPIO_OUT_PIN07_Pos)
#define GPIO_OUT_PIN07                                      GPIO_OUT_PIN07_Msk
#define GPIO_OUT_PIN08_Pos                                  (8U)
#define GPIO_OUT_PIN08_Msk                                  (0x1UL << GPIO_OUT_PIN08_Pos)
#define GPIO_OUT_PIN08                                      GPIO_OUT_PIN08_Msk
#define GPIO_OUT_PIN09_Pos                                  (9U)
#define GPIO_OUT_PIN09_Msk                                  (0x1UL << GPIO_OUT_PIN09_Pos)
#define GPIO_OUT_PIN09                                      GPIO_OUT_PIN09_Msk
#define GPIO_OUT_PIN10_Pos                                  (10U)
#define GPIO_OUT_PIN10_Msk                                  (0x1UL << GPIO_OUT_PIN10_Pos)
#define GPIO_OUT_PIN10                                      GPIO_OUT_PIN10_Msk
#define GPIO_OUT_PIN11_Pos                                  (11U)
#define GPIO_OUT_PIN11_Msk                                  (0x1UL << GPIO_OUT_PIN11_Pos)
#define GPIO_OUT_PIN11                                      GPIO_OUT_PIN11_Msk
#define GPIO_OUT_PIN12_Pos                                  (12U)
#define GPIO_OUT_PIN12_Msk                                  (0x1UL << GPIO_OUT_PIN12_Pos)
#define GPIO_OUT_PIN12                                      GPIO_OUT_PIN12_Msk
#define GPIO_OUT_PIN13_Pos                                  (13U)
#define GPIO_OUT_PIN13_Msk                                  (0x1UL << GPIO_OUT_PIN13_Pos)
#define GPIO_OUT_PIN13                                      GPIO_OUT_PIN13_Msk
#define GPIO_OUT_PIN14_Pos                                  (14U)
#define GPIO_OUT_PIN14_Msk                                  (0x1UL << GPIO_OUT_PIN14_Pos)
#define GPIO_OUT_PIN14                                      GPIO_OUT_PIN14_Msk
#define GPIO_OUT_PIN15_Pos                                  (15U)
#define GPIO_OUT_PIN15_Msk                                  (0x1UL << GPIO_OUT_PIN15_Pos)
#define GPIO_OUT_PIN15                                      GPIO_OUT_PIN15_Msk

// GPIO_ADS
#define GPIO_ADS_PIN00_Pos                                  (0U)
#define GPIO_ADS_PIN00_Msk                                  (0x1UL << GPIO_ADS_PIN00_Pos)
#define GPIO_ADS_PIN00                                      GPIO_ADS_PIN00_Msk
#define GPIO_ADS_PIN01_Pos                                  (1U)
#define GPIO_ADS_PIN01_Msk                                  (0x1UL << GPIO_ADS_PIN01_Pos)
#define GPIO_ADS_PIN01                                      GPIO_ADS_PIN01_Msk
#define GPIO_ADS_PIN02_Pos                                  (2U)
#define GPIO_ADS_PIN02_Msk                                  (0x1UL << GPIO_ADS_PIN02_Pos)
#define GPIO_ADS_PIN02                                      GPIO_ADS_PIN02_Msk
#define GPIO_ADS_PIN03_Pos                                  (3U)
#define GPIO_ADS_PIN03_Msk                                  (0x1UL << GPIO_ADS_PIN03_Pos)
#define GPIO_ADS_PIN03                                      GPIO_ADS_PIN03_Msk
#define GPIO_ADS_PIN04_Pos                                  (4U)
#define GPIO_ADS_PIN04_Msk                                  (0x1UL << GPIO_ADS_PIN04_Pos)
#define GPIO_ADS_PIN04                                      GPIO_ADS_PIN04_Msk
#define GPIO_ADS_PIN05_Pos                                  (5U)
#define GPIO_ADS_PIN05_Msk                                  (0x1UL << GPIO_ADS_PIN05_Pos)
#define GPIO_ADS_PIN05                                      GPIO_ADS_PIN05_Msk
#define GPIO_ADS_PIN06_Pos                                  (6U)
#define GPIO_ADS_PIN06_Msk                                  (0x1UL << GPIO_ADS_PIN06_Pos)
#define GPIO_ADS_PIN06                                      GPIO_ADS_PIN06_Msk
#define GPIO_ADS_PIN07_Pos                                  (7U)
#define GPIO_ADS_PIN07_Msk                                  (0x1UL << GPIO_ADS_PIN07_Pos)
#define GPIO_ADS_PIN07                                      GPIO_ADS_PIN07_Msk
#define GPIO_ADS_PIN08_Pos                                  (8U)
#define GPIO_ADS_PIN08_Msk                                  (0x1UL << GPIO_ADS_PIN08_Pos)
#define GPIO_ADS_PIN08                                      GPIO_ADS_PIN08_Msk
#define GPIO_ADS_PIN09_Pos                                  (9U)
#define GPIO_ADS_PIN09_Msk                                  (0x1UL << GPIO_ADS_PIN09_Pos)
#define GPIO_ADS_PIN09                                      GPIO_ADS_PIN09_Msk
#define GPIO_ADS_PIN10_Pos                                  (10U)
#define GPIO_ADS_PIN10_Msk                                  (0x1UL << GPIO_ADS_PIN10_Pos)
#define GPIO_ADS_PIN10                                      GPIO_ADS_PIN10_Msk
#define GPIO_ADS_PIN11_Pos                                  (11U)
#define GPIO_ADS_PIN11_Msk                                  (0x1UL << GPIO_ADS_PIN11_Pos)
#define GPIO_ADS_PIN11                                      GPIO_ADS_PIN11_Msk
#define GPIO_ADS_PIN12_Pos                                  (12U)
#define GPIO_ADS_PIN12_Msk                                  (0x1UL << GPIO_ADS_PIN12_Pos)
#define GPIO_ADS_PIN12                                      GPIO_ADS_PIN12_Msk
#define GPIO_ADS_PIN13_Pos                                  (13U)
#define GPIO_ADS_PIN13_Msk                                  (0x1UL << GPIO_ADS_PIN13_Pos)
#define GPIO_ADS_PIN13                                      GPIO_ADS_PIN13_Msk
#define GPIO_ADS_PIN14_Pos                                  (14U)
#define GPIO_ADS_PIN14_Msk                                  (0x1UL << GPIO_ADS_PIN14_Pos)
#define GPIO_ADS_PIN14                                      GPIO_ADS_PIN14_Msk
#define GPIO_ADS_PIN15_Pos                                  (15U)
#define GPIO_ADS_PIN15_Msk                                  (0x1UL << GPIO_ADS_PIN15_Pos)
#define GPIO_ADS_PIN15                                      GPIO_ADS_PIN15_Msk

// GPIO_BSET
#define GPIO_BSET_PIN00_Pos                                 (0U)
#define GPIO_BSET_PIN00_Msk                                 (0x1UL << GPIO_BSET_PIN00_Pos)
#define GPIO_BSET_PIN00                                     GPIO_BSET_PIN00_Msk
#define GPIO_BSET_PIN01_Pos                                 (1U)
#define GPIO_BSET_PIN01_Msk                                 (0x1UL << GPIO_BSET_PIN01_Pos)
#define GPIO_BSET_PIN01                                     GPIO_BSET_PIN01_Msk
#define GPIO_BSET_PIN02_Pos                                 (2U)
#define GPIO_BSET_PIN02_Msk                                 (0x1UL << GPIO_BSET_PIN02_Pos)
#define GPIO_BSET_PIN02                                     GPIO_BSET_PIN02_Msk
#define GPIO_BSET_PIN03_Pos                                 (3U)
#define GPIO_BSET_PIN03_Msk                                 (0x1UL << GPIO_BSET_PIN03_Pos)
#define GPIO_BSET_PIN03                                     GPIO_BSET_PIN03_Msk
#define GPIO_BSET_PIN04_Pos                                 (4U)
#define GPIO_BSET_PIN04_Msk                                 (0x1UL << GPIO_BSET_PIN04_Pos)
#define GPIO_BSET_PIN04                                     GPIO_BSET_PIN04_Msk
#define GPIO_BSET_PIN05_Pos                                 (5U)
#define GPIO_BSET_PIN05_Msk                                 (0x1UL << GPIO_BSET_PIN05_Pos)
#define GPIO_BSET_PIN05                                     GPIO_BSET_PIN05_Msk
#define GPIO_BSET_PIN06_Pos                                 (6U)
#define GPIO_BSET_PIN06_Msk                                 (0x1UL << GPIO_BSET_PIN06_Pos)
#define GPIO_BSET_PIN06                                     GPIO_BSET_PIN06_Msk
#define GPIO_BSET_PIN07_Pos                                 (7U)
#define GPIO_BSET_PIN07_Msk                                 (0x1UL << GPIO_BSET_PIN07_Pos)
#define GPIO_BSET_PIN07                                     GPIO_BSET_PIN07_Msk
#define GPIO_BSET_PIN08_Pos                                 (8U)
#define GPIO_BSET_PIN08_Msk                                 (0x1UL << GPIO_BSET_PIN08_Pos)
#define GPIO_BSET_PIN08                                     GPIO_BSET_PIN08_Msk
#define GPIO_BSET_PIN09_Pos                                 (9U)
#define GPIO_BSET_PIN09_Msk                                 (0x1UL << GPIO_BSET_PIN09_Pos)
#define GPIO_BSET_PIN09                                     GPIO_BSET_PIN09_Msk
#define GPIO_BSET_PIN10_Pos                                 (10U)
#define GPIO_BSET_PIN10_Msk                                 (0x1UL << GPIO_BSET_PIN10_Pos)
#define GPIO_BSET_PIN10                                     GPIO_BSET_PIN10_Msk
#define GPIO_BSET_PIN11_Pos                                 (11U)
#define GPIO_BSET_PIN11_Msk                                 (0x1UL << GPIO_BSET_PIN11_Pos)
#define GPIO_BSET_PIN11                                     GPIO_BSET_PIN11_Msk
#define GPIO_BSET_PIN12_Pos                                 (12U)
#define GPIO_BSET_PIN12_Msk                                 (0x1UL << GPIO_BSET_PIN12_Pos)
#define GPIO_BSET_PIN12                                     GPIO_BSET_PIN12_Msk
#define GPIO_BSET_PIN13_Pos                                 (13U)
#define GPIO_BSET_PIN13_Msk                                 (0x1UL << GPIO_BSET_PIN13_Pos)
#define GPIO_BSET_PIN13                                     GPIO_BSET_PIN13_Msk
#define GPIO_BSET_PIN14_Pos                                 (14U)
#define GPIO_BSET_PIN14_Msk                                 (0x1UL << GPIO_BSET_PIN14_Pos)
#define GPIO_BSET_PIN14                                     GPIO_BSET_PIN14_Msk
#define GPIO_BSET_PIN15_Pos                                 (15U)
#define GPIO_BSET_PIN15_Msk                                 (0x1UL << GPIO_BSET_PIN15_Pos)
#define GPIO_BSET_PIN15                                     GPIO_BSET_PIN15_Msk

// GPIO_BCLR
#define GPIO_BCLR_PIN00_Pos                                 (0U)
#define GPIO_BCLR_PIN00_Msk                                 (0x1UL << GPIO_BCLR_PIN00_Pos)
#define GPIO_BCLR_PIN00                                     GPIO_BCLR_PIN00_Msk
#define GPIO_BCLR_PIN01_Pos                                 (1U)
#define GPIO_BCLR_PIN01_Msk                                 (0x1UL << GPIO_BCLR_PIN01_Pos)
#define GPIO_BCLR_PIN01                                     GPIO_BCLR_PIN01_Msk
#define GPIO_BCLR_PIN02_Pos                                 (2U)
#define GPIO_BCLR_PIN02_Msk                                 (0x1UL << GPIO_BCLR_PIN02_Pos)
#define GPIO_BCLR_PIN02                                     GPIO_BCLR_PIN02_Msk
#define GPIO_BCLR_PIN03_Pos                                 (3U)
#define GPIO_BCLR_PIN03_Msk                                 (0x1UL << GPIO_BCLR_PIN03_Pos)
#define GPIO_BCLR_PIN03                                     GPIO_BCLR_PIN03_Msk
#define GPIO_BCLR_PIN04_Pos                                 (4U)
#define GPIO_BCLR_PIN04_Msk                                 (0x1UL << GPIO_BCLR_PIN04_Pos)
#define GPIO_BCLR_PIN04                                     GPIO_BCLR_PIN04_Msk
#define GPIO_BCLR_PIN05_Pos                                 (5U)
#define GPIO_BCLR_PIN05_Msk                                 (0x1UL << GPIO_BCLR_PIN05_Pos)
#define GPIO_BCLR_PIN05                                     GPIO_BCLR_PIN05_Msk
#define GPIO_BCLR_PIN06_Pos                                 (6U)
#define GPIO_BCLR_PIN06_Msk                                 (0x1UL << GPIO_BCLR_PIN06_Pos)
#define GPIO_BCLR_PIN06                                     GPIO_BCLR_PIN06_Msk
#define GPIO_BCLR_PIN07_Pos                                 (7U)
#define GPIO_BCLR_PIN07_Msk                                 (0x1UL << GPIO_BCLR_PIN07_Pos)
#define GPIO_BCLR_PIN07                                     GPIO_BCLR_PIN07_Msk
#define GPIO_BCLR_PIN08_Pos                                 (8U)
#define GPIO_BCLR_PIN08_Msk                                 (0x1UL << GPIO_BCLR_PIN08_Pos)
#define GPIO_BCLR_PIN08                                     GPIO_BCLR_PIN08_Msk
#define GPIO_BCLR_PIN09_Pos                                 (9U)
#define GPIO_BCLR_PIN09_Msk                                 (0x1UL << GPIO_BCLR_PIN09_Pos)
#define GPIO_BCLR_PIN09                                     GPIO_BCLR_PIN09_Msk
#define GPIO_BCLR_PIN10_Pos                                 (10U)
#define GPIO_BCLR_PIN10_Msk                                 (0x1UL << GPIO_BCLR_PIN10_Pos)
#define GPIO_BCLR_PIN10                                     GPIO_BCLR_PIN10_Msk
#define GPIO_BCLR_PIN11_Pos                                 (11U)
#define GPIO_BCLR_PIN11_Msk                                 (0x1UL << GPIO_BCLR_PIN11_Pos)
#define GPIO_BCLR_PIN11                                     GPIO_BCLR_PIN11_Msk
#define GPIO_BCLR_PIN12_Pos                                 (12U)
#define GPIO_BCLR_PIN12_Msk                                 (0x1UL << GPIO_BCLR_PIN12_Pos)
#define GPIO_BCLR_PIN12                                     GPIO_BCLR_PIN12_Msk
#define GPIO_BCLR_PIN13_Pos                                 (13U)
#define GPIO_BCLR_PIN13_Msk                                 (0x1UL << GPIO_BCLR_PIN13_Pos)
#define GPIO_BCLR_PIN13                                     GPIO_BCLR_PIN13_Msk
#define GPIO_BCLR_PIN14_Pos                                 (14U)
#define GPIO_BCLR_PIN14_Msk                                 (0x1UL << GPIO_BCLR_PIN14_Pos)
#define GPIO_BCLR_PIN14                                     GPIO_BCLR_PIN14_Msk
#define GPIO_BCLR_PIN15_Pos                                 (15U)
#define GPIO_BCLR_PIN15_Msk                                 (0x1UL << GPIO_BCLR_PIN15_Pos)
#define GPIO_BCLR_PIN15                                     GPIO_BCLR_PIN15_Msk

// GPIO_BSETCLR
#define GPIO_BSETCLR_BCLRPIN00_Pos                          (0U)
#define GPIO_BSETCLR_BCLRPIN00_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN00_Pos)
#define GPIO_BSETCLR_BCLRPIN00                              GPIO_BSETCLR_BCLRPIN00_Msk
#define GPIO_BSETCLR_BCLRPIN01_Pos                          (1U)
#define GPIO_BSETCLR_BCLRPIN01_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN01_Pos)
#define GPIO_BSETCLR_BCLRPIN01                              GPIO_BSETCLR_BCLRPIN01_Msk
#define GPIO_BSETCLR_BCLRPIN02_Pos                          (2U)
#define GPIO_BSETCLR_BCLRPIN02_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN02_Pos)
#define GPIO_BSETCLR_BCLRPIN02                              GPIO_BSETCLR_BCLRPIN02_Msk
#define GPIO_BSETCLR_BCLRPIN03_Pos                          (3U)
#define GPIO_BSETCLR_BCLRPIN03_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN03_Pos)
#define GPIO_BSETCLR_BCLRPIN03                              GPIO_BSETCLR_BCLRPIN03_Msk
#define GPIO_BSETCLR_BCLRPIN04_Pos                          (4U)
#define GPIO_BSETCLR_BCLRPIN04_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN04_Pos)
#define GPIO_BSETCLR_BCLRPIN04                              GPIO_BSETCLR_BCLRPIN04_Msk
#define GPIO_BSETCLR_BCLRPIN05_Pos                          (5U)
#define GPIO_BSETCLR_BCLRPIN05_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN05_Pos)
#define GPIO_BSETCLR_BCLRPIN05                              GPIO_BSETCLR_BCLRPIN05_Msk
#define GPIO_BSETCLR_BCLRPIN06_Pos                          (6U)
#define GPIO_BSETCLR_BCLRPIN06_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN06_Pos)
#define GPIO_BSETCLR_BCLRPIN06                              GPIO_BSETCLR_BCLRPIN06_Msk
#define GPIO_BSETCLR_BCLRPIN07_Pos                          (7U)
#define GPIO_BSETCLR_BCLRPIN07_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN07_Pos)
#define GPIO_BSETCLR_BCLRPIN07                              GPIO_BSETCLR_BCLRPIN07_Msk
#define GPIO_BSETCLR_BCLRPIN08_Pos                          (8U)
#define GPIO_BSETCLR_BCLRPIN08_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN08_Pos)
#define GPIO_BSETCLR_BCLRPIN08                              GPIO_BSETCLR_BCLRPIN08_Msk
#define GPIO_BSETCLR_BCLRPIN09_Pos                          (9U)
#define GPIO_BSETCLR_BCLRPIN09_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN09_Pos)
#define GPIO_BSETCLR_BCLRPIN09                              GPIO_BSETCLR_BCLRPIN09_Msk
#define GPIO_BSETCLR_BCLRPIN10_Pos                          (10U)
#define GPIO_BSETCLR_BCLRPIN10_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN10_Pos)
#define GPIO_BSETCLR_BCLRPIN10                              GPIO_BSETCLR_BCLRPIN10_Msk
#define GPIO_BSETCLR_BCLRPIN11_Pos                          (11U)
#define GPIO_BSETCLR_BCLRPIN11_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN11_Pos)
#define GPIO_BSETCLR_BCLRPIN11                              GPIO_BSETCLR_BCLRPIN11_Msk
#define GPIO_BSETCLR_BCLRPIN12_Pos                          (12U)
#define GPIO_BSETCLR_BCLRPIN12_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN12_Pos)
#define GPIO_BSETCLR_BCLRPIN12                              GPIO_BSETCLR_BCLRPIN12_Msk
#define GPIO_BSETCLR_BCLRPIN13_Pos                          (13U)
#define GPIO_BSETCLR_BCLRPIN13_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN13_Pos)
#define GPIO_BSETCLR_BCLRPIN13                              GPIO_BSETCLR_BCLRPIN13_Msk
#define GPIO_BSETCLR_BCLRPIN14_Pos                          (14U)
#define GPIO_BSETCLR_BCLRPIN14_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN14_Pos)
#define GPIO_BSETCLR_BCLRPIN14                              GPIO_BSETCLR_BCLRPIN14_Msk
#define GPIO_BSETCLR_BCLRPIN15_Pos                          (15U)
#define GPIO_BSETCLR_BCLRPIN15_Msk                          (0x1UL << GPIO_BSETCLR_BCLRPIN15_Pos)
#define GPIO_BSETCLR_BCLRPIN15                              GPIO_BSETCLR_BCLRPIN15_Msk
#define GPIO_BSETCLR_BSETPIN00_Pos                          (16U)
#define GPIO_BSETCLR_BSETPIN00_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN00_Pos)
#define GPIO_BSETCLR_BSETPIN00                              GPIO_BSETCLR_BSETPIN00_Msk
#define GPIO_BSETCLR_BSETPIN01_Pos                          (17U)
#define GPIO_BSETCLR_BSETPIN01_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN01_Pos)
#define GPIO_BSETCLR_BSETPIN01                              GPIO_BSETCLR_BSETPIN01_Msk
#define GPIO_BSETCLR_BSETPIN02_Pos                          (18U)
#define GPIO_BSETCLR_BSETPIN02_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN02_Pos)
#define GPIO_BSETCLR_BSETPIN02                              GPIO_BSETCLR_BSETPIN02_Msk
#define GPIO_BSETCLR_BSETPIN03_Pos                          (19U)
#define GPIO_BSETCLR_BSETPIN03_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN03_Pos)
#define GPIO_BSETCLR_BSETPIN03                              GPIO_BSETCLR_BSETPIN03_Msk
#define GPIO_BSETCLR_BSETPIN04_Pos                          (20U)
#define GPIO_BSETCLR_BSETPIN04_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN04_Pos)
#define GPIO_BSETCLR_BSETPIN04                              GPIO_BSETCLR_BSETPIN04_Msk
#define GPIO_BSETCLR_BSETPIN05_Pos                          (21U)
#define GPIO_BSETCLR_BSETPIN05_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN05_Pos)
#define GPIO_BSETCLR_BSETPIN05                              GPIO_BSETCLR_BSETPIN05_Msk
#define GPIO_BSETCLR_BSETPIN06_Pos                          (22U)
#define GPIO_BSETCLR_BSETPIN06_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN06_Pos)
#define GPIO_BSETCLR_BSETPIN06                              GPIO_BSETCLR_BSETPIN06_Msk
#define GPIO_BSETCLR_BSETPIN07_Pos                          (23U)
#define GPIO_BSETCLR_BSETPIN07_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN07_Pos)
#define GPIO_BSETCLR_BSETPIN07                              GPIO_BSETCLR_BSETPIN07_Msk
#define GPIO_BSETCLR_BSETPIN08_Pos                          (24U)
#define GPIO_BSETCLR_BSETPIN08_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN08_Pos)
#define GPIO_BSETCLR_BSETPIN08                              GPIO_BSETCLR_BSETPIN08_Msk
#define GPIO_BSETCLR_BSETPIN09_Pos                          (25U)
#define GPIO_BSETCLR_BSETPIN09_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN09_Pos)
#define GPIO_BSETCLR_BSETPIN09                              GPIO_BSETCLR_BSETPIN09_Msk
#define GPIO_BSETCLR_BSETPIN10_Pos                          (26U)
#define GPIO_BSETCLR_BSETPIN10_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN10_Pos)
#define GPIO_BSETCLR_BSETPIN10                              GPIO_BSETCLR_BSETPIN10_Msk
#define GPIO_BSETCLR_BSETPIN11_Pos                          (27U)
#define GPIO_BSETCLR_BSETPIN11_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN11_Pos)
#define GPIO_BSETCLR_BSETPIN11                              GPIO_BSETCLR_BSETPIN11_Msk
#define GPIO_BSETCLR_BSETPIN12_Pos                          (28U)
#define GPIO_BSETCLR_BSETPIN12_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN12_Pos)
#define GPIO_BSETCLR_BSETPIN12                              GPIO_BSETCLR_BSETPIN12_Msk
#define GPIO_BSETCLR_BSETPIN13_Pos                          (29U)
#define GPIO_BSETCLR_BSETPIN13_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN13_Pos)
#define GPIO_BSETCLR_BSETPIN13                              GPIO_BSETCLR_BSETPIN13_Msk
#define GPIO_BSETCLR_BSETPIN14_Pos                          (30U)
#define GPIO_BSETCLR_BSETPIN14_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN14_Pos)
#define GPIO_BSETCLR_BSETPIN14                              GPIO_BSETCLR_BSETPIN14_Msk
#define GPIO_BSETCLR_BSETPIN15_Pos                          (31U)
#define GPIO_BSETCLR_BSETPIN15_Msk                          (0x1UL << GPIO_BSETCLR_BSETPIN15_Pos)
#define GPIO_BSETCLR_BSETPIN15                              GPIO_BSETCLR_BSETPIN15_Msk

// GPIO_PU
#define GPIO_PU_PIN00_Pos                                   (0U)
#define GPIO_PU_PIN00_Msk                                   (0x1UL << GPIO_PU_PIN00_Pos)
#define GPIO_PU_PIN00                                       GPIO_PU_PIN00_Msk
#define GPIO_PU_PIN01_Pos                                   (1U)
#define GPIO_PU_PIN01_Msk                                   (0x1UL << GPIO_PU_PIN01_Pos)
#define GPIO_PU_PIN01                                       GPIO_PU_PIN01_Msk
#define GPIO_PU_PIN02_Pos                                   (2U)
#define GPIO_PU_PIN02_Msk                                   (0x1UL << GPIO_PU_PIN02_Pos)
#define GPIO_PU_PIN02                                       GPIO_PU_PIN02_Msk
#define GPIO_PU_PIN03_Pos                                   (3U)
#define GPIO_PU_PIN03_Msk                                   (0x1UL << GPIO_PU_PIN03_Pos)
#define GPIO_PU_PIN03                                       GPIO_PU_PIN03_Msk
#define GPIO_PU_PIN04_Pos                                   (4U)
#define GPIO_PU_PIN04_Msk                                   (0x1UL << GPIO_PU_PIN04_Pos)
#define GPIO_PU_PIN04                                       GPIO_PU_PIN04_Msk
#define GPIO_PU_PIN05_Pos                                   (5U)
#define GPIO_PU_PIN05_Msk                                   (0x1UL << GPIO_PU_PIN05_Pos)
#define GPIO_PU_PIN05                                       GPIO_PU_PIN05_Msk
#define GPIO_PU_PIN06_Pos                                   (6U)
#define GPIO_PU_PIN06_Msk                                   (0x1UL << GPIO_PU_PIN06_Pos)
#define GPIO_PU_PIN06                                       GPIO_PU_PIN06_Msk
#define GPIO_PU_PIN07_Pos                                   (7U)
#define GPIO_PU_PIN07_Msk                                   (0x1UL << GPIO_PU_PIN07_Pos)
#define GPIO_PU_PIN07                                       GPIO_PU_PIN07_Msk
#define GPIO_PU_PIN08_Pos                                   (8U)
#define GPIO_PU_PIN08_Msk                                   (0x1UL << GPIO_PU_PIN08_Pos)
#define GPIO_PU_PIN08                                       GPIO_PU_PIN08_Msk
#define GPIO_PU_PIN09_Pos                                   (9U)
#define GPIO_PU_PIN09_Msk                                   (0x1UL << GPIO_PU_PIN09_Pos)
#define GPIO_PU_PIN09                                       GPIO_PU_PIN09_Msk
#define GPIO_PU_PIN10_Pos                                   (10U)
#define GPIO_PU_PIN10_Msk                                   (0x1UL << GPIO_PU_PIN10_Pos)
#define GPIO_PU_PIN10                                       GPIO_PU_PIN10_Msk
#define GPIO_PU_PIN11_Pos                                   (11U)
#define GPIO_PU_PIN11_Msk                                   (0x1UL << GPIO_PU_PIN11_Pos)
#define GPIO_PU_PIN11                                       GPIO_PU_PIN11_Msk
#define GPIO_PU_PIN12_Pos                                   (12U)
#define GPIO_PU_PIN12_Msk                                   (0x1UL << GPIO_PU_PIN12_Pos)
#define GPIO_PU_PIN12                                       GPIO_PU_PIN12_Msk
#define GPIO_PU_PIN13_Pos                                   (13U)
#define GPIO_PU_PIN13_Msk                                   (0x1UL << GPIO_PU_PIN13_Pos)
#define GPIO_PU_PIN13                                       GPIO_PU_PIN13_Msk
#define GPIO_PU_PIN14_Pos                                   (14U)
#define GPIO_PU_PIN14_Msk                                   (0x1UL << GPIO_PU_PIN14_Pos)
#define GPIO_PU_PIN14                                       GPIO_PU_PIN14_Msk
#define GPIO_PU_PIN15_Pos                                   (15U)
#define GPIO_PU_PIN15_Msk                                   (0x1UL << GPIO_PU_PIN15_Pos)
#define GPIO_PU_PIN15                                       GPIO_PU_PIN15_Msk

// GPIO_OD
#define GPIO_OD_PIN00_Pos                                   (0U)
#define GPIO_OD_PIN00_Msk                                   (0x1UL << GPIO_OD_PIN00_Pos)
#define GPIO_OD_PIN00                                       GPIO_OD_PIN00_Msk
#define GPIO_OD_PIN01_Pos                                   (1U)
#define GPIO_OD_PIN01_Msk                                   (0x1UL << GPIO_OD_PIN01_Pos)
#define GPIO_OD_PIN01                                       GPIO_OD_PIN01_Msk
#define GPIO_OD_PIN02_Pos                                   (2U)
#define GPIO_OD_PIN02_Msk                                   (0x1UL << GPIO_OD_PIN02_Pos)
#define GPIO_OD_PIN02                                       GPIO_OD_PIN02_Msk
#define GPIO_OD_PIN03_Pos                                   (3U)
#define GPIO_OD_PIN03_Msk                                   (0x1UL << GPIO_OD_PIN03_Pos)
#define GPIO_OD_PIN03                                       GPIO_OD_PIN03_Msk
#define GPIO_OD_PIN04_Pos                                   (4U)
#define GPIO_OD_PIN04_Msk                                   (0x1UL << GPIO_OD_PIN04_Pos)
#define GPIO_OD_PIN04                                       GPIO_OD_PIN04_Msk
#define GPIO_OD_PIN05_Pos                                   (5U)
#define GPIO_OD_PIN05_Msk                                   (0x1UL << GPIO_OD_PIN05_Pos)
#define GPIO_OD_PIN05                                       GPIO_OD_PIN05_Msk
#define GPIO_OD_PIN06_Pos                                   (6U)
#define GPIO_OD_PIN06_Msk                                   (0x1UL << GPIO_OD_PIN06_Pos)
#define GPIO_OD_PIN06                                       GPIO_OD_PIN06_Msk
#define GPIO_OD_PIN07_Pos                                   (7U)
#define GPIO_OD_PIN07_Msk                                   (0x1UL << GPIO_OD_PIN07_Pos)
#define GPIO_OD_PIN07                                       GPIO_OD_PIN07_Msk
#define GPIO_OD_PIN08_Pos                                   (8U)
#define GPIO_OD_PIN08_Msk                                   (0x1UL << GPIO_OD_PIN08_Pos)
#define GPIO_OD_PIN08                                       GPIO_OD_PIN08_Msk
#define GPIO_OD_PIN09_Pos                                   (9U)
#define GPIO_OD_PIN09_Msk                                   (0x1UL << GPIO_OD_PIN09_Pos)
#define GPIO_OD_PIN09                                       GPIO_OD_PIN09_Msk
#define GPIO_OD_PIN10_Pos                                   (10U)
#define GPIO_OD_PIN10_Msk                                   (0x1UL << GPIO_OD_PIN10_Pos)
#define GPIO_OD_PIN10                                       GPIO_OD_PIN10_Msk
#define GPIO_OD_PIN11_Pos                                   (11U)
#define GPIO_OD_PIN11_Msk                                   (0x1UL << GPIO_OD_PIN11_Pos)
#define GPIO_OD_PIN11                                       GPIO_OD_PIN11_Msk
#define GPIO_OD_PIN12_Pos                                   (12U)
#define GPIO_OD_PIN12_Msk                                   (0x1UL << GPIO_OD_PIN12_Pos)
#define GPIO_OD_PIN12                                       GPIO_OD_PIN12_Msk
#define GPIO_OD_PIN13_Pos                                   (13U)
#define GPIO_OD_PIN13_Msk                                   (0x1UL << GPIO_OD_PIN13_Pos)
#define GPIO_OD_PIN13                                       GPIO_OD_PIN13_Msk
#define GPIO_OD_PIN14_Pos                                   (14U)
#define GPIO_OD_PIN14_Msk                                   (0x1UL << GPIO_OD_PIN14_Pos)
#define GPIO_OD_PIN14                                       GPIO_OD_PIN14_Msk
#define GPIO_OD_PIN15_Pos                                   (15U)
#define GPIO_OD_PIN15_Msk                                   (0x1UL << GPIO_OD_PIN15_Pos)
#define GPIO_OD_PIN15                                       GPIO_OD_PIN15_Msk

// GPIO_HIE
#define GPIO_HIE_PIN00_Pos                                  (0U)
#define GPIO_HIE_PIN00_Msk                                  (0x1UL << GPIO_HIE_PIN00_Pos)
#define GPIO_HIE_PIN00                                      GPIO_HIE_PIN00_Msk
#define GPIO_HIE_PIN01_Pos                                  (1U)
#define GPIO_HIE_PIN01_Msk                                  (0x1UL << GPIO_HIE_PIN01_Pos)
#define GPIO_HIE_PIN01                                      GPIO_HIE_PIN01_Msk
#define GPIO_HIE_PIN02_Pos                                  (2U)
#define GPIO_HIE_PIN02_Msk                                  (0x1UL << GPIO_HIE_PIN02_Pos)
#define GPIO_HIE_PIN02                                      GPIO_HIE_PIN02_Msk
#define GPIO_HIE_PIN03_Pos                                  (3U)
#define GPIO_HIE_PIN03_Msk                                  (0x1UL << GPIO_HIE_PIN03_Pos)
#define GPIO_HIE_PIN03                                      GPIO_HIE_PIN03_Msk
#define GPIO_HIE_PIN04_Pos                                  (4U)
#define GPIO_HIE_PIN04_Msk                                  (0x1UL << GPIO_HIE_PIN04_Pos)
#define GPIO_HIE_PIN04                                      GPIO_HIE_PIN04_Msk
#define GPIO_HIE_PIN05_Pos                                  (5U)
#define GPIO_HIE_PIN05_Msk                                  (0x1UL << GPIO_HIE_PIN05_Pos)
#define GPIO_HIE_PIN05                                      GPIO_HIE_PIN05_Msk
#define GPIO_HIE_PIN06_Pos                                  (6U)
#define GPIO_HIE_PIN06_Msk                                  (0x1UL << GPIO_HIE_PIN06_Pos)
#define GPIO_HIE_PIN06                                      GPIO_HIE_PIN06_Msk
#define GPIO_HIE_PIN07_Pos                                  (7U)
#define GPIO_HIE_PIN07_Msk                                  (0x1UL << GPIO_HIE_PIN07_Pos)
#define GPIO_HIE_PIN07                                      GPIO_HIE_PIN07_Msk
#define GPIO_HIE_PIN08_Pos                                  (8U)
#define GPIO_HIE_PIN08_Msk                                  (0x1UL << GPIO_HIE_PIN08_Pos)
#define GPIO_HIE_PIN08                                      GPIO_HIE_PIN08_Msk
#define GPIO_HIE_PIN09_Pos                                  (9U)
#define GPIO_HIE_PIN09_Msk                                  (0x1UL << GPIO_HIE_PIN09_Pos)
#define GPIO_HIE_PIN09                                      GPIO_HIE_PIN09_Msk
#define GPIO_HIE_PIN10_Pos                                  (10U)
#define GPIO_HIE_PIN10_Msk                                  (0x1UL << GPIO_HIE_PIN10_Pos)
#define GPIO_HIE_PIN10                                      GPIO_HIE_PIN10_Msk
#define GPIO_HIE_PIN11_Pos                                  (11U)
#define GPIO_HIE_PIN11_Msk                                  (0x1UL << GPIO_HIE_PIN11_Pos)
#define GPIO_HIE_PIN11                                      GPIO_HIE_PIN11_Msk
#define GPIO_HIE_PIN12_Pos                                  (12U)
#define GPIO_HIE_PIN12_Msk                                  (0x1UL << GPIO_HIE_PIN12_Pos)
#define GPIO_HIE_PIN12                                      GPIO_HIE_PIN12_Msk
#define GPIO_HIE_PIN13_Pos                                  (13U)
#define GPIO_HIE_PIN13_Msk                                  (0x1UL << GPIO_HIE_PIN13_Pos)
#define GPIO_HIE_PIN13                                      GPIO_HIE_PIN13_Msk
#define GPIO_HIE_PIN14_Pos                                  (14U)
#define GPIO_HIE_PIN14_Msk                                  (0x1UL << GPIO_HIE_PIN14_Pos)
#define GPIO_HIE_PIN14                                      GPIO_HIE_PIN14_Msk
#define GPIO_HIE_PIN15_Pos                                  (15U)
#define GPIO_HIE_PIN15_Msk                                  (0x1UL << GPIO_HIE_PIN15_Pos)
#define GPIO_HIE_PIN15                                      GPIO_HIE_PIN15_Msk

// GPIO_LIE
#define GPIO_LIE_PIN00_Pos                                  (0U)
#define GPIO_LIE_PIN00_Msk                                  (0x1UL << GPIO_LIE_PIN00_Pos)
#define GPIO_LIE_PIN00                                      GPIO_LIE_PIN00_Msk
#define GPIO_LIE_PIN01_Pos                                  (1U)
#define GPIO_LIE_PIN01_Msk                                  (0x1UL << GPIO_LIE_PIN01_Pos)
#define GPIO_LIE_PIN01                                      GPIO_LIE_PIN01_Msk
#define GPIO_LIE_PIN02_Pos                                  (2U)
#define GPIO_LIE_PIN02_Msk                                  (0x1UL << GPIO_LIE_PIN02_Pos)
#define GPIO_LIE_PIN02                                      GPIO_LIE_PIN02_Msk
#define GPIO_LIE_PIN03_Pos                                  (3U)
#define GPIO_LIE_PIN03_Msk                                  (0x1UL << GPIO_LIE_PIN03_Pos)
#define GPIO_LIE_PIN03                                      GPIO_LIE_PIN03_Msk
#define GPIO_LIE_PIN04_Pos                                  (4U)
#define GPIO_LIE_PIN04_Msk                                  (0x1UL << GPIO_LIE_PIN04_Pos)
#define GPIO_LIE_PIN04                                      GPIO_LIE_PIN04_Msk
#define GPIO_LIE_PIN05_Pos                                  (5U)
#define GPIO_LIE_PIN05_Msk                                  (0x1UL << GPIO_LIE_PIN05_Pos)
#define GPIO_LIE_PIN05                                      GPIO_LIE_PIN05_Msk
#define GPIO_LIE_PIN06_Pos                                  (6U)
#define GPIO_LIE_PIN06_Msk                                  (0x1UL << GPIO_LIE_PIN06_Pos)
#define GPIO_LIE_PIN06                                      GPIO_LIE_PIN06_Msk
#define GPIO_LIE_PIN07_Pos                                  (7U)
#define GPIO_LIE_PIN07_Msk                                  (0x1UL << GPIO_LIE_PIN07_Pos)
#define GPIO_LIE_PIN07                                      GPIO_LIE_PIN07_Msk
#define GPIO_LIE_PIN08_Pos                                  (8U)
#define GPIO_LIE_PIN08_Msk                                  (0x1UL << GPIO_LIE_PIN08_Pos)
#define GPIO_LIE_PIN08                                      GPIO_LIE_PIN08_Msk
#define GPIO_LIE_PIN09_Pos                                  (9U)
#define GPIO_LIE_PIN09_Msk                                  (0x1UL << GPIO_LIE_PIN09_Pos)
#define GPIO_LIE_PIN09                                      GPIO_LIE_PIN09_Msk
#define GPIO_LIE_PIN10_Pos                                  (10U)
#define GPIO_LIE_PIN10_Msk                                  (0x1UL << GPIO_LIE_PIN10_Pos)
#define GPIO_LIE_PIN10                                      GPIO_LIE_PIN10_Msk
#define GPIO_LIE_PIN11_Pos                                  (11U)
#define GPIO_LIE_PIN11_Msk                                  (0x1UL << GPIO_LIE_PIN11_Pos)
#define GPIO_LIE_PIN11                                      GPIO_LIE_PIN11_Msk
#define GPIO_LIE_PIN12_Pos                                  (12U)
#define GPIO_LIE_PIN12_Msk                                  (0x1UL << GPIO_LIE_PIN12_Pos)
#define GPIO_LIE_PIN12                                      GPIO_LIE_PIN12_Msk
#define GPIO_LIE_PIN13_Pos                                  (13U)
#define GPIO_LIE_PIN13_Msk                                  (0x1UL << GPIO_LIE_PIN13_Pos)
#define GPIO_LIE_PIN13                                      GPIO_LIE_PIN13_Msk
#define GPIO_LIE_PIN14_Pos                                  (14U)
#define GPIO_LIE_PIN14_Msk                                  (0x1UL << GPIO_LIE_PIN14_Pos)
#define GPIO_LIE_PIN14                                      GPIO_LIE_PIN14_Msk
#define GPIO_LIE_PIN15_Pos                                  (15U)
#define GPIO_LIE_PIN15_Msk                                  (0x1UL << GPIO_LIE_PIN15_Pos)
#define GPIO_LIE_PIN15                                      GPIO_LIE_PIN15_Msk

// GPIO_RIE
#define GPIO_RIE_PIN00_Pos                                  (0U)
#define GPIO_RIE_PIN00_Msk                                  (0x1UL << GPIO_RIE_PIN00_Pos)
#define GPIO_RIE_PIN00                                      GPIO_RIE_PIN00_Msk
#define GPIO_RIE_PIN01_Pos                                  (1U)
#define GPIO_RIE_PIN01_Msk                                  (0x1UL << GPIO_RIE_PIN01_Pos)
#define GPIO_RIE_PIN01                                      GPIO_RIE_PIN01_Msk
#define GPIO_RIE_PIN02_Pos                                  (2U)
#define GPIO_RIE_PIN02_Msk                                  (0x1UL << GPIO_RIE_PIN02_Pos)
#define GPIO_RIE_PIN02                                      GPIO_RIE_PIN02_Msk
#define GPIO_RIE_PIN03_Pos                                  (3U)
#define GPIO_RIE_PIN03_Msk                                  (0x1UL << GPIO_RIE_PIN03_Pos)
#define GPIO_RIE_PIN03                                      GPIO_RIE_PIN03_Msk
#define GPIO_RIE_PIN04_Pos                                  (4U)
#define GPIO_RIE_PIN04_Msk                                  (0x1UL << GPIO_RIE_PIN04_Pos)
#define GPIO_RIE_PIN04                                      GPIO_RIE_PIN04_Msk
#define GPIO_RIE_PIN05_Pos                                  (5U)
#define GPIO_RIE_PIN05_Msk                                  (0x1UL << GPIO_RIE_PIN05_Pos)
#define GPIO_RIE_PIN05                                      GPIO_RIE_PIN05_Msk
#define GPIO_RIE_PIN06_Pos                                  (6U)
#define GPIO_RIE_PIN06_Msk                                  (0x1UL << GPIO_RIE_PIN06_Pos)
#define GPIO_RIE_PIN06                                      GPIO_RIE_PIN06_Msk
#define GPIO_RIE_PIN07_Pos                                  (7U)
#define GPIO_RIE_PIN07_Msk                                  (0x1UL << GPIO_RIE_PIN07_Pos)
#define GPIO_RIE_PIN07                                      GPIO_RIE_PIN07_Msk
#define GPIO_RIE_PIN08_Pos                                  (8U)
#define GPIO_RIE_PIN08_Msk                                  (0x1UL << GPIO_RIE_PIN08_Pos)
#define GPIO_RIE_PIN08                                      GPIO_RIE_PIN08_Msk
#define GPIO_RIE_PIN09_Pos                                  (9U)
#define GPIO_RIE_PIN09_Msk                                  (0x1UL << GPIO_RIE_PIN09_Pos)
#define GPIO_RIE_PIN09                                      GPIO_RIE_PIN09_Msk
#define GPIO_RIE_PIN10_Pos                                  (10U)
#define GPIO_RIE_PIN10_Msk                                  (0x1UL << GPIO_RIE_PIN10_Pos)
#define GPIO_RIE_PIN10                                      GPIO_RIE_PIN10_Msk
#define GPIO_RIE_PIN11_Pos                                  (11U)
#define GPIO_RIE_PIN11_Msk                                  (0x1UL << GPIO_RIE_PIN11_Pos)
#define GPIO_RIE_PIN11                                      GPIO_RIE_PIN11_Msk
#define GPIO_RIE_PIN12_Pos                                  (12U)
#define GPIO_RIE_PIN12_Msk                                  (0x1UL << GPIO_RIE_PIN12_Pos)
#define GPIO_RIE_PIN12                                      GPIO_RIE_PIN12_Msk
#define GPIO_RIE_PIN13_Pos                                  (13U)
#define GPIO_RIE_PIN13_Msk                                  (0x1UL << GPIO_RIE_PIN13_Pos)
#define GPIO_RIE_PIN13                                      GPIO_RIE_PIN13_Msk
#define GPIO_RIE_PIN14_Pos                                  (14U)
#define GPIO_RIE_PIN14_Msk                                  (0x1UL << GPIO_RIE_PIN14_Pos)
#define GPIO_RIE_PIN14                                      GPIO_RIE_PIN14_Msk
#define GPIO_RIE_PIN15_Pos                                  (15U)
#define GPIO_RIE_PIN15_Msk                                  (0x1UL << GPIO_RIE_PIN15_Pos)
#define GPIO_RIE_PIN15                                      GPIO_RIE_PIN15_Msk

// GPIO_FIE
#define GPIO_FIE_PIN00_Pos                                  (0U)
#define GPIO_FIE_PIN00_Msk                                  (0x1UL << GPIO_FIE_PIN00_Pos)
#define GPIO_FIE_PIN00                                      GPIO_FIE_PIN00_Msk
#define GPIO_FIE_PIN01_Pos                                  (1U)
#define GPIO_FIE_PIN01_Msk                                  (0x1UL << GPIO_FIE_PIN01_Pos)
#define GPIO_FIE_PIN01                                      GPIO_FIE_PIN01_Msk
#define GPIO_FIE_PIN02_Pos                                  (2U)
#define GPIO_FIE_PIN02_Msk                                  (0x1UL << GPIO_FIE_PIN02_Pos)
#define GPIO_FIE_PIN02                                      GPIO_FIE_PIN02_Msk
#define GPIO_FIE_PIN03_Pos                                  (3U)
#define GPIO_FIE_PIN03_Msk                                  (0x1UL << GPIO_FIE_PIN03_Pos)
#define GPIO_FIE_PIN03                                      GPIO_FIE_PIN03_Msk
#define GPIO_FIE_PIN04_Pos                                  (4U)
#define GPIO_FIE_PIN04_Msk                                  (0x1UL << GPIO_FIE_PIN04_Pos)
#define GPIO_FIE_PIN04                                      GPIO_FIE_PIN04_Msk
#define GPIO_FIE_PIN05_Pos                                  (5U)
#define GPIO_FIE_PIN05_Msk                                  (0x1UL << GPIO_FIE_PIN05_Pos)
#define GPIO_FIE_PIN05                                      GPIO_FIE_PIN05_Msk
#define GPIO_FIE_PIN06_Pos                                  (6U)
#define GPIO_FIE_PIN06_Msk                                  (0x1UL << GPIO_FIE_PIN06_Pos)
#define GPIO_FIE_PIN06                                      GPIO_FIE_PIN06_Msk
#define GPIO_FIE_PIN07_Pos                                  (7U)
#define GPIO_FIE_PIN07_Msk                                  (0x1UL << GPIO_FIE_PIN07_Pos)
#define GPIO_FIE_PIN07                                      GPIO_FIE_PIN07_Msk
#define GPIO_FIE_PIN08_Pos                                  (8U)
#define GPIO_FIE_PIN08_Msk                                  (0x1UL << GPIO_FIE_PIN08_Pos)
#define GPIO_FIE_PIN08                                      GPIO_FIE_PIN08_Msk
#define GPIO_FIE_PIN09_Pos                                  (9U)
#define GPIO_FIE_PIN09_Msk                                  (0x1UL << GPIO_FIE_PIN09_Pos)
#define GPIO_FIE_PIN09                                      GPIO_FIE_PIN09_Msk
#define GPIO_FIE_PIN10_Pos                                  (10U)
#define GPIO_FIE_PIN10_Msk                                  (0x1UL << GPIO_FIE_PIN10_Pos)
#define GPIO_FIE_PIN10                                      GPIO_FIE_PIN10_Msk
#define GPIO_FIE_PIN11_Pos                                  (11U)
#define GPIO_FIE_PIN11_Msk                                  (0x1UL << GPIO_FIE_PIN11_Pos)
#define GPIO_FIE_PIN11                                      GPIO_FIE_PIN11_Msk
#define GPIO_FIE_PIN12_Pos                                  (12U)
#define GPIO_FIE_PIN12_Msk                                  (0x1UL << GPIO_FIE_PIN12_Pos)
#define GPIO_FIE_PIN12                                      GPIO_FIE_PIN12_Msk
#define GPIO_FIE_PIN13_Pos                                  (13U)
#define GPIO_FIE_PIN13_Msk                                  (0x1UL << GPIO_FIE_PIN13_Pos)
#define GPIO_FIE_PIN13                                      GPIO_FIE_PIN13_Msk
#define GPIO_FIE_PIN14_Pos                                  (14U)
#define GPIO_FIE_PIN14_Msk                                  (0x1UL << GPIO_FIE_PIN14_Pos)
#define GPIO_FIE_PIN14                                      GPIO_FIE_PIN14_Msk
#define GPIO_FIE_PIN15_Pos                                  (15U)
#define GPIO_FIE_PIN15_Msk                                  (0x1UL << GPIO_FIE_PIN15_Pos)
#define GPIO_FIE_PIN15                                      GPIO_FIE_PIN15_Msk

// GPIO_STAT
#define GPIO_STAT_PIN00_Pos                                 (0U)
#define GPIO_STAT_PIN00_Msk                                 (0x1UL << GPIO_STAT_PIN00_Pos)
#define GPIO_STAT_PIN00                                     GPIO_STAT_PIN00_Msk
#define GPIO_STAT_PIN01_Pos                                 (1U)
#define GPIO_STAT_PIN01_Msk                                 (0x1UL << GPIO_STAT_PIN01_Pos)
#define GPIO_STAT_PIN01                                     GPIO_STAT_PIN01_Msk
#define GPIO_STAT_PIN02_Pos                                 (2U)
#define GPIO_STAT_PIN02_Msk                                 (0x1UL << GPIO_STAT_PIN02_Pos)
#define GPIO_STAT_PIN02                                     GPIO_STAT_PIN02_Msk
#define GPIO_STAT_PIN03_Pos                                 (3U)
#define GPIO_STAT_PIN03_Msk                                 (0x1UL << GPIO_STAT_PIN03_Pos)
#define GPIO_STAT_PIN03                                     GPIO_STAT_PIN03_Msk
#define GPIO_STAT_PIN04_Pos                                 (4U)
#define GPIO_STAT_PIN04_Msk                                 (0x1UL << GPIO_STAT_PIN04_Pos)
#define GPIO_STAT_PIN04                                     GPIO_STAT_PIN04_Msk
#define GPIO_STAT_PIN05_Pos                                 (5U)
#define GPIO_STAT_PIN05_Msk                                 (0x1UL << GPIO_STAT_PIN05_Pos)
#define GPIO_STAT_PIN05                                     GPIO_STAT_PIN05_Msk
#define GPIO_STAT_PIN06_Pos                                 (6U)
#define GPIO_STAT_PIN06_Msk                                 (0x1UL << GPIO_STAT_PIN06_Pos)
#define GPIO_STAT_PIN06                                     GPIO_STAT_PIN06_Msk
#define GPIO_STAT_PIN07_Pos                                 (7U)
#define GPIO_STAT_PIN07_Msk                                 (0x1UL << GPIO_STAT_PIN07_Pos)
#define GPIO_STAT_PIN07                                     GPIO_STAT_PIN07_Msk
#define GPIO_STAT_PIN08_Pos                                 (8U)
#define GPIO_STAT_PIN08_Msk                                 (0x1UL << GPIO_STAT_PIN08_Pos)
#define GPIO_STAT_PIN08                                     GPIO_STAT_PIN08_Msk
#define GPIO_STAT_PIN09_Pos                                 (9U)
#define GPIO_STAT_PIN09_Msk                                 (0x1UL << GPIO_STAT_PIN09_Pos)
#define GPIO_STAT_PIN09                                     GPIO_STAT_PIN09_Msk
#define GPIO_STAT_PIN10_Pos                                 (10U)
#define GPIO_STAT_PIN10_Msk                                 (0x1UL << GPIO_STAT_PIN10_Pos)
#define GPIO_STAT_PIN10                                     GPIO_STAT_PIN10_Msk
#define GPIO_STAT_PIN11_Pos                                 (11U)
#define GPIO_STAT_PIN11_Msk                                 (0x1UL << GPIO_STAT_PIN11_Pos)
#define GPIO_STAT_PIN11                                     GPIO_STAT_PIN11_Msk
#define GPIO_STAT_PIN12_Pos                                 (12U)
#define GPIO_STAT_PIN12_Msk                                 (0x1UL << GPIO_STAT_PIN12_Pos)
#define GPIO_STAT_PIN12                                     GPIO_STAT_PIN12_Msk
#define GPIO_STAT_PIN13_Pos                                 (13U)
#define GPIO_STAT_PIN13_Msk                                 (0x1UL << GPIO_STAT_PIN13_Pos)
#define GPIO_STAT_PIN13                                     GPIO_STAT_PIN13_Msk
#define GPIO_STAT_PIN14_Pos                                 (14U)
#define GPIO_STAT_PIN14_Msk                                 (0x1UL << GPIO_STAT_PIN14_Pos)
#define GPIO_STAT_PIN14                                     GPIO_STAT_PIN14_Msk
#define GPIO_STAT_PIN15_Pos                                 (15U)
#define GPIO_STAT_PIN15_Msk                                 (0x1UL << GPIO_STAT_PIN15_Pos)
#define GPIO_STAT_PIN15                                     GPIO_STAT_PIN15_Msk

// GPIO_ICLR
#define GPIO_ICLR_PIN00_Pos                                 (0U)
#define GPIO_ICLR_PIN00_Msk                                 (0x1UL << GPIO_ICLR_PIN00_Pos)
#define GPIO_ICLR_PIN00                                     GPIO_ICLR_PIN00_Msk
#define GPIO_ICLR_PIN01_Pos                                 (1U)
#define GPIO_ICLR_PIN01_Msk                                 (0x1UL << GPIO_ICLR_PIN01_Pos)
#define GPIO_ICLR_PIN01                                     GPIO_ICLR_PIN01_Msk
#define GPIO_ICLR_PIN02_Pos                                 (2U)
#define GPIO_ICLR_PIN02_Msk                                 (0x1UL << GPIO_ICLR_PIN02_Pos)
#define GPIO_ICLR_PIN02                                     GPIO_ICLR_PIN02_Msk
#define GPIO_ICLR_PIN03_Pos                                 (3U)
#define GPIO_ICLR_PIN03_Msk                                 (0x1UL << GPIO_ICLR_PIN03_Pos)
#define GPIO_ICLR_PIN03                                     GPIO_ICLR_PIN03_Msk
#define GPIO_ICLR_PIN04_Pos                                 (4U)
#define GPIO_ICLR_PIN04_Msk                                 (0x1UL << GPIO_ICLR_PIN04_Pos)
#define GPIO_ICLR_PIN04                                     GPIO_ICLR_PIN04_Msk
#define GPIO_ICLR_PIN05_Pos                                 (5U)
#define GPIO_ICLR_PIN05_Msk                                 (0x1UL << GPIO_ICLR_PIN05_Pos)
#define GPIO_ICLR_PIN05                                     GPIO_ICLR_PIN05_Msk
#define GPIO_ICLR_PIN06_Pos                                 (6U)
#define GPIO_ICLR_PIN06_Msk                                 (0x1UL << GPIO_ICLR_PIN06_Pos)
#define GPIO_ICLR_PIN06                                     GPIO_ICLR_PIN06_Msk
#define GPIO_ICLR_PIN07_Pos                                 (7U)
#define GPIO_ICLR_PIN07_Msk                                 (0x1UL << GPIO_ICLR_PIN07_Pos)
#define GPIO_ICLR_PIN07                                     GPIO_ICLR_PIN07_Msk
#define GPIO_ICLR_PIN08_Pos                                 (8U)
#define GPIO_ICLR_PIN08_Msk                                 (0x1UL << GPIO_ICLR_PIN08_Pos)
#define GPIO_ICLR_PIN08                                     GPIO_ICLR_PIN08_Msk
#define GPIO_ICLR_PIN09_Pos                                 (9U)
#define GPIO_ICLR_PIN09_Msk                                 (0x1UL << GPIO_ICLR_PIN09_Pos)
#define GPIO_ICLR_PIN09                                     GPIO_ICLR_PIN09_Msk
#define GPIO_ICLR_PIN10_Pos                                 (10U)
#define GPIO_ICLR_PIN10_Msk                                 (0x1UL << GPIO_ICLR_PIN10_Pos)
#define GPIO_ICLR_PIN10                                     GPIO_ICLR_PIN10_Msk
#define GPIO_ICLR_PIN11_Pos                                 (11U)
#define GPIO_ICLR_PIN11_Msk                                 (0x1UL << GPIO_ICLR_PIN11_Pos)
#define GPIO_ICLR_PIN11                                     GPIO_ICLR_PIN11_Msk
#define GPIO_ICLR_PIN12_Pos                                 (12U)
#define GPIO_ICLR_PIN12_Msk                                 (0x1UL << GPIO_ICLR_PIN12_Pos)
#define GPIO_ICLR_PIN12                                     GPIO_ICLR_PIN12_Msk
#define GPIO_ICLR_PIN13_Pos                                 (13U)
#define GPIO_ICLR_PIN13_Msk                                 (0x1UL << GPIO_ICLR_PIN13_Pos)
#define GPIO_ICLR_PIN13                                     GPIO_ICLR_PIN13_Msk
#define GPIO_ICLR_PIN14_Pos                                 (14U)
#define GPIO_ICLR_PIN14_Msk                                 (0x1UL << GPIO_ICLR_PIN14_Pos)
#define GPIO_ICLR_PIN14                                     GPIO_ICLR_PIN14_Msk
#define GPIO_ICLR_PIN15_Pos                                 (15U)
#define GPIO_ICLR_PIN15_Msk                                 (0x1UL << GPIO_ICLR_PIN15_Pos)
#define GPIO_ICLR_PIN15                                     GPIO_ICLR_PIN15_Msk



//********************    Bits Define For Peripheral GPIOAUX    ********************//
// GPIOAUX_CTRL1
#define GPIOAUX_CTRL1_IR_POL_Pos                            (14U)
#define GPIOAUX_CTRL1_IR_POL_Msk                            (0x1UL << GPIOAUX_CTRL1_IR_POL_Pos)
#define GPIOAUX_CTRL1_IR_POL                                GPIOAUX_CTRL1_IR_POL_Msk
#define GPIOAUX_CTRL1_HSI2C_LSEL_Pos                        (15U)
#define GPIOAUX_CTRL1_HSI2C_LSEL_Msk                        (0x1UL << GPIOAUX_CTRL1_HSI2C_LSEL_Pos)
#define GPIOAUX_CTRL1_HSI2C_LSEL                            GPIOAUX_CTRL1_HSI2C_LSEL_Msk

// GPIOAUX_CTRL2
#define GPIOAUX_CTRL2_TCLK_SEL_Pos                          (4U)
#define GPIOAUX_CTRL2_TCLK_SEL_Msk                          (0x3UL << GPIOAUX_CTRL2_TCLK_SEL_Pos)
#define GPIOAUX_CTRL2_TCLK_SEL                              GPIOAUX_CTRL2_TCLK_SEL_Msk
#define GPIOAUX_CTRL2_TCLK_DIV_Pos                          (6U)
#define GPIOAUX_CTRL2_TCLK_DIV_Msk                          (0x3UL << GPIOAUX_CTRL2_TCLK_DIV_Pos)
#define GPIOAUX_CTRL2_TCLK_DIV                              GPIOAUX_CTRL2_TCLK_DIV_Msk

// GPIOAUX_TIMES
#define GPIOAUX_TIMES_CTIM0_E_Pos                           (0U)
#define GPIOAUX_TIMES_CTIM0_E_Msk                           (0x3UL << GPIOAUX_TIMES_CTIM0_E_Pos)
#define GPIOAUX_TIMES_CTIM0_E                               GPIOAUX_TIMES_CTIM0_E_Msk
#define GPIOAUX_TIMES_CTIM1_E_Pos                           (3U)
#define GPIOAUX_TIMES_CTIM1_E_Msk                           (0x3UL << GPIOAUX_TIMES_CTIM1_E_Pos)
#define GPIOAUX_TIMES_CTIM1_E                               GPIOAUX_TIMES_CTIM1_E_Msk
#define GPIOAUX_TIMES_ATIM3_E_Pos                           (9U)
#define GPIOAUX_TIMES_ATIM3_E_Msk                           (0x7UL << GPIOAUX_TIMES_ATIM3_E_Pos)
#define GPIOAUX_TIMES_ATIM3_E                               GPIOAUX_TIMES_ATIM3_E_Msk

// GPIOAUX_TIMCPS
#define GPIOAUX_TIMCPS_CTIM0_C0_Pos                         (0U)
#define GPIOAUX_TIMCPS_CTIM0_C0_Msk                         (0x3UL << GPIOAUX_TIMCPS_CTIM0_C0_Pos)
#define GPIOAUX_TIMCPS_CTIM0_C0                             GPIOAUX_TIMCPS_CTIM0_C0_Msk
#define GPIOAUX_TIMCPS_CTIM1_C0_Pos                         (3U)
#define GPIOAUX_TIMCPS_CTIM1_C0_Msk                         (0x3UL << GPIOAUX_TIMCPS_CTIM1_C0_Pos)
#define GPIOAUX_TIMCPS_CTIM1_C0                             GPIOAUX_TIMCPS_CTIM1_C0_Msk
#define GPIOAUX_TIMCPS_ATIM3_C0A_Pos                        (9U)
#define GPIOAUX_TIMCPS_ATIM3_C0A_Msk                        (0x3UL << GPIOAUX_TIMCPS_ATIM3_C0A_Pos)
#define GPIOAUX_TIMCPS_ATIM3_C0A                            GPIOAUX_TIMCPS_ATIM3_C0A_Msk

// GPIOAUX_FLTCFG
#define GPIOAUX_FLTCFG_PB0FLT_EN_Pos                        (5U)
#define GPIOAUX_FLTCFG_PB0FLT_EN_Msk                        (0x1UL << GPIOAUX_FLTCFG_PB0FLT_EN_Pos)
#define GPIOAUX_FLTCFG_PB0FLT_EN                            GPIOAUX_FLTCFG_PB0FLT_EN_Msk
#define GPIOAUX_FLTCFG_PA8FLT_EN_Pos                        (6U)
#define GPIOAUX_FLTCFG_PA8FLT_EN_Msk                        (0x1UL << GPIOAUX_FLTCFG_PA8FLT_EN_Pos)
#define GPIOAUX_FLTCFG_PA8FLT_EN                            GPIOAUX_FLTCFG_PA8FLT_EN_Msk
#define GPIOAUX_FLTCFG_PA0FLT_EN_Pos                        (7U)
#define GPIOAUX_FLTCFG_PA0FLT_EN_Msk                        (0x1UL << GPIOAUX_FLTCFG_PA0FLT_EN_Pos)
#define GPIOAUX_FLTCFG_PA0FLT_EN                            GPIOAUX_FLTCFG_PA0FLT_EN_Msk
#define GPIOAUX_FLTCFG_FCLK_DIV_Pos                         (8U)
#define GPIOAUX_FLTCFG_FCLK_DIV_Msk                         (0x3UL << GPIOAUX_FLTCFG_FCLK_DIV_Pos)
#define GPIOAUX_FLTCFG_FCLK_DIV                             GPIOAUX_FLTCFG_FCLK_DIV_Msk
#define GPIOAUX_FLTCFG_FCLK_SEL_Pos                         (10U)
#define GPIOAUX_FLTCFG_FCLK_SEL_Msk                         (0x1UL << GPIOAUX_FLTCFG_FCLK_SEL_Pos)
#define GPIOAUX_FLTCFG_FCLK_SEL                             GPIOAUX_FLTCFG_FCLK_SEL_Msk



//********************    Bits Define For Peripheral GTIM    ********************//
// GTIM_ARR
#define GTIM_ARR_ARR_Pos                                    (0U)
#define GTIM_ARR_ARR_Msk                                    (0xFFFFUL << GTIM_ARR_ARR_Pos)
#define GTIM_ARR_ARR                                        GTIM_ARR_ARR_Msk

// GTIM_CNT
#define GTIM_CNT_CNT_Pos                                    (0U)
#define GTIM_CNT_CNT_Msk                                    (0xFFFFUL << GTIM_CNT_CNT_Pos)
#define GTIM_CNT_CNT                                        GTIM_CNT_CNT_Msk

// GTIM_CMMR
#define GTIM_CMMR_CC0M_Pos                                  (0U)
#define GTIM_CMMR_CC0M_Msk                                  (0x7UL << GTIM_CMMR_CC0M_Pos)
#define GTIM_CMMR_CC0M                                      GTIM_CMMR_CC0M_Msk
#define GTIM_CMMR_CC1M_Pos                                  (4U)
#define GTIM_CMMR_CC1M_Msk                                  (0x7UL << GTIM_CMMR_CC1M_Pos)
#define GTIM_CMMR_CC1M                                      GTIM_CMMR_CC1M_Msk
#define GTIM_CMMR_CC2M_Pos                                  (8U)
#define GTIM_CMMR_CC2M_Msk                                  (0x7UL << GTIM_CMMR_CC2M_Pos)
#define GTIM_CMMR_CC2M                                      GTIM_CMMR_CC2M_Msk
#define GTIM_CMMR_CC3M_Pos                                  (12U)
#define GTIM_CMMR_CC3M_Msk                                  (0x7UL << GTIM_CMMR_CC3M_Pos)
#define GTIM_CMMR_CC3M                                      GTIM_CMMR_CC3M_Msk

// GTIM_CR1
#define GTIM_CR1_ETRFLT_Pos                                 (4U)
#define GTIM_CR1_ETRFLT_Msk                                 (0x7UL << GTIM_CR1_ETRFLT_Pos)
#define GTIM_CR1_ETRFLT                                     GTIM_CR1_ETRFLT_Msk

// GTIM_CR0
#define GTIM_CR0_CEN_Pos                                    (0U)
#define GTIM_CR0_CEN_Msk                                    (0x1UL << GTIM_CR0_CEN_Pos)
#define GTIM_CR0_CEN                                        GTIM_CR0_CEN_Msk
#define GTIM_CR0_MD_Pos                                     (1U)
#define GTIM_CR0_MD_Msk                                     (0x3UL << GTIM_CR0_MD_Pos)
#define GTIM_CR0_MD                                         GTIM_CR0_MD_Msk
#define GTIM_CR0_TOGEN_Pos                                  (3U)
#define GTIM_CR0_TOGEN_Msk                                  (0x1UL << GTIM_CR0_TOGEN_Pos)
#define GTIM_CR0_TOGEN                                      GTIM_CR0_TOGEN_Msk
#define GTIM_CR0_PRS_Pos                                    (4U)
#define GTIM_CR0_PRS_Msk                                    (0xFUL << GTIM_CR0_PRS_Pos)
#define GTIM_CR0_PRS                                        GTIM_CR0_PRS_Msk
#define GTIM_CR0_OST_Pos                                    (8U)
#define GTIM_CR0_OST_Msk                                    (0x1UL << GTIM_CR0_OST_Pos)
#define GTIM_CR0_OST                                        GTIM_CR0_OST_Msk
#define GTIM_CR0_TRS_Pos                                    (9U)
#define GTIM_CR0_TRS_Msk                                    (0x3UL << GTIM_CR0_TRS_Pos)
#define GTIM_CR0_TRS                                        GTIM_CR0_TRS_Msk
#define GTIM_CR0_ETP_Pos                                    (11U)
#define GTIM_CR0_ETP_Msk                                    (0x1UL << GTIM_CR0_ETP_Pos)
#define GTIM_CR0_ETP                                        GTIM_CR0_ETP_Msk

// GTIM_IER
#define GTIM_IER_UI_Pos                                     (0U)
#define GTIM_IER_UI_Msk                                     (0x1UL << GTIM_IER_UI_Pos)
#define GTIM_IER_UI                                         GTIM_IER_UI_Msk
#define GTIM_IER_TI_Pos                                     (1U)
#define GTIM_IER_TI_Msk                                     (0x1UL << GTIM_IER_TI_Pos)
#define GTIM_IER_TI                                         GTIM_IER_TI_Msk
#define GTIM_IER_CC0_Pos                                    (2U)
#define GTIM_IER_CC0_Msk                                    (0x1UL << GTIM_IER_CC0_Pos)
#define GTIM_IER_CC0                                        GTIM_IER_CC0_Msk
#define GTIM_IER_CC1_Pos                                    (3U)
#define GTIM_IER_CC1_Msk                                    (0x1UL << GTIM_IER_CC1_Pos)
#define GTIM_IER_CC1                                        GTIM_IER_CC1_Msk
#define GTIM_IER_CC2_Pos                                    (4U)
#define GTIM_IER_CC2_Msk                                    (0x1UL << GTIM_IER_CC2_Pos)
#define GTIM_IER_CC2                                        GTIM_IER_CC2_Msk
#define GTIM_IER_CC3_Pos                                    (5U)
#define GTIM_IER_CC3_Msk                                    (0x1UL << GTIM_IER_CC3_Pos)
#define GTIM_IER_CC3                                        GTIM_IER_CC3_Msk
#define GTIM_IER_OVTRAD_Pos                                 (10U)
#define GTIM_IER_OVTRAD_Msk                                 (0x1UL << GTIM_IER_OVTRAD_Pos)
#define GTIM_IER_OVTRAD                                     GTIM_IER_OVTRAD_Msk
#define GTIM_IER_C0TRAD_Pos                                 (11U)
#define GTIM_IER_C0TRAD_Msk                                 (0x1UL << GTIM_IER_C0TRAD_Pos)
#define GTIM_IER_C0TRAD                                     GTIM_IER_C0TRAD_Msk

// GTIM_IFR
#define GTIM_IFR_UI_Pos                                     (0U)
#define GTIM_IFR_UI_Msk                                     (0x1UL << GTIM_IFR_UI_Pos)
#define GTIM_IFR_UI                                         GTIM_IFR_UI_Msk
#define GTIM_IFR_TI_Pos                                     (1U)
#define GTIM_IFR_TI_Msk                                     (0x1UL << GTIM_IFR_TI_Pos)
#define GTIM_IFR_TI                                         GTIM_IFR_TI_Msk
#define GTIM_IFR_CC0_Pos                                    (2U)
#define GTIM_IFR_CC0_Msk                                    (0x1UL << GTIM_IFR_CC0_Pos)
#define GTIM_IFR_CC0                                        GTIM_IFR_CC0_Msk
#define GTIM_IFR_CC1_Pos                                    (3U)
#define GTIM_IFR_CC1_Msk                                    (0x1UL << GTIM_IFR_CC1_Pos)
#define GTIM_IFR_CC1                                        GTIM_IFR_CC1_Msk
#define GTIM_IFR_CC2_Pos                                    (4U)
#define GTIM_IFR_CC2_Msk                                    (0x1UL << GTIM_IFR_CC2_Pos)
#define GTIM_IFR_CC2                                        GTIM_IFR_CC2_Msk
#define GTIM_IFR_CC3_Pos                                    (5U)
#define GTIM_IFR_CC3_Msk                                    (0x1UL << GTIM_IFR_CC3_Pos)
#define GTIM_IFR_CC3                                        GTIM_IFR_CC3_Msk

// GTIM_ICR
#define GTIM_ICR_UI_Pos                                     (0U)
#define GTIM_ICR_UI_Msk                                     (0x1UL << GTIM_ICR_UI_Pos)
#define GTIM_ICR_UI                                         GTIM_ICR_UI_Msk
#define GTIM_ICR_TI_Pos                                     (1U)
#define GTIM_ICR_TI_Msk                                     (0x1UL << GTIM_ICR_TI_Pos)
#define GTIM_ICR_TI                                         GTIM_ICR_TI_Msk
#define GTIM_ICR_CC0_Pos                                    (2U)
#define GTIM_ICR_CC0_Msk                                    (0x1UL << GTIM_ICR_CC0_Pos)
#define GTIM_ICR_CC0                                        GTIM_ICR_CC0_Msk
#define GTIM_ICR_CC1_Pos                                    (3U)
#define GTIM_ICR_CC1_Msk                                    (0x1UL << GTIM_ICR_CC1_Pos)
#define GTIM_ICR_CC1                                        GTIM_ICR_CC1_Msk
#define GTIM_ICR_CC2_Pos                                    (4U)
#define GTIM_ICR_CC2_Msk                                    (0x1UL << GTIM_ICR_CC2_Pos)
#define GTIM_ICR_CC2                                        GTIM_ICR_CC2_Msk
#define GTIM_ICR_CC3_Pos                                    (5U)
#define GTIM_ICR_CC3_Msk                                    (0x1UL << GTIM_ICR_CC3_Pos)
#define GTIM_ICR_CC3                                        GTIM_ICR_CC3_Msk

// GTIM_CCR0
#define GTIM_CCR0_CCR_Pos                                   (0U)
#define GTIM_CCR0_CCR_Msk                                   (0xFFFFUL << GTIM_CCR0_CCR_Pos)
#define GTIM_CCR0_CCR                                       GTIM_CCR0_CCR_Msk

// GTIM_CCR1
#define GTIM_CCR1_CCR_Pos                                   (0U)
#define GTIM_CCR1_CCR_Msk                                   (0xFFFFUL << GTIM_CCR1_CCR_Pos)
#define GTIM_CCR1_CCR                                       GTIM_CCR1_CCR_Msk

// GTIM_CCR2
#define GTIM_CCR2_CCR_Pos                                   (0U)
#define GTIM_CCR2_CCR_Msk                                   (0xFFFFUL << GTIM_CCR2_CCR_Pos)
#define GTIM_CCR2_CCR                                       GTIM_CCR2_CCR_Msk

// GTIM_CCR3
#define GTIM_CCR3_CCR_Pos                                   (0U)
#define GTIM_CCR3_CCR_Msk                                   (0xFFFFUL << GTIM_CCR3_CCR_Pos)
#define GTIM_CCR3_CCR                                       GTIM_CCR3_CCR_Msk



//********************    Bits Define For Peripheral HSI2C    ********************//
// HSI2C_MCR
#define HSI2C_MCR_MEN_Pos                                   (0U)
#define HSI2C_MCR_MEN_Msk                                   (0x1UL << HSI2C_MCR_MEN_Pos)
#define HSI2C_MCR_MEN                                       HSI2C_MCR_MEN_Msk
#define HSI2C_MCR_RST_Pos                                   (1U)
#define HSI2C_MCR_RST_Msk                                   (0x1UL << HSI2C_MCR_RST_Pos)
#define HSI2C_MCR_RST                                       HSI2C_MCR_RST_Msk
#define HSI2C_MCR_DBGEN_Pos                                 (3U)
#define HSI2C_MCR_DBGEN_Msk                                 (0x1UL << HSI2C_MCR_DBGEN_Pos)
#define HSI2C_MCR_DBGEN                                     HSI2C_MCR_DBGEN_Msk

// HSI2C_MSR
#define HSI2C_MSR_TDF_Pos                                   (0U)
#define HSI2C_MSR_TDF_Msk                                   (0x1UL << HSI2C_MSR_TDF_Pos)
#define HSI2C_MSR_TDF                                       HSI2C_MSR_TDF_Msk
#define HSI2C_MSR_RDF_Pos                                   (1U)
#define HSI2C_MSR_RDF_Msk                                   (0x1UL << HSI2C_MSR_RDF_Pos)
#define HSI2C_MSR_RDF                                       HSI2C_MSR_RDF_Msk
#define HSI2C_MSR_EPF_Pos                                   (8U)
#define HSI2C_MSR_EPF_Msk                                   (0x1UL << HSI2C_MSR_EPF_Pos)
#define HSI2C_MSR_EPF                                       HSI2C_MSR_EPF_Msk
#define HSI2C_MSR_SDF_Pos                                   (9U)
#define HSI2C_MSR_SDF_Msk                                   (0x1UL << HSI2C_MSR_SDF_Pos)
#define HSI2C_MSR_SDF                                       HSI2C_MSR_SDF_Msk
#define HSI2C_MSR_NDF_Pos                                   (10U)
#define HSI2C_MSR_NDF_Msk                                   (0x1UL << HSI2C_MSR_NDF_Pos)
#define HSI2C_MSR_NDF                                       HSI2C_MSR_NDF_Msk
#define HSI2C_MSR_ALF_Pos                                   (11U)
#define HSI2C_MSR_ALF_Msk                                   (0x1UL << HSI2C_MSR_ALF_Pos)
#define HSI2C_MSR_ALF                                       HSI2C_MSR_ALF_Msk
#define HSI2C_MSR_FEF_Pos                                   (12U)
#define HSI2C_MSR_FEF_Msk                                   (0x1UL << HSI2C_MSR_FEF_Pos)
#define HSI2C_MSR_FEF                                       HSI2C_MSR_FEF_Msk
#define HSI2C_MSR_PLTF_Pos                                  (13U)
#define HSI2C_MSR_PLTF_Msk                                  (0x1UL << HSI2C_MSR_PLTF_Pos)
#define HSI2C_MSR_PLTF                                      HSI2C_MSR_PLTF_Msk
#define HSI2C_MSR_DMF_Pos                                   (14U)
#define HSI2C_MSR_DMF_Msk                                   (0x1UL << HSI2C_MSR_DMF_Pos)
#define HSI2C_MSR_DMF                                       HSI2C_MSR_DMF_Msk
#define HSI2C_MSR_MBF_Pos                                   (24U)
#define HSI2C_MSR_MBF_Msk                                   (0x1UL << HSI2C_MSR_MBF_Pos)
#define HSI2C_MSR_MBF                                       HSI2C_MSR_MBF_Msk
#define HSI2C_MSR_BBF_Pos                                   (25U)
#define HSI2C_MSR_BBF_Msk                                   (0x1UL << HSI2C_MSR_BBF_Pos)
#define HSI2C_MSR_BBF                                       HSI2C_MSR_BBF_Msk

// HSI2C_MIER
#define HSI2C_MIER_TDIE_Pos                                 (0U)
#define HSI2C_MIER_TDIE_Msk                                 (0x1UL << HSI2C_MIER_TDIE_Pos)
#define HSI2C_MIER_TDIE                                     HSI2C_MIER_TDIE_Msk
#define HSI2C_MIER_RDIE_Pos                                 (1U)
#define HSI2C_MIER_RDIE_Msk                                 (0x1UL << HSI2C_MIER_RDIE_Pos)
#define HSI2C_MIER_RDIE                                     HSI2C_MIER_RDIE_Msk
#define HSI2C_MIER_EPIE_Pos                                 (8U)
#define HSI2C_MIER_EPIE_Msk                                 (0x1UL << HSI2C_MIER_EPIE_Pos)
#define HSI2C_MIER_EPIE                                     HSI2C_MIER_EPIE_Msk
#define HSI2C_MIER_SDIE_Pos                                 (9U)
#define HSI2C_MIER_SDIE_Msk                                 (0x1UL << HSI2C_MIER_SDIE_Pos)
#define HSI2C_MIER_SDIE                                     HSI2C_MIER_SDIE_Msk
#define HSI2C_MIER_NDIE_Pos                                 (10U)
#define HSI2C_MIER_NDIE_Msk                                 (0x1UL << HSI2C_MIER_NDIE_Pos)
#define HSI2C_MIER_NDIE                                     HSI2C_MIER_NDIE_Msk
#define HSI2C_MIER_ALIE_Pos                                 (11U)
#define HSI2C_MIER_ALIE_Msk                                 (0x1UL << HSI2C_MIER_ALIE_Pos)
#define HSI2C_MIER_ALIE                                     HSI2C_MIER_ALIE_Msk
#define HSI2C_MIER_FEIE_Pos                                 (12U)
#define HSI2C_MIER_FEIE_Msk                                 (0x1UL << HSI2C_MIER_FEIE_Pos)
#define HSI2C_MIER_FEIE                                     HSI2C_MIER_FEIE_Msk
#define HSI2C_MIER_PLTIE_Pos                                (13U)
#define HSI2C_MIER_PLTIE_Msk                                (0x1UL << HSI2C_MIER_PLTIE_Pos)
#define HSI2C_MIER_PLTIE                                    HSI2C_MIER_PLTIE_Msk
#define HSI2C_MIER_DMIE_Pos                                 (14U)
#define HSI2C_MIER_DMIE_Msk                                 (0x1UL << HSI2C_MIER_DMIE_Pos)
#define HSI2C_MIER_DMIE                                     HSI2C_MIER_DMIE_Msk

// HSI2C_MSCR
#define HSI2C_MSCR_EPC_Pos                                  (8U)
#define HSI2C_MSCR_EPC_Msk                                  (0x1UL << HSI2C_MSCR_EPC_Pos)
#define HSI2C_MSCR_EPC                                      HSI2C_MSCR_EPC_Msk
#define HSI2C_MSCR_SDC_Pos                                  (9U)
#define HSI2C_MSCR_SDC_Msk                                  (0x1UL << HSI2C_MSCR_SDC_Pos)
#define HSI2C_MSCR_SDC                                      HSI2C_MSCR_SDC_Msk
#define HSI2C_MSCR_NDC_Pos                                  (10U)
#define HSI2C_MSCR_NDC_Msk                                  (0x1UL << HSI2C_MSCR_NDC_Pos)
#define HSI2C_MSCR_NDC                                      HSI2C_MSCR_NDC_Msk
#define HSI2C_MSCR_ALC_Pos                                  (11U)
#define HSI2C_MSCR_ALC_Msk                                  (0x1UL << HSI2C_MSCR_ALC_Pos)
#define HSI2C_MSCR_ALC                                      HSI2C_MSCR_ALC_Msk
#define HSI2C_MSCR_FEC_Pos                                  (12U)
#define HSI2C_MSCR_FEC_Msk                                  (0x1UL << HSI2C_MSCR_FEC_Pos)
#define HSI2C_MSCR_FEC                                      HSI2C_MSCR_FEC_Msk
#define HSI2C_MSCR_PLTC_Pos                                 (13U)
#define HSI2C_MSCR_PLTC_Msk                                 (0x1UL << HSI2C_MSCR_PLTC_Pos)
#define HSI2C_MSCR_PLTC                                     HSI2C_MSCR_PLTC_Msk
#define HSI2C_MSCR_DMC_Pos                                  (14U)
#define HSI2C_MSCR_DMC_Msk                                  (0x1UL << HSI2C_MSCR_DMC_Pos)
#define HSI2C_MSCR_DMC                                      HSI2C_MSCR_DMC_Msk

// HSI2C_MCFGR1
#define HSI2C_MCFGR1_PRESCALE_Pos                           (0U)
#define HSI2C_MCFGR1_PRESCALE_Msk                           (0x7UL << HSI2C_MCFGR1_PRESCALE_Pos)
#define HSI2C_MCFGR1_PRESCALE                               HSI2C_MCFGR1_PRESCALE_Msk
#define HSI2C_MCFGR1_AUTOSTOP_Pos                           (8U)
#define HSI2C_MCFGR1_AUTOSTOP_Msk                           (0x1UL << HSI2C_MCFGR1_AUTOSTOP_Pos)
#define HSI2C_MCFGR1_AUTOSTOP                               HSI2C_MCFGR1_AUTOSTOP_Msk
#define HSI2C_MCFGR1_IGNACK_Pos                             (9U)
#define HSI2C_MCFGR1_IGNACK_Msk                             (0x1UL << HSI2C_MCFGR1_IGNACK_Pos)
#define HSI2C_MCFGR1_IGNACK                                 HSI2C_MCFGR1_IGNACK_Msk
#define HSI2C_MCFGR1_TIMECFG_Pos                            (10U)
#define HSI2C_MCFGR1_TIMECFG_Msk                            (0x1UL << HSI2C_MCFGR1_TIMECFG_Pos)
#define HSI2C_MCFGR1_TIMECFG                                HSI2C_MCFGR1_TIMECFG_Msk
#define HSI2C_MCFGR1_RDMO_Pos                               (12U)
#define HSI2C_MCFGR1_RDMO_Msk                               (0x1UL << HSI2C_MCFGR1_RDMO_Pos)
#define HSI2C_MCFGR1_RDMO                                   HSI2C_MCFGR1_RDMO_Msk
#define HSI2C_MCFGR1_MATCFG_Pos                             (13U)
#define HSI2C_MCFGR1_MATCFG_Msk                             (0x7UL << HSI2C_MCFGR1_MATCFG_Pos)
#define HSI2C_MCFGR1_MATCFG                                 HSI2C_MCFGR1_MATCFG_Msk

// HSI2C_MCFGR2
#define HSI2C_MCFGR2_BUSIDLE_Pos                            (0U)
#define HSI2C_MCFGR2_BUSIDLE_Msk                            (0xFFFUL << HSI2C_MCFGR2_BUSIDLE_Pos)
#define HSI2C_MCFGR2_BUSIDLE                                HSI2C_MCFGR2_BUSIDLE_Msk
#define HSI2C_MCFGR2_FILTSCL_Pos                            (16U)
#define HSI2C_MCFGR2_FILTSCL_Msk                            (0xFUL << HSI2C_MCFGR2_FILTSCL_Pos)
#define HSI2C_MCFGR2_FILTSCL                                HSI2C_MCFGR2_FILTSCL_Msk
#define HSI2C_MCFGR2_FILTBPSCL_Pos                          (23U)
#define HSI2C_MCFGR2_FILTBPSCL_Msk                          (0x1UL << HSI2C_MCFGR2_FILTBPSCL_Pos)
#define HSI2C_MCFGR2_FILTBPSCL                              HSI2C_MCFGR2_FILTBPSCL_Msk
#define HSI2C_MCFGR2_FILTSDA_Pos                            (24U)
#define HSI2C_MCFGR2_FILTSDA_Msk                            (0xFUL << HSI2C_MCFGR2_FILTSDA_Pos)
#define HSI2C_MCFGR2_FILTSDA                                HSI2C_MCFGR2_FILTSDA_Msk
#define HSI2C_MCFGR2_FILTBPSDA_Pos                          (31U)
#define HSI2C_MCFGR2_FILTBPSDA_Msk                          (0x1UL << HSI2C_MCFGR2_FILTBPSDA_Pos)
#define HSI2C_MCFGR2_FILTBPSDA                              HSI2C_MCFGR2_FILTBPSDA_Msk

// HSI2C_MCFGR3
#define HSI2C_MCFGR3_PINLOW_Pos                             (8U)
#define HSI2C_MCFGR3_PINLOW_Msk                             (0xFFFUL << HSI2C_MCFGR3_PINLOW_Pos)
#define HSI2C_MCFGR3_PINLOW                                 HSI2C_MCFGR3_PINLOW_Msk

// HSI2C_MCCR0
#define HSI2C_MCCR0_CLKLO_Pos                               (0U)
#define HSI2C_MCCR0_CLKLO_Msk                               (0x3FUL << HSI2C_MCCR0_CLKLO_Pos)
#define HSI2C_MCCR0_CLKLO                                   HSI2C_MCCR0_CLKLO_Msk
#define HSI2C_MCCR0_CLKHI_Pos                               (8U)
#define HSI2C_MCCR0_CLKHI_Msk                               (0x3FUL << HSI2C_MCCR0_CLKHI_Pos)
#define HSI2C_MCCR0_CLKHI                                   HSI2C_MCCR0_CLKHI_Msk
#define HSI2C_MCCR0_SETHOLD_Pos                             (16U)
#define HSI2C_MCCR0_SETHOLD_Msk                             (0x3FUL << HSI2C_MCCR0_SETHOLD_Pos)
#define HSI2C_MCCR0_SETHOLD                                 HSI2C_MCCR0_SETHOLD_Msk
#define HSI2C_MCCR0_DATAVD_Pos                              (24U)
#define HSI2C_MCCR0_DATAVD_Msk                              (0x3FUL << HSI2C_MCCR0_DATAVD_Pos)
#define HSI2C_MCCR0_DATAVD                                  HSI2C_MCCR0_DATAVD_Msk

// HSI2C_MCCR1
#define HSI2C_MCCR1_CLKLO_Pos                               (0U)
#define HSI2C_MCCR1_CLKLO_Msk                               (0x3FUL << HSI2C_MCCR1_CLKLO_Pos)
#define HSI2C_MCCR1_CLKLO                                   HSI2C_MCCR1_CLKLO_Msk
#define HSI2C_MCCR1_CLKHI_Pos                               (8U)
#define HSI2C_MCCR1_CLKHI_Msk                               (0x3FUL << HSI2C_MCCR1_CLKHI_Pos)
#define HSI2C_MCCR1_CLKHI                                   HSI2C_MCCR1_CLKHI_Msk
#define HSI2C_MCCR1_SETHOLD_Pos                             (16U)
#define HSI2C_MCCR1_SETHOLD_Msk                             (0x3FUL << HSI2C_MCCR1_SETHOLD_Pos)
#define HSI2C_MCCR1_SETHOLD                                 HSI2C_MCCR1_SETHOLD_Msk
#define HSI2C_MCCR1_DATAVD_Pos                              (24U)
#define HSI2C_MCCR1_DATAVD_Msk                              (0x3FUL << HSI2C_MCCR1_DATAVD_Pos)
#define HSI2C_MCCR1_DATAVD                                  HSI2C_MCCR1_DATAVD_Msk

// HSI2C_MTDR
#define HSI2C_MTDR_DATA_Pos                                 (0U)
#define HSI2C_MTDR_DATA_Msk                                 (0xFFUL << HSI2C_MTDR_DATA_Pos)
#define HSI2C_MTDR_DATA                                     HSI2C_MTDR_DATA_Msk
#define HSI2C_MTDR_CMD_Pos                                  (8U)
#define HSI2C_MTDR_CMD_Msk                                  (0x7UL << HSI2C_MTDR_CMD_Pos)
#define HSI2C_MTDR_CMD                                      HSI2C_MTDR_CMD_Msk

// HSI2C_MRDR
#define HSI2C_MRDR_DATA_Pos                                 (0U)
#define HSI2C_MRDR_DATA_Msk                                 (0xFFUL << HSI2C_MRDR_DATA_Pos)
#define HSI2C_MRDR_DATA                                     HSI2C_MRDR_DATA_Msk
#define HSI2C_MRDR_RXEMPTY_Pos                              (14U)
#define HSI2C_MRDR_RXEMPTY_Msk                              (0x1UL << HSI2C_MRDR_RXEMPTY_Pos)
#define HSI2C_MRDR_RXEMPTY                                  HSI2C_MRDR_RXEMPTY_Msk

// HSI2C_MDMR
#define HSI2C_MDMR_MATCH0_Pos                               (0U)
#define HSI2C_MDMR_MATCH0_Msk                               (0xFFUL << HSI2C_MDMR_MATCH0_Pos)
#define HSI2C_MDMR_MATCH0                                   HSI2C_MDMR_MATCH0_Msk
#define HSI2C_MDMR_MATCH1_Pos                               (16U)
#define HSI2C_MDMR_MATCH1_Msk                               (0xFFUL << HSI2C_MDMR_MATCH1_Pos)
#define HSI2C_MDMR_MATCH1                                   HSI2C_MDMR_MATCH1_Msk

// HSI2C_SCR0
#define HSI2C_SCR0_SEN_Pos                                  (0U)
#define HSI2C_SCR0_SEN_Msk                                  (0x1UL << HSI2C_SCR0_SEN_Pos)
#define HSI2C_SCR0_SEN                                      HSI2C_SCR0_SEN_Msk
#define HSI2C_SCR0_RST_Pos                                  (1U)
#define HSI2C_SCR0_RST_Msk                                  (0x1UL << HSI2C_SCR0_RST_Pos)
#define HSI2C_SCR0_RST                                      HSI2C_SCR0_RST_Msk

// HSI2C_SSR
#define HSI2C_SSR_TDF_Pos                                   (0U)
#define HSI2C_SSR_TDF_Msk                                   (0x1UL << HSI2C_SSR_TDF_Pos)
#define HSI2C_SSR_TDF                                       HSI2C_SSR_TDF_Msk
#define HSI2C_SSR_RDF_Pos                                   (1U)
#define HSI2C_SSR_RDF_Msk                                   (0x1UL << HSI2C_SSR_RDF_Pos)
#define HSI2C_SSR_RDF                                       HSI2C_SSR_RDF_Msk
#define HSI2C_SSR_AVF_Pos                                   (2U)
#define HSI2C_SSR_AVF_Msk                                   (0x1UL << HSI2C_SSR_AVF_Pos)
#define HSI2C_SSR_AVF                                       HSI2C_SSR_AVF_Msk
#define HSI2C_SSR_TAF_Pos                                   (3U)
#define HSI2C_SSR_TAF_Msk                                   (0x1UL << HSI2C_SSR_TAF_Pos)
#define HSI2C_SSR_TAF                                       HSI2C_SSR_TAF_Msk
#define HSI2C_SSR_RSF_Pos                                   (8U)
#define HSI2C_SSR_RSF_Msk                                   (0x1UL << HSI2C_SSR_RSF_Pos)
#define HSI2C_SSR_RSF                                       HSI2C_SSR_RSF_Msk
#define HSI2C_SSR_SDF_Pos                                   (9U)
#define HSI2C_SSR_SDF_Msk                                   (0x1UL << HSI2C_SSR_SDF_Pos)
#define HSI2C_SSR_SDF                                       HSI2C_SSR_SDF_Msk
#define HSI2C_SSR_BEF_Pos                                   (10U)
#define HSI2C_SSR_BEF_Msk                                   (0x1UL << HSI2C_SSR_BEF_Pos)
#define HSI2C_SSR_BEF                                       HSI2C_SSR_BEF_Msk
#define HSI2C_SSR_FEF_Pos                                   (11U)
#define HSI2C_SSR_FEF_Msk                                   (0x1UL << HSI2C_SSR_FEF_Pos)
#define HSI2C_SSR_FEF                                       HSI2C_SSR_FEF_Msk
#define HSI2C_SSR_AM0F_Pos                                  (12U)
#define HSI2C_SSR_AM0F_Msk                                  (0x1UL << HSI2C_SSR_AM0F_Pos)
#define HSI2C_SSR_AM0F                                      HSI2C_SSR_AM0F_Msk
#define HSI2C_SSR_AM1F_Pos                                  (13U)
#define HSI2C_SSR_AM1F_Msk                                  (0x1UL << HSI2C_SSR_AM1F_Pos)
#define HSI2C_SSR_AM1F                                      HSI2C_SSR_AM1F_Msk
#define HSI2C_SSR_GCF_Pos                                   (14U)
#define HSI2C_SSR_GCF_Msk                                   (0x1UL << HSI2C_SSR_GCF_Pos)
#define HSI2C_SSR_GCF                                       HSI2C_SSR_GCF_Msk
#define HSI2C_SSR_SARF_Pos                                  (15U)
#define HSI2C_SSR_SARF_Msk                                  (0x1UL << HSI2C_SSR_SARF_Pos)
#define HSI2C_SSR_SARF                                      HSI2C_SSR_SARF_Msk
#define HSI2C_SSR_SBF_Pos                                   (24U)
#define HSI2C_SSR_SBF_Msk                                   (0x1UL << HSI2C_SSR_SBF_Pos)
#define HSI2C_SSR_SBF                                       HSI2C_SSR_SBF_Msk
#define HSI2C_SSR_BBF_Pos                                   (25U)
#define HSI2C_SSR_BBF_Msk                                   (0x1UL << HSI2C_SSR_BBF_Pos)
#define HSI2C_SSR_BBF                                       HSI2C_SSR_BBF_Msk

// HSI2C_SIER
#define HSI2C_SIER_TDIE_Pos                                 (0U)
#define HSI2C_SIER_TDIE_Msk                                 (0x1UL << HSI2C_SIER_TDIE_Pos)
#define HSI2C_SIER_TDIE                                     HSI2C_SIER_TDIE_Msk
#define HSI2C_SIER_RDIE_Pos                                 (1U)
#define HSI2C_SIER_RDIE_Msk                                 (0x1UL << HSI2C_SIER_RDIE_Pos)
#define HSI2C_SIER_RDIE                                     HSI2C_SIER_RDIE_Msk
#define HSI2C_SIER_AVIE_Pos                                 (2U)
#define HSI2C_SIER_AVIE_Msk                                 (0x1UL << HSI2C_SIER_AVIE_Pos)
#define HSI2C_SIER_AVIE                                     HSI2C_SIER_AVIE_Msk
#define HSI2C_SIER_TAIE_Pos                                 (3U)
#define HSI2C_SIER_TAIE_Msk                                 (0x1UL << HSI2C_SIER_TAIE_Pos)
#define HSI2C_SIER_TAIE                                     HSI2C_SIER_TAIE_Msk
#define HSI2C_SIER_RSIE_Pos                                 (8U)
#define HSI2C_SIER_RSIE_Msk                                 (0x1UL << HSI2C_SIER_RSIE_Pos)
#define HSI2C_SIER_RSIE                                     HSI2C_SIER_RSIE_Msk
#define HSI2C_SIER_SDIE_Pos                                 (9U)
#define HSI2C_SIER_SDIE_Msk                                 (0x1UL << HSI2C_SIER_SDIE_Pos)
#define HSI2C_SIER_SDIE                                     HSI2C_SIER_SDIE_Msk
#define HSI2C_SIER_BEIE_Pos                                 (10U)
#define HSI2C_SIER_BEIE_Msk                                 (0x1UL << HSI2C_SIER_BEIE_Pos)
#define HSI2C_SIER_BEIE                                     HSI2C_SIER_BEIE_Msk
#define HSI2C_SIER_FEIE_Pos                                 (11U)
#define HSI2C_SIER_FEIE_Msk                                 (0x1UL << HSI2C_SIER_FEIE_Pos)
#define HSI2C_SIER_FEIE                                     HSI2C_SIER_FEIE_Msk
#define HSI2C_SIER_AM0IE_Pos                                (12U)
#define HSI2C_SIER_AM0IE_Msk                                (0x1UL << HSI2C_SIER_AM0IE_Pos)
#define HSI2C_SIER_AM0IE                                    HSI2C_SIER_AM0IE_Msk
#define HSI2C_SIER_AM1IE_Pos                                (13U)
#define HSI2C_SIER_AM1IE_Msk                                (0x1UL << HSI2C_SIER_AM1IE_Pos)
#define HSI2C_SIER_AM1IE                                    HSI2C_SIER_AM1IE_Msk
#define HSI2C_SIER_GCIE_Pos                                 (14U)
#define HSI2C_SIER_GCIE_Msk                                 (0x1UL << HSI2C_SIER_GCIE_Pos)
#define HSI2C_SIER_GCIE                                     HSI2C_SIER_GCIE_Msk
#define HSI2C_SIER_SARIE_Pos                                (15U)
#define HSI2C_SIER_SARIE_Msk                                (0x1UL << HSI2C_SIER_SARIE_Pos)
#define HSI2C_SIER_SARIE                                    HSI2C_SIER_SARIE_Msk

// HSI2C_SSCR
#define HSI2C_SSCR_RSC_Pos                                  (8U)
#define HSI2C_SSCR_RSC_Msk                                  (0x1UL << HSI2C_SSCR_RSC_Pos)
#define HSI2C_SSCR_RSC                                      HSI2C_SSCR_RSC_Msk
#define HSI2C_SSCR_SDC_Pos                                  (9U)
#define HSI2C_SSCR_SDC_Msk                                  (0x1UL << HSI2C_SSCR_SDC_Pos)
#define HSI2C_SSCR_SDC                                      HSI2C_SSCR_SDC_Msk
#define HSI2C_SSCR_BEC_Pos                                  (10U)
#define HSI2C_SSCR_BEC_Msk                                  (0x1UL << HSI2C_SSCR_BEC_Pos)
#define HSI2C_SSCR_BEC                                      HSI2C_SSCR_BEC_Msk
#define HSI2C_SSCR_FEC_Pos                                  (11U)
#define HSI2C_SSCR_FEC_Msk                                  (0x1UL << HSI2C_SSCR_FEC_Pos)
#define HSI2C_SSCR_FEC                                      HSI2C_SSCR_FEC_Msk

// HSI2C_SCR1
#define HSI2C_SCR1_ADRSTALL_Pos                             (0U)
#define HSI2C_SCR1_ADRSTALL_Msk                             (0x1UL << HSI2C_SCR1_ADRSTALL_Pos)
#define HSI2C_SCR1_ADRSTALL                                 HSI2C_SCR1_ADRSTALL_Msk
#define HSI2C_SCR1_RXSTALL_Pos                              (1U)
#define HSI2C_SCR1_RXSTALL_Msk                              (0x1UL << HSI2C_SCR1_RXSTALL_Pos)
#define HSI2C_SCR1_RXSTALL                                  HSI2C_SCR1_RXSTALL_Msk
#define HSI2C_SCR1_TXDSTALL_Pos                             (2U)
#define HSI2C_SCR1_TXDSTALL_Msk                             (0x1UL << HSI2C_SCR1_TXDSTALL_Pos)
#define HSI2C_SCR1_TXDSTALL                                 HSI2C_SCR1_TXDSTALL_Msk
#define HSI2C_SCR1_ACKSTALL_Pos                             (3U)
#define HSI2C_SCR1_ACKSTALL_Msk                             (0x1UL << HSI2C_SCR1_ACKSTALL_Pos)
#define HSI2C_SCR1_ACKSTALL                                 HSI2C_SCR1_ACKSTALL_Msk
#define HSI2C_SCR1_GCEN_Pos                                 (8U)
#define HSI2C_SCR1_GCEN_Msk                                 (0x1UL << HSI2C_SCR1_GCEN_Pos)
#define HSI2C_SCR1_GCEN                                     HSI2C_SCR1_GCEN_Msk
#define HSI2C_SCR1_SAEN_Pos                                 (9U)
#define HSI2C_SCR1_SAEN_Msk                                 (0x1UL << HSI2C_SCR1_SAEN_Pos)
#define HSI2C_SCR1_SAEN                                     HSI2C_SCR1_SAEN_Msk
#define HSI2C_SCR1_TXCFG_Pos                                (10U)
#define HSI2C_SCR1_TXCFG_Msk                                (0x1UL << HSI2C_SCR1_TXCFG_Pos)
#define HSI2C_SCR1_TXCFG                                    HSI2C_SCR1_TXCFG_Msk
#define HSI2C_SCR1_RXCFG_Pos                                (11U)
#define HSI2C_SCR1_RXCFG_Msk                                (0x1UL << HSI2C_SCR1_RXCFG_Pos)
#define HSI2C_SCR1_RXCFG                                    HSI2C_SCR1_RXCFG_Msk
#define HSI2C_SCR1_IGNACK_Pos                               (12U)
#define HSI2C_SCR1_IGNACK_Msk                               (0x1UL << HSI2C_SCR1_IGNACK_Pos)
#define HSI2C_SCR1_IGNACK                                   HSI2C_SCR1_IGNACK_Msk
#define HSI2C_SCR1_HSMEN_Pos                                (13U)
#define HSI2C_SCR1_HSMEN_Msk                                (0x1UL << HSI2C_SCR1_HSMEN_Pos)
#define HSI2C_SCR1_HSMEN                                    HSI2C_SCR1_HSMEN_Msk
#define HSI2C_SCR1_ADDRMODE_Pos                             (16U)
#define HSI2C_SCR1_ADDRMODE_Msk                             (0x7UL << HSI2C_SCR1_ADDRMODE_Pos)
#define HSI2C_SCR1_ADDRMODE                                 HSI2C_SCR1_ADDRMODE_Msk

// HSI2C_SCR2
#define HSI2C_SCR2_CLKHOLD_Pos                              (0U)
#define HSI2C_SCR2_CLKHOLD_Msk                              (0xFUL << HSI2C_SCR2_CLKHOLD_Pos)
#define HSI2C_SCR2_CLKHOLD                                  HSI2C_SCR2_CLKHOLD_Msk
#define HSI2C_SCR2_DATAVD_Pos                               (8U)
#define HSI2C_SCR2_DATAVD_Msk                               (0x3FUL << HSI2C_SCR2_DATAVD_Pos)
#define HSI2C_SCR2_DATAVD                                   HSI2C_SCR2_DATAVD_Msk
#define HSI2C_SCR2_FILTEN_Pos                               (14U)
#define HSI2C_SCR2_FILTEN_Msk                               (0x1UL << HSI2C_SCR2_FILTEN_Pos)
#define HSI2C_SCR2_FILTEN                                   HSI2C_SCR2_FILTEN_Msk
#define HSI2C_SCR2_FILTSCL_Pos                              (16U)
#define HSI2C_SCR2_FILTSCL_Msk                              (0xFUL << HSI2C_SCR2_FILTSCL_Pos)
#define HSI2C_SCR2_FILTSCL                                  HSI2C_SCR2_FILTSCL_Msk
#define HSI2C_SCR2_FILTSDA_Pos                              (20U)
#define HSI2C_SCR2_FILTSDA_Msk                              (0xFUL << HSI2C_SCR2_FILTSDA_Pos)
#define HSI2C_SCR2_FILTSDA                                  HSI2C_SCR2_FILTSDA_Msk

// HSI2C_STAR
#define HSI2C_STAR_TXNACK_Pos                               (0U)
#define HSI2C_STAR_TXNACK_Msk                               (0x1UL << HSI2C_STAR_TXNACK_Pos)
#define HSI2C_STAR_TXNACK                                   HSI2C_STAR_TXNACK_Msk

// HSI2C_STDR
#define HSI2C_STDR_DATA_Pos                                 (0U)
#define HSI2C_STDR_DATA_Msk                                 (0xFFUL << HSI2C_STDR_DATA_Pos)
#define HSI2C_STDR_DATA                                     HSI2C_STDR_DATA_Msk

// HSI2C_SRDR
#define HSI2C_SRDR_DATA_Pos                                 (0U)
#define HSI2C_SRDR_DATA_Msk                                 (0xFFUL << HSI2C_SRDR_DATA_Pos)
#define HSI2C_SRDR_DATA                                     HSI2C_SRDR_DATA_Msk
#define HSI2C_SRDR_REMP_Pos                                 (14U)
#define HSI2C_SRDR_REMP_Msk                                 (0x1UL << HSI2C_SRDR_REMP_Pos)
#define HSI2C_SRDR_REMP                                     HSI2C_SRDR_REMP_Msk
#define HSI2C_SRDR_SOF_Pos                                  (15U)
#define HSI2C_SRDR_SOF_Msk                                  (0x1UL << HSI2C_SRDR_SOF_Pos)
#define HSI2C_SRDR_SOF                                      HSI2C_SRDR_SOF_Msk

// HSI2C_SADDR
#define HSI2C_SADDR_ADDR0_Pos                               (1U)
#define HSI2C_SADDR_ADDR0_Msk                               (0x3FFUL << HSI2C_SADDR_ADDR0_Pos)
#define HSI2C_SADDR_ADDR0                                   HSI2C_SADDR_ADDR0_Msk
#define HSI2C_SADDR_ADDR1_Pos                               (17U)
#define HSI2C_SADDR_ADDR1_Msk                               (0x3FFUL << HSI2C_SADDR_ADDR1_Pos)
#define HSI2C_SADDR_ADDR1                                   HSI2C_SADDR_ADDR1_Msk

// HSI2C_SASR
#define HSI2C_SASR_RADDR_Pos                                (0U)
#define HSI2C_SASR_RADDR_Msk                                (0x7FFUL << HSI2C_SASR_RADDR_Pos)
#define HSI2C_SASR_RADDR                                    HSI2C_SASR_RADDR_Msk
#define HSI2C_SASR_ANV_Pos                                  (14U)
#define HSI2C_SASR_ANV_Msk                                  (0x1UL << HSI2C_SASR_ANV_Pos)
#define HSI2C_SASR_ANV                                      HSI2C_SASR_ANV_Msk



//********************    Bits Define For Peripheral IWDT    ********************//
// IWDT_KR
#define IWDT_KR_KR_Pos                                      (0U)
#define IWDT_KR_KR_Msk                                      (0xFFFFUL << IWDT_KR_KR_Pos)
#define IWDT_KR_KR                                          IWDT_KR_KR_Msk

// IWDT_CR
#define IWDT_CR_PRS_Pos                                     (0U)
#define IWDT_CR_PRS_Msk                                     (0x7UL << IWDT_CR_PRS_Pos)
#define IWDT_CR_PRS                                         IWDT_CR_PRS_Msk
#define IWDT_CR_IE_Pos                                      (4U)
#define IWDT_CR_IE_Msk                                      (0x1UL << IWDT_CR_IE_Pos)
#define IWDT_CR_IE                                          IWDT_CR_IE_Msk
#define IWDT_CR_ACTION_Pos                                  (5U)
#define IWDT_CR_ACTION_Msk                                  (0x1UL << IWDT_CR_ACTION_Pos)
#define IWDT_CR_ACTION                                      IWDT_CR_ACTION_Msk
#define IWDT_CR_PAUSE_Pos                                   (6U)
#define IWDT_CR_PAUSE_Msk                                   (0x1UL << IWDT_CR_PAUSE_Pos)
#define IWDT_CR_PAUSE                                       IWDT_CR_PAUSE_Msk

// IWDT_ARR
#define IWDT_ARR_ARR_Pos                                    (0U)
#define IWDT_ARR_ARR_Msk                                    (0xFFFUL << IWDT_ARR_ARR_Pos)
#define IWDT_ARR_ARR                                        IWDT_ARR_ARR_Msk

// IWDT_SR
#define IWDT_SR_CRF_Pos                                     (0U)
#define IWDT_SR_CRF_Msk                                     (0x1UL << IWDT_SR_CRF_Pos)
#define IWDT_SR_CRF                                         IWDT_SR_CRF_Msk
#define IWDT_SR_ARRF_Pos                                    (1U)
#define IWDT_SR_ARRF_Msk                                    (0x1UL << IWDT_SR_ARRF_Pos)
#define IWDT_SR_ARRF                                        IWDT_SR_ARRF_Msk
#define IWDT_SR_WINRF_Pos                                   (2U)
#define IWDT_SR_WINRF_Msk                                   (0x1UL << IWDT_SR_WINRF_Pos)
#define IWDT_SR_WINRF                                       IWDT_SR_WINRF_Msk
#define IWDT_SR_OV_Pos                                      (3U)
#define IWDT_SR_OV_Msk                                      (0x1UL << IWDT_SR_OV_Pos)
#define IWDT_SR_OV                                          IWDT_SR_OV_Msk
#define IWDT_SR_RUN_Pos                                     (4U)
#define IWDT_SR_RUN_Msk                                     (0x1UL << IWDT_SR_RUN_Pos)
#define IWDT_SR_RUN                                         IWDT_SR_RUN_Msk

// IWDT_WINR
#define IWDT_WINR_WINR_Pos                                  (0U)
#define IWDT_WINR_WINR_Msk                                  (0xFFFUL << IWDT_WINR_WINR_Pos)
#define IWDT_WINR_WINR                                      IWDT_WINR_WINR_Msk



//********************    Bits Define For Peripheral LPUART    ********************//
// LPUART_SBUF
#define LPUART_SBUF_DATA_Pos                                (0U)
#define LPUART_SBUF_DATA_Msk                                (0xFFUL << LPUART_SBUF_DATA_Pos)
#define LPUART_SBUF_DATA                                    LPUART_SBUF_DATA_Msk
#define LPUART_SBUF_DATA8_Pos                               (8U)
#define LPUART_SBUF_DATA8_Msk                               (0x1UL << LPUART_SBUF_DATA8_Pos)
#define LPUART_SBUF_DATA8                                   LPUART_SBUF_DATA8_Msk

// LPUART_SCON
#define LPUART_SCON_RCIE_Pos                                (0U)
#define LPUART_SCON_RCIE_Msk                                (0x1UL << LPUART_SCON_RCIE_Pos)
#define LPUART_SCON_RCIE                                    LPUART_SCON_RCIE_Msk
#define LPUART_SCON_TCIE_Pos                                (1U)
#define LPUART_SCON_TCIE_Msk                                (0x1UL << LPUART_SCON_TCIE_Pos)
#define LPUART_SCON_TCIE                                    LPUART_SCON_TCIE_Msk
#define LPUART_SCON_B8CONT_Pos                              (2U)
#define LPUART_SCON_B8CONT_Msk                              (0x3UL << LPUART_SCON_B8CONT_Pos)
#define LPUART_SCON_B8CONT                                  LPUART_SCON_B8CONT_Msk
#define LPUART_SCON_REN_Pos                                 (4U)
#define LPUART_SCON_REN_Msk                                 (0x1UL << LPUART_SCON_REN_Pos)
#define LPUART_SCON_REN                                     LPUART_SCON_REN_Msk
#define LPUART_SCON_ADRDET_Pos                              (5U)
#define LPUART_SCON_ADRDET_Msk                              (0x1UL << LPUART_SCON_ADRDET_Pos)
#define LPUART_SCON_ADRDET                                  LPUART_SCON_ADRDET_Msk
#define LPUART_SCON_SM_Pos                                  (6U)
#define LPUART_SCON_SM_Msk                                  (0x3UL << LPUART_SCON_SM_Pos)
#define LPUART_SCON_SM                                      LPUART_SCON_SM_Msk
#define LPUART_SCON_TXEIE_Pos                               (8U)
#define LPUART_SCON_TXEIE_Msk                               (0x1UL << LPUART_SCON_TXEIE_Pos)
#define LPUART_SCON_TXEIE                                   LPUART_SCON_TXEIE_Msk
#define LPUART_SCON_OVER_Pos                                (9U)
#define LPUART_SCON_OVER_Msk                                (0x3UL << LPUART_SCON_OVER_Pos)
#define LPUART_SCON_OVER                                    LPUART_SCON_OVER_Msk
#define LPUART_SCON_SCLKSEL_Pos                             (11U)
#define LPUART_SCON_SCLKSEL_Msk                             (0x3UL << LPUART_SCON_SCLKSEL_Pos)
#define LPUART_SCON_SCLKSEL                                 LPUART_SCON_SCLKSEL_Msk
#define LPUART_SCON_PEIE_Pos                                (13U)
#define LPUART_SCON_PEIE_Msk                                (0x1UL << LPUART_SCON_PEIE_Pos)
#define LPUART_SCON_PEIE                                    LPUART_SCON_PEIE_Msk
#define LPUART_SCON_STOPBIT_Pos                             (14U)
#define LPUART_SCON_STOPBIT_Msk                             (0x3UL << LPUART_SCON_STOPBIT_Pos)
#define LPUART_SCON_STOPBIT                                 LPUART_SCON_STOPBIT_Msk
#define LPUART_SCON_RTSEN_Pos                               (18U)
#define LPUART_SCON_RTSEN_Msk                               (0x1UL << LPUART_SCON_RTSEN_Pos)
#define LPUART_SCON_RTSEN                                   LPUART_SCON_RTSEN_Msk
#define LPUART_SCON_CTSEN_Pos                               (19U)
#define LPUART_SCON_CTSEN_Msk                               (0x1UL << LPUART_SCON_CTSEN_Pos)
#define LPUART_SCON_CTSEN                                   LPUART_SCON_CTSEN_Msk
#define LPUART_SCON_CTSIE_Pos                               (20U)
#define LPUART_SCON_CTSIE_Msk                               (0x1UL << LPUART_SCON_CTSIE_Pos)
#define LPUART_SCON_CTSIE                                   LPUART_SCON_CTSIE_Msk
#define LPUART_SCON_FEIE_Pos                                (21U)
#define LPUART_SCON_FEIE_Msk                                (0x1UL << LPUART_SCON_FEIE_Pos)
#define LPUART_SCON_FEIE                                    LPUART_SCON_FEIE_Msk
#define LPUART_SCON_HDSEL_Pos                               (22U)
#define LPUART_SCON_HDSEL_Msk                               (0x1UL << LPUART_SCON_HDSEL_Pos)
#define LPUART_SCON_HDSEL                                   LPUART_SCON_HDSEL_Msk

// LPUART_SADDR
#define LPUART_SADDR_ADDR_Pos                               (0U)
#define LPUART_SADDR_ADDR_Msk                               (0xFFUL << LPUART_SADDR_ADDR_Pos)
#define LPUART_SADDR_ADDR                                   LPUART_SADDR_ADDR_Msk

// LPUART_SADEN
#define LPUART_SADEN_MASK_Pos                               (0U)
#define LPUART_SADEN_MASK_Msk                               (0xFFUL << LPUART_SADEN_MASK_Pos)
#define LPUART_SADEN_MASK                                   LPUART_SADEN_MASK_Msk

// LPUART_ISR
#define LPUART_ISR_RC_Pos                                   (0U)
#define LPUART_ISR_RC_Msk                                   (0x1UL << LPUART_ISR_RC_Pos)
#define LPUART_ISR_RC                                       LPUART_ISR_RC_Msk
#define LPUART_ISR_TC_Pos                                   (1U)
#define LPUART_ISR_TC_Msk                                   (0x1UL << LPUART_ISR_TC_Pos)
#define LPUART_ISR_TC                                       LPUART_ISR_TC_Msk
#define LPUART_ISR_FE_Pos                                   (2U)
#define LPUART_ISR_FE_Msk                                   (0x1UL << LPUART_ISR_FE_Pos)
#define LPUART_ISR_FE                                       LPUART_ISR_FE_Msk
#define LPUART_ISR_TXE_Pos                                  (3U)
#define LPUART_ISR_TXE_Msk                                  (0x1UL << LPUART_ISR_TXE_Pos)
#define LPUART_ISR_TXE                                      LPUART_ISR_TXE_Msk
#define LPUART_ISR_PE_Pos                                   (4U)
#define LPUART_ISR_PE_Msk                                   (0x1UL << LPUART_ISR_PE_Pos)
#define LPUART_ISR_PE                                       LPUART_ISR_PE_Msk
#define LPUART_ISR_CTSIF_Pos                                (5U)
#define LPUART_ISR_CTSIF_Msk                                (0x1UL << LPUART_ISR_CTSIF_Pos)
#define LPUART_ISR_CTSIF                                    LPUART_ISR_CTSIF_Msk
#define LPUART_ISR_CTS_Pos                                  (6U)
#define LPUART_ISR_CTS_Msk                                  (0x1UL << LPUART_ISR_CTS_Pos)
#define LPUART_ISR_CTS                                      LPUART_ISR_CTS_Msk

// LPUART_ICR
#define LPUART_ICR_RCCF_Pos                                 (0U)
#define LPUART_ICR_RCCF_Msk                                 (0x1UL << LPUART_ICR_RCCF_Pos)
#define LPUART_ICR_RCCF                                     LPUART_ICR_RCCF_Msk
#define LPUART_ICR_TCCF_Pos                                 (1U)
#define LPUART_ICR_TCCF_Msk                                 (0x1UL << LPUART_ICR_TCCF_Pos)
#define LPUART_ICR_TCCF                                     LPUART_ICR_TCCF_Msk
#define LPUART_ICR_FECF_Pos                                 (2U)
#define LPUART_ICR_FECF_Msk                                 (0x1UL << LPUART_ICR_FECF_Pos)
#define LPUART_ICR_FECF                                     LPUART_ICR_FECF_Msk
#define LPUART_ICR_PECF_Pos                                 (4U)
#define LPUART_ICR_PECF_Msk                                 (0x1UL << LPUART_ICR_PECF_Pos)
#define LPUART_ICR_PECF                                     LPUART_ICR_PECF_Msk
#define LPUART_ICR_CTSIFCF_Pos                              (5U)
#define LPUART_ICR_CTSIFCF_Msk                              (0x1UL << LPUART_ICR_CTSIFCF_Pos)
#define LPUART_ICR_CTSIFCF                                  LPUART_ICR_CTSIFCF_Msk

// LPUART_SCNT
#define LPUART_SCNT_SCNT_Pos                                (0U)
#define LPUART_SCNT_SCNT_Msk                                (0xFFFFUL << LPUART_SCNT_SCNT_Pos)
#define LPUART_SCNT_SCNT                                    LPUART_SCNT_SCNT_Msk

// LPUART_BSEL
#define LPUART_BSEL_BSEL_Pos                                (0U)
#define LPUART_BSEL_BSEL_Msk                                (0x3UL << LPUART_BSEL_BSEL_Pos)
#define LPUART_BSEL_BSEL                                    LPUART_BSEL_BSEL_Msk

// LPUART_MODU
#define LPUART_MODU_MODU_Pos                                (0U)
#define LPUART_MODU_MODU_Msk                                (0xFFFUL << LPUART_MODU_MODU_Pos)
#define LPUART_MODU_MODU                                    LPUART_MODU_MODU_Msk



//********************    Bits Define For Peripheral LVD    ********************//
// LVD_CR
#define LVD_CR_EN_Pos                                       (0U)
#define LVD_CR_EN_Msk                                       (0x1UL << LVD_CR_EN_Pos)
#define LVD_CR_EN                                           LVD_CR_EN_Msk
#define LVD_CR_ACT_Pos                                      (1U)
#define LVD_CR_ACT_Msk                                      (0x1UL << LVD_CR_ACT_Pos)
#define LVD_CR_ACT                                          LVD_CR_ACT_Msk
#define LVD_CR_SOURCE_Pos                                   (2U)
#define LVD_CR_SOURCE_Msk                                   (0x3UL << LVD_CR_SOURCE_Pos)
#define LVD_CR_SOURCE                                       LVD_CR_SOURCE_Msk
#define LVD_CR_VTDS_Pos                                     (4U)
#define LVD_CR_VTDS_Msk                                     (0xFUL << LVD_CR_VTDS_Pos)
#define LVD_CR_VTDS                                         LVD_CR_VTDS_Msk
#define LVD_CR_DEBOUNCE_TIME_Pos                            (8U)
#define LVD_CR_DEBOUNCE_TIME_Msk                            (0xFUL << LVD_CR_DEBOUNCE_TIME_Pos)
#define LVD_CR_DEBOUNCE_TIME                                LVD_CR_DEBOUNCE_TIME_Msk
#define LVD_CR_FTEN_Pos                                     (12U)
#define LVD_CR_FTEN_Msk                                     (0x1UL << LVD_CR_FTEN_Pos)
#define LVD_CR_FTEN                                         LVD_CR_FTEN_Msk
#define LVD_CR_RTEN_Pos                                     (13U)
#define LVD_CR_RTEN_Msk                                     (0x1UL << LVD_CR_RTEN_Pos)
#define LVD_CR_RTEN                                         LVD_CR_RTEN_Msk
#define LVD_CR_HTEN_Pos                                     (14U)
#define LVD_CR_HTEN_Msk                                     (0x1UL << LVD_CR_HTEN_Pos)
#define LVD_CR_HTEN                                         LVD_CR_HTEN_Msk
#define LVD_CR_IE_Pos                                       (15U)
#define LVD_CR_IE_Msk                                       (0x1UL << LVD_CR_IE_Pos)
#define LVD_CR_IE                                           LVD_CR_IE_Msk
#define LVD_CR_FLT_MODE_Pos                                 (17U)
#define LVD_CR_FLT_MODE_Msk                                 (0x3UL << LVD_CR_FLT_MODE_Pos)
#define LVD_CR_FLT_MODE                                     LVD_CR_FLT_MODE_Msk

// LVD_SR
#define LVD_SR_INTF_Pos                                     (0U)
#define LVD_SR_INTF_Msk                                     (0x1UL << LVD_SR_INTF_Pos)
#define LVD_SR_INTF                                         LVD_SR_INTF_Msk
#define LVD_SR_FLTV_Pos                                     (1U)
#define LVD_SR_FLTV_Msk                                     (0x1UL << LVD_SR_FLTV_Pos)
#define LVD_SR_FLTV                                         LVD_SR_FLTV_Msk



//********************    Bits Define For Peripheral RTC    ********************//
// RTC_CR0
#define RTC_CR0_PRDS_Pos                                    (0U)
#define RTC_CR0_PRDS_Msk                                    (0x7UL << RTC_CR0_PRDS_Pos)
#define RTC_CR0_PRDS                                        RTC_CR0_PRDS_Msk
#define RTC_CR0_AMPM_Pos                                    (3U)
#define RTC_CR0_AMPM_Msk                                    (0x1UL << RTC_CR0_AMPM_Pos)
#define RTC_CR0_AMPM                                        RTC_CR0_AMPM_Msk
#define RTC_CR0_HZ1OE_Pos                                   (5U)
#define RTC_CR0_HZ1OE_Msk                                   (0x1UL << RTC_CR0_HZ1OE_Pos)
#define RTC_CR0_HZ1OE                                       RTC_CR0_HZ1OE_Msk
#define RTC_CR0_HZ1SEL_Pos                                  (6U)
#define RTC_CR0_HZ1SEL_Msk                                  (0x1UL << RTC_CR0_HZ1SEL_Pos)
#define RTC_CR0_HZ1SEL                                      RTC_CR0_HZ1SEL_Msk
#define RTC_CR0_START_Pos                                   (7U)
#define RTC_CR0_START_Msk                                   (0x1UL << RTC_CR0_START_Pos)
#define RTC_CR0_START                                       RTC_CR0_START_Msk
#define RTC_CR0_PRDX_Pos                                    (8U)
#define RTC_CR0_PRDX_Msk                                    (0x3FUL << RTC_CR0_PRDX_Pos)
#define RTC_CR0_PRDX                                        RTC_CR0_PRDX_Msk
#define RTC_CR0_PRDSEL_Pos                                  (14U)
#define RTC_CR0_PRDSEL_Msk                                  (0x1UL << RTC_CR0_PRDSEL_Pos)
#define RTC_CR0_PRDSEL                                      RTC_CR0_PRDSEL_Msk

// RTC_CR1
#define RTC_CR1_WAIT_Pos                                    (0U)
#define RTC_CR1_WAIT_Msk                                    (0x1UL << RTC_CR1_WAIT_Pos)
#define RTC_CR1_WAIT                                        RTC_CR1_WAIT_Msk
#define RTC_CR1_WAITF_Pos                                   (1U)
#define RTC_CR1_WAITF_Msk                                   (0x1UL << RTC_CR1_WAITF_Pos)
#define RTC_CR1_WAITF                                       RTC_CR1_WAITF_Msk
#define RTC_CR1_CKSEL_Pos                                   (8U)
#define RTC_CR1_CKSEL_Msk                                   (0x7UL << RTC_CR1_CKSEL_Pos)
#define RTC_CR1_CKSEL                                       RTC_CR1_CKSEL_Msk

// RTC_SEC
#define RTC_SEC_SECL_Pos                                    (0U)
#define RTC_SEC_SECL_Msk                                    (0xFUL << RTC_SEC_SECL_Pos)
#define RTC_SEC_SECL                                        RTC_SEC_SECL_Msk
#define RTC_SEC_SECH_Pos                                    (4U)
#define RTC_SEC_SECH_Msk                                    (0x7UL << RTC_SEC_SECH_Pos)
#define RTC_SEC_SECH                                        RTC_SEC_SECH_Msk

// RTC_MIN
#define RTC_MIN_MINL_Pos                                    (0U)
#define RTC_MIN_MINL_Msk                                    (0xFUL << RTC_MIN_MINL_Pos)
#define RTC_MIN_MINL                                        RTC_MIN_MINL_Msk
#define RTC_MIN_MINH_Pos                                    (4U)
#define RTC_MIN_MINH_Msk                                    (0x7UL << RTC_MIN_MINH_Pos)
#define RTC_MIN_MINH                                        RTC_MIN_MINH_Msk

// RTC_HOUR
#define RTC_HOUR_HOURL_Pos                                  (0U)
#define RTC_HOUR_HOURL_Msk                                  (0xFUL << RTC_HOUR_HOURL_Pos)
#define RTC_HOUR_HOURL                                      RTC_HOUR_HOURL_Msk
#define RTC_HOUR_HOURH_Pos                                  (4U)
#define RTC_HOUR_HOURH_Msk                                  (0x3UL << RTC_HOUR_HOURH_Pos)
#define RTC_HOUR_HOURH                                      RTC_HOUR_HOURH_Msk

// RTC_WEEK
#define RTC_WEEK_WEEK_Pos                                   (0U)
#define RTC_WEEK_WEEK_Msk                                   (0x7UL << RTC_WEEK_WEEK_Pos)
#define RTC_WEEK_WEEK                                       RTC_WEEK_WEEK_Msk

// RTC_DAY
#define RTC_DAY_DAYL_Pos                                    (0U)
#define RTC_DAY_DAYL_Msk                                    (0xFUL << RTC_DAY_DAYL_Pos)
#define RTC_DAY_DAYL                                        RTC_DAY_DAYL_Msk
#define RTC_DAY_DAYH_Pos                                    (4U)
#define RTC_DAY_DAYH_Msk                                    (0x3UL << RTC_DAY_DAYH_Pos)
#define RTC_DAY_DAYH                                        RTC_DAY_DAYH_Msk

// RTC_MON
#define RTC_MON_MON_Pos                                     (0U)
#define RTC_MON_MON_Msk                                     (0x1FUL << RTC_MON_MON_Pos)
#define RTC_MON_MON                                         RTC_MON_MON_Msk

// RTC_YEAR
#define RTC_YEAR_YEARL_Pos                                  (0U)
#define RTC_YEAR_YEARL_Msk                                  (0xFUL << RTC_YEAR_YEARL_Pos)
#define RTC_YEAR_YEARL                                      RTC_YEAR_YEARL_Msk
#define RTC_YEAR_YEARH_Pos                                  (4U)
#define RTC_YEAR_YEARH_Msk                                  (0xFUL << RTC_YEAR_YEARH_Pos)
#define RTC_YEAR_YEARH                                      RTC_YEAR_YEARH_Msk

// RTC_COMPEN
#define RTC_COMPEN_CR_Pos                                   (0U)
#define RTC_COMPEN_CR_Msk                                   (0x1FFFUL << RTC_COMPEN_CR_Pos)
#define RTC_COMPEN_CR                                       RTC_COMPEN_CR_Msk
#define RTC_COMPEN_CSTEPS_Pos                               (14U)
#define RTC_COMPEN_CSTEPS_Msk                               (0x1UL << RTC_COMPEN_CSTEPS_Pos)
#define RTC_COMPEN_CSTEPS                                   RTC_COMPEN_CSTEPS_Msk
#define RTC_COMPEN_EN_Pos                                   (15U)
#define RTC_COMPEN_EN_Msk                                   (0x1UL << RTC_COMPEN_EN_Pos)
#define RTC_COMPEN_EN                                       RTC_COMPEN_EN_Msk

// RTC_HCOMP
#define RTC_HCOMP_PARA_Pos                                  (0U)
#define RTC_HCOMP_PARA_Msk                                  (0x3FUL << RTC_HCOMP_PARA_Pos)
#define RTC_HCOMP_PARA                                      RTC_HCOMP_PARA_Msk

// RTC_CR2
#define RTC_CR2_WUCKSEL_Pos                                 (0U)
#define RTC_CR2_WUCKSEL_Msk                                 (0x7UL << RTC_CR2_WUCKSEL_Pos)
#define RTC_CR2_WUCKSEL                                     RTC_CR2_WUCKSEL_Msk
#define RTC_CR2_TSEDG_Pos                                   (3U)
#define RTC_CR2_TSEDG_Msk                                   (0x1UL << RTC_CR2_TSEDG_Pos)
#define RTC_CR2_TSEDG                                       RTC_CR2_TSEDG_Msk
#define RTC_CR2_TSE_Pos                                     (6U)
#define RTC_CR2_TSE_Msk                                     (0x1UL << RTC_CR2_TSE_Pos)
#define RTC_CR2_TSE                                         RTC_CR2_TSE_Msk
#define RTC_CR2_WUTE_Pos                                    (7U)
#define RTC_CR2_WUTE_Msk                                    (0x1UL << RTC_CR2_WUTE_Pos)
#define RTC_CR2_WUTE                                        RTC_CR2_WUTE_Msk
#define RTC_CR2_ALMAE_Pos                                   (9U)
#define RTC_CR2_ALMAE_Msk                                   (0x1UL << RTC_CR2_ALMAE_Pos)
#define RTC_CR2_ALMAE                                       RTC_CR2_ALMAE_Msk
#define RTC_CR2_ALMBE_Pos                                   (10U)
#define RTC_CR2_ALMBE_Msk                                   (0x1UL << RTC_CR2_ALMBE_Pos)
#define RTC_CR2_ALMBE                                       RTC_CR2_ALMBE_Msk

// RTC_ALMA
#define RTC_ALMA_SECL_Pos                                   (0U)
#define RTC_ALMA_SECL_Msk                                   (0xFUL << RTC_ALMA_SECL_Pos)
#define RTC_ALMA_SECL                                       RTC_ALMA_SECL_Msk
#define RTC_ALMA_SECH_Pos                                   (4U)
#define RTC_ALMA_SECH_Msk                                   (0x7UL << RTC_ALMA_SECH_Pos)
#define RTC_ALMA_SECH                                       RTC_ALMA_SECH_Msk
#define RTC_ALMA_MSKS_Pos                                   (7U)
#define RTC_ALMA_MSKS_Msk                                   (0x1UL << RTC_ALMA_MSKS_Pos)
#define RTC_ALMA_MSKS                                       RTC_ALMA_MSKS_Msk
#define RTC_ALMA_MINL_Pos                                   (8U)
#define RTC_ALMA_MINL_Msk                                   (0xFUL << RTC_ALMA_MINL_Pos)
#define RTC_ALMA_MINL                                       RTC_ALMA_MINL_Msk
#define RTC_ALMA_MINH_Pos                                   (12U)
#define RTC_ALMA_MINH_Msk                                   (0x7UL << RTC_ALMA_MINH_Pos)
#define RTC_ALMA_MINH                                       RTC_ALMA_MINH_Msk
#define RTC_ALMA_MSKM_Pos                                   (15U)
#define RTC_ALMA_MSKM_Msk                                   (0x1UL << RTC_ALMA_MSKM_Pos)
#define RTC_ALMA_MSKM                                       RTC_ALMA_MSKM_Msk
#define RTC_ALMA_HOURL_Pos                                  (16U)
#define RTC_ALMA_HOURL_Msk                                  (0xFUL << RTC_ALMA_HOURL_Pos)
#define RTC_ALMA_HOURL                                      RTC_ALMA_HOURL_Msk
#define RTC_ALMA_HOURH_Pos                                  (20U)
#define RTC_ALMA_HOURH_Msk                                  (0x3UL << RTC_ALMA_HOURH_Pos)
#define RTC_ALMA_HOURH                                      RTC_ALMA_HOURH_Msk
#define RTC_ALMA_MSKH_Pos                                   (23U)
#define RTC_ALMA_MSKH_Msk                                   (0x1UL << RTC_ALMA_MSKH_Pos)
#define RTC_ALMA_MSKH                                       RTC_ALMA_MSKH_Msk
#define RTC_ALMA_WEEK_Pos                                   (24U)
#define RTC_ALMA_WEEK_Msk                                   (0x7FUL << RTC_ALMA_WEEK_Pos)
#define RTC_ALMA_WEEK                                       RTC_ALMA_WEEK_Msk

// RTC_ALMB
#define RTC_ALMB_SECL_Pos                                   (0U)
#define RTC_ALMB_SECL_Msk                                   (0xFUL << RTC_ALMB_SECL_Pos)
#define RTC_ALMB_SECL                                       RTC_ALMB_SECL_Msk
#define RTC_ALMB_SECH_Pos                                   (4U)
#define RTC_ALMB_SECH_Msk                                   (0x7UL << RTC_ALMB_SECH_Pos)
#define RTC_ALMB_SECH                                       RTC_ALMB_SECH_Msk
#define RTC_ALMB_MSKS_Pos                                   (7U)
#define RTC_ALMB_MSKS_Msk                                   (0x1UL << RTC_ALMB_MSKS_Pos)
#define RTC_ALMB_MSKS                                       RTC_ALMB_MSKS_Msk
#define RTC_ALMB_MINL_Pos                                   (8U)
#define RTC_ALMB_MINL_Msk                                   (0xFUL << RTC_ALMB_MINL_Pos)
#define RTC_ALMB_MINL                                       RTC_ALMB_MINL_Msk
#define RTC_ALMB_MINH_Pos                                   (12U)
#define RTC_ALMB_MINH_Msk                                   (0x7UL << RTC_ALMB_MINH_Pos)
#define RTC_ALMB_MINH                                       RTC_ALMB_MINH_Msk
#define RTC_ALMB_MSKM_Pos                                   (15U)
#define RTC_ALMB_MSKM_Msk                                   (0x1UL << RTC_ALMB_MSKM_Pos)
#define RTC_ALMB_MSKM                                       RTC_ALMB_MSKM_Msk
#define RTC_ALMB_HOURL_Pos                                  (16U)
#define RTC_ALMB_HOURL_Msk                                  (0xFUL << RTC_ALMB_HOURL_Pos)
#define RTC_ALMB_HOURL                                      RTC_ALMB_HOURL_Msk
#define RTC_ALMB_HOURH_Pos                                  (20U)
#define RTC_ALMB_HOURH_Msk                                  (0x3UL << RTC_ALMB_HOURH_Pos)
#define RTC_ALMB_HOURH                                      RTC_ALMB_HOURH_Msk
#define RTC_ALMB_MSKH_Pos                                   (23U)
#define RTC_ALMB_MSKH_Msk                                   (0x1UL << RTC_ALMB_MSKH_Pos)
#define RTC_ALMB_MSKH                                       RTC_ALMB_MSKH_Msk
#define RTC_ALMB_WEEK_Pos                                   (24U)
#define RTC_ALMB_WEEK_Msk                                   (0x7FUL << RTC_ALMB_WEEK_Pos)
#define RTC_ALMB_WEEK                                       RTC_ALMB_WEEK_Msk

// RTC_TSTR
#define RTC_TSTR_SECL_Pos                                   (0U)
#define RTC_TSTR_SECL_Msk                                   (0xFUL << RTC_TSTR_SECL_Pos)
#define RTC_TSTR_SECL                                       RTC_TSTR_SECL_Msk
#define RTC_TSTR_SECH_Pos                                   (4U)
#define RTC_TSTR_SECH_Msk                                   (0x7UL << RTC_TSTR_SECH_Pos)
#define RTC_TSTR_SECH                                       RTC_TSTR_SECH_Msk
#define RTC_TSTR_MINL_Pos                                   (8U)
#define RTC_TSTR_MINL_Msk                                   (0xFUL << RTC_TSTR_MINL_Pos)
#define RTC_TSTR_MINL                                       RTC_TSTR_MINL_Msk
#define RTC_TSTR_MINH_Pos                                   (12U)
#define RTC_TSTR_MINH_Msk                                   (0x7UL << RTC_TSTR_MINH_Pos)
#define RTC_TSTR_MINH                                       RTC_TSTR_MINH_Msk
#define RTC_TSTR_HOURL_Pos                                  (16U)
#define RTC_TSTR_HOURL_Msk                                  (0xFUL << RTC_TSTR_HOURL_Pos)
#define RTC_TSTR_HOURL                                      RTC_TSTR_HOURL_Msk
#define RTC_TSTR_HOURH_Pos                                  (20U)
#define RTC_TSTR_HOURH_Msk                                  (0x3UL << RTC_TSTR_HOURH_Pos)
#define RTC_TSTR_HOURH                                      RTC_TSTR_HOURH_Msk

// RTC_TSDR
#define RTC_TSDR_DAYL_Pos                                   (0U)
#define RTC_TSDR_DAYL_Msk                                   (0xFUL << RTC_TSDR_DAYL_Pos)
#define RTC_TSDR_DAYL                                       RTC_TSDR_DAYL_Msk
#define RTC_TSDR_DAYH_Pos                                   (4U)
#define RTC_TSDR_DAYH_Msk                                   (0x3UL << RTC_TSDR_DAYH_Pos)
#define RTC_TSDR_DAYH                                       RTC_TSDR_DAYH_Msk
#define RTC_TSDR_MON_Pos                                    (8U)
#define RTC_TSDR_MON_Msk                                    (0x1FUL << RTC_TSDR_MON_Pos)
#define RTC_TSDR_MON                                        RTC_TSDR_MON_Msk
#define RTC_TSDR_WEEK_Pos                                   (13U)
#define RTC_TSDR_WEEK_Msk                                   (0x7UL << RTC_TSDR_WEEK_Pos)
#define RTC_TSDR_WEEK                                       RTC_TSDR_WEEK_Msk

// RTC_WUTR
#define RTC_WUTR_ARR_Pos                                    (0U)
#define RTC_WUTR_ARR_Msk                                    (0xFFFFUL << RTC_WUTR_ARR_Pos)
#define RTC_WUTR_ARR                                        RTC_WUTR_ARR_Msk

// RTC_IER
#define RTC_IER_ALMA_Pos                                    (0U)
#define RTC_IER_ALMA_Msk                                    (0x1UL << RTC_IER_ALMA_Pos)
#define RTC_IER_ALMA                                        RTC_IER_ALMA_Msk
#define RTC_IER_ALMB_Pos                                    (1U)
#define RTC_IER_ALMB_Msk                                    (0x1UL << RTC_IER_ALMB_Pos)
#define RTC_IER_ALMB                                        RTC_IER_ALMB_Msk
#define RTC_IER_WU_Pos                                      (2U)
#define RTC_IER_WU_Msk                                      (0x1UL << RTC_IER_WU_Pos)
#define RTC_IER_WU                                          RTC_IER_WU_Msk
#define RTC_IER_TS_Pos                                      (3U)
#define RTC_IER_TS_Msk                                      (0x1UL << RTC_IER_TS_Pos)
#define RTC_IER_TS                                          RTC_IER_TS_Msk
#define RTC_IER_PRD_Pos                                     (6U)
#define RTC_IER_PRD_Msk                                     (0x1UL << RTC_IER_PRD_Pos)
#define RTC_IER_PRD                                         RTC_IER_PRD_Msk

// RTC_IFR
#define RTC_IFR_ALMA_Pos                                    (0U)
#define RTC_IFR_ALMA_Msk                                    (0x1UL << RTC_IFR_ALMA_Pos)
#define RTC_IFR_ALMA                                        RTC_IFR_ALMA_Msk
#define RTC_IFR_ALMB_Pos                                    (1U)
#define RTC_IFR_ALMB_Msk                                    (0x1UL << RTC_IFR_ALMB_Pos)
#define RTC_IFR_ALMB                                        RTC_IFR_ALMB_Msk
#define RTC_IFR_WU_Pos                                      (2U)
#define RTC_IFR_WU_Msk                                      (0x1UL << RTC_IFR_WU_Pos)
#define RTC_IFR_WU                                          RTC_IFR_WU_Msk
#define RTC_IFR_TS_Pos                                      (3U)
#define RTC_IFR_TS_Msk                                      (0x1UL << RTC_IFR_TS_Pos)
#define RTC_IFR_TS                                          RTC_IFR_TS_Msk
#define RTC_IFR_TSOV_Pos                                    (4U)
#define RTC_IFR_TSOV_Msk                                    (0x1UL << RTC_IFR_TSOV_Pos)
#define RTC_IFR_TSOV                                        RTC_IFR_TSOV_Msk
#define RTC_IFR_PRD_Pos                                     (6U)
#define RTC_IFR_PRD_Msk                                     (0x1UL << RTC_IFR_PRD_Pos)
#define RTC_IFR_PRD                                         RTC_IFR_PRD_Msk

// RTC_ICR
#define RTC_ICR_ALMA_Pos                                    (0U)
#define RTC_ICR_ALMA_Msk                                    (0x1UL << RTC_ICR_ALMA_Pos)
#define RTC_ICR_ALMA                                        RTC_ICR_ALMA_Msk
#define RTC_ICR_ALMB_Pos                                    (1U)
#define RTC_ICR_ALMB_Msk                                    (0x1UL << RTC_ICR_ALMB_Pos)
#define RTC_ICR_ALMB                                        RTC_ICR_ALMB_Msk
#define RTC_ICR_WU_Pos                                      (2U)
#define RTC_ICR_WU_Msk                                      (0x1UL << RTC_ICR_WU_Pos)
#define RTC_ICR_WU                                          RTC_ICR_WU_Msk
#define RTC_ICR_TS_Pos                                      (3U)
#define RTC_ICR_TS_Msk                                      (0x1UL << RTC_ICR_TS_Pos)
#define RTC_ICR_TS                                          RTC_ICR_TS_Msk
#define RTC_ICR_TSOV_Pos                                    (4U)
#define RTC_ICR_TSOV_Msk                                    (0x1UL << RTC_ICR_TSOV_Pos)
#define RTC_ICR_TSOV                                        RTC_ICR_TSOV_Msk
#define RTC_ICR_PRD_Pos                                     (6U)
#define RTC_ICR_PRD_Msk                                     (0x1UL << RTC_ICR_PRD_Pos)
#define RTC_ICR_PRD                                         RTC_ICR_PRD_Msk

// RTC_WPR
#define RTC_WPR_WPR_Pos                                     (0U)
#define RTC_WPR_WPR_Msk                                     (0xFFUL << RTC_WPR_WPR_Pos)
#define RTC_WPR_WPR                                         RTC_WPR_WPR_Msk



//********************    Bits Define For Peripheral SPI    ********************//
// SPI_CR0
#define SPI_CR0_EN_Pos                                      (0U)
#define SPI_CR0_EN_Msk                                      (0x1UL << SPI_CR0_EN_Pos)
#define SPI_CR0_EN                                          SPI_CR0_EN_Msk
#define SPI_CR0_BRR_Pos                                     (1U)
#define SPI_CR0_BRR_Msk                                     (0x7UL << SPI_CR0_BRR_Pos)
#define SPI_CR0_BRR                                         SPI_CR0_BRR_Msk
#define SPI_CR0_CPHA_Pos                                    (4U)
#define SPI_CR0_CPHA_Msk                                    (0x1UL << SPI_CR0_CPHA_Pos)
#define SPI_CR0_CPHA                                        SPI_CR0_CPHA_Msk
#define SPI_CR0_CPOL_Pos                                    (5U)
#define SPI_CR0_CPOL_Msk                                    (0x1UL << SPI_CR0_CPOL_Pos)
#define SPI_CR0_CPOL                                        SPI_CR0_CPOL_Msk
#define SPI_CR0_MSTR_Pos                                    (6U)
#define SPI_CR0_MSTR_Msk                                    (0x1UL << SPI_CR0_MSTR_Pos)
#define SPI_CR0_MSTR                                        SPI_CR0_MSTR_Msk
#define SPI_CR0_LSBF_Pos                                    (7U)
#define SPI_CR0_LSBF_Msk                                    (0x1UL << SPI_CR0_LSBF_Pos)
#define SPI_CR0_LSBF                                        SPI_CR0_LSBF_Msk
#define SPI_CR0_WIDTH_Pos                                   (8U)
#define SPI_CR0_WIDTH_Msk                                   (0xFUL << SPI_CR0_WIDTH_Pos)
#define SPI_CR0_WIDTH                                       SPI_CR0_WIDTH_Msk
#define SPI_CR0_SSM_Pos                                     (12U)
#define SPI_CR0_SSM_Msk                                     (0x1UL << SPI_CR0_SSM_Pos)
#define SPI_CR0_SSM                                         SPI_CR0_SSM_Msk
#define SPI_CR0_CM_Pos                                      (13U)
#define SPI_CR0_CM_Msk                                      (0x3UL << SPI_CR0_CM_Pos)
#define SPI_CR0_CM                                          SPI_CR0_CM_Msk
#define SPI_CR0_SMP_Pos                                     (15U)
#define SPI_CR0_SMP_Msk                                     (0x1UL << SPI_CR0_SMP_Pos)
#define SPI_CR0_SMP                                         SPI_CR0_SMP_Msk

// SPI_CR1
#define SPI_CR1_TXEIE_Pos                                   (0U)
#define SPI_CR1_TXEIE_Msk                                   (0x1UL << SPI_CR1_TXEIE_Pos)
#define SPI_CR1_TXEIE                                       SPI_CR1_TXEIE_Msk
#define SPI_CR1_RXNEIE_Pos                                  (1U)
#define SPI_CR1_RXNEIE_Msk                                  (0x1UL << SPI_CR1_RXNEIE_Pos)
#define SPI_CR1_RXNEIE                                      SPI_CR1_RXNEIE_Msk
#define SPI_CR1_SSFIE_Pos                                   (2U)
#define SPI_CR1_SSFIE_Msk                                   (0x1UL << SPI_CR1_SSFIE_Pos)
#define SPI_CR1_SSFIE                                       SPI_CR1_SSFIE_Msk
#define SPI_CR1_SSRIE_Pos                                   (3U)
#define SPI_CR1_SSRIE_Msk                                   (0x1UL << SPI_CR1_SSRIE_Pos)
#define SPI_CR1_SSRIE                                       SPI_CR1_SSRIE_Msk
#define SPI_CR1_UDFIE_Pos                                   (4U)
#define SPI_CR1_UDFIE_Msk                                   (0x1UL << SPI_CR1_UDFIE_Pos)
#define SPI_CR1_UDFIE                                       SPI_CR1_UDFIE_Msk
#define SPI_CR1_OVFIE_Pos                                   (5U)
#define SPI_CR1_OVFIE_Msk                                   (0x1UL << SPI_CR1_OVFIE_Pos)
#define SPI_CR1_OVFIE                                       SPI_CR1_OVFIE_Msk
#define SPI_CR1_SSERRIE_Pos                                 (6U)
#define SPI_CR1_SSERRIE_Msk                                 (0x1UL << SPI_CR1_SSERRIE_Pos)
#define SPI_CR1_SSERRIE                                     SPI_CR1_SSERRIE_Msk
#define SPI_CR1_MODFIE_Pos                                  (7U)
#define SPI_CR1_MODFIE_Msk                                  (0x1UL << SPI_CR1_MODFIE_Pos)
#define SPI_CR1_MODFIE                                      SPI_CR1_MODFIE_Msk

// SPI_HDOE
#define SPI_HDOE_HDOE_Pos                                   (0U)
#define SPI_HDOE_HDOE_Msk                                   (0x1UL << SPI_HDOE_HDOE_Pos)
#define SPI_HDOE_HDOE                                       SPI_HDOE_HDOE_Msk

// SPI_SSI
#define SPI_SSI_SSI_Pos                                     (0U)
#define SPI_SSI_SSI_Msk                                     (0x1UL << SPI_SSI_SSI_Pos)
#define SPI_SSI_SSI                                         SPI_SSI_SSI_Msk

// SPI_SR
#define SPI_SR_TXE_Pos                                      (0U)
#define SPI_SR_TXE_Msk                                      (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE                                          SPI_SR_TXE_Msk
#define SPI_SR_RXNE_Pos                                     (1U)
#define SPI_SR_RXNE_Msk                                     (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE                                         SPI_SR_RXNE_Msk
#define SPI_SR_SSF_Pos                                      (2U)
#define SPI_SR_SSF_Msk                                      (0x1UL << SPI_SR_SSF_Pos)
#define SPI_SR_SSF                                          SPI_SR_SSF_Msk
#define SPI_SR_SSR_Pos                                      (3U)
#define SPI_SR_SSR_Msk                                      (0x1UL << SPI_SR_SSR_Pos)
#define SPI_SR_SSR                                          SPI_SR_SSR_Msk
#define SPI_SR_UDF_Pos                                      (4U)
#define SPI_SR_UDF_Msk                                      (0x1UL << SPI_SR_UDF_Pos)
#define SPI_SR_UDF                                          SPI_SR_UDF_Msk
#define SPI_SR_OVF_Pos                                      (5U)
#define SPI_SR_OVF_Msk                                      (0x1UL << SPI_SR_OVF_Pos)
#define SPI_SR_OVF                                          SPI_SR_OVF_Msk
#define SPI_SR_SSERR_Pos                                    (6U)
#define SPI_SR_SSERR_Msk                                    (0x1UL << SPI_SR_SSERR_Pos)
#define SPI_SR_SSERR                                        SPI_SR_SSERR_Msk
#define SPI_SR_MODF_Pos                                     (7U)
#define SPI_SR_MODF_Msk                                     (0x1UL << SPI_SR_MODF_Pos)
#define SPI_SR_MODF                                         SPI_SR_MODF_Msk
#define SPI_SR_BUSY_Pos                                     (8U)
#define SPI_SR_BUSY_Msk                                     (0x1UL << SPI_SR_BUSY_Pos)
#define SPI_SR_BUSY                                         SPI_SR_BUSY_Msk
#define SPI_SR_SSLVL_Pos                                    (9U)
#define SPI_SR_SSLVL_Msk                                    (0x1UL << SPI_SR_SSLVL_Pos)
#define SPI_SR_SSLVL                                        SPI_SR_SSLVL_Msk

// SPI_ICR
#define SPI_ICR_TXE_Pos                                     (0U)
#define SPI_ICR_TXE_Msk                                     (0x1UL << SPI_ICR_TXE_Pos)
#define SPI_ICR_TXE                                         SPI_ICR_TXE_Msk
#define SPI_ICR_RXNE_Pos                                    (1U)
#define SPI_ICR_RXNE_Msk                                    (0x1UL << SPI_ICR_RXNE_Pos)
#define SPI_ICR_RXNE                                        SPI_ICR_RXNE_Msk
#define SPI_ICR_SSF_Pos                                     (2U)
#define SPI_ICR_SSF_Msk                                     (0x1UL << SPI_ICR_SSF_Pos)
#define SPI_ICR_SSF                                         SPI_ICR_SSF_Msk
#define SPI_ICR_SSR_Pos                                     (3U)
#define SPI_ICR_SSR_Msk                                     (0x1UL << SPI_ICR_SSR_Pos)
#define SPI_ICR_SSR                                         SPI_ICR_SSR_Msk
#define SPI_ICR_UDF_Pos                                     (4U)
#define SPI_ICR_UDF_Msk                                     (0x1UL << SPI_ICR_UDF_Pos)
#define SPI_ICR_UDF                                         SPI_ICR_UDF_Msk
#define SPI_ICR_OVF_Pos                                     (5U)
#define SPI_ICR_OVF_Msk                                     (0x1UL << SPI_ICR_OVF_Pos)
#define SPI_ICR_OVF                                         SPI_ICR_OVF_Msk
#define SPI_ICR_SSERR_Pos                                   (6U)
#define SPI_ICR_SSERR_Msk                                   (0x1UL << SPI_ICR_SSERR_Pos)
#define SPI_ICR_SSERR                                       SPI_ICR_SSERR_Msk
#define SPI_ICR_MODF_Pos                                    (7U)
#define SPI_ICR_MODF_Msk                                    (0x1UL << SPI_ICR_MODF_Pos)
#define SPI_ICR_MODF                                        SPI_ICR_MODF_Msk

// SPI_DR
#define SPI_DR_DR_Pos                                       (0U)
#define SPI_DR_DR_Msk                                       (0xFFFFUL << SPI_DR_DR_Pos)
#define SPI_DR_DR                                           SPI_DR_DR_Msk



//********************    Bits Define For Peripheral SYSCTRL    ********************//
// SYSCTRL_SYSCTRL0
#define SYSCTRL_SYSCTRL0_RC48M_EN_Pos                       (0U)
#define SYSCTRL_SYSCTRL0_RC48M_EN_Msk                       (0x1UL << SYSCTRL_SYSCTRL0_RC48M_EN_Pos)
#define SYSCTRL_SYSCTRL0_RC48M_EN                           SYSCTRL_SYSCTRL0_RC48M_EN_Msk
#define SYSCTRL_SYSCTRL0_RCL_EN_Pos                         (2U)
#define SYSCTRL_SYSCTRL0_RCL_EN_Msk                         (0x1UL << SYSCTRL_SYSCTRL0_RCL_EN_Pos)
#define SYSCTRL_SYSCTRL0_RCL_EN                             SYSCTRL_SYSCTRL0_RCL_EN_Msk
#define SYSCTRL_SYSCTRL0_XTL_EN_Pos                         (3U)
#define SYSCTRL_SYSCTRL0_XTL_EN_Msk                         (0x1UL << SYSCTRL_SYSCTRL0_XTL_EN_Pos)
#define SYSCTRL_SYSCTRL0_XTL_EN                             SYSCTRL_SYSCTRL0_XTL_EN_Msk
#define SYSCTRL_SYSCTRL0_CLKSW_Pos                          (5U)
#define SYSCTRL_SYSCTRL0_CLKSW_Msk                          (0x7UL << SYSCTRL_SYSCTRL0_CLKSW_Pos)
#define SYSCTRL_SYSCTRL0_CLKSW                              SYSCTRL_SYSCTRL0_CLKSW_Msk
#define SYSCTRL_SYSCTRL0_HCLK_PRS_Pos                       (8U)
#define SYSCTRL_SYSCTRL0_HCLK_PRS_Msk                       (0x7UL << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos)
#define SYSCTRL_SYSCTRL0_HCLK_PRS                           SYSCTRL_SYSCTRL0_HCLK_PRS_Msk
#define SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Pos                 (15U)
#define SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Msk                 (0x1UL << SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Pos)
#define SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M                     SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Msk

// SYSCTRL_SYSCTRL1
#define SYSCTRL_SYSCTRL1_RESET_USE_IO_Pos                   (0U)
#define SYSCTRL_SYSCTRL1_RESET_USE_IO_Msk                   (0x1UL << SYSCTRL_SYSCTRL1_RESET_USE_IO_Pos)
#define SYSCTRL_SYSCTRL1_RESET_USE_IO                       SYSCTRL_SYSCTRL1_RESET_USE_IO_Msk
#define SYSCTRL_SYSCTRL1_EXTH_EN_Pos                        (1U)
#define SYSCTRL_SYSCTRL1_EXTH_EN_Msk                        (0x1UL << SYSCTRL_SYSCTRL1_EXTH_EN_Pos)
#define SYSCTRL_SYSCTRL1_EXTH_EN                            SYSCTRL_SYSCTRL1_EXTH_EN_Msk
#define SYSCTRL_SYSCTRL1_EXTL_EN_Pos                        (2U)
#define SYSCTRL_SYSCTRL1_EXTL_EN_Msk                        (0x1UL << SYSCTRL_SYSCTRL1_EXTL_EN_Pos)
#define SYSCTRL_SYSCTRL1_EXTL_EN                            SYSCTRL_SYSCTRL1_EXTL_EN_Msk
#define SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Pos                  (3U)
#define SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Msk                  (0x1UL << SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Pos)
#define SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON                      SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Msk
#define SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN_Pos                 (4U)
#define SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN_Msk                 (0x1UL << SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN_Pos)
#define SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN                     SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN_Msk
#define SYSCTRL_SYSCTRL1_LOCKUP_EN_Pos                      (6U)
#define SYSCTRL_SYSCTRL1_LOCKUP_EN_Msk                      (0x1UL << SYSCTRL_SYSCTRL1_LOCKUP_EN_Pos)
#define SYSCTRL_SYSCTRL1_LOCKUP_EN                          SYSCTRL_SYSCTRL1_LOCKUP_EN_Msk
#define SYSCTRL_SYSCTRL1_SPI_PCTRL_Pos                      (7U)
#define SYSCTRL_SYSCTRL1_SPI_PCTRL_Msk                      (0x1UL << SYSCTRL_SYSCTRL1_SPI_PCTRL_Pos)
#define SYSCTRL_SYSCTRL1_SPI_PCTRL                          SYSCTRL_SYSCTRL1_SPI_PCTRL_Msk
#define SYSCTRL_SYSCTRL1_SWD_USE_IO_Pos                     (8U)
#define SYSCTRL_SYSCTRL1_SWD_USE_IO_Msk                     (0x1UL << SYSCTRL_SYSCTRL1_SWD_USE_IO_Pos)
#define SYSCTRL_SYSCTRL1_SWD_USE_IO                         SYSCTRL_SYSCTRL1_SWD_USE_IO_Msk
#define SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL_Pos                (9U)
#define SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL_Msk                (0x1UL << SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL_Pos)
#define SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL                    SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL_Msk
#define SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL_Pos                (10U)
#define SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL_Msk                (0x1UL << SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL_Pos)
#define SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL                    SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL_Msk

// SYSCTRL_SYSCTRL2
#define SYSCTRL_SYSCTRL2_SYSCTRL2_Pos                       (0U)
#define SYSCTRL_SYSCTRL2_SYSCTRL2_Msk                       (0xFFFFUL << SYSCTRL_SYSCTRL2_SYSCTRL2_Pos)
#define SYSCTRL_SYSCTRL2_SYSCTRL2                           SYSCTRL_SYSCTRL2_SYSCTRL2_Msk

// SYSCTRL_RC48M_CR
#define SYSCTRL_RC48M_CR_TRIMF_Pos                          (2U)
#define SYSCTRL_RC48M_CR_TRIMF_Msk                          (0x3FUL << SYSCTRL_RC48M_CR_TRIMF_Pos)
#define SYSCTRL_RC48M_CR_TRIMF                              SYSCTRL_RC48M_CR_TRIMF_Msk
#define SYSCTRL_RC48M_CR_TRIMC_Pos                          (8U)
#define SYSCTRL_RC48M_CR_TRIMC_Msk                          (0xFFUL << SYSCTRL_RC48M_CR_TRIMC_Pos)
#define SYSCTRL_RC48M_CR_TRIMC                              SYSCTRL_RC48M_CR_TRIMC_Msk
#define SYSCTRL_RC48M_CR_FSEL_Pos                           (16U)
#define SYSCTRL_RC48M_CR_FSEL_Msk                           (0x3UL << SYSCTRL_RC48M_CR_FSEL_Pos)
#define SYSCTRL_RC48M_CR_FSEL                               SYSCTRL_RC48M_CR_FSEL_Msk
#define SYSCTRL_RC48M_CR_STABLE_Pos                         (31U)
#define SYSCTRL_RC48M_CR_STABLE_Msk                         (0x1UL << SYSCTRL_RC48M_CR_STABLE_Pos)
#define SYSCTRL_RC48M_CR_STABLE                             SYSCTRL_RC48M_CR_STABLE_Msk

// SYSCTRL_RCL_CR
#define SYSCTRL_RCL_CR_TRIM_Pos                             (0U)
#define SYSCTRL_RCL_CR_TRIM_Msk                             (0x3FFUL << SYSCTRL_RCL_CR_TRIM_Pos)
#define SYSCTRL_RCL_CR_TRIM                                 SYSCTRL_RCL_CR_TRIM_Msk
#define SYSCTRL_RCL_CR_STABLE_Pos                           (12U)
#define SYSCTRL_RCL_CR_STABLE_Msk                           (0x1UL << SYSCTRL_RCL_CR_STABLE_Pos)
#define SYSCTRL_RCL_CR_STABLE                               SYSCTRL_RCL_CR_STABLE_Msk
#define SYSCTRL_RCL_CR_MSEL_Pos                             (16U)
#define SYSCTRL_RCL_CR_MSEL_Msk                             (0x1UL << SYSCTRL_RCL_CR_MSEL_Pos)
#define SYSCTRL_RCL_CR_MSEL                                 SYSCTRL_RCL_CR_MSEL_Msk

// SYSCTRL_XTL_CR
#define SYSCTRL_XTL_CR_DRIVER_Pos                           (0U)
#define SYSCTRL_XTL_CR_DRIVER_Msk                           (0x3UL << SYSCTRL_XTL_CR_DRIVER_Pos)
#define SYSCTRL_XTL_CR_DRIVER                               SYSCTRL_XTL_CR_DRIVER_Msk
#define SYSCTRL_XTL_CR_AMP_SEL_Pos                          (2U)
#define SYSCTRL_XTL_CR_AMP_SEL_Msk                          (0x3UL << SYSCTRL_XTL_CR_AMP_SEL_Pos)
#define SYSCTRL_XTL_CR_AMP_SEL                              SYSCTRL_XTL_CR_AMP_SEL_Msk
#define SYSCTRL_XTL_CR_STARTUP_Pos                          (4U)
#define SYSCTRL_XTL_CR_STARTUP_Msk                          (0x3UL << SYSCTRL_XTL_CR_STARTUP_Pos)
#define SYSCTRL_XTL_CR_STARTUP                              SYSCTRL_XTL_CR_STARTUP_Msk
#define SYSCTRL_XTL_CR_STABLE_Pos                           (6U)
#define SYSCTRL_XTL_CR_STABLE_Msk                           (0x1UL << SYSCTRL_XTL_CR_STABLE_Pos)
#define SYSCTRL_XTL_CR_STABLE                               SYSCTRL_XTL_CR_STABLE_Msk
#define SYSCTRL_XTL_CR_DETIE_Pos                            (7U)
#define SYSCTRL_XTL_CR_DETIE_Msk                            (0x1UL << SYSCTRL_XTL_CR_DETIE_Pos)
#define SYSCTRL_XTL_CR_DETIE                                SYSCTRL_XTL_CR_DETIE_Msk
#define SYSCTRL_XTL_CR_DETTIME_Pos                          (8U)
#define SYSCTRL_XTL_CR_DETTIME_Msk                          (0x1UL << SYSCTRL_XTL_CR_DETTIME_Pos)
#define SYSCTRL_XTL_CR_DETTIME                              SYSCTRL_XTL_CR_DETTIME_Msk
#define SYSCTRL_XTL_CR_DETEN_Pos                            (9U)
#define SYSCTRL_XTL_CR_DETEN_Msk                            (0x1UL << SYSCTRL_XTL_CR_DETEN_Pos)
#define SYSCTRL_XTL_CR_DETEN                                SYSCTRL_XTL_CR_DETEN_Msk
#define SYSCTRL_XTL_CR_FAULT_STATE_Pos                      (10U)
#define SYSCTRL_XTL_CR_FAULT_STATE_Msk                      (0x1UL << SYSCTRL_XTL_CR_FAULT_STATE_Pos)
#define SYSCTRL_XTL_CR_FAULT_STATE                          SYSCTRL_XTL_CR_FAULT_STATE_Msk

// SYSCTRL_RESET_FLAG
#define SYSCTRL_RESET_FLAG_POR5V_Pos                        (0U)
#define SYSCTRL_RESET_FLAG_POR5V_Msk                        (0x1UL << SYSCTRL_RESET_FLAG_POR5V_Pos)
#define SYSCTRL_RESET_FLAG_POR5V                            SYSCTRL_RESET_FLAG_POR5V_Msk
#define SYSCTRL_RESET_FLAG_POR15V_Pos                       (1U)
#define SYSCTRL_RESET_FLAG_POR15V_Msk                       (0x1UL << SYSCTRL_RESET_FLAG_POR15V_Pos)
#define SYSCTRL_RESET_FLAG_POR15V                           SYSCTRL_RESET_FLAG_POR15V_Msk
#define SYSCTRL_RESET_FLAG_LVD_FLAG_Pos                     (2U)
#define SYSCTRL_RESET_FLAG_LVD_FLAG_Msk                     (0x1UL << SYSCTRL_RESET_FLAG_LVD_FLAG_Pos)
#define SYSCTRL_RESET_FLAG_LVD_FLAG                         SYSCTRL_RESET_FLAG_LVD_FLAG_Msk
#define SYSCTRL_RESET_FLAG_IWDT_FLAG_Pos                    (3U)
#define SYSCTRL_RESET_FLAG_IWDT_FLAG_Msk                    (0x1UL << SYSCTRL_RESET_FLAG_IWDT_FLAG_Pos)
#define SYSCTRL_RESET_FLAG_IWDT_FLAG                        SYSCTRL_RESET_FLAG_IWDT_FLAG_Msk
#define SYSCTRL_RESET_FLAG_LOCKUP_Pos                       (5U)
#define SYSCTRL_RESET_FLAG_LOCKUP_Msk                       (0x1UL << SYSCTRL_RESET_FLAG_LOCKUP_Pos)
#define SYSCTRL_RESET_FLAG_LOCKUP                           SYSCTRL_RESET_FLAG_LOCKUP_Msk
#define SYSCTRL_RESET_FLAG_SYSREQ_Pos                       (6U)
#define SYSCTRL_RESET_FLAG_SYSREQ_Msk                       (0x1UL << SYSCTRL_RESET_FLAG_SYSREQ_Pos)
#define SYSCTRL_RESET_FLAG_SYSREQ                           SYSCTRL_RESET_FLAG_SYSREQ_Msk
#define SYSCTRL_RESET_FLAG_RSTB_Pos                         (7U)
#define SYSCTRL_RESET_FLAG_RSTB_Msk                         (0x1UL << SYSCTRL_RESET_FLAG_RSTB_Pos)
#define SYSCTRL_RESET_FLAG_RSTB                             SYSCTRL_RESET_FLAG_RSTB_Msk

// SYSCTRL_PERI_CLKEN0
#define SYSCTRL_PERI_CLKEN0_LPUART0_EN_Pos                  (2U)
#define SYSCTRL_PERI_CLKEN0_LPUART0_EN_Msk                  (0x1UL << SYSCTRL_PERI_CLKEN0_LPUART0_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_LPUART0_EN                      SYSCTRL_PERI_CLKEN0_LPUART0_EN_Msk
#define SYSCTRL_PERI_CLKEN0_LPUART1_EN_Pos                  (3U)
#define SYSCTRL_PERI_CLKEN0_LPUART1_EN_Msk                  (0x1UL << SYSCTRL_PERI_CLKEN0_LPUART1_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_LPUART1_EN                      SYSCTRL_PERI_CLKEN0_LPUART1_EN_Msk
#define SYSCTRL_PERI_CLKEN0_SPI_EN_Pos                      (6U)
#define SYSCTRL_PERI_CLKEN0_SPI_EN_Msk                      (0x1UL << SYSCTRL_PERI_CLKEN0_SPI_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_SPI_EN                          SYSCTRL_PERI_CLKEN0_SPI_EN_Msk
#define SYSCTRL_PERI_CLKEN0_ATIM3_EN_Pos                    (11U)
#define SYSCTRL_PERI_CLKEN0_ATIM3_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN0_ATIM3_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_ATIM3_EN                        SYSCTRL_PERI_CLKEN0_ATIM3_EN_Msk
#define SYSCTRL_PERI_CLKEN0_IWDT_EN_Pos                     (15U)
#define SYSCTRL_PERI_CLKEN0_IWDT_EN_Msk                     (0x1UL << SYSCTRL_PERI_CLKEN0_IWDT_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_IWDT_EN                         SYSCTRL_PERI_CLKEN0_IWDT_EN_Msk
#define SYSCTRL_PERI_CLKEN0_ADC_EN_Pos                      (16U)
#define SYSCTRL_PERI_CLKEN0_ADC_EN_Msk                      (0x1UL << SYSCTRL_PERI_CLKEN0_ADC_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_ADC_EN                          SYSCTRL_PERI_CLKEN0_ADC_EN_Msk
#define SYSCTRL_PERI_CLKEN0_VC_EN_Pos                       (17U)
#define SYSCTRL_PERI_CLKEN0_VC_EN_Msk                       (0x1UL << SYSCTRL_PERI_CLKEN0_VC_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_VC_EN                           SYSCTRL_PERI_CLKEN0_VC_EN_Msk
#define SYSCTRL_PERI_CLKEN0_TRNG_EN_Pos                     (18U)
#define SYSCTRL_PERI_CLKEN0_TRNG_EN_Msk                     (0x1UL << SYSCTRL_PERI_CLKEN0_TRNG_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_TRNG_EN                         SYSCTRL_PERI_CLKEN0_TRNG_EN_Msk
#define SYSCTRL_PERI_CLKEN0_RTC_EN_Pos                      (20U)
#define SYSCTRL_PERI_CLKEN0_RTC_EN_Msk                      (0x1UL << SYSCTRL_PERI_CLKEN0_RTC_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_RTC_EN                          SYSCTRL_PERI_CLKEN0_RTC_EN_Msk
#define SYSCTRL_PERI_CLKEN0_GPIO_EN_Pos                     (28U)
#define SYSCTRL_PERI_CLKEN0_GPIO_EN_Msk                     (0x1UL << SYSCTRL_PERI_CLKEN0_GPIO_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_GPIO_EN                         SYSCTRL_PERI_CLKEN0_GPIO_EN_Msk
#define SYSCTRL_PERI_CLKEN0_HSI2C_EN_Pos                    (30U)
#define SYSCTRL_PERI_CLKEN0_HSI2C_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN0_HSI2C_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_HSI2C_EN                        SYSCTRL_PERI_CLKEN0_HSI2C_EN_Msk
#define SYSCTRL_PERI_CLKEN0_FLASH_EN_Pos                    (31U)
#define SYSCTRL_PERI_CLKEN0_FLASH_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN0_FLASH_EN_Pos)
#define SYSCTRL_PERI_CLKEN0_FLASH_EN                        SYSCTRL_PERI_CLKEN0_FLASH_EN_Msk

// SYSCTRL_PERI_CLKEN1
#define SYSCTRL_PERI_CLKEN1_CTIM0_EN_Pos                    (0U)
#define SYSCTRL_PERI_CLKEN1_CTIM0_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN1_CTIM0_EN_Pos)
#define SYSCTRL_PERI_CLKEN1_CTIM0_EN                        SYSCTRL_PERI_CLKEN1_CTIM0_EN_Msk
#define SYSCTRL_PERI_CLKEN1_CTIM1_EN_Pos                    (1U)
#define SYSCTRL_PERI_CLKEN1_CTIM1_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN1_CTIM1_EN_Pos)
#define SYSCTRL_PERI_CLKEN1_CTIM1_EN                        SYSCTRL_PERI_CLKEN1_CTIM1_EN_Msk
#define SYSCTRL_PERI_CLKEN1_CTRIM_EN_Pos                    (2U)
#define SYSCTRL_PERI_CLKEN1_CTRIM_EN_Msk                    (0x1UL << SYSCTRL_PERI_CLKEN1_CTRIM_EN_Pos)
#define SYSCTRL_PERI_CLKEN1_CTRIM_EN                        SYSCTRL_PERI_CLKEN1_CTRIM_EN_Msk

// SYSCTRL_PERI_RESET0
#define SYSCTRL_PERI_RESET0_LPUART0_RST_Pos                 (2U)
#define SYSCTRL_PERI_RESET0_LPUART0_RST_Msk                 (0x1UL << SYSCTRL_PERI_RESET0_LPUART0_RST_Pos)
#define SYSCTRL_PERI_RESET0_LPUART0_RST                     SYSCTRL_PERI_RESET0_LPUART0_RST_Msk
#define SYSCTRL_PERI_RESET0_LPUART1_RST_Pos                 (3U)
#define SYSCTRL_PERI_RESET0_LPUART1_RST_Msk                 (0x1UL << SYSCTRL_PERI_RESET0_LPUART1_RST_Pos)
#define SYSCTRL_PERI_RESET0_LPUART1_RST                     SYSCTRL_PERI_RESET0_LPUART1_RST_Msk
#define SYSCTRL_PERI_RESET0_SPI_RST_Pos                     (6U)
#define SYSCTRL_PERI_RESET0_SPI_RST_Msk                     (0x1UL << SYSCTRL_PERI_RESET0_SPI_RST_Pos)
#define SYSCTRL_PERI_RESET0_SPI_RST                         SYSCTRL_PERI_RESET0_SPI_RST_Msk
#define SYSCTRL_PERI_RESET0_ATIM3_RST_Pos                   (11U)
#define SYSCTRL_PERI_RESET0_ATIM3_RST_Msk                   (0x1UL << SYSCTRL_PERI_RESET0_ATIM3_RST_Pos)
#define SYSCTRL_PERI_RESET0_ATIM3_RST                       SYSCTRL_PERI_RESET0_ATIM3_RST_Msk
#define SYSCTRL_PERI_RESET0_ADC_RST_Pos                     (16U)
#define SYSCTRL_PERI_RESET0_ADC_RST_Msk                     (0x1UL << SYSCTRL_PERI_RESET0_ADC_RST_Pos)
#define SYSCTRL_PERI_RESET0_ADC_RST                         SYSCTRL_PERI_RESET0_ADC_RST_Msk
#define SYSCTRL_PERI_RESET0_VC_RST_Pos                      (17U)
#define SYSCTRL_PERI_RESET0_VC_RST_Msk                      (0x1UL << SYSCTRL_PERI_RESET0_VC_RST_Pos)
#define SYSCTRL_PERI_RESET0_VC_RST                          SYSCTRL_PERI_RESET0_VC_RST_Msk
#define SYSCTRL_PERI_RESET0_TRNG_RST_Pos                    (18U)
#define SYSCTRL_PERI_RESET0_TRNG_RST_Msk                    (0x1UL << SYSCTRL_PERI_RESET0_TRNG_RST_Pos)
#define SYSCTRL_PERI_RESET0_TRNG_RST                        SYSCTRL_PERI_RESET0_TRNG_RST_Msk
#define SYSCTRL_PERI_RESET0_RTC_RST_Pos                     (20U)
#define SYSCTRL_PERI_RESET0_RTC_RST_Msk                     (0x1UL << SYSCTRL_PERI_RESET0_RTC_RST_Pos)
#define SYSCTRL_PERI_RESET0_RTC_RST                         SYSCTRL_PERI_RESET0_RTC_RST_Msk
#define SYSCTRL_PERI_RESET0_GPIO_RST_Pos                    (28U)
#define SYSCTRL_PERI_RESET0_GPIO_RST_Msk                    (0x1UL << SYSCTRL_PERI_RESET0_GPIO_RST_Pos)
#define SYSCTRL_PERI_RESET0_GPIO_RST                        SYSCTRL_PERI_RESET0_GPIO_RST_Msk
#define SYSCTRL_PERI_RESET0_HSI2C_RST_Pos                   (30U)
#define SYSCTRL_PERI_RESET0_HSI2C_RST_Msk                   (0x1UL << SYSCTRL_PERI_RESET0_HSI2C_RST_Pos)
#define SYSCTRL_PERI_RESET0_HSI2C_RST                       SYSCTRL_PERI_RESET0_HSI2C_RST_Msk

// SYSCTRL_PERI_RESET1
#define SYSCTRL_PERI_RESET1_CTIM0_RST_Pos                   (0U)
#define SYSCTRL_PERI_RESET1_CTIM0_RST_Msk                   (0x1UL << SYSCTRL_PERI_RESET1_CTIM0_RST_Pos)
#define SYSCTRL_PERI_RESET1_CTIM0_RST                       SYSCTRL_PERI_RESET1_CTIM0_RST_Msk
#define SYSCTRL_PERI_RESET1_CTIM1_RST_Pos                   (1U)
#define SYSCTRL_PERI_RESET1_CTIM1_RST_Msk                   (0x1UL << SYSCTRL_PERI_RESET1_CTIM1_RST_Pos)
#define SYSCTRL_PERI_RESET1_CTIM1_RST                       SYSCTRL_PERI_RESET1_CTIM1_RST_Msk
#define SYSCTRL_PERI_RESET1_CTRIM_RST_Pos                   (2U)
#define SYSCTRL_PERI_RESET1_CTRIM_RST_Msk                   (0x1UL << SYSCTRL_PERI_RESET1_CTRIM_RST_Pos)
#define SYSCTRL_PERI_RESET1_CTRIM_RST                       SYSCTRL_PERI_RESET1_CTRIM_RST_Msk

// SYSCTRL_DEBUG_ACTIVE
#define SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG_Pos                 (8U)
#define SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG_Msk                 (0x1UL << SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG_Pos)
#define SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG                     SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG_Msk
#define SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG_Pos                  (9U)
#define SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG_Msk                  (0x1UL << SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG_Pos)
#define SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG                      SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG_Msk
#define SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG_Pos                (11U)
#define SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG_Msk                (0x1UL << SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG_Pos)
#define SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG                    SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG_Msk
#define SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG_Pos                (16U)
#define SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG_Msk                (0x1UL << SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG_Pos)
#define SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG                    SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG_Msk
#define SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG_Pos                (17U)
#define SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG_Msk                (0x1UL << SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG_Pos)
#define SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG                    SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG_Msk



//********************    Bits Define For Peripheral TRNG    ********************//
// TRNG_CR
#define TRNG_CR_RNGCIR_EN_Pos                               (0U)
#define TRNG_CR_RNGCIR_EN_Msk                               (0x1UL << TRNG_CR_RNGCIR_EN_Pos)
#define TRNG_CR_RNGCIR_EN                                   TRNG_CR_RNGCIR_EN_Msk
#define TRNG_CR_RNG_RUN_Pos                                 (1U)
#define TRNG_CR_RNG_RUN_Msk                                 (0x1UL << TRNG_CR_RNG_RUN_Pos)
#define TRNG_CR_RNG_RUN                                     TRNG_CR_RNG_RUN_Msk

// TRNG_MODE
#define TRNG_MODE_LOAD_Pos                                  (0U)
#define TRNG_MODE_LOAD_Msk                                  (0x1UL << TRNG_MODE_LOAD_Pos)
#define TRNG_MODE_LOAD                                      TRNG_MODE_LOAD_Msk
#define TRNG_MODE_FDBK_Pos                                  (1U)
#define TRNG_MODE_FDBK_Msk                                  (0x1UL << TRNG_MODE_FDBK_Pos)
#define TRNG_MODE_FDBK                                      TRNG_MODE_FDBK_Msk
#define TRNG_MODE_CNT_Pos                                   (2U)
#define TRNG_MODE_CNT_Msk                                   (0x7UL << TRNG_MODE_CNT_Pos)
#define TRNG_MODE_CNT                                       TRNG_MODE_CNT_Msk

// TRNG_DATA0
#define TRNG_DATA0_DATA0_Pos                                (0U)
#define TRNG_DATA0_DATA0_Msk                                (0xFFFFFFFFUL << TRNG_DATA0_DATA0_Pos)
#define TRNG_DATA0_DATA0                                    TRNG_DATA0_DATA0_Msk

// TRNG_DATA1
#define TRNG_DATA1_DATA1_Pos                                (0U)
#define TRNG_DATA1_DATA1_Msk                                (0xFFFFFFFFUL << TRNG_DATA1_DATA1_Pos)
#define TRNG_DATA1_DATA1                                    TRNG_DATA1_DATA1_Msk



//********************    Bits Define For Peripheral VC    ********************//
// VC_VC0_CR0
#define VC_VC0_CR0_DIV_Pos                                  (0U)
#define VC_VC0_CR0_DIV_Msk                                  (0x3FUL << VC_VC0_CR0_DIV_Pos)
#define VC_VC0_CR0_DIV                                      VC_VC0_CR0_DIV_Msk
#define VC_VC0_CR0_DIV_EN_Pos                               (6U)
#define VC_VC0_CR0_DIV_EN_Msk                               (0x1UL << VC_VC0_CR0_DIV_EN_Pos)
#define VC_VC0_CR0_DIV_EN                                   VC_VC0_CR0_DIV_EN_Msk
#define VC_VC0_CR0_BIAS_Pos                                 (8U)
#define VC_VC0_CR0_BIAS_Msk                                 (0x3UL << VC_VC0_CR0_BIAS_Pos)
#define VC_VC0_CR0_BIAS                                     VC_VC0_CR0_BIAS_Msk
#define VC_VC0_CR0_HYS_Pos                                  (10U)
#define VC_VC0_CR0_HYS_Msk                                  (0x3UL << VC_VC0_CR0_HYS_Pos)
#define VC_VC0_CR0_HYS                                      VC_VC0_CR0_HYS_Msk

// VC_VC0_CR1
#define VC_VC0_CR1_PSEL_Pos                                 (0U)
#define VC_VC0_CR1_PSEL_Msk                                 (0xFUL << VC_VC0_CR1_PSEL_Pos)
#define VC_VC0_CR1_PSEL                                     VC_VC0_CR1_PSEL_Msk
#define VC_VC0_CR1_NSEL_Pos                                 (4U)
#define VC_VC0_CR1_NSEL_Msk                                 (0xFUL << VC_VC0_CR1_NSEL_Pos)
#define VC_VC0_CR1_NSEL                                     VC_VC0_CR1_NSEL_Msk
#define VC_VC0_CR1_FLTTIME_Pos                              (8U)
#define VC_VC0_CR1_FLTTIME_Msk                              (0xFUL << VC_VC0_CR1_FLTTIME_Pos)
#define VC_VC0_CR1_FLTTIME                                  VC_VC0_CR1_FLTTIME_Msk
#define VC_VC0_CR1_FALLING_Pos                              (12U)
#define VC_VC0_CR1_FALLING_Msk                              (0x1UL << VC_VC0_CR1_FALLING_Pos)
#define VC_VC0_CR1_FALLING                                  VC_VC0_CR1_FALLING_Msk
#define VC_VC0_CR1_RISING_Pos                               (13U)
#define VC_VC0_CR1_RISING_Msk                               (0x1UL << VC_VC0_CR1_RISING_Pos)
#define VC_VC0_CR1_RISING                                   VC_VC0_CR1_RISING_Msk
#define VC_VC0_CR1_LEVEL_Pos                                (14U)
#define VC_VC0_CR1_LEVEL_Msk                                (0x1UL << VC_VC0_CR1_LEVEL_Pos)
#define VC_VC0_CR1_LEVEL                                    VC_VC0_CR1_LEVEL_Msk
#define VC_VC0_CR1_IE_Pos                                   (15U)
#define VC_VC0_CR1_IE_Msk                                   (0x1UL << VC_VC0_CR1_IE_Pos)
#define VC_VC0_CR1_IE                                       VC_VC0_CR1_IE_Msk
#define VC_VC0_CR1_EN_Pos                                   (16U)
#define VC_VC0_CR1_EN_Msk                                   (0x1UL << VC_VC0_CR1_EN_Pos)
#define VC_VC0_CR1_EN                                       VC_VC0_CR1_EN_Msk
#define VC_VC0_CR1_FLTCLK_Pos                               (17U)
#define VC_VC0_CR1_FLTCLK_Msk                               (0x1UL << VC_VC0_CR1_FLTCLK_Pos)
#define VC_VC0_CR1_FLTCLK                                   VC_VC0_CR1_FLTCLK_Msk
#define VC_VC0_CR1_FLT_MODE_Pos                             (18U)
#define VC_VC0_CR1_FLT_MODE_Msk                             (0x3UL << VC_VC0_CR1_FLT_MODE_Pos)
#define VC_VC0_CR1_FLT_MODE                                 VC_VC0_CR1_FLT_MODE_Msk

// VC_VC0_CR2
#define VC_VC0_CR2_POL_Pos                                  (0U)
#define VC_VC0_CR2_POL_Msk                                  (0x1UL << VC_VC0_CR2_POL_Pos)
#define VC_VC0_CR2_POL                                      VC_VC0_CR2_POL_Msk
#define VC_VC0_CR2_ATIM3CLR_Pos                             (4U)
#define VC_VC0_CR2_ATIM3CLR_Msk                             (0x1UL << VC_VC0_CR2_ATIM3CLR_Pos)
#define VC_VC0_CR2_ATIM3CLR                                 VC_VC0_CR2_ATIM3CLR_Msk
#define VC_VC0_CR2_ATIMBK_Pos                               (5U)
#define VC_VC0_CR2_ATIMBK_Msk                               (0x1UL << VC_VC0_CR2_ATIMBK_Pos)
#define VC_VC0_CR2_ATIMBK                                   VC_VC0_CR2_ATIMBK_Msk
#define VC_VC0_CR2_WINDOW_Pos                               (6U)
#define VC_VC0_CR2_WINDOW_Msk                               (0x1UL << VC_VC0_CR2_WINDOW_Pos)
#define VC_VC0_CR2_WINDOW                                   VC_VC0_CR2_WINDOW_Msk
#define VC_VC0_CR2_BLANK_Pos                                (8U)
#define VC_VC0_CR2_BLANK_Msk                                (0x7UL << VC_VC0_CR2_BLANK_Pos)
#define VC_VC0_CR2_BLANK                                    VC_VC0_CR2_BLANK_Msk

// VC_VC0_SR
#define VC_VC0_SR_INTF_Pos                                  (0U)
#define VC_VC0_SR_INTF_Msk                                  (0x1UL << VC_VC0_SR_INTF_Pos)
#define VC_VC0_SR_INTF                                      VC_VC0_SR_INTF_Msk
#define VC_VC0_SR_FLTV_Pos                                  (1U)
#define VC_VC0_SR_FLTV_Msk                                  (0x1UL << VC_VC0_SR_FLTV_Pos)
#define VC_VC0_SR_FLTV                                      VC_VC0_SR_FLTV_Msk

// VC_VC1_CR0
#define VC_VC1_CR0_DIV_Pos                                  (0U)
#define VC_VC1_CR0_DIV_Msk                                  (0x3FUL << VC_VC1_CR0_DIV_Pos)
#define VC_VC1_CR0_DIV                                      VC_VC1_CR0_DIV_Msk
#define VC_VC1_CR0_DIV_EN_Pos                               (6U)
#define VC_VC1_CR0_DIV_EN_Msk                               (0x1UL << VC_VC1_CR0_DIV_EN_Pos)
#define VC_VC1_CR0_DIV_EN                                   VC_VC1_CR0_DIV_EN_Msk
#define VC_VC1_CR0_BIAS_Pos                                 (8U)
#define VC_VC1_CR0_BIAS_Msk                                 (0x3UL << VC_VC1_CR0_BIAS_Pos)
#define VC_VC1_CR0_BIAS                                     VC_VC1_CR0_BIAS_Msk
#define VC_VC1_CR0_HYS_Pos                                  (10U)
#define VC_VC1_CR0_HYS_Msk                                  (0x3UL << VC_VC1_CR0_HYS_Pos)
#define VC_VC1_CR0_HYS                                      VC_VC1_CR0_HYS_Msk

// VC_VC1_CR1
#define VC_VC1_CR1_PSEL_Pos                                 (0U)
#define VC_VC1_CR1_PSEL_Msk                                 (0xFUL << VC_VC1_CR1_PSEL_Pos)
#define VC_VC1_CR1_PSEL                                     VC_VC1_CR1_PSEL_Msk
#define VC_VC1_CR1_NSEL_Pos                                 (4U)
#define VC_VC1_CR1_NSEL_Msk                                 (0xFUL << VC_VC1_CR1_NSEL_Pos)
#define VC_VC1_CR1_NSEL                                     VC_VC1_CR1_NSEL_Msk
#define VC_VC1_CR1_FLTTIME_Pos                              (8U)
#define VC_VC1_CR1_FLTTIME_Msk                              (0xFUL << VC_VC1_CR1_FLTTIME_Pos)
#define VC_VC1_CR1_FLTTIME                                  VC_VC1_CR1_FLTTIME_Msk
#define VC_VC1_CR1_FALLING_Pos                              (12U)
#define VC_VC1_CR1_FALLING_Msk                              (0x1UL << VC_VC1_CR1_FALLING_Pos)
#define VC_VC1_CR1_FALLING                                  VC_VC1_CR1_FALLING_Msk
#define VC_VC1_CR1_RISING_Pos                               (13U)
#define VC_VC1_CR1_RISING_Msk                               (0x1UL << VC_VC1_CR1_RISING_Pos)
#define VC_VC1_CR1_RISING                                   VC_VC1_CR1_RISING_Msk
#define VC_VC1_CR1_LEVEL_Pos                                (14U)
#define VC_VC1_CR1_LEVEL_Msk                                (0x1UL << VC_VC1_CR1_LEVEL_Pos)
#define VC_VC1_CR1_LEVEL                                    VC_VC1_CR1_LEVEL_Msk
#define VC_VC1_CR1_IE_Pos                                   (15U)
#define VC_VC1_CR1_IE_Msk                                   (0x1UL << VC_VC1_CR1_IE_Pos)
#define VC_VC1_CR1_IE                                       VC_VC1_CR1_IE_Msk
#define VC_VC1_CR1_EN_Pos                                   (16U)
#define VC_VC1_CR1_EN_Msk                                   (0x1UL << VC_VC1_CR1_EN_Pos)
#define VC_VC1_CR1_EN                                       VC_VC1_CR1_EN_Msk
#define VC_VC1_CR1_FLTCLK_Pos                               (17U)
#define VC_VC1_CR1_FLTCLK_Msk                               (0x1UL << VC_VC1_CR1_FLTCLK_Pos)
#define VC_VC1_CR1_FLTCLK                                   VC_VC1_CR1_FLTCLK_Msk
#define VC_VC1_CR1_FLT_MODE_Pos                             (18U)
#define VC_VC1_CR1_FLT_MODE_Msk                             (0x3UL << VC_VC1_CR1_FLT_MODE_Pos)
#define VC_VC1_CR1_FLT_MODE                                 VC_VC1_CR1_FLT_MODE_Msk

// VC_VC1_CR2
#define VC_VC1_CR2_POL_Pos                                  (0U)
#define VC_VC1_CR2_POL_Msk                                  (0x1UL << VC_VC1_CR2_POL_Pos)
#define VC_VC1_CR2_POL                                      VC_VC1_CR2_POL_Msk
#define VC_VC1_CR2_ATIM3CLR_Pos                             (4U)
#define VC_VC1_CR2_ATIM3CLR_Msk                             (0x1UL << VC_VC1_CR2_ATIM3CLR_Pos)
#define VC_VC1_CR2_ATIM3CLR                                 VC_VC1_CR2_ATIM3CLR_Msk
#define VC_VC1_CR2_ATIMBK_Pos                               (5U)
#define VC_VC1_CR2_ATIMBK_Msk                               (0x1UL << VC_VC1_CR2_ATIMBK_Pos)
#define VC_VC1_CR2_ATIMBK                                   VC_VC1_CR2_ATIMBK_Msk
#define VC_VC1_CR2_WINDOW_Pos                               (6U)
#define VC_VC1_CR2_WINDOW_Msk                               (0x1UL << VC_VC1_CR2_WINDOW_Pos)
#define VC_VC1_CR2_WINDOW                                   VC_VC1_CR2_WINDOW_Msk
#define VC_VC1_CR2_BLANK_Pos                                (8U)
#define VC_VC1_CR2_BLANK_Msk                                (0x7UL << VC_VC1_CR2_BLANK_Pos)
#define VC_VC1_CR2_BLANK                                    VC_VC1_CR2_BLANK_Msk

// VC_VC1_SR
#define VC_VC1_SR_INTF_Pos                                  (0U)
#define VC_VC1_SR_INTF_Msk                                  (0x1UL << VC_VC1_SR_INTF_Pos)
#define VC_VC1_SR_INTF                                      VC_VC1_SR_INTF_Msk
#define VC_VC1_SR_FLTV_Pos                                  (1U)
#define VC_VC1_SR_FLTV_Msk                                  (0x1UL << VC_VC1_SR_FLTV_Pos)
#define VC_VC1_SR_FLTV                                      VC_VC1_SR_FLTV_Msk

// VC_VC_TRIM
#define VC_VC_TRIM_TRIM0_Pos                                (0U)
#define VC_VC_TRIM_TRIM0_Msk                                (0xFUL << VC_VC_TRIM_TRIM0_Pos)
#define VC_VC_TRIM_TRIM0                                    VC_VC_TRIM_TRIM0_Msk
#define VC_VC_TRIM_TRIM1_Pos                                (4U)
#define VC_VC_TRIM_TRIM1_Msk                                (0xFUL << VC_VC_TRIM_TRIM1_Pos)
#define VC_VC_TRIM_TRIM1                                    VC_VC_TRIM_TRIM1_Msk





#ifdef __cplusplus
}
#endif

#endif /* __HC32L021_H__ */

