/**
 *******************************************************************************
 * @file  hsi2c.c
 * @brief This file provides firmware functions to manage the HSI2C
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
#include "hsi2c.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_HSI2C HSI2C模块驱动库
 * @brief HSI2C Driver Library HSI2C模块驱动库
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
/**
 * @addtogroup HSI2C_Global_Variables HSI2C全局变量定义
 * @{
 */
en_hsi2c_status_machine_t enMasterStatusMachine = Hsi2cStatusStart; /* 主机状态机状态 */
stc_hsi2c_master_init_t   stcHsi2cMasterInit    = {0x0u};           /* 主机初始化结构体 */
stc_hsi2c_slave_init_t    stcHsi2cSlaveInit     = {0x0u};           /* 从机初始化结构体 */
stc_hsi2c_com_t           stcHsi2cCom           = {0x0u};           /* 通信结构体 */
/**
 * @}
 */
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
 * @defgroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */

/**
 * @addtogroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */

/**
 * @brief  HSI2C主机初始化
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cInit HSI2C主机配置结构体 @ref stc_hsi2c_master_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterInit(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    /* Master reset */
    if (pstcHsi2cInit->bResetBeforeInit)
    {
        HSI2C_MasterReset(HSI2Cx);
    }

    /* Debug enable setting */
    MODIFY_REG32(HSI2Cx->MCR, HSI2C_MCR_DBGEN_Msk, pstcHsi2cInit->u32EnableDebug);

    /* Master config register setting */
    HSI2C_MasterMcfgr1Config(HSI2Cx, (stc_hsi2c_master_config1_t *)(&pstcHsi2cInit->stcMasterConfig1));
    HSI2C_MasterMcfgr2Config(HSI2Cx, (stc_hsi2c_master_config2_t *)(&pstcHsi2cInit->stcMasterConfig2));
    HSI2C_MasterMcfgr3Config(HSI2Cx, (stc_hsi2c_master_config3_t *)(&pstcHsi2cInit->stcMasterConfig3));

    /* Baud rate setting */
    if (Ok != HSI2C_MasterBaudRateSet(HSI2Cx, pstcHsi2cInit, u32SrcClockHz))
    {
        return Error;
    }

    /* Master enable, slave disable */
    HSI2C_SlaveDisable(HSI2Cx);
    HSI2C_MasterEnable(HSI2Cx);

    return Ok;
}

