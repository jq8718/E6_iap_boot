/**
 *******************************************************************************
 * @file  gpio.h
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

#ifndef __GPIO_H__
#define __GPIO_H__

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
 * @addtogroup DDL_GPIO GPIO模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO全局类型定义
 * @{
 */

/**
 * @brief GPIO 端口配置结构体定义
 */
typedef struct
{
    uint32_t  u32Pin;       /*!< 端口PIN脚选择 @ref GPIO_Pins_Define */
    uint32_t  u32Mode;      /*!< 端口模式选择  @ref GPIO_Mode_Define */
    uint32_t  u32PullUp;    /*!< 端口上拉配置 @ref GPIO_Pull_Up_Define */
    uint32_t  u32ExternInt; /*!< 端口外部中断功能 @ref GPIO_Extern_Int_Define */
    boolean_t bOutputValue; /*!< 端口PIN脚设置初始值 @ref boolean_t */
} stc_gpio_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Macros GPIO全局宏定义
 * @{
 */

/**
 * @defgroup GPIO_Pins_Define GPIO引脚定义
 * @{
 */
#define GPIO_PIN_00  ((uint16_t)0x0001u) /*!<  PIN 00  SELECTED */
#define GPIO_PIN_01  ((uint16_t)0x0002u) /*!<  PIN 01  SELECTED */
#define GPIO_PIN_02  ((uint16_t)0x0004u) /*!<  PIN 02  SELECTED */
#define GPIO_PIN_03  ((uint16_t)0x0008u) /*!<  PIN 03  SELECTED */
#define GPIO_PIN_04  ((uint16_t)0x0010u) /*!<  PIN 04  SELECTED */
#define GPIO_PIN_05  ((uint16_t)0x0020u) /*!<  PIN 05  SELECTED */
#define GPIO_PIN_06  ((uint16_t)0x0040u) /*!<  PIN 06  SELECTED */
#define GPIO_PIN_07  ((uint16_t)0x0080u) /*!<  PIN 07  SELECTED */
#define GPIO_PIN_08  ((uint16_t)0x0100u) /*!<  PIN 08  SELECTED */
#define GPIO_PIN_09  ((uint16_t)0x0200u) /*!<  PIN 09  SELECTED */
#define GPIO_PIN_10  ((uint16_t)0x0400u) /*!<  PIN 10  SELECTED */
#define GPIO_PIN_11  ((uint16_t)0x0800u) /*!<  PIN 11  SELECTED */
#define GPIO_PIN_12  ((uint16_t)0x1000u) /*!<  PIN 12  SELECTED */
#define GPIO_PIN_13  ((uint16_t)0x2000u) /*!<  PIN 13  SELECTED */
#define GPIO_PIN_14  ((uint16_t)0x4000u) /*!<  PIN 14  SELECTED */
#define GPIO_PIN_15  ((uint16_t)0x8000u) /*!<  PIN 15  SELECTED */
#define GPIO_PIN_ALL ((uint16_t)0xFFFFu) /*!<  PIN ALL SELECTED */
/**
 * @}
 */

/** @defgroup GPIO_Mode_Define GPIO模式定义
 *        Elements values convention: 0x00UVWXYZ
 *           - V  : IO中断方式
 *           - W  ：IO驱动模式
 *           - X  : IO输入电平方式
 *           - Y  : IO输出方式 (Push Pull or Open Drain)
 *           - Z  : IO模式 (Input, Output, Alternate or Analog)
 * @{
 */
#define GPIO_MD_INPUT     ((uint32_t)0x00000001u) /*!< 高阻输入模式 */

#define GPIO_MD_OUTPUT_PP ((uint32_t)0x00000002u) /*!< 推挽输出模式(Push Pull) */
#define GPIO_MD_OUTPUT_OD ((uint32_t)0x00000012u) /*!< 开漏输出模式(Open Drain) */

#define GPIO_MD_ANALOG    ((uint32_t)0x00000004u) /*!< 模拟功能模式 */

#define GPIO_MD_INT_INPUT ((uint32_t)0x00000F01u) /*!< 外部中断输入模式 */
/**
 * @}
 */

/** @defgroup GPIO_Pull_Up_Define GPIO上拉定义
 * @{
 */
#define GPIO_PULL_UP   ((uint32_t)0x00100000u) /*!< 端口上拉 */
#define GPIO_PULL_NONE ((uint32_t)0x00000000u) /*!< 端口无上拉 */
/**
 * @}
 */

/** @defgroup  GPIO_Extern_Int_Define GPIO外部中断触发方式定义
 * @{
 */
#define GPIO_EXTI_NONE           ((uint32_t)0x00000000u) /*!< 不触发 */
#define GPIO_EXTI_RISING         ((uint32_t)0x00010000u) /*!< 上升沿触发 */
#define GPIO_EXTI_FALLING        ((uint32_t)0x00020000u) /*!< 下降沿触发 */
#define GPIO_EXTI_RISING_FALLING ((uint32_t)0x00030000u) /*!< 双沿触发 */
#define GPIO_EXTI_HIGH           ((uint32_t)0x00040000u) /*!< 高电平触发 */
#define GPIO_EXTI_LOW            ((uint32_t)0x00080000u) /*!< 低电平触发 */
/**
 * @}
 */

/**
 * @defgroup GPIO_Analog_Func_Macros GPIO模拟功能设置全局宏定义
 * @{
 */
#define GPIO_PORTA_ANALOG_SET() SET_REG_BIT(GPIOA->ADS, GPIO_PIN_ALL)

#define GPIO_PA00_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_00) /*!< PA00 GPIO_ANALOG */
#define GPIO_PA01_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_01) /*!< PA01 GPIO_ANALOG */
#define GPIO_PA02_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_02) /*!< PA02 GPIO_ANALOG */
#define GPIO_PA03_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_03) /*!< PA03 GPIO_ANALOG */
#define GPIO_PA04_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_04) /*!< PA04 GPIO_ANALOG */
#define GPIO_PA05_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_05) /*!< PA05 GPIO_ANALOG */
#define GPIO_PA06_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_06) /*!< PA06 GPIO_ANALOG */
#define GPIO_PA07_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_07) /*!< PA07 GPIO_ANALOG */
#define GPIO_PA08_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_08) /*!< PA08 GPIO_ANALOG */
#define GPIO_PA09_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_09) /*!< PA09 GPIO_ANALOG */
#define GPIO_PA10_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_10) /*!< PA10 GPIO_ANALOG */
#define GPIO_PA11_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_11) /*!< PA11 GPIO_ANALOG */
#define GPIO_PA12_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_12) /*!< PA12 GPIO_ANALOG */
#define GPIO_PA13_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_13) /*!< PA13 GPIO_ANALOG */
#define GPIO_PA14_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_14) /*!< PA14 GPIO_ANALOG */
#define GPIO_PA15_ANALOG_SET()  SET_REG_BIT(GPIOA->ADS, GPIO_PIN_15) /*!< PA15 GPIO_ANALOG */
/**
 * @}
 */

/**
 * @defgroup GPIO_Alternate_Func_Macros GPIO端口复用功能类型定义
 * @note  具体功能及含义请参考用户手册GPIO复用表或下表
 * @{
 */
///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PSEL  ||   GpioAf1   ||   GpioAf2   ||   GpioAf3   ||   GpioAf4   ||   GpioAf5   ||   GpioAf6   ||   GpioAf7   ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PA00  ||CTIM1_CH0    ||LPUART1_TXD  ||             ||             ||ATIM3_CH0A   ||RTC_1HZ      ||ATIM3_GATE   ||*///
///*||PA01  ||LPUART1_TXD  ||             ||             ||RTC_TAMP     ||ATIM3_CH0B   ||SPI_MISO     ||HSI2C_SCL    ||*///
///*||PA02  ||LPUART1_RXD  ||ATIM3_CH2A   ||             ||CTIM0_CH0    ||ATIM3_CH1A   ||SPI_MOSI     ||HSI2C_SDA    ||*///
///*||PA03  ||LPUART0_RXD  ||HSI2C_SDA    ||             ||CTIM1_TOG    ||ATIM3_CH1B   ||SPI_SCK      ||             ||*///
///*||PA04  ||LPUART0_TXD  ||HSI2C_SCL    ||             ||CTIM1_TOGN   ||ATIM3_CH2A   ||SPI_CS       ||ATIM3_BK     ||*///
///*||PA05  ||CTIM1_CH3    ||SPI_CS       ||ATIM3_CH2B   ||             ||RTC_1HZ      ||CTIM0_ETR    ||ATIM3_ETR    ||*///
///*||PA06  ||HSI2C_SDA    ||LPUART1_CTS  ||ATIM3_CH0B   ||             ||SPI_SCK      ||LPUART0_RXD  ||LVD_OUT      ||*///
///*||PA07  ||HSI2C_SCL    ||LPUART1_RTS  ||CTIM1_ETR    ||             ||SPI_CS       ||LPUART0_TXD  ||ATIM3_GATE   ||*///
///*||PA08  ||             ||ATIM3_CH2B   ||             ||CTIM0_CH0    ||SPI_MISO     ||LPUART1_TXD  ||IR_OUT       ||*///
///*||PA09  ||             ||ATIM3_CH1B   ||             ||CTIM0_CH1    ||SPI_MOSI     ||LPUART1_RXD  ||             ||*///
///*||PA10  ||SPI_SCK      ||CTIM0_CH3    ||             ||             ||LPUART0_RXD  ||HSI2C_SDA    ||             ||*///
///*||PA11  ||SPI_MOSI     ||ATIM3_CH0A   ||             ||CTIM0_CH2    ||LPUART0_TXD  ||HSI2C_SCL    ||CTRIM_ETRTOG ||*///
///*||PA12  ||SPI_CS       ||             ||ATIM3_CH1A   ||CTIM0_CH1    ||LPUART1_RXD  ||             ||LPUART0_RTS  ||*///
///*||PA13  ||SPI_MISO     ||             ||ATIM3_CH2A   ||CTIM1_CH1    ||LPUART0_RXD  ||CTIM0_TOG    ||ATIM3_BK     ||*///
///*||PA14  ||CTRIM_ETRTOG ||CTIM1_ETR    ||             ||VC0_OUT      ||LPUART0_TXD  ||CTIM0_TOGN   ||TCLK_OUT     ||*///
///*||PA15  ||LPUART0_CTS  ||CTIM1_CH2    ||             ||VC1_OUT      ||LPUART1_TXD  ||CTIM0_ETR    ||RTC_1HZ      ||*///
///*||PB00  ||             ||             ||             ||             ||CTIM0_ETR    ||ATIM3_ETR    ||ATIM3_BK     ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///

/**
 * @defgroup GPIO_Alternate_Func GPIO端口复用类型定义
 * @{
 */
#define GPIO_AF0 (0x0u) /*!< GPIO功能 */
#define GPIO_AF1 (0x1u) /*!< GPIO AF1:复用功能1 */
#define GPIO_AF2 (0x2u) /*!< GPIO AF2:复用功能2 */
#define GPIO_AF3 (0x3u) /*!< GPIO AF3:复用功能3 */
#define GPIO_AF4 (0x4u) /*!< GPIO AF4:复用功能4 */
#define GPIO_AF5 (0x5u) /*!< GPIO AF5:复用功能5 */
#define GPIO_AF6 (0x6u) /*!< GPIO AF6:复用功能6 */
#define GPIO_AF7 (0x7u) /*!< GPIO AF7:复用功能7 */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF0_Macros GPIO复用功能AF0宏定义
 * @{
 */
#define GPIO_PA00_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk) /*!< PA00 GPIO_FUNCTION */
#define GPIO_PA01_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk) /*!< PA01 GPIO_FUNCTION */
#define GPIO_PA02_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk) /*!< PA02 GPIO_FUNCTION */
#define GPIO_PA03_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk) /*!< PA03 GPIO_FUNCTION */
#define GPIO_PA04_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk) /*!< PA04 GPIO_FUNCTION */
#define GPIO_PA05_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk) /*!< PA05 GPIO_FUNCTION */
#define GPIO_PA06_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk) /*!< PA06 GPIO_FUNCTION */
#define GPIO_PA07_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk) /*!< PA07 GPIO_FUNCTION */
#define GPIO_PA08_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk) /*!< PA08 GPIO_FUNCTION */
#define GPIO_PA09_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN09_SEL, GPIO_PIN09_SEL_SEL_Msk) /*!< PA09 GPIO_FUNCTION */
#define GPIO_PA10_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN10_SEL, GPIO_PIN10_SEL_SEL_Msk) /*!< PA10 GPIO_FUNCTION */
#define GPIO_PA11_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk) /*!< PA11 GPIO_FUNCTION */
#define GPIO_PA12_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk) /*!< PA12 GPIO_FUNCTION */
#define GPIO_PA13_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk) /*!< PA13 GPIO_FUNCTION */
#define GPIO_PA14_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk) /*!< PA14 GPIO_FUNCTION */
#define GPIO_PA15_AF_GPIO_SET() CLR_REG_BIT(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk) /*!< PA15 GPIO_FUNCTION */
#define GPIO_PB00_AF_GPIO_SET() CLR_REG_BIT(GPIOB->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk) /*!< PB00 GPIO_FUNCTION */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF1_Macros GPIO复用功能AF1宏定义
 * @{
 */
#define GPIO_PA00_AF_CTIM1_CH0()    MODIFY_REG(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN00_SEL_SEL_Pos)) /*!< CTIM1_CH0    */
#define GPIO_PA01_AF_LPUART1_TXD()  MODIFY_REG(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN01_SEL_SEL_Pos)) /*!< LPUART1_TXD  */
#define GPIO_PA02_AF_LPUART1_RXD()  MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN02_SEL_SEL_Pos)) /*!< LPUART1_RXD  */
#define GPIO_PA03_AF_LPUART0_RXD()  MODIFY_REG(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN03_SEL_SEL_Pos)) /*!< LPUART0_RXD  */
#define GPIO_PA04_AF_LPUART0_TXD()  MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN04_SEL_SEL_Pos)) /*!< LPUART0_TXD  */
#define GPIO_PA05_AF_CTIM1_CH3()    MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN05_SEL_SEL_Pos)) /*!< CTIM1_CH3    */
#define GPIO_PA06_AF_HSI2C_SDA()    MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN06_SEL_SEL_Pos)) /*!< HSI2C_SDA    */
#define GPIO_PA07_AF_HSI2C_SCL()    MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN07_SEL_SEL_Pos)) /*!< HSI2C_SCL    */
#define GPIO_PA10_AF_SPI_SCK()      MODIFY_REG(GPIOA->PIN10_SEL, GPIO_PIN10_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN10_SEL_SEL_Pos)) /*!< SPI_SCK      */
#define GPIO_PA11_AF_SPI_MOSI()     MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN11_SEL_SEL_Pos)) /*!< SPI_MOSI     */
#define GPIO_PA12_AF_SPI_CS()       MODIFY_REG(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN12_SEL_SEL_Pos)) /*!< SPI_CS       */
#define GPIO_PA13_AF_SPI_MISO()     MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN13_SEL_SEL_Pos)) /*!< SPI_MISO     */
#define GPIO_PA14_AF_CTRIM_ETRTOG() MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN14_SEL_SEL_Pos)) /*!< CTRIM_ETRTOG */
#define GPIO_PA15_AF_LPUART0_CTS()  MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF1 << GPIO_PIN15_SEL_SEL_Pos)) /*!< LPUART0_CTS  */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF2_Macros GPIO复用功能AF2宏定义
 * @{
 */
#define GPIO_PA00_AF_LPUART1_TXD() MODIFY_REG(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN00_SEL_SEL_Pos)) /*!< LPUART1_TXD */
#define GPIO_PA02_AF_ATIM3_CH2A()  MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN02_SEL_SEL_Pos)) /*!< ATIM3_CH2A  */
#define GPIO_PA03_AF_HSI2C_SDA()   MODIFY_REG(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN03_SEL_SEL_Pos)) /*!< HSI2C_SDA   */
#define GPIO_PA04_AF_HSI2C_SCL()   MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN04_SEL_SEL_Pos)) /*!< HSI2C_SCL   */
#define GPIO_PA05_AF_SPI_CS()      MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN05_SEL_SEL_Pos)) /*!< SPI_CS      */
#define GPIO_PA06_AF_LPUART1_CTS() MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN06_SEL_SEL_Pos)) /*!< LPUART1_CTS */
#define GPIO_PA07_AF_LPUART1_RTS() MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN07_SEL_SEL_Pos)) /*!< LPUART1_RTS */
#define GPIO_PA08_AF_ATIM3_CH2B()  MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN08_SEL_SEL_Pos)) /*!< ATIM3_CH2B  */
#define GPIO_PA09_AF_ATIM3_CH1B()  MODIFY_REG(GPIOA->PIN09_SEL, GPIO_PIN09_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN09_SEL_SEL_Pos)) /*!< ATIM3_CH1B  */
#define GPIO_PA10_AF_CTIM0_CH3()   MODIFY_REG(GPIOA->PIN10_SEL, GPIO_PIN10_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN10_SEL_SEL_Pos)) /*!< CTIM0_CH3   */
#define GPIO_PA11_AF_ATIM3_CH0A()  MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN11_SEL_SEL_Pos)) /*!< ATIM3_CH0A  */
#define GPIO_PA14_AF_CTIM1_ETR()   MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN14_SEL_SEL_Pos)) /*!< CTIM1_ETR   */
#define GPIO_PA15_AF_CTIM1_CH2()   MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF2 << GPIO_PIN15_SEL_SEL_Pos)) /*!< CTIM1_CH2   */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF3_Macros GPIO复用功能AF3宏定义
 * @{
 */
#define GPIO_PA05_AF_ATIM3_CH2B() MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF3 << GPIO_PIN05_SEL_SEL_Pos)) /*!< ATIM3_CH2B */
#define GPIO_PA06_AF_ATIM3_CH0B() MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF3 << GPIO_PIN06_SEL_SEL_Pos)) /*!< ATIM3_CH0B */
#define GPIO_PA07_AF_CTIM1_ETR()  MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF3 << GPIO_PIN07_SEL_SEL_Pos)) /*!< CTIM1_ETR  */
#define GPIO_PA12_AF_ATIM3_CH1A() MODIFY_REG(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk, (GPIO_AF3 << GPIO_PIN12_SEL_SEL_Pos)) /*!< ATIM3_CH1A */
#define GPIO_PA13_AF_ATIM3_CH2A() MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF3 << GPIO_PIN13_SEL_SEL_Pos)) /*!< ATIM3_CH2A */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF4_Macros GPIO复用功能AF4宏定义
 * @{
 */
#define GPIO_PA01_AF_RTC_TAMP()   MODIFY_REG(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN01_SEL_SEL_Pos)) /*!< RTC_TAMP   */
#define GPIO_PA02_AF_CTIM0_CH0()  MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN02_SEL_SEL_Pos)) /*!< CTIM0_CH0  */
#define GPIO_PA03_AF_CTIM1_TOG()  MODIFY_REG(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN03_SEL_SEL_Pos)) /*!< CTIM1_TOG  */
#define GPIO_PA04_AF_CTIM1_TOGN() MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN04_SEL_SEL_Pos)) /*!< CTIM1_TOGN */
#define GPIO_PA08_AF_CTIM0_CH0()  MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN08_SEL_SEL_Pos)) /*!< CTIM0_CH0  */
#define GPIO_PA09_AF_CTIM0_CH1()  MODIFY_REG(GPIOA->PIN09_SEL, GPIO_PIN09_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN09_SEL_SEL_Pos)) /*!< CTIM0_CH1  */
#define GPIO_PA11_AF_CTIM0_CH2()  MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN11_SEL_SEL_Pos)) /*!< CTIM0_CH2  */
#define GPIO_PA12_AF_CTIM0_CH1()  MODIFY_REG(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN12_SEL_SEL_Pos)) /*!< CTIM0_CH1  */
#define GPIO_PA13_AF_CTIM1_CH1()  MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN13_SEL_SEL_Pos)) /*!< CTIM1_CH1  */
#define GPIO_PA14_AF_VC0_OUT()    MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN14_SEL_SEL_Pos)) /*!< VC0_OUT    */
#define GPIO_PA15_AF_VC1_OUT()    MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF4 << GPIO_PIN15_SEL_SEL_Pos)) /*!< VC1_OUT    */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF5_Macros GPIO复用功能AF5宏定义
 * @{
 */
#define GPIO_PA00_AF_ATIM3_CH0A()  MODIFY_REG(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN00_SEL_SEL_Pos)) /*!< ATIM3_CH0A  */
#define GPIO_PA01_AF_ATIM3_CH0B()  MODIFY_REG(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN01_SEL_SEL_Pos)) /*!< ATIM3_CH0B  */
#define GPIO_PA02_AF_ATIM3_CH1A()  MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN02_SEL_SEL_Pos)) /*!< ATIM3_CH1A  */
#define GPIO_PA03_AF_ATIM3_CH1B()  MODIFY_REG(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN03_SEL_SEL_Pos)) /*!< ATIM3_CH1B  */
#define GPIO_PA04_AF_ATIM3_CH2A()  MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN04_SEL_SEL_Pos)) /*!< ATIM3_CH2A  */
#define GPIO_PA05_AF_RTC_1HZ()     MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN05_SEL_SEL_Pos)) /*!< RTC_1HZ     */
#define GPIO_PA06_AF_SPI_SCK()     MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN06_SEL_SEL_Pos)) /*!< SPI_SCK     */
#define GPIO_PA07_AF_SPI_CS()      MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN07_SEL_SEL_Pos)) /*!< SPI_CS      */
#define GPIO_PA08_AF_SPI_MISO()    MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN08_SEL_SEL_Pos)) /*!< SPI_MISO    */
#define GPIO_PA09_AF_SPI_MOSI()    MODIFY_REG(GPIOA->PIN09_SEL, GPIO_PIN09_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN09_SEL_SEL_Pos)) /*!< SPI_MOSI    */
#define GPIO_PA10_AF_LPUART0_RXD() MODIFY_REG(GPIOA->PIN10_SEL, GPIO_PIN10_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN10_SEL_SEL_Pos)) /*!< LPUART0_RXD */
#define GPIO_PA11_AF_LPUART0_TXD() MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN11_SEL_SEL_Pos)) /*!< LPUART0_TXD */
#define GPIO_PA12_AF_LPUART1_RXD() MODIFY_REG(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN12_SEL_SEL_Pos)) /*!< LPUART1_RXD */
#define GPIO_PA13_AF_LPUART0_RXD() MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN13_SEL_SEL_Pos)) /*!< LPUART0_RXD */
#define GPIO_PA14_AF_LPUART0_TXD() MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN14_SEL_SEL_Pos)) /*!< LPUART0_TXD */
#define GPIO_PA15_AF_LPUART1_TXD() MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN15_SEL_SEL_Pos)) /*!< LPUART1_TXD */
#define GPIO_PB00_AF_CTIM0_ETR()   MODIFY_REG(GPIOB->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF5 << GPIO_PIN00_SEL_SEL_Pos)) /*!< CTIM0_ETR   */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF6_Macros GPIO复用功能AF6宏定义
 * @{
 */
#define GPIO_PA00_AF_RTC_1HZ()     MODIFY_REG(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN00_SEL_SEL_Pos)) /*!< RTC_1HZ     */
#define GPIO_PA01_AF_SPI_MISO()    MODIFY_REG(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN01_SEL_SEL_Pos)) /*!< SPI_MISO    */
#define GPIO_PA02_AF_SPI_MOSI()    MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN02_SEL_SEL_Pos)) /*!< SPI_MOSI    */
#define GPIO_PA03_AF_SPI_SCK()     MODIFY_REG(GPIOA->PIN03_SEL, GPIO_PIN03_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN03_SEL_SEL_Pos)) /*!< SPI_SCK     */
#define GPIO_PA04_AF_SPI_CS()      MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN04_SEL_SEL_Pos)) /*!< SPI_CS      */
#define GPIO_PA05_AF_CTIM0_ETR()   MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN05_SEL_SEL_Pos)) /*!< CTIM0_ETR   */
#define GPIO_PA06_AF_LPUART0_RXD() MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN06_SEL_SEL_Pos)) /*!< LPUART0_RXD */
#define GPIO_PA07_AF_LPUART0_TXD() MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN07_SEL_SEL_Pos)) /*!< LPUART0_TXD */
#define GPIO_PA08_AF_LPUART1_TXD() MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN08_SEL_SEL_Pos)) /*!< LPUART1_TXD */
#define GPIO_PA09_AF_LPUART1_RXD() MODIFY_REG(GPIOA->PIN09_SEL, GPIO_PIN09_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN09_SEL_SEL_Pos)) /*!< LPUART1_RXD */
#define GPIO_PA10_AF_HSI2C_SDA()   MODIFY_REG(GPIOA->PIN10_SEL, GPIO_PIN10_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN10_SEL_SEL_Pos)) /*!< HSI2C_SDA   */
#define GPIO_PA11_AF_HSI2C_SCL()   MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN11_SEL_SEL_Pos)) /*!< HSI2C_SCL   */
#define GPIO_PA13_AF_CTIM0_TOG()   MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN13_SEL_SEL_Pos)) /*!< CTIM0_TOG   */
#define GPIO_PA14_AF_CTIM0_TOGN()  MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN14_SEL_SEL_Pos)) /*!< CTIM0_TOGN  */
#define GPIO_PA15_AF_CTIM0_ETR()   MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN15_SEL_SEL_Pos)) /*!< CTIM0_ETR   */
#define GPIO_PB00_AF_ATIM3_ETR()   MODIFY_REG(GPIOB->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN00_SEL_SEL_Pos)) /*!< ATIM3_ETR   */
/**
 * @}
 */

/**
 * @defgroup GPIO_AF7_Macros GPIO复用功能AF7宏定义
 * @{
 */
#define GPIO_PA00_AF_ATIM3_GATE()   MODIFY_REG(GPIOA->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN00_SEL_SEL_Pos)) /*!< ATIM3_GATE   */
#define GPIO_PA01_AF_HSI2C_SCL()    MODIFY_REG(GPIOA->PIN01_SEL, GPIO_PIN01_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN01_SEL_SEL_Pos)) /*!< HSI2C_SCL    */
#define GPIO_PA02_AF_HSI2C_SDA()    MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN02_SEL_SEL_Pos)) /*!< HSI2C_SDA    */
#define GPIO_PA04_AF_ATIM3_BK()     MODIFY_REG(GPIOA->PIN04_SEL, GPIO_PIN04_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN04_SEL_SEL_Pos)) /*!< ATIM3_BK     */
#define GPIO_PA05_AF_ATIM3_ETR()    MODIFY_REG(GPIOA->PIN05_SEL, GPIO_PIN05_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN05_SEL_SEL_Pos)) /*!< ATIM3_ETR    */
#define GPIO_PA06_AF_LVD_OUT()      MODIFY_REG(GPIOA->PIN06_SEL, GPIO_PIN06_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN06_SEL_SEL_Pos)) /*!< LVD_OUT      */
#define GPIO_PA07_AF_ATIM3_GATE()   MODIFY_REG(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN07_SEL_SEL_Pos)) /*!< ATIM3_GATE   */
#define GPIO_PA08_AF_IR_OUT()       MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN08_SEL_SEL_Pos)) /*!< IR_OUT       */
#define GPIO_PA11_AF_CTRIM_ETRTOG() MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN11_SEL_SEL_Pos)) /*!< CTRIM_ETRTOG */
#define GPIO_PA12_AF_LPUART0_RTS()  MODIFY_REG(GPIOA->PIN12_SEL, GPIO_PIN12_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN12_SEL_SEL_Pos)) /*!< LPUART0_RTS  */
#define GPIO_PA13_AF_ATIM3_BK()     MODIFY_REG(GPIOA->PIN13_SEL, GPIO_PIN13_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN13_SEL_SEL_Pos)) /*!< ATIM3_BK     */
#define GPIO_PA14_AF_TCLK_OUT()     MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN14_SEL_SEL_Pos)) /*!< TCLK_OUT     */
#define GPIO_PA15_AF_RTC_1HZ()      MODIFY_REG(GPIOA->PIN15_SEL, GPIO_PIN15_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN15_SEL_SEL_Pos)) /*!< RTC_1HZ      */
#define GPIO_PB00_AF_ATIM3_BK()     MODIFY_REG(GPIOB->PIN00_SEL, GPIO_PIN00_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN00_SEL_SEL_Pos)) /*!< ATIM3_BK     */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_Data_Action_Macros GPIO数据操作全局宏定义
 * @{
 */

/**
 * @defgroup GPIO_Data_Read_Macros GPIO数据读全局宏定义
 * @{
 */
#define GPIO_PORTA_READ() READ_REG_BIT(GPIOA->IN, GPIO_PIN_ALL) /*!< READ PIN ALL BIT */

#define GPIO_PA00_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_00) /*!< READ GPIOA PIN 00 BIT */
#define GPIO_PA01_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_01) /*!< READ GPIOA PIN 01 BIT */
#define GPIO_PA02_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_02) /*!< READ GPIOA PIN 02 BIT */
#define GPIO_PA03_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_03) /*!< READ GPIOA PIN 03 BIT */
#define GPIO_PA04_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_04) /*!< READ GPIOA PIN 04 BIT */
#define GPIO_PA05_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_05) /*!< READ GPIOA PIN 05 BIT */
#define GPIO_PA06_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_06) /*!< READ GPIOA PIN 06 BIT */
#define GPIO_PA07_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_07) /*!< READ GPIOA PIN 07 BIT */
#define GPIO_PA08_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_08) /*!< READ GPIOA PIN 08 BIT */
#define GPIO_PA09_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_09) /*!< READ GPIOA PIN 09 BIT */
#define GPIO_PA10_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_10) /*!< READ GPIOA PIN 10 BIT */
#define GPIO_PA11_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_11) /*!< READ GPIOA PIN 11 BIT */
#define GPIO_PA12_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_12) /*!< READ GPIOA PIN 12 BIT */
#define GPIO_PA13_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_13) /*!< READ GPIOA PIN 13 BIT */
#define GPIO_PA14_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_14) /*!< READ GPIOA PIN 14 BIT */
#define GPIO_PA15_READ()  READ_REG_BIT(GPIOA->IN, GPIO_PIN_15) /*!< READ GPIOA PIN 15 BIT */

#define GPIO_PB00_READ()  READ_REG_BIT(GPIOB->IN, GPIO_PIN_00) /*!< READ GPIOB PIN 00 BIT */

/**
 * @}
 */

/**
 * @defgroup GPIO_Data_Write_Macros GPIO数据写全局宏定义
 * @{
 */
#define GPIO_PORTA_WRITE(uint16_value)        WRITE_REG(GPIOA->OUT, (uint16_value))                                                /*!< PORTA WRITE */
#define GPIO_PORTA_WRITE_ATOMIC(uint16_value) WRITE_REG(GPIOA->BSETCLR, (((uint32_t)(uint16_value) << 0x10u) | (~(uint16_value)))) /*!< PORTA WRITE ATOMIC */
/**
 * @}
 */

/**
 * @defgroup GPIO_Data_Set_Macros GPIO数据写1全局宏定义
 * @{
 */
#define GPIO_PORTA_SET(pins) WRITE_REG(GPIOA->BSET, (pins)) /*!< SET GPIOA PIN ALL BIT */

#define GPIO_PA00_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_00) /*!< SET GPIOA PIN 00 BIT */
#define GPIO_PA01_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_01) /*!< SET GPIOA PIN 01 BIT */
#define GPIO_PA02_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_02) /*!< SET GPIOA PIN 02 BIT */
#define GPIO_PA03_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_03) /*!< SET GPIOA PIN 03 BIT */
#define GPIO_PA04_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_04) /*!< SET GPIOA PIN 04 BIT */
#define GPIO_PA05_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_05) /*!< SET GPIOA PIN 05 BIT */
#define GPIO_PA06_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_06) /*!< SET GPIOA PIN 06 BIT */
#define GPIO_PA07_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_07) /*!< SET GPIOA PIN 07 BIT */
#define GPIO_PA08_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_08) /*!< SET GPIOA PIN 08 BIT */
#define GPIO_PA09_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_09) /*!< SET GPIOA PIN 09 BIT */
#define GPIO_PA10_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_10) /*!< SET GPIOA PIN 10 BIT */
#define GPIO_PA11_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_11) /*!< SET GPIOA PIN 11 BIT */
#define GPIO_PA12_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_12) /*!< SET GPIOA PIN 12 BIT */
#define GPIO_PA13_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_13) /*!< SET GPIOA PIN 13 BIT */
#define GPIO_PA14_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_14) /*!< SET GPIOA PIN 14 BIT */
#define GPIO_PA15_SET()      WRITE_REG(GPIOA->BSET, GPIO_PIN_15) /*!< SET GPIOA PIN 15 BIT */
/**
 * @}
 */

/**
 * @defgroup GPIO_Data_Reset_Macros GPIO数据清0全局宏定义
 * @{
 */
#define GPIO_PORTA_RESET(pins) WRITE_REG(GPIOA->BCLR, (pins)) /*!< RESET PINS */

#define GPIO_PA00_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_00) /*!< RESET GPIOA PIN 00 */
#define GPIO_PA01_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_01) /*!< RESET GPIOA PIN 01 */
#define GPIO_PA02_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_02) /*!< RESET GPIOA PIN 02 */
#define GPIO_PA03_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_03) /*!< RESET GPIOA PIN 03 */
#define GPIO_PA04_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_04) /*!< RESET GPIOA PIN 04 */
#define GPIO_PA05_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_05) /*!< RESET GPIOA PIN 05 */
#define GPIO_PA06_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_06) /*!< RESET GPIOA PIN 06 */
#define GPIO_PA07_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_07) /*!< RESET GPIOA PIN 07 */
#define GPIO_PA08_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_08) /*!< RESET GPIOA PIN 08 */
#define GPIO_PA09_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_09) /*!< RESET GPIOA PIN 09 */
#define GPIO_PA10_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_10) /*!< RESET GPIOA PIN 10 */
#define GPIO_PA11_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_11) /*!< RESET GPIOA PIN 11 */
#define GPIO_PA12_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_12) /*!< RESET GPIOA PIN 12 */
#define GPIO_PA13_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_13) /*!< RESET GPIOA PIN 13 */
#define GPIO_PA14_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_14) /*!< RESET GPIOA PIN 14 */
#define GPIO_PA15_RESET()      WRITE_REG(GPIOA->BCLR, GPIO_PIN_15) /*!< RESET GPIOA PIN 15 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_CTRL1_Func_Config_Macros GPIO辅助功能配置寄存器1全局宏定义
 * @{
 */

/**
 * @defgroup GPIO_CTRL1_HSI2C_LSEL_Voltage_Select GPIO辅助功能 HSI2C I/O信号有效电平选择类型定义
 * @{
 */
#define GPIO_PA02_PA11_AF_CTRL1_HSI2C_LSEL_NORMAL_VOLTAGE_SET() \
    do \
    { \
        MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN02_SEL_SEL_Pos)); \
        MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN11_SEL_SEL_Pos)); \
        CLR_REG_BIT(GPIOAUX->CTRL1, GPIOAUX_CTRL1_HSI2C_LSEL_Msk); \
    } while (0) /*!< 输入电平正常识别   */

#define GPIO_PA02_PA11_AF_CTRL1_HSI2C_LSEL_LOW_VOLTAGE_SET() \
    do \
    { \
        MODIFY_REG(GPIOA->PIN02_SEL, GPIO_PIN02_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN02_SEL_SEL_Pos)); \
        MODIFY_REG(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk, (GPIO_AF6 << GPIO_PIN11_SEL_SEL_Pos)); \
        SET_REG_BIT(GPIOAUX->CTRL1, GPIOAUX_CTRL1_HSI2C_LSEL_Msk); \
    } while (0) /*!< 输入电平低电压识别 */
/**
 * @}
 */

/**
 * @defgroup GPIO_CTRL1_IR_POL_Polarity_Select GPIO辅助功能IR输出极性选择类型定义
 * @{
 */
#define GPIO_PA08_AF_CTRL1_IR_P_SET() \
    do \
    { \
        MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN08_SEL_SEL_Pos)); \
        CLR_REG_BIT(GPIOAUX->CTRL1, GPIOAUX_CTRL1_IR_POL_Msk); \
    } while (0) /*!< IR正向输出 */

#define GPIO_PA08_AF_CTRL1_IR_N_SET() \
    do \
    { \
        MODIFY_REG(GPIOA->PIN08_SEL, GPIO_PIN08_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN08_SEL_SEL_Pos)); \
        SET_REG_BIT(GPIOAUX->CTRL1, GPIOAUX_CTRL1_IR_POL_Msk); \
    } while (0) /*!< IR反向输出 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_CTRL2_Func_Config_Macros GPIO辅助功能配置寄存器2全局宏定义
 * @{
 */

/**
 * @defgroup GPIO_CTRL2_TCLK_Src_Div_Select GPIO辅助功能TCLK输出信号源和分频选择类型定义
 * @{
 */
#define PA14_AF_TCLK_OUT_SET(sel, div) \
    do \
    { \
        MODIFY_REG(GPIOA->PIN14_SEL, GPIO_PIN14_SEL_SEL_Msk, (GPIO_AF7 << GPIO_PIN14_SEL_SEL_Pos)); \
        MODIFY_REG(GPIOAUX->CTRL2, GPIOAUX_CTRL2_TCLK_DIV_Msk, ((div) << GPIOAUX_CTRL2_TCLK_DIV_Pos)); \
        MODIFY_REG(GPIOAUX->CTRL2, GPIOAUX_CTRL2_TCLK_SEL_Msk, ((sel) << GPIOAUX_CTRL2_TCLK_SEL_Pos)); \
    } while (0) /*!< PA14_AF_TCLK设置 */

#define GPIO_PA14_AF_TCLK_OUT_RC48M_DIV1() PA14_AF_TCLK_OUT_SET(0, 0) /*!< PA14 RC48M TCLK/1 */
#define GPIO_PA14_AF_TCLK_OUT_RC48M_DIV2() PA14_AF_TCLK_OUT_SET(0, 1) /*!< PA14 RC48M TCLK/2 */
#define GPIO_PA14_AF_TCLK_OUT_RC48M_DIV4() PA14_AF_TCLK_OUT_SET(0, 2) /*!< PA14 RC48M TCLK/4 */
#define GPIO_PA14_AF_TCLK_OUT_RC48M_DIV8() PA14_AF_TCLK_OUT_SET(0, 3) /*!< PA14 RC48M TCLK/8 */
#define GPIO_PA14_AF_TCLK_OUT_RCL_DIV1()   PA14_AF_TCLK_OUT_SET(1, 0) /*!< PA14 RCL TCLK/1 */
#define GPIO_PA14_AF_TCLK_OUT_RCL_DIV2()   PA14_AF_TCLK_OUT_SET(1, 1) /*!< PA14 RCL TCLK/2 */
#define GPIO_PA14_AF_TCLK_OUT_RCL_DIV4()   PA14_AF_TCLK_OUT_SET(1, 2) /*!< PA14 RCL TCLK/4 */
#define GPIO_PA14_AF_TCLK_OUT_RCL_DIV8()   PA14_AF_TCLK_OUT_SET(1, 3) /*!< PA14 RCL TCLK/8 */
#define GPIO_PA14_AF_TCLK_OUT_HCLK_DIV1()  PA14_AF_TCLK_OUT_SET(2, 0) /*!< PA14 HCLK TCLK/1 */
#define GPIO_PA14_AF_TCLK_OUT_HCLK_DIV2()  PA14_AF_TCLK_OUT_SET(2, 1) /*!< PA14 HCLK TCLK/2 */
#define GPIO_PA14_AF_TCLK_OUT_HCLK_DIV4()  PA14_AF_TCLK_OUT_SET(2, 2) /*!< PA14 HCLK TCLK/4 */
#define GPIO_PA14_AF_TCLK_OUT_HCLK_DIV8()  PA14_AF_TCLK_OUT_SET(2, 3) /*!< PA14 HCLK TCLK/8 */
#define GPIO_PA14_AF_TCLK_OUT_XTL_DIV1()   PA14_AF_TCLK_OUT_SET(3, 0) /*!< PA14 XTL TCLK/1 */
#define GPIO_PA14_AF_TCLK_OUT_XTL_DIV2()   PA14_AF_TCLK_OUT_SET(3, 1) /*!< PA14 XTL TCLK/2 */
#define GPIO_PA14_AF_TCLK_OUT_XTL_DIV4()   PA14_AF_TCLK_OUT_SET(3, 2) /*!< PA14 XTL TCLK/4 */
#define GPIO_PA14_AF_TCLK_OUT_XTL_DIV8()   PA14_AF_TCLK_OUT_SET(3, 3) /*!< PA14 XTL TCLK/8 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_TIMES_Func_Config_Macros GPIO辅助功能定时器配置全局宏定义
 * @{
 */
/**
 * @defgroup GPIO_TIMES_ATIM3_ETR_Func_Select GPIO辅助功能定时器ATIM3_ETR输入选择定义
 * @{
 */
#define GPIO_TIMES_ATIM3_E_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_ATIM3_E_Msk, (0x0u << GPIOAUX_TIMES_ATIM3_E_Pos)) /*!< ATIM3定时器ETR输入选择 PXY_SEL */
#define GPIO_TIMES_ATIM3_E_LPUART0_RXD() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_ATIM3_E_Msk, (0x1u << GPIOAUX_TIMES_ATIM3_E_Pos)) /*!< ATIM3定时器ETR输入选择 LPUART0_RXD */
#define GPIO_TIMES_ATIM3_E_LPUART1_RXD() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_ATIM3_E_Msk, (0x2u << GPIOAUX_TIMES_ATIM3_E_Pos)) /*!< ATIM3定时器ETR输入选择 LPUART1_RXD */
#define GPIO_TIMES_ATIM3_E_VC0_OUT() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_ATIM3_E_Msk, (0x3u << GPIOAUX_TIMES_ATIM3_E_Pos)) /*!< ATIM3定时器ETR输入选择 VC0_OUT */
#define GPIO_TIMES_ATIM3_E_LVD_OUT() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_ATIM3_E_Msk, (0x4u << GPIOAUX_TIMES_ATIM3_E_Pos)) /*!< ATIM3定时器ETR输入选择 LVD_OUT */

/**
 * @}
 */

/**
 * @defgroup GPIO_TIMES_CTIM1_ETR_Func_Select GPIO辅助功能定时器CTIM1_ETR输入选择定义
 * @{
 */
#define GPIO_TIMES_CTIM1_E_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM1_E_Msk, (0x0u << GPIOAUX_TIMES_CTIM1_E_Pos)) /*!< CTIM1定时器ETR输入选择 PXY_SEL */
#define GPIO_TIMES_CTIM1_E_LPUART1_RXD() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM1_E_Msk, (0x1u << GPIOAUX_TIMES_CTIM1_E_Pos)) /*!< CTIM1定时器ETR输入选择 LPUART1_RXD */
#define GPIO_TIMES_CTIM1_E_VC1_OUT() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM1_E_Msk, (0x2u << GPIOAUX_TIMES_CTIM1_E_Pos)) /*!< CTIM1定时器ETR输入选择 VC1_OUT */

/**
 * @}
 */

/**
 * @defgroup GPIO_TIMES_CTIM0_ETR_Func_Select GPIO辅助功能定时器CTIM0_ETR输入选择定义
 * @{
 */
#define GPIO_TIMES_CTIM0_E_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM0_E_Msk, (0x0u << GPIOAUX_TIMES_CTIM0_E_Pos)) /*!< CTIM0定时器ETR输入选择 PXY_SEL */
#define GPIO_TIMES_CTIM0_E_LPUART0_RXD() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM0_E_Msk, (0x1u << GPIOAUX_TIMES_CTIM0_E_Pos)) /*!< CTIM0定时器ETR输入选择 LPUART0_RXD */
#define GPIO_TIMES_CTIM0_E_VC0_OUT() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM0_E_Msk, (0x2u << GPIOAUX_TIMES_CTIM0_E_Pos)) /*!< CTIM0定时器ETR输入选择 VC0_OUT */
#define GPIO_TIMES_CTIM0_E_LVD_OUT() \
    MODIFY_REG(GPIOAUX->TIMES, GPIOAUX_TIMES_CTIM0_E_Msk, (0x3u << GPIOAUX_TIMES_CTIM0_E_Pos)) /*!< CTIM0定时器ETR输入选择 LVD_OUT */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_TIMCPS_Func_Config_Macros GPIO辅助功能定时器捕获输入配置全局宏定义
 * @{
 */
/**
 * @defgroup GPIO_TIMCPS_ATIM3_C0A_Func_Select GPIO辅助功能定时器ATIM3_C0A输入选择定义
 * @{
 */
#define GPIO_TIMCPS_ATIM3_C0A_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_ATIM3_C0A_Msk, (0x0u << GPIOAUX_TIMCPS_ATIM3_C0A_Pos)) /*!< ATIM3定时器CH0A输入选择 PXY_SEL */
#define GPIO_TIMCPS_ATIM3_C0A_LPUART0_RXD() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_ATIM3_C0A_Msk, (0x1u << GPIOAUX_TIMCPS_ATIM3_C0A_Pos)) /*!< ATIM3定时器CH0A输入选择 LPUART0_RXD */
#define GPIO_TIMCPS_ATIM3_C0A_LPUART1_RXD() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_ATIM3_C0A_Msk, (0x2u << GPIOAUX_TIMCPS_ATIM3_C0A_Pos)) /*!< ATIM3定时器CH0A输入选择 LPUART1_RXD */
#define GPIO_TIMCPS_ATIM3_C0A_VC1_OUT() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_ATIM3_C0A_Msk, (0x3u << GPIOAUX_TIMCPS_ATIM3_C0A_Pos)) /*!< ATIM3定时器CH0A输入选择 VC1_OUT */
/**
 * @}
 */

/**
 * @defgroup GPIO_TIMCPS_CTIM1_C0_Func_Select GPIO辅助功能定时器CTIM1_C0输入选择定义
 * @{
 */
#define GPIO_TIMCPS_CTIM1_C0_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM1_C0_Msk, (0x0u << GPIOAUX_TIMCPS_CTIM1_C0_Pos)) /*!< CTIM1定时器CH1输入选择 PXY_SEL */
#define GPIO_TIMCPS_CTIM1_C0_LPUART0_RXD() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM1_C0_Msk, (0x1u << GPIOAUX_TIMCPS_CTIM1_C0_Pos)) /*!< CTIM1定时器CH1输入选择 LPUART0_RXD */
#define GPIO_TIMCPS_CTIM1_C0_VC0_OUT_O() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM1_C0_Msk, (0x2u << GPIOAUX_TIMCPS_CTIM1_C0_Pos)) /*!< CTIM1定时器CH1输入选择 VC0_OUT_O */
/**
 * @}
 */

/**
 * @defgroup GPIO_TIMCPS_CTIM0_C0_Func_Select GPIO辅助功能定时器CTIM0_C0输入选择定义
 * @{
 */
#define GPIO_TIMCPS_CTIM0_C0_PXY_SEL() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM0_C0_Msk, (0x0u << GPIOAUX_TIMCPS_CTIM0_C0_Pos)) /*!< CTIM0定时器CH0输入选择 PXY_SEL */
#define GPIO_TIMCPS_CTIM0_C0_LPUART1_RXD() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM0_C0_Msk, (0x1u << GPIOAUX_TIMCPS_CTIM0_C0_Pos)) /*!< CTIM0定时器CH0输入选择 LPUART1_RXD */
#define GPIO_TIMCPS_CTIM0_C0_VC1_OUT() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM0_C0_Msk, (0x2u << GPIOAUX_TIMCPS_CTIM0_C0_Pos)) /*!< CTIM0定时器CH0输入选择 VC1_OUT */
#define GPIO_TIMCPS_CTIM0_C0_LVD_OUT() \
    MODIFY_REG(GPIOAUX->TIMCPS, GPIOAUX_TIMCPS_CTIM0_C0_Msk, (0x3u << GPIOAUX_TIMCPS_CTIM0_C0_Pos)) /*!< CTIM0定时器CH0输入选择 LVD_OUT */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup GPIO_FLTCFG_Func_Config_Macros GPIO滤波功能配置配置全局宏定义
 * @{
 */

/**
 * @defgroup GPIO_FLTCFG_Filter_Func_Config GPIO滤波功能配置类型定义
 * @{
 */
#define PA0_FILTER_SET(sel, div) \
    do \
    { \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_DIV_Msk, ((div) << GPIOAUX_FLTCFG_FCLK_DIV_Pos)); \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_SEL_Msk, ((sel) << GPIOAUX_FLTCFG_FCLK_SEL_Pos)); \
        SET_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PA0FLT_EN_Msk); \
    } while (0) /*!< PA0_FILTER设置 */

#define PA8_FILTER_SET(sel, div) \
    do \
    { \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_DIV_Msk, ((div) << GPIOAUX_FLTCFG_FCLK_DIV_Pos)); \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_SEL_Msk, ((sel) << GPIOAUX_FLTCFG_FCLK_SEL_Pos)); \
        SET_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PA8FLT_EN_Msk); \
    } while (0) /*!< PA8_FILTER设置 */

