---
name: i2c-iap-protocol-decisions
description: Key protocol design decisions from I2C IAP Bootloader discussion session
metadata:
  type: project
---

# I2C IAP Bootloader 协议设计决策汇总

讨论日期：2026-06-15 ~ 2026-06-16
产物文件：[I2C_IAP_Bootloader_Protocol.md](I2C_IAP_Bootloader_Protocol.md)

## 协议核心架构

- I2C 从机模式，1 字节 sub-address（`u8SubAddrSize = 1`）
- SCL Clock Stretching 必须启用（TXDSTALL + RXSTALL + ACKSTALL）
- 虚拟寄存器映射：STATUS(0x00), ERROR(0x01), CTRL(0x02), TX_LEN(0x06), MAILBOX(0x20~0x231)
- MAILBOX 按地址写入，自动增量，支持多帧分次写入
- CRC16 算法：初始值 0xA28C，多项式 0x8408（0x1021 反射），输出取反

## 帧格式

- 8 字节定长 Header：Magic(2) + Version(1) + Cmd(1) + Seq(1) + Flags(1) + PayloadLen(2)
- PayloadLen 字段定位 CRC 偏移：crc_offset = 8 + payload_len
- 所有帧 PayloadLen >= 1，Payload[0] 统一为结果码（0x00=OK，其他=ERROR 码）
- Flags 保留固定 0x00，不用 bit7 区分请求/响应（I2C W/R 方向已区分）
- 字节序：小端（ARM Cortex-M0+ 原生）

## 命令集（5 条）

| 0x20 | HANDSHAKE | Payload: 无 |
| 0x24 | ERASE_FLASH | Payload: AppSize(4) — 擦除目标固定 APP_ADDR |
| 0x22 | APP_DOWNLOAD | Payload: FlashAddr(4) + Firmware(N) |
| 0x25 | CRC_FLASH | Payload: AppSize(4) — 校验起始固定 APP_ADDR；Boot 存 app_size/app_crc 到参数区 |
| 0x21 | JUMP_TO_APP | Payload: 无；Boot 重算 CRC 与参数区比对后再决定跳转 |

去掉的命令：START_UPDATE, APP_UPLOAD, RX_LEN 寄存器

## 状态机

- 去掉 RX_READY 状态，COMMIT 本身触发解析
- 去掉 Boot GPIO 强制进入，纯靠参数区状态机
- APP → Boot：APP 写 UPDATE_REQUEST → NVIC_SystemReset()
- Boot → APP：软跳转 ResetHandler（不硬件复位），CLEAR 后延时 → IAP_ResetConfig → 跳转
- ERASE_FLASH 不写参数区——保护由 JUMP_TO_BOOT 时写的 UPDATE_REQUEST 提供
- CRC_FLASH 写参数区 app_size/app_crc，JUMP_TO_APP 在 Boot 内部闭环验证
- IMAGE_PENDING 不重试（单次尝试），跳转失败后不写 INVALID，直接留在 Boot

**Why:** 简化协议、减少寄存器数、Boot 自验证不信任主机传参、I2C 事务边界已区分请求/响应无需额外标记。

## 参数区

- stc_boot_param_t 结构体：magic + state + app_addr + app_size + app_crc + boot_count + app_version + header_crc
- 三状态：UPDATE_REQUEST(0xA5A55A5A), IMAGE_PENDING(0x5AA55AA5), IMAGE_VALID(0x55AAAA55)
- boot_count 不递增（避免 Flash 擦写代价）
- IMAGE_VALID 由 APP 写入，Bootloader 不写
- Boot 和 APP 必须共用同一份 stc_boot_param_t 定义

**How to apply:** 实现时以 [I2C_IAP_Bootloader_Protocol.md](I2C_IAP_Bootloader_Protocol.md) 为准，[I2C_IAP_Bootloader_Design.md](I2C_IAP_Bootloader_Design.md) 为辅助参考。