/**
 * @brief  HSI2C主机波特率设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cInit HSI2C主机配置结构体 @ref stc_hsi2c_master_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterBaudRateSet(HSI2C_TypeDef *HSI2Cx, const stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    uint8_t  u8MasterEnableStatus = 0x0u;
    uint8_t  u8FilterScl          = 0x0u;
    uint8_t  u8Prescale           = 0x0u;
    uint32_t u32ClockCycle        = 0x0u;
    uint32_t u32SclLatency        = 0x0u;
    uint32_t u32SclPeriod         = 0x0u;
    uint32_t u32ErrorOffset       = 0x0u;
    uint32_t u32CalculateBaudRate = 0x0u;
    uint16_t u16Divider           = 1u;

    uint8_t  u8ClockHigh      = 0x0u;
    uint8_t  u8ClockLow       = 0x0u;
    uint8_t  u8HoldDelay      = 0x0u;
    uint8_t  u8DataValidDelay = 0x0u;
    uint8_t  u8BestClockCycle = 0x0u;
    uint8_t  u8BestPrescale   = 0x0u;
    uint8_t  u8BestDivider    = 0x0u;
    uint32_t u32BestError     = 0xFFFFFFFFu;

    /* Disable slave mode and backup master enable status */
    HSI2Cx->SCR0         = 0;
    u8MasterEnableStatus = (uint8_t)((HSI2Cx->MCR & HSI2C_MCR_MEN_Msk) >> HSI2C_MCR_MEN_Pos);
    HSI2Cx->MCR_f.MEN    = 0u;

    /* Baud rate = (u32SrcClockHz / 2 ^ PRESCALE) / (CLKHI + CLKLO + 2 + SCL_LATENCY)
     * SCL_LATENCY = ROUNDDOWN ( (2 + FILTSCL + SCL_RISETIME) / (2 ^ PRESCALE) )
     */
    u8FilterScl = (uint8_t)((HSI2Cx->MCFGR2 & HSI2C_MCFGR2_FILTSCL_Msk) >> HSI2C_MCFGR2_FILTSCL_Pos);
    for (u8Prescale = 0u; u8Prescale <= 7u; u8Prescale++)
    {
        /* Calculate the u32ClockCycle, u32ClockCycle = CLKLO + CLKHI, u16Divider = 2 ^ u8Prescale */
        u32SclLatency    = (2u + u8FilterScl) / u16Divider;
        uint32_t u32Temp = (uint32_t)((10u * u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / u16Divider + 5u) / 10u);
        if (u32Temp >= u32SclLatency + 2u)
        {
            u32ClockCycle = u32Temp - u32SclLatency - 2u;
        }
        else
        {
            u32ClockCycle = 0u;
        }

        if (u32ClockCycle > (120u - u32SclLatency))
        {
            u16Divider *= 2u;
            if (u16Divider == 256)
            {
                return Error; /* Invalid setting of source clock or baud rate */
            }
            else
            {
                continue;
            }
        }

        /* Calculate the computed baudrate and compare it with the desired baudrate */
        u32CalculateBaudRate = (u32SrcClockHz / (uint32_t)u16Divider) / ((uint32_t)u32ClockCycle + 2U + u32SclLatency);
        u32ErrorOffset       = pstcHsi2cInit->u32BaudRateHz > u32CalculateBaudRate ? pstcHsi2cInit->u32BaudRateHz - u32CalculateBaudRate :
                                                                                     u32CalculateBaudRate - pstcHsi2cInit->u32BaudRateHz;
        if (u32ErrorOffset < u32BestError)
        {
            u8BestPrescale   = u8Prescale;
            u8BestDivider    = u16Divider;
            u8BestClockCycle = u32ClockCycle;
            u32BestError     = u32ErrorOffset;

            /* Target baud rate is achieved */
            if (u32ErrorOffset == 0u)
            {
                break;
            }
        }
        u16Divider *= 2u;
    }

    u32SclLatency = (2u + u8FilterScl) / u8BestDivider;
    u32SclPeriod  = u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / u8BestDivider;
    /* Clock high period */
    u8ClockHigh = (u8BestClockCycle - u32SclLatency) / 2u;
    while (u8ClockHigh > (u8BestClockCycle - 52u * u32SclPeriod / 100u + 1u))
    {
        if (u8ClockHigh > 1u)
        {
            u8ClockHigh--;
        }
        else
        {
            u8ClockHigh = 1u;
            break;
        }
    }
    if (u8ClockHigh < 1)
    {
        u8ClockHigh++;
    }

    /* Clock low period */
    if (u8BestClockCycle >= u8ClockHigh)
    {
        u8ClockLow = (uint32_t)u8BestClockCycle - (uint32_t)u8ClockHigh;
    }
    else
    {
        return Error; /* Invalid setting of source clock or baud rate */
    }
    if (u8ClockHigh >= u8ClockLow)
    {
        return Error; /* Invalid setting of source clock or baud rate */
    }
    /* Setup hold delay */
    u8HoldDelay = (uint8_t)(u32SclPeriod / 2u) - 1u;
    /* Data valid delay */
    u8DataValidDelay = (uint8_t)(u32SclPeriod / 4u) - 1u;
    /* Filter SDA */
    if ((u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u) > (u8BestDivider + 2u))
    {
        /* Read out the FILTSDA configuration, if it is smaller than expected, change the setting. */
        uint8_t u8FilterSda = (uint8_t)((HSI2Cx->MCFGR2 & HSI2C_MCFGR2_FILTSDA_Msk) >> HSI2C_MCFGR2_FILTSDA_Pos);
        if (u8FilterSda < (u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u - u8BestDivider - 2u))
        {
            u8FilterSda = (uint8_t)(u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u) - u8BestDivider - 2u;
        }
        MODIFY_REG32(HSI2Cx->MCFGR2, HSI2C_MCFGR2_FILTSDA_Msk, ((uint32_t)u8FilterSda << HSI2C_MCFGR2_FILTSDA_Pos));
    }

    /* Set CLKHI, CLKLO, SETHOLD, DATAVD value */
    HSI2Cx->MCCR0 = ((uint32_t)u8ClockHigh << HSI2C_MCCR0_CLKHI_Pos) | ((uint32_t)u8ClockLow << HSI2C_MCCR0_CLKLO_Pos)
                    | ((uint32_t)u8HoldDelay << HSI2C_MCCR0_SETHOLD_Pos) | ((uint32_t)u8DataValidDelay << HSI2C_MCCR0_DATAVD_Pos);

    /* Set prescale value */
    MODIFY_REG32(HSI2Cx->MCFGR1, HSI2C_MCFGR1_PRESCALE_Msk, ((uint32_t)u8BestPrescale << HSI2C_MCFGR1_PRESCALE_Pos));

    /* Restore master enable status */
    HSI2Cx->MCR_f.MEN = u8MasterEnableStatus;

    return Ok;
}
/**
 * @brief  HSI2C主机中断传输设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterTransferInt(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size)
{
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_MasterFlagGet(HSI2Cx, HSI2C_MASTER_FLAG_BBF)) /* Bus busy */
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.HSI2CxBaseAddr = HSI2Cx;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = (uint16_t)stcHsi2cCom.u32Len;

            HSI2C_MasterIntDisable(HSI2Cx, HSI2C_MASTER_INT_ALL);     /* Disable interrupts */
            HSI2C_MasterFlagClear(HSI2Cx, HSI2C_MASTER_FLAG_CLR_ALL); /* Clear flags */

            HSI2Cx->MCFGR1 &= ~HSI2C_MCFGR1_AUTOSTOP_Msk; /* Disable auto-stop */

            HSI2C_MasterIntEnable(HSI2Cx, HSI2C_MASTER_INT_ALL); /* Enable interrupts */
        }
    }
    else
    {
        enResult = Error;
    }

    return enResult;
}

/**
 * @brief  HSI2C主机状态机控制（Start）
 * @retval None
 */