#define PB0_FILTER_SET(sel, div) \
    do \
    { \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_DIV_Msk, ((div) << GPIOAUX_FLTCFG_FCLK_DIV_Pos)); \
        MODIFY_REG(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_FCLK_SEL_Msk, ((sel) << GPIOAUX_FLTCFG_FCLK_SEL_Pos)); \
        SET_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PB0FLT_EN_Msk); \
    } while (0) /*!< PB0_FILTER设置 */

#define PA0_FILTER_OFF()               CLR_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PA0FLT_EN_Msk) /*!< PA0_FILTER关闭 */
#define PA8_FILTER_OFF()               CLR_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PA8FLT_EN_Msk) /*!< PA8_FILTER关闭 */
#define PB0_FILTER_OFF()               CLR_REG_BIT(GPIOAUX->FLTCFG, GPIOAUX_FLTCFG_PB0FLT_EN_Msk) /*!< PB0_FILTER关闭 */

#define GPIO_PA0_FILTER_OFF()          PA0_FILTER_OFF()     /*!< PA0 FILTER OFF */
#define GPIO_PA0_FILTER_HCLK_DIV1()    PA0_FILTER_SET(0, 0) /*!< PA0 HCLK FCLK/1 */
#define GPIO_PA0_FILTER_HCLK_DIV4()    PA0_FILTER_SET(0, 1) /*!< PA0 HCLK FCLK/4 */
#define GPIO_PA0_FILTER_HCLK_DIV16()   PA0_FILTER_SET(0, 2) /*!< PA0 HCLK FCLK/16 */
#define GPIO_PA0_FILTER_HCLK_DIV64()   PA0_FILTER_SET(0, 3) /*!< PA0 HCLK FCLK/64 */
#define GPIO_PA0_FILTER_RC256K_DIV1()  PA0_FILTER_SET(1, 0) /*!< PA0 RC256K FCLK/1 */
#define GPIO_PA0_FILTER_RC256K_DIV4()  PA0_FILTER_SET(1, 1) /*!< PA0 RC256K FCLK/4 */
#define GPIO_PA0_FILTER_RC256K_DIV16() PA0_FILTER_SET(1, 2) /*!< PA0 RC256K FCLK/16 */
#define GPIO_PA0_FILTER_RC256K_DIV64() PA0_FILTER_SET(1, 3) /*!< PA0 RC256K FCLK/64 */

