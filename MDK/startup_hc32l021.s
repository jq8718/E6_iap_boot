;/******************************************************************************
;*  
;* Copyright (C) 2024, Xiaohua Semiconductor Co., Ltd. All rights reserved.
;* 
;* This software component is licensed by XHSC under BSD 3-Clause license
;* (the "License"); You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                    opensource.org/licenses/BSD-3-Clause
;* 
;*/
;/*****************************************************************************/

;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2024-12-01                                                   */
;/*  Target-mcu  {MCU_PN_H}                                                   */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors                       
                DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset        
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

                DCD     PORTA_IRQHandler          ;0
                DCD     PORTB_IRQHandler          ;1
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     ATIM3_IRQHandler          ;5
                DCD     0                         
                DCD     0                         
                DCD     LPUART0_IRQHandler        ;8
                DCD     LPUART1_IRQHandler        ;9
                DCD     SPI_IRQHandler            ;10
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     CTIM0_IRQHandler          ;14
                DCD     CTIM1_IRQHandler          ;15
                DCD     0                         
                DCD     0                         
                DCD     HSI2C_IRQHandler          ;18
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     IWDT_IRQHandler           ;22
                DCD     RTC_IRQHandler            ;23
                DCD     ADC_IRQHandler            ;24
                DCD     0                         
                DCD     VC0_IRQHandler            ;26
                DCD     VC1_IRQHandler            ;27
                DCD     LVD_IRQHandler            ;28
                DCD     0                         
                DCD     FLASH_IRQHandler          ;30
                DCD     CTRIM_CLKDET_IRQHandler   ;31

                

__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
               ;IMPORT  SystemInit
                IMPORT  __main

               ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0
                MOVS    R1, #0                 ; for warning, 
                ADD     R1, PC,#0              ; for A1609W, 
                CMP     R1, R0
                BLS     RAMCODE

              ; ram code base address. 
                ADD     R2, R0,R2
RAMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08 
                STR     R2, [R0]

              ; LDR     R0, =SystemInit
              ; BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
                
                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PORTA_IRQHandler                [WEAK]
                EXPORT  PORTB_IRQHandler                [WEAK]
                EXPORT  ATIM3_IRQHandler                [WEAK]
                EXPORT  LPUART0_IRQHandler              [WEAK]
                EXPORT  LPUART1_IRQHandler              [WEAK]
                EXPORT  SPI_IRQHandler                  [WEAK]
                EXPORT  CTIM0_IRQHandler                [WEAK]
                EXPORT  CTIM1_IRQHandler                [WEAK]
                EXPORT  HSI2C_IRQHandler                [WEAK]
                EXPORT  IWDT_IRQHandler                 [WEAK]
                EXPORT  RTC_IRQHandler                  [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  VC0_IRQHandler                  [WEAK]
                EXPORT  VC1_IRQHandler                  [WEAK]
                EXPORT  LVD_IRQHandler                  [WEAK]
                EXPORT  FLASH_IRQHandler                [WEAK]
                EXPORT  CTRIM_CLKDET_IRQHandler         [WEAK]

PORTA_IRQHandler
PORTB_IRQHandler
ATIM3_IRQHandler
LPUART0_IRQHandler
LPUART1_IRQHandler
SPI_IRQHandler
CTIM0_IRQHandler
CTIM1_IRQHandler
HSI2C_IRQHandler
IWDT_IRQHandler
RTC_IRQHandler
ADC_IRQHandler
VC0_IRQHandler
VC1_IRQHandler
LVD_IRQHandler
FLASH_IRQHandler
CTRIM_CLKDET_IRQHandler

                
               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