void HSI2C_MasterStatusMachineStart(void)
{
    if (stcHsi2cMasterInit.u8SubAddrSize != 0x0u) /* 需要发送Sub address */
    {
        HSI2C_MasterStart(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterWriteSlaveRead); /* Start 主机写，从机读 */
        enMasterStatusMachine = Hsi2cStatusSubAddr;                                                               /* 状态：发送Sub address */
    }
    else /* 无需发送Sub address */
    {
        if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
        {
            HSI2C_MasterStart(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterWriteSlaveRead); /* Start 主机写，从机读 */
            enMasterStatusMachine = Hsi2cStatusTransData;                                                             /* 状态：传送数据 */
        }
        else /* 主机读，从机写 */
        {
            HSI2C_MasterStart(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterReadSlaveWrite); /* Start 主机读，从机写 */
            enMasterStatusMachine = Hsi2cStatusRxCmd;                                                                 /* 状态：接收命令 */
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Sub address）
 * @retval None
 */
void HSI2C_MasterStatusMachineSubAddr(void)
{
    if (stcHsi2cCom.u32DataIndex < stcHsi2cMasterInit.u8SubAddrSize) /* 发送Sub address */
    {
        stcHsi2cCom.HSI2CxBaseAddr->MTDR =
            HSI2C_CMD_TX_DATA | (uint32_t)(stcHsi2cMasterInit.u8SubAddr[stcHsi2cMasterInit.u8SubAddrSize - stcHsi2cCom.u32DataIndex - 1]);
        stcHsi2cCom.u32DataIndex++;

        if (stcHsi2cCom.u32DataIndex >= stcHsi2cMasterInit.u8SubAddrSize)
        {                                                              /* Sub address已发送完成 */
            if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
            {
                enMasterStatusMachine = Hsi2cStatusTransData; /* 状态：传送数据 */
            }
            else /* 主机读，从机写 */
            {
                if (stcHsi2cMasterInit.u8SubAddrSize != 0x0u) /* 已发送Sub address */
                {
                    enMasterStatusMachine = Hsi2cStatusRestart; /* 状态：Restart */
                }
                else /* 未发送Sub address */
                {
                    enMasterStatusMachine = Hsi2cStatusRxCmd; /* 状态：接收命令 */
                }
            }
            stcHsi2cCom.u32DataIndex = 0;
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Restart）
 * @retval None
 */
void HSI2C_MasterStatusMachineRestart(void)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite)
    {
        HSI2C_MasterStart(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterReadSlaveWrite); /* Restart 主机读，从机写 */
        enMasterStatusMachine = Hsi2cStatusRxCmd;                                                                 /* 状态：接收命令 */
    }
}

/**
 * @brief
 * @retval None
 */
/**
 * @brief  HSI2C主机状态机控制（Receive command）
 * @param  [in] pu32RxLen 接收数据长度指针值
 * @retval None
 */
void HSI2C_MasterStatusMachineRxCmd(uint32_t *pu32RxLen)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite) /* 主机读，从机写 */
    {
        if (*pu32RxLen > 256U) /* Send receive and length(高字节) command */
        {
            stcHsi2cCom.HSI2CxBaseAddr->MTDR = (uint32_t)(HSI2C_CMD_RX_DATA) | (0xFFul << HSI2C_MTDR_DATA_Pos);
            *pu32RxLen                      -= 256U;
        }
        else /* Send receive and length(低字节) command */
        {
            stcHsi2cCom.HSI2CxBaseAddr->MTDR = (uint32_t)(HSI2C_CMD_RX_DATA) | ((uint32_t)(stcHsi2cCom.u32RxSize - 1U) << HSI2C_MTDR_DATA_Pos);
            enMasterStatusMachine            = Hsi2cStatusTransData; /* 状态：传送数据 */
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Data transfer）
 * @retval None
 */
void HSI2C_MasterStatusMachineTrans(void)
{
    if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len) /* Transfer length is finished */
    {
        if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
        {
            enMasterStatusMachine = Hsi2cStatusStop; /* 状态：Stop */
        }
        else /* 主机读，从机写 */
        {
            HSI2C_MasterStop(stcHsi2cCom.HSI2CxBaseAddr); /* Send stop command */
            enMasterStatusMachine = Hsi2cStatusWaitEnd;   /* 状态：等待结束 */
            /* Will send NACK automatically when Rx transfer size is finished */
        }
        stcHsi2cCom.u32DataIndex = 0;
    }
}

/**
 * @brief  HSI2C主机状态机控制（Stop）
 * @retval None
 */
void HSI2C_MasterStatusMachineStop(void)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
    {
        HSI2C_MasterStop(stcHsi2cCom.HSI2CxBaseAddr); /* Send stop command */
        enMasterStatusMachine = Hsi2cStatusWaitEnd;   /* 状态：等待结束 */
    }
}

/**
 * @brief  HSI2C主机轮询传输设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @param  [in] u32Timeout 传输超时时间
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 *           - ErrorTimeout：超时
 */
en_result_t HSI2C_MasterTransferPoll(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t    u32Flag  = 0;
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_MasterFlagGet(HSI2Cx, HSI2C_MASTER_FLAG_BBF))
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine = Hsi2cStatusStart;

            stcHsi2cCom.HSI2CxBaseAddr = HSI2Cx;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cCom.u32Len;

            HSI2C_MasterFlagClear(HSI2Cx, HSI2C_MASTER_FLAG_CLR_ALL); /* Clear flags */

            HSI2Cx->MCFGR1 &= ~HSI2C_MCFGR1_AUTOSTOP_Msk; /* Disable auto-stop */

            while (1)
            {
                if (0x0u == u32Timeout--)
                {
                    enResult = ErrorTimeout; /* 等待超时 */
                    break;
                }
                u32Flag                          = stcHsi2cCom.HSI2CxBaseAddr->MSR;
                stcHsi2cCom.HSI2CxBaseAddr->MSCR = u32Flag;

                if (Hsi2cComSuccess == HSI2C_MasterErrorGet(u32Flag))
                {
                    switch (enMasterStatusMachine)
                    {
                        case Hsi2cStatusStart:
                            HSI2C_MasterStatusMachineStart();
                            break;
                        case Hsi2cStatusSubAddr:
                            if ((u32Flag & HSI2C_MSR_TDF_Msk) == HSI2C_MSR_TDF_Msk)
                            {
                                HSI2C_MasterStatusMachineSubAddr();
                            }
                            break;
                        case Hsi2cStatusRestart:
                            if ((u32Flag & HSI2C_MSR_TDF_Msk) == HSI2C_MSR_TDF_Msk)
                            {
                                HSI2C_MasterStatusMachineRestart();
                            }
                            break;
                        case Hsi2cStatusRxCmd:
                            if ((u32Flag & HSI2C_MSR_TDF_Msk) == HSI2C_MSR_TDF_Msk)
                            {
                                HSI2C_MasterStatusMachineRxCmd(&stcHsi2cCom.u32RxSize);
                            }
                            break;
                        case Hsi2cStatusTransData:
                            if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len) /* Data transmit or receive */
                            {
                                if ((u32Flag & HSI2C_MSR_TDF_Msk) == HSI2C_MSR_TDF_Msk)
                                {
                                    if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* Transmit */
                                    {
                                        HSI2C_MasterWriteData(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++]);
                                    }
                                }
                                if ((u32Flag & HSI2C_MSR_RDF_Msk) == HSI2C_MSR_RDF_Msk)
                                {
                                    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite) /* Recieve */
                                    {
                                        if (Ok == HSI2C_MasterReadData(stcHsi2cCom.HSI2CxBaseAddr, &stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex]))
                                        {
                                            stcHsi2cCom.u32DataIndex++;
                                        }
                                    }
                                }
                            }
                            HSI2C_MasterStatusMachineTrans();
                            break;
                        case Hsi2cStatusStop:
                            if ((u32Flag & HSI2C_MSR_TDF_Msk) == HSI2C_MSR_TDF_Msk)
                            {
                                HSI2C_MasterStatusMachineStop();
                            }
                            break;
                        case Hsi2cStatusWaitEnd:
                            /* Wait for transfer end */
                            if (u32Flag & HSI2C_MSR_SDF_Msk)
                            {
                                stcHsi2cCom.enComStatus = Hsi2cComIdle;
                            }
                            break;
                        default:
                            break;
                    }

                    if (stcHsi2cCom.enComStatus == Hsi2cComIdle)
                    {
                        break; /* Transfer完成 */
                    }
                }
                else /* Error handling */
                {
                    /* Disable all master interrupts */
                    HSI2C_MasterIntDisable(stcHsi2cCom.HSI2CxBaseAddr, HSI2C_MASTER_INT_ALL);

                    /* Arbitration lost? */
                    if (u32Flag & HSI2C_MSR_ALF_Msk)
                    {
                        /* Reset master */
                        HSI2C_MasterReset(HSI2Cx);
                    }
                    /* Pin low timeout? */
                    else if (u32Flag & HSI2C_MSR_PLTF_Msk)
                    {
                        /* Reset master */
                        HSI2C_MasterReset(HSI2Cx);
                        /* ======================================= */
                        /* ==========       WARNING       ======== */
                        /* ======================================= */
                        /* 1. 根据实际情况添加代码处理引脚低条件      */
                        /* 2. 当引脚低超时持续时，PLTF不能被清除掉    */
                        /* 3. 在I2C可以开始启动条件之前，必须清除PLTF */
                    }
                    /* Master busy? */
                    else if (u32Flag & HSI2C_MSR_MBF_Msk)
                    {
                        /* Send stop command */
                        HSI2C_MasterStop(stcHsi2cCom.HSI2CxBaseAddr);
                    }
                    else
                    {
                        ;
                    }

                    stcHsi2cCom.enComStatus = Hsi2cComIdle;
                    enResult                = Error;
                    break;
                }
            }
        }
    }
    else
    {
        enResult = Error;
    }
    return enResult;
}