#define GPIO_PA8_FILTER_OFF()          PA8_FILTER_OFF()     /*!< PA8 FILTER OFF */
#define GPIO_PA8_FILTER_HCLK_DIV1()    PA8_FILTER_SET(0, 0) /*!< PA8 HCLK FCLK/1 */
#define GPIO_PA8_FILTER_HCLK_DIV4()    PA8_FILTER_SET(0, 1) /*!< PA8 HCLK FCLK/4 */
#define GPIO_PA8_FILTER_HCLK_DIV16()   PA8_FILTER_SET(0, 2) /*!< PA8 HCLK FCLK/16 */
#define GPIO_PA8_FILTER_HCLK_DIV64()   PA8_FILTER_SET(0, 3) /*!< PA8 HCLK FCLK/64 */
#define GPIO_PA8_FILTER_RC256K_DIV1()  PA8_FILTER_SET(1, 0) /*!< PA8 RC256K FCLK/1 */
#define GPIO_PA8_FILTER_RC256K_DIV4()  PA8_FILTER_SET(1, 1) /*!< PA8 RC256K FCLK/4 */
#define GPIO_PA8_FILTER_RC256K_DIV16() PA8_FILTER_SET(1, 2) /*!< PA8 RC256K FCLK/16 */
#define GPIO_PA8_FILTER_RC256K_DIV64() PA8_FILTER_SET(1, 3) /*!< PA8 RC256K FCLK/64 */