/**
 * @brief  HSI2C从机初始化
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cInit HSI2C从机配置结构体 @ref stc_hsi2c_slave_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval None
 */
void HSI2C_SlaveInit(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    /* Slave reset */
    if (pstcHsi2cInit->bResetBeforeInit)
    {
        HSI2C_SlaveReset(HSI2Cx);
    }

    /* Slave control register setting */
    HSI2C_SlaveScr1Config(HSI2Cx, (stc_hsi2c_slave_control1_t *)(&pstcHsi2cInit->stcSlaveConfig1));
    HSI2C_SlaveScr2Config(HSI2Cx, (stc_hsi2c_slave_control2_t *)(&pstcHsi2cInit->stcSlaveConfig2));

    /* Configure slave address */
    MODIFY_REG32(HSI2Cx->SADDR, HSI2C_SADDR_ADDR0_Msk | HSI2C_SADDR_ADDR1_Msk,
                 ((pstcHsi2cInit->u32SlaveAddr0) << HSI2C_SADDR_ADDR0_Pos) | ((pstcHsi2cInit->u32SlaveAddr1) << HSI2C_SADDR_ADDR1_Pos));

    /* Slave enable, master disable */
    HSI2C_MasterDisable(HSI2Cx);
    HSI2C_SlaveEnable(HSI2Cx);
}

/**
 * @brief  HSI2C从机中断传输设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_SlaveTransferInt(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size)
{
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_SlaveFlagGet(HSI2Cx, HSI2C_SLAVE_FLAG_BBF)) /* Bus busy */
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.HSI2CxBaseAddr = HSI2Cx;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cSlaveInit.u8SubAddrSize;

            HSI2C_SlaveIntDisable(HSI2Cx, HSI2C_SLAVE_INT_ALL);     /* Disable interrupts */
            HSI2C_SlaveFlagClear(HSI2Cx, HSI2C_SLAVE_FLAG_CLR_ALL); /* Clear flags */
            HSI2C_SlaveIntEnable(HSI2Cx, HSI2C_SLAVE_INT_ALL);      /* Enable interrupts */
        }
    }
    else
    {
        enResult = Error;
    }

    return enResult;
}

/**
 * @brief  HSI2C从机轮询传输设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @param  [in] u32Timeout 传输超时时间
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 *           - ErrorTimeout：超时
 */
en_result_t HSI2C_SlaveTransferPoll(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enResult = Ok;
    uint32_t    u32Flag  = 0;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_SlaveFlagGet(HSI2Cx, HSI2C_SLAVE_FLAG_BBF))
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.HSI2CxBaseAddr = HSI2Cx;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0U;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cSlaveInit.u8SubAddrSize;

            HSI2C_SlaveFlagClear(HSI2Cx, HSI2C_SLAVE_FLAG_CLR_ALL); /* Clear flags */

            while (1)
            {
                if (0x0u == u32Timeout--)
                {
                    enResult = ErrorTimeout; /* 等待超时 */
                    break;
                }

                u32Flag                          = stcHsi2cCom.HSI2CxBaseAddr->SSR;
                stcHsi2cCom.HSI2CxBaseAddr->SSCR = u32Flag;

                if (Hsi2cComSuccess == HSI2C_SlaveErrorGet(u32Flag))
                {
                    /* Receive */
                    if (u32Flag & HSI2C_SLAVE_FLAG_RDF)
                    {
                        uint32_t u32RxData = stcHsi2cCom.HSI2CxBaseAddr->SRDR;
                        if (!(u32RxData & HSI2C_SRDR_REMP_Msk))
                        {
                            if (0 != stcHsi2cCom.u32RxSize) /* 需要接收Sub address */
                            {
                                stcHsi2cCom.u8SubAddr[stcHsi2cCom.u32RxSize - 1] = (uint8_t)(u32RxData);
                                stcHsi2cCom.u32RxSize--;
                            }
                            else /* 不需要接收Sub address */
                            {
                                if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len)
                                {
                                    stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++] = (uint8_t)(u32RxData);
                                }
                                if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len)
                                {
                                    stcHsi2cCom.HSI2CxBaseAddr->STAR = HSI2C_STAR_TXNACK_Msk; /* Send NACK */
                                    stcHsi2cCom.u32DataIndex         = 0;
                                }
                            }
                        }
                    }

                    /* Transmit */
                    if (u32Flag & HSI2C_SLAVE_FLAG_TDF)
                    {
                        if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len)
                        {
                            HSI2C_SlaveWriteData(stcHsi2cCom.HSI2CxBaseAddr, stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++]);
                        }
                        if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len)
                        {
                            stcHsi2cCom.u32DataIndex = 0;
                        }
                    }

                    /* Stop or restart */
                    if (u32Flag & (HSI2C_SLAVE_FLAG_RSF | HSI2C_SLAVE_FLAG_SDF))
                    {
                        if (u32Flag & HSI2C_SLAVE_FLAG_SDF)
                        {
                            stcHsi2cCom.enComStatus = Hsi2cComIdle;
                        }
                        stcHsi2cCom.HSI2CxBaseAddr->STAR = 0;
                    }

                    /* Valid address */
                    if (u32Flag & (HSI2C_SLAVE_FLAG_AVF | HSI2C_SLAVE_FLAG_AM0F | HSI2C_SLAVE_FLAG_AM1F))
                    {
                        /* Get received slave address */
                        volatile uint32_t u32Temp = stcHsi2cCom.HSI2CxBaseAddr->SASR;
                    }

                    /* Transmit ACK */
                    if (u32Flag & HSI2C_SLAVE_FLAG_TAF)
                    {
                        stcHsi2cCom.HSI2CxBaseAddr->STAR = 0;
                    }

                    if (stcHsi2cCom.enComStatus == Hsi2cComIdle)
                    {
                        break; /* Transfer完成 */
                    }
                }
                else /* Error handling */
                {
                    HSI2C_SlaveTransAbort(stcHsi2cCom.HSI2CxBaseAddr);
                    stcHsi2cCom.enComStatus = Hsi2cComIdle;
                    enResult                = Error;
                    break;
                }
            }
        }
    }
    return enResult;
}

/**
 * @brief  主机配置寄存器1设置(MCFGR1寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cConfig MCFGR1寄存器配置结构体 @ref stc_hsi2c_master_config1_t
 * @retval None
 */
void HSI2C_MasterMcfgr1Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config1_t *pstcHsi2cConfig)
{
    MODIFY_REG32(HSI2Cx->MCFGR1,
                 HSI2C_MCFGR1_MATCFG_Msk | HSI2C_MCFGR1_RDMO_Msk | HSI2C_MCFGR1_TIMECFG_Msk | HSI2C_MCFGR1_IGNACK_Msk | HSI2C_MCFGR1_AUTOSTOP_Msk,
                 pstcHsi2cConfig->u32MatchConfig | pstcHsi2cConfig->u32ReceiveDataMatchOnly | pstcHsi2cConfig->u32TimeoutConfig | pstcHsi2cConfig->u32IgnoreNack
                     | pstcHsi2cConfig->u32AutoStop);
}

/**
 * @brief  主机配置寄存器2设置(MCFGR2寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cConfig MCFGR2寄存器配置结构体 @ref stc_hsi2c_master_config2_t
 * @retval None
 */
void HSI2C_MasterMcfgr2Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config2_t *pstcHsi2cConfig)
{
    MODIFY_REG32(HSI2Cx->MCFGR2, HSI2C_MCFGR2_FILTSDA_Msk | HSI2C_MCFGR2_FILTSCL_Msk | HSI2C_MCFGR2_BUSIDLE_Msk,
                 (pstcHsi2cConfig->u32SdaGlitchFilterConfig << HSI2C_MCFGR2_FILTSDA_Pos)
                     | (pstcHsi2cConfig->u32SclGlitchFilterConfig << HSI2C_MCFGR2_FILTSCL_Pos)
                     | (pstcHsi2cConfig->u32BusIdleTimeout << HSI2C_MCFGR2_BUSIDLE_Pos));
    MODIFY_REG32(HSI2Cx->MCFGR2, HSI2C_MCFGR2_FILTBPSDA_Msk | HSI2C_MCFGR2_FILTBPSCL_Msk,
                 pstcHsi2cConfig->u32SdaFilterEnable | pstcHsi2cConfig->u32SclFilterEnable);
}

/**
 * @brief  主机配置寄存器3设置(MCFGR3寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cConfig MCFGR3寄存器配置结构体 @ref stc_hsi2c_master_config3_t
 * @retval None
 */
void HSI2C_MasterMcfgr3Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config3_t *pstcHsi2cConfig)
{
    MODIFY_REG32(HSI2Cx->MCFGR3, HSI2C_MCFGR3_PINLOW_Msk, pstcHsi2cConfig->u32PinLowTimeout << HSI2C_MCFGR3_PINLOW_Pos);
}