#define GPIO_PB0_FILTER_OFF()          PB0_FILTER_OFF()     /*!< PB0 FILTER OFF */
#define GPIO_PB0_FILTER_HCLK_DIV1()    PB0_FILTER_SET(0, 0) /*!< PB0 HCLK FCLK/1 */
#define GPIO_PB0_FILTER_HCLK_DIV4()    PB0_FILTER_SET(0, 1) /*!< PB0 HCLK FCLK/4 */
#define GPIO_PB0_FILTER_HCLK_DIV16()   PB0_FILTER_SET(0, 2) /*!< PB0 HCLK FCLK/16 */
#define GPIO_PB0_FILTER_HCLK_DIV64()   PB0_FILTER_SET(0, 3) /*!< PB0 HCLK FCLK/64 */
#define GPIO_PB0_FILTER_RC256K_DIV1()  PB0_FILTER_SET(1, 0) /*!< PB0 RC256K FCLK/1 */
#define GPIO_PB0_FILTER_RC256K_DIV4()  PB0_FILTER_SET(1, 1) /*!< PB0 RC256K FCLK/4 */
#define GPIO_PB0_FILTER_RC256K_DIV16() PB0_FILTER_SET(1, 2) /*!< PB0 RC256K FCLK/16 */
#define GPIO_PB0_FILTER_RC256K_DIV64() PB0_FILTER_SET(1, 3) /*!< PB0 RC256K FCLK/64 */
/**
 * @}
 */

/**
 * @defgroup GPIO_Init_Func_Macros GPIO初始化函数宏定义
 * @{
 */
#define GPIOA_Init(pstcgpioinit) GPIO_Init(GPIOA, (pstcgpioinit))
#define GPIOB_Init(pstcgpioinit) GPIO_Init(GPIOB, (pstcgpioinit))
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
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
 Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup GPIO_Global_Func GPIO全局函数定义
 * @{
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, stc_gpio_init_t *pstcGpioInit); /* GPIO初始化 */

boolean_t GPIO_IntFlagGet(GPIO_TypeDef *GPIOx, uint32_t u32Pin);   /* 中断状态获取 */
void      GPIO_IntFlagClear(GPIO_TypeDef *GPIOx, uint32_t u32Pin); /* 中断状态清除 */

void GPIO_StcInit(stc_gpio_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __GPIO_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