/**
 * @brief  主机数据配置设置(MDMR寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32MatchValue0 Compared against the received data when receive data match is enabled. 数据范围：0 ~ 0xFF
 * @param  [in] u32MatchValue1 Compared against the received data when receive data match is enabled. 数据范围：0 ~ 0xFF
 * @retval None
 */
void HSI2C_MasterDataMatchConfig(HSI2C_TypeDef *HSI2Cx, uint32_t u32MatchValue0, uint32_t u32MatchValue1)
{
    MODIFY_REG32(HSI2Cx->MDMR, HSI2C_MDMR_MATCH0_Msk | HSI2C_MDMR_MATCH1_Msk,
                 (uint32_t)((u32MatchValue1 << HSI2C_MDMR_MATCH1_Pos) | (uint32_t)(u32MatchValue0 << HSI2C_MDMR_MATCH0_Pos)));
}

/**
 * @brief  从机控制寄存器2设置(SCR1寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cConfig SCR1寄存器配置结构体 @ref stc_hsi2c_slave_control1_t
 * @retval None
 */
void HSI2C_SlaveScr1Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_control1_t *pstcHsi2cConfig)
{
    HSI2Cx->SCR1 = pstcHsi2cConfig->u32FuncSelect | pstcHsi2cConfig->u32ConfigAddrMatchMode;
}

/**
 * @brief  从机控制寄存器2设置(SCR2寄存器设置)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pstcHsi2cConfig SCR2寄存器配置结构体 @ref stc_hsi2c_slave_control2_t
 * @retval None
 */
void HSI2C_SlaveScr2Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_control2_t *pstcHsi2cConfig)
{
    MODIFY_REG32(HSI2Cx->SCR2, HSI2C_SCR2_CLKHOLD_Msk | HSI2C_SCR2_DATAVD_Msk | HSI2C_SCR2_FILTSCL_Msk | HSI2C_SCR2_FILTSDA_Msk,
                 (pstcHsi2cConfig->u32TimingClockHoldTime << HSI2C_SCR2_CLKHOLD_Pos) | (pstcHsi2cConfig->u32TimingDataValidDelay << HSI2C_SCR2_DATAVD_Pos)
                     | (pstcHsi2cConfig->u32SclGlitchFilterWidth << HSI2C_SCR2_FILTSCL_Pos)
                     | (pstcHsi2cConfig->u32SdaGlitchFilterWidth << HSI2C_SCR2_FILTSDA_Pos));
    MODIFY_REG32(HSI2Cx->SCR2, HSI2C_SCR2_FILTEN_Msk, pstcHsi2cConfig->u32FilterEnable);
}

/**
 * @brief  HSI2C主机软件复位
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterReset(HSI2C_TypeDef *HSI2Cx)
{
    HSI2Cx->MCR = HSI2C_MCR_RST_Msk;
    HSI2Cx->MCR = 0x0u;
}

/**
 * @brief  HSI2C从机软件复位
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveReset(HSI2C_TypeDef *HSI2Cx)
{
    HSI2Cx->SCR0 = HSI2C_SCR0_RST_Msk;
    HSI2Cx->SCR0 = 0x0u;
}

/**
 * @brief  HSI2C主机使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterEnable(HSI2C_TypeDef *HSI2Cx)
{
    SET_REG32_BIT(HSI2Cx->MCR, HSI2C_MCR_MEN_Msk);
}

/**
 * @brief  HSI2C从机使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveEnable(HSI2C_TypeDef *HSI2Cx)
{
    SET_REG32_BIT(HSI2Cx->SCR0, HSI2C_SCR0_SEN_Msk);
}

/**
 * @brief  HSI2C主机禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterDisable(HSI2C_TypeDef *HSI2Cx)
{
    CLR_REG32_BIT(HSI2Cx->MCR, HSI2C_MCR_MEN_Msk);
}

/**
 * @brief  HSI2C从机禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveDisable(HSI2C_TypeDef *HSI2Cx)
{
    CLR_REG32_BIT(HSI2Cx->SCR0, HSI2C_SCR0_SEN_Msk);
}

/**
 * @brief  HSI2C主机标志位获取
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cFlag HSI2C主机标志位选择 @ref HSI2C_Master_Flag
 * @retval boolean_t
 *           - TRUE: 标志置位
 *           - FALSE: 标志未置位
 */
boolean_t HSI2C_MasterFlagGet(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag)
{
    return READ_REG32_BIT(HSI2Cx->MSR, u32Hsi2cFlag) ? TRUE : FALSE;
}

/**
 * @brief  HSI2C从机标志位获取
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cFlag HSI2C从机标志位选择 @ref HSI2C_Slave_Flag
 * @retval boolean_t
 *           - TRUE: 标志置位
 *           - FALSE: 标志未置位
 */
boolean_t HSI2C_SlaveFlagGet(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag)
{
    return READ_REG32_BIT(HSI2Cx->SSR, u32Hsi2cFlag) ? TRUE : FALSE;
}

/**
 * @brief  HSI2C主机标志位清除
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cFlag HSI2C主机标志位选择 @ref HSI2C_Master_Flag
 * @retval None
 */
void HSI2C_MasterFlagClear(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag)
{
    SET_REG32_BIT(HSI2Cx->MSCR, u32Hsi2cFlag);
}

/**
 * @brief  HSI2C从机标志位清除
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cFlag HSI2C从机标志位选择 @ref HSI2C_Slave_Flag
 * @retval None
 */
void HSI2C_SlaveFlagClear(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag)
{
    SET_REG32_BIT(HSI2Cx->SSCR, u32Hsi2cFlag);
}

/**
 * @brief  HSI2C主机中断使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cInt HSI2C主机中断选择 @ref HSI2C_Master_Int
 * @retval None
 */
void HSI2C_MasterIntEnable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt)
{
    SET_REG32_BIT(HSI2Cx->MIER, u32Hsi2cInt);
}

/**
 * @brief  HSI2C主机中断禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cInt HSI2C主机中断选择 @ref HSI2C_Master_Int
 * @retval None
 */
void HSI2C_MasterIntDisable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt)
{
    CLR_REG32_BIT(HSI2Cx->MIER, u32Hsi2cInt);
}

/**
 * @brief  HSI2C从机中断使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cInt HSI2C从机中断选择 @ref HSI2C_Slave_Int
 * @retval None
 */
void HSI2C_SlaveIntEnable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt)
{
    SET_REG32_BIT(HSI2Cx->SIER, u32Hsi2cInt);
}

/**
 * @brief  HSI2C从机中断禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32Hsi2cInt HSI2C从机中断选择 @ref HSI2C_Slave_Int
 * @retval None
 */
void HSI2C_SlaveIntDisable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt)
{
    CLR_REG32_BIT(HSI2Cx->SIER, u32Hsi2cInt);
}
/**
 * @brief  HSI2C主机中断使能获取
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval uint32_t 主机中断使能寄存器值
 */
uint32_t HSI2C_MasterIntGet(HSI2C_TypeDef *HSI2Cx)
{
    return READ_REG32(HSI2Cx->MIER);
}

/**
 * @brief  HSI2C从机中断使能获取
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval uint32_t 从机中断使能寄存器值
 */
uint32_t HSI2C_SlaveIntGet(HSI2C_TypeDef *HSI2Cx)
{
    return READ_REG32(HSI2Cx->SIER);
}

/**
 * @brief  HSI2C主机Start命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u8SlaveAddr 从机地址
 * @param  [in] enTransDir 传输方向 @ref en_hsi2c_dir_t
 * @retval None
 */
void HSI2C_MasterStart(HSI2C_TypeDef *HSI2Cx, uint8_t u8SlaveAddr, en_hsi2c_dir_t enTransDir)
{
    HSI2Cx->MTDR = HSI2C_CMD_START_TX_DATA | (((uint32_t)u8SlaveAddr << 1) + (uint32_t)enTransDir);
}

/**
 * @brief  HSI2C主机Stop命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterStop(HSI2C_TypeDef *HSI2Cx)
{
    HSI2Cx->MTDR = HSI2C_CMD_STOP;
}

/**
 * @brief  HSI2C主机写数据命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u8Data 主机写数据
 * @retval None
 */
void HSI2C_MasterWriteData(HSI2C_TypeDef *HSI2Cx, uint8_t u8Data)
{
    HSI2Cx->MTDR = HSI2C_CMD_TX_DATA | (uint32_t)u8Data;
}

/**
 * @brief  HSI2C从机写数据命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u8Data 从机写数据
 * @retval None
 */
void HSI2C_SlaveWriteData(HSI2C_TypeDef *HSI2Cx, uint8_t u8Data)
{
    HSI2Cx->STDR = (uint32_t)u8Data;
}

/**
 * @brief  HSI2C主机读数据命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u8Len 读数据长度
 * @retval None
 */
void HSI2C_MasterReceiveCmd(HSI2C_TypeDef *HSI2Cx, uint8_t u8Len)
{
    HSI2Cx->MTDR = HSI2C_CMD_RX_DATA | (uint32_t)u8Len;
}

/**
 * @brief  HSI2C主机读数据(RXEMPTY & DATA)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_MasterReadData(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data)
{
    uint32_t u32Temp = HSI2Cx->MRDR;
    if (0 == (u32Temp & HSI2C_MRDR_RXEMPTY_Msk))
    {
        *pu8Data = (uint8_t)(u32Temp & HSI2C_MRDR_DATA_Msk);
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C从机读数据(SOF，REMP & DATA)
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_SlaveReadData(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data)
{
    uint32_t u32Temp = HSI2Cx->SRDR;
    if (0 == (u32Temp & HSI2C_SRDR_REMP_Msk))
    {
        *pu8Data = (uint8_t)(u32Temp & HSI2C_SRDR_DATA_Msk);
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C从机写地址
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u16Addr0 从机地址0. 数据范围：0 ~ 0x3FF
 * @param  [in] u16Addr1 从机地址1. 数据范围：0 ~ 0x3FF
 * @retval None
 */
void HSI2C_SlaveWriteAddr(HSI2C_TypeDef *HSI2Cx, uint16_t u16Addr0, uint16_t u16Addr1)
{
    MODIFY_REG32(HSI2Cx->SADDR, HSI2C_SADDR_ADDR0_Msk | HSI2C_SADDR_ADDR1_Msk,
                 ((uint32_t)u16Addr0 << HSI2C_SADDR_ADDR0_Pos) | ((uint32_t)u16Addr1 << HSI2C_SADDR_ADDR1_Pos));
}

/**
 * @brief  HSI2C从机读接收的地址
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu16Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_SlaveReadAddr(HSI2C_TypeDef *HSI2Cx, uint16_t *pu16Data)
{
    uint32_t u32Temp = HSI2Cx->SASR;
    if (0 == (u32Temp & HSI2C_SASR_ANV_Msk))
    {
        *pu16Data = (uint16_t)(u32Temp & HSI2C_SASR_RADDR_Msk);
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C主机错误标志位读取
 * @param  [in] u32MasterFlag 主机MSR寄存器的值
 * @retval en_hsi2c_com_error_t 主机错误结果
 *           - Hsi2cComErrorPinLowTimeout: SCL or SDA were held low longer than the timeout
 *           - Hsi2cComErrorBufError: Buffer error
 *           - Hsi2cComErrorArbitrationLost: Arbitration lost error
 *           - Hsi2cComErrorNack: The slave device sent a NACK in response to a byte
 *           - Hsi2cComSuccess: The operation is successful
 */
en_hsi2c_com_error_t HSI2C_MasterErrorGet(uint32_t u32MasterFlag)
{
    en_hsi2c_com_error_t enComResult = Hsi2cComSuccess;
    if (0 != u32MasterFlag)
    {
        /* Get master error status */
        if (0 != (u32MasterFlag & (uint32_t)HSI2C_MSR_PLTF_Msk))
        {
            enComResult = Hsi2cComErrorPinLowTimeout;
        }
        else if (0 != (u32MasterFlag & (uint32_t)HSI2C_MSR_FEF_Msk))
        {
            enComResult = Hsi2cComErrorBufError;
        }
        else if (0 != (u32MasterFlag & (uint32_t)HSI2C_MSR_ALF_Msk))
        {
            enComResult = Hsi2cComErrorArbitrationLost;
        }
        else if (0 != (u32MasterFlag & (uint32_t)HSI2C_MSR_NDF_Msk))
        {
            enComResult = Hsi2cComErrorNack;
        }
        else
        {
            enComResult = Hsi2cComSuccess;
        }
    }
    return enComResult;
}

/**
 * @brief  HSI2C从机错误标志位读取
 * @param  [in] u32SlaveFlag 从机SSR寄存器的值
 * @retval en_hsi2c_com_error_t 从机错误结果
 *           - Hsi2cComErrorBitError: Transferred bit was not seen on the bus
 *           - Hsi2cComErrorBufError: Buffer error
 *           - Hsi2cComSuccess: The operation is successful
 */
en_hsi2c_com_error_t HSI2C_SlaveErrorGet(uint32_t u32SlaveFlag)
{
    en_hsi2c_com_error_t enComResult = Hsi2cComSuccess;
    if (0 != u32SlaveFlag)
    {
        /* Get slave error status */
        if (0 != (u32SlaveFlag & (uint32_t)HSI2C_SSR_BEF_Msk))
        {
            enComResult = Hsi2cComErrorBitError;
        }
        else if (0 != (u32SlaveFlag & (uint32_t)HSI2C_SSR_FEF_Msk))
        {
            enComResult = Hsi2cComErrorBufError;
        }
        else
        {
            enComResult = Hsi2cComSuccess;
        }
    }
    return enComResult;
}

/**
 * @brief  HSI2C主机传输终止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterTransAbort(HSI2C_TypeDef *HSI2Cx)
{
    /* Disable all interrupts */
    HSI2C_MasterIntDisable(stcHsi2cCom.HSI2CxBaseAddr, HSI2C_MASTER_INT_ALL);

    /* Master busy? */
    if (HSI2C_MasterFlagGet(HSI2Cx, HSI2C_MASTER_FLAG_MBF))
    {
        /* Send stop command */
        HSI2C_MasterStop(stcHsi2cCom.HSI2CxBaseAddr);
    }
}

/**
 * @brief  HSI2C从机传输终止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveTransAbort(HSI2C_TypeDef *HSI2Cx)
{
    /* Disable all interrupts */
    HSI2C_SlaveIntDisable(stcHsi2cCom.HSI2CxBaseAddr, HSI2C_SLAVE_INT_ALL);

    /* Transmit NACK */
    SET_REG32_BIT(stcHsi2cCom.HSI2CxBaseAddr->STAR, HSI2C_STAR_TXNACK_Msk);
}

/**
 * @brief  HSI2C从机ACK/NACK发送
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] u32AckNack ACK/NACK @ref HSI2C_Slave_Transfer_Ack_Nack
 * @retval None
 */
void HSI2C_SlaveTransNack(HSI2C_TypeDef *HSI2Cx, uint32_t u32AckNack)
{
    MODIFY_REG32(HSI2Cx->STAR, HSI2C_STAR_TXNACK_Msk, u32AckNack);
}

/**
 * @brief  HSI2C 10位地址模式获取高字节
 * @param  [in] u16AddrData 从机设备地址
 * @retval uint8_t 10位从机设备地址的高字节
 */
uint8_t HSI2C_10BitAddrMdHighBitsGet(uint16_t u16AddrData)
{
    return ((uint8_t)((u16AddrData >> 8) & 0x03u) | 0x78u);
}

/**
 * @brief  HSI2C 10位地址模式获取低字节
 * @param  [in] u16AddrData 从机设备地址
 * @retval uint8_t 10位从机设备地址的低字节
 */
uint8_t HSI2C_10BitAddrMdLowBitsGet(uint16_t u16AddrData)
{
    return (uint8_t)((u16AddrData & 0xFFu));
}

/**
 * @brief  主机结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_hsi2c_master_init_t
 * @retval None
 */
void HSI2C_MasterStcInit(stc_hsi2c_master_init_t *pstcInit)
{
    /* 初始值清零 */
    DDL_ZERO_STRUCT(*pstcInit);

    pstcInit->bResetBeforeInit                    = FALSE;
    pstcInit->u32EnableDebug                      = HSI2C_MASTER_DEBUG_OFF;
    pstcInit->u32BaudRateHz                       = 0;
    pstcInit->u8SlaveAddr                         = 0;
    pstcInit->enDir                               = Hsi2cMasterWriteSlaveRead;
    pstcInit->stcMasterConfig2.u32SdaFilterEnable = HSI2C_MASTER_FILTBPSDA_ENABLE;
    pstcInit->stcMasterConfig2.u32SclFilterEnable = HSI2C_MASTER_FILTBPSCL_ENABLE;
    pstcInit->u32SubAddr                          = 0;
    pstcInit->u8SubAddrSize                       = 0;
}
/**
 * @}
 */

/**
 * @brief  从机结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_hsi2c_slave_init_t
 * @retval None
 */
void HSI2C_SlaveStcInit(stc_hsi2c_slave_init_t *pstcInit)
{
    /* 初始值清零 */
    DDL_ZERO_STRUCT(*pstcInit);

    pstcInit->bResetBeforeInit = FALSE;
    pstcInit->u32SlaveAddr0    = 0;
    pstcInit->u32SlaveAddr1    = 0;
    pstcInit->enDir            = Hsi2cMasterWriteSlaveRead;
    pstcInit->u8SubAddrSize    = 0;
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
