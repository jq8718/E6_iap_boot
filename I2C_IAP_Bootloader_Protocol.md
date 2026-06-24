# HC32L021 I2C IAP Bootloader 协议规格

> 基于 `I2C_IAP_Bootloader_Design.md` 讨论迭代后的最终协议规格。

---

## 0. 芯片资源

### 0.1 HC32L021 Flash 地址布局

```
总容量: 64KB (0x10000), 扇区大小 512B (0x200), 共 128 扇区
```

| 区域                 | 起始             | 结束                 | 大小                  | 扇区 |
|---------------------|------------------|----------------------|-----------------------|--------|
| **BOOT 区**         | `0x00000000`     | `0x00001FFF`         | 8KB `(0x2000)`        | 16 扇区 (0~15) |
| └─ BOOT 程序        | `0x00000000`     | `0x00001DFF`         | 7.5KB `(0x1E00)`      | 15 扇区 (0~14) |
| └─ **BOOT 参数区**  | **`0x00001E00`** | **`0x00001FFF`**     | **512B `(0x200)`**    | **1 扇区 (15)** |
| **APP 区**          | **`0x00002000`** | **`0x0000FDFF`**     | **55.5KB `(0xDE00)`** | **111 扇区 (16~126)** |
| 保留                | `0x0000FE00`      | `0x0000FFFF`        | 512B `(0x200)`        | 1 扇区 (127) |

```c
/* source/utils.h */
#define FLASH_SECTOR_SIZE    (0x200u)                               /* 512B */
#define FLASH_START_ADDR     ((uint32_t)0x00000000u)
#define FLASH_SIZE           (FLASH_SECTOR_NUM * FLASH_SECTOR_SIZE)  /* 0x10000 = 64KB */
#define BOOT_SIZE            (16u * FLASH_SECTOR_SIZE)               /* 0x2000 = 8KB */
#define BOOT_PARAM_ADDR      (FLASH_START_ADDR + BOOT_SIZE - FLASH_SECTOR_SIZE)  /* 0x1E00 */
#define APP_ADDR             (FLASH_START_ADDR + BOOT_SIZE)          /* 0x2000 */
#define APP_MAX_SIZE         (FLASH_SIZE - BOOT_SIZE - FLASH_SECTOR_SIZE)         /* 0xDE00 = 56832 */
```

### 0.2 引脚配置

| 功能 | 引脚 | 复用 | 方向 | 说明 |
|------|------|------|------|------|
| **HSI2C SDA** | PA06 | AF1: HSI2C_SDA | 开漏输出 | I2C 数据线，需外部上拉 |
| **HSI2C SCL** | PA07 | AF1: HSI2C_SCL | 开漏输出 | I2C 时钟线，需外部上拉 |
| **LPUART1 TX** | PA01 | AF1: LPUART1_TXD | 推挽输出 | 调试串口输出 (115200-8N1) |

```c
/* source/config_hc32l021.c — I2C 引脚初始化 */
stcGpioInit.u32Pin       = GPIO_PIN_06 | GPIO_PIN_07;
stcGpioInit.u32Mode      = GPIO_MD_OUTPUT_OD;  /* 开漏 */
stcGpioInit.bOutputValue = TRUE;
GPIOA_Init(&stcGpioInit);
GPIO_PA06_AF_HSI2C_SDA();
GPIO_PA07_AF_HSI2C_SCL();

/* source/config_hc32l021.c — LPUART 引脚初始化 */
GPIOA->OUT = GPIO_PIN_01;                      /* 预拉高 */
stcGpioInit.u32Pin       = GPIO_PIN_01;
stcGpioInit.u32Mode      = GPIO_MD_OUTPUT_PP;  /* 推挽 */
stcGpioInit.bOutputValue = TRUE;
GPIOA_Init(&stcGpioInit);
GPIO_PA01_AF_LPUART1_TXD();
```

---

## 1. I2C 从机配置

### 1.1 硬件要求

| 参数 | 值 | 说明 |
|------|------|------|
| Sub-address | **1 字节** | `u8SubAddrSize = 1`，用于虚拟寄存器寻址 |
| SCL Stall | **必须启用** | `TXDSTALL`, `RXSTALL`, `ACKSTALL` 全部使能 |
| 从机地址 | `0x32` | 7-bit，不与总线其他器件冲突 |
| 时钟源 | 系统时钟 | HC32L021 上电默认 4MHz → Boot 初始化后 48MHz |

### 1.2 SCL Clock Stretching 作用

Flash 擦写期间 CPU 被 Stall，I2C ISR 无法执行。启用 SCL Stall 后，I2C 硬件自动拉低 SCL 等待 CPU 恢复，避免 NACK。

```c
// HSI2C 从机初始化关键配置
stcSlaveInit.u8SubAddrSize = 1;
stcSlaveInit.stcSlaveConfig1.u32FuncSelect =
    HSI2C_SLAVE_TXDSTALL_ENABLE  |   // 发送数据时允许 Stall SCL
    HSI2C_SLAVE_RXSTALL_ENABLE   |   // 接收数据时允许 Stall SCL
    HSI2C_SLAVE_ACKSTALL_ENABLE;     // ACK 阶段允许 Stall SCL
```

---

	## 2. 虚拟寄存器

Bootloader 作为 I2C 从机，通过 1 字节 sub-address 映射虚拟寄存器。

### 2.0 寄存器地址总表

| 地址 | 名称 | 方向 | 字节数 | 由谁读写 | 说明 |
|------|------|------|--------|---------|------|
| `0x00` | `REG_STATUS` | R | 1 | 主机读 | Boot 当前状态 |
| `0x01` | `REG_ERROR` | R | 1 | 主机读 | 最近错误码 |
| `0x02` | `REG_CTRL` | W | 1 | 主机写 | 控制命令（COMMIT/CLEAR/ABORT） 读返回 `0x00`|
| `0x03` | *保留* | R | 1 | — | 读返回 `0x00`，写忽略 |
| `0x04` | `REG_FW_VERSION_LOW` | R | 1 | 主机读 | 固件版本低字节，APP/Boot 均支持 |
| `0x05` | `REG_FW_VERSION_HIGH` | R | 1 | 主机读 | 固件版本高字节，bit15=1 标识 Boot，=0 标识 APP |
| `0x06` | `REG_TX_LEN` | R | 1 | 主机读 | 响应帧长度低字节（仅 `RESP_READY` 有效） |
| `0x07` | `REG_TX_LEN_HIGH` | R | 1 | 主机读 | 响应帧长度高字节 |
| `0x08`~`0x0F` | *保留* | R | — | — | 读返回 `0x00`，写忽略 |
| `0x10` | `REG_AIM_DELAY_LOW` | R/W | 1 | **APP** | 瞄准灯开启延时低字节，Boot 读返回 `0x00` |
| `0x11` | `REG_AIM_DELAY_HIGH` | R/W | 1 | **APP** | 瞄准灯开启延时高字节，Boot 读返回 `0x00` |
| `0x12` | `REG_AIM_DURATION_LOW` | R/W | 1 | **APP** | 瞄准灯开启时长低字节，Boot 读返回 `0x00` |
| `0x13` | `REG_AIM_DURATION_HIGH` | R/W | 1 | **APP** | 瞄准灯开启时长高字节，Boot 读返回 `0x00` |
| `0x14` | `REG_FILL_DELAY_LOW` | R/W | 1 | **APP** | 补光灯开启延时低字节，Boot 读返回 `0x00` |
| `0x15` | `REG_FILL_DELAY_HIGH` | R/W | 1 | **APP** | 补光灯开启延时高字节，Boot 读返回 `0x00` |
| `0x16` | `REG_FILL_DURATION_LOW` | R/W | 1 | **APP** | 补光灯开启时长低字节，Boot 读返回 `0x00` |
| `0x17` | `REG_FILL_DURATION_HIGH` | R/W | 1 | **APP** | 补光灯开启时长高字节，Boot 读返回 `0x00` |
| `0x18` | `REG_SUM8_LIGHT` | W | 1 | **APP** | SUM8 校验触发灯光参数更新，Boot 写忽略 |
| `0x19` | `REG_FRAME_RATE` | R/W | 1 | **APP** | 帧率，Boot 读返回 `0x00` |
| `0x1A` | `REG_EXPOSURE_LOW` | R/W | 1 | **APP** | 曝光时长低字节，Boot 读返回 `0x00` |
| `0x1B` | `REG_EXPOSURE_HIGH` | R/W | 1 | **APP** | 曝光时长高字节，Boot 读返回 `0x00` |
| `0x1C` | `REG_SUM8_SENSOR` | W | 1 | **APP** | SUM8 校验触发相机参数更新，Boot 写忽略 |
| `0x1D`~`0x1F` | *保留* | R | 1 | — | 读返回 `0x00`，写忽略 |
| `0x20`~`0x231` | `REG_MAILBOX` | W/R | 530 | 主机读写 | 请求帧写入 / 响应帧读取 |

> **寄存器访问规则**：所有寄存器读写后 sub-address 自动 +1，支持单次 I2C 事务连续读取/写入相邻寄存器。

**实现代码定义**（`source/utils.h`）：

```c
/* 寄存器地址 — 系统 (Boot + APP) */
#define REG_STATUS            (0x00u)
#define REG_ERROR             (0x01u)
#define REG_CTRL              (0x02u)
#define REG_FW_VERSION_LOW    (0x04u)
#define REG_FW_VERSION_HIGH   (0x05u)
#define REG_TX_LEN            (0x06u)
#define REG_TX_LEN_HIGH       (0x07u)
#define REG_MAILBOX_START     (0x20u)
#define REG_MAILBOX_END       (0x231u)

/* 寄存器地址 — APP 专用 (Boot 读返回 0, 写忽略) */
#define REG_AIM_DELAY_LOW     (0x10u)
#define REG_AIM_DELAY_HIGH    (0x11u)
#define REG_AIM_DURATION_LOW  (0x12u)
#define REG_AIM_DURATION_HIGH (0x13u)
#define REG_FILL_DELAY_LOW    (0x14u)
#define REG_FILL_DELAY_HIGH   (0x15u)
#define REG_FILL_DURATION_LOW (0x16u)
#define REG_FILL_DURATION_HIGH (0x17u)
#define REG_SUM8_LIGHT        (0x18u)
#define REG_FRAME_RATE        (0x19u)
#define REG_EXPOSURE_LOW      (0x1Au)
#define REG_EXPOSURE_HIGH     (0x1Bu)
#define REG_SUM8_SENSOR       (0x1Cu)

/* 固件版本标识：Boot 读出时 bit15=1 */
#define FW_VERSION_BOOT_MASK  (0x8000u)

/* STATUS 值 */
#define STATUS_IDLE       (0x00u)
#define STATUS_BUSY       (0x02u)
#define STATUS_RESP_READY (0x03u)
#define STATUS_ERROR      (0x04u)

/* CTRL 值 */
#define CTRL_COMMIT (0xA5u)
#define CTRL_CLEAR  (0x5Au)
#define CTRL_ABORT  (0xC3u)

/* ERROR 码 */
#define ERROR_CODE_OK          (0x00u)
#define ERROR_CODE_CRC         (0x01u)
#define ERROR_CODE_FRAME       (0x02u)
#define ERROR_CODE_UNSUPPORTED (0x03u)
#define ERROR_CODE_ADDR        (0x04u)
#define ERROR_CODE_FLASH       (0x05u)
#define ERROR_CODE_BUSY        (0x06u)
#define ERROR_CODE_SEQ         (0x07u)
#define ERROR_CODE_APP_INVALID (0x08u)
```

### 2.1 STATUS（地址 0x00，只读 1 字节）

STATUS 寄存器指示 Bootloader 当前工作状态。主机在每次写命令前应先检查 STATUS == IDLE。

| 合法值 | 名称 | 触发条件 | 行为说明 |
|--------|------|---------|---------|
| `0x00` | `IDLE` | 空闲/被 CLEAR/ABORT 清空 | 可写 MAILBOX，可写 COMMIT |
| `0x02` | `BUSY` | 收到 COMMIT 后开始执行 | Flash 擦写/CRC/跳转准备中，勿写 MAILBOX |
| `0x03` | `RESP_READY` | 命令执行成功 | 响应帧已在 MAILBOX 中，主机可读 |
| `0x04` | `ERROR` | 命令执行或帧校验失败 | 读取 ERROR 寄存器获取错误码 |

**状态转换**：

```text
                          (APP正常启动后写IMAGE_VALID)
IMAGE_VALID ──冷启动跳APP──→ APP  ←────────────────── IMAGE_VALID
    │                                                    ↑
    └跳失败→停在Bootloader                               │
                                                         │
UPDATE_REQUEST ──IAP流程──→ JUMP_TO_APP ──→ IMAGE_PENDING ──(跳APP成功)──→ APP
     ↑                                                    │
     │                                      掉电重启→停在Bootloader不跳
     └──JUMP_TO_BOOT(APP侧)───┘
```

**参数区状态值定义**：

| 名称 | 值 | 由谁写入 | 说明 |
|------|-----|---------|------|
| `UPDATE_REQUEST` | `0xA5A55A5A` | APP（JUMP_TO_BOOT 时） | 请求升级，Bootloader 应停留在 IAP 模式 |
| `IMAGE_PENDING` | `0x5AA55AA5` | Boot（JUMP_TO_APP 校验通过后） | 跳转即将执行，掉电不重试 |
| `IMAGE_VALID` | `0x55AAAA55` | APP（自身初始化确认后） | 固件已验证，下次冷启动直接跳 |

**关键规则**：
- Bootloader 只写 `UPDATE_REQUEST`（被 APP 调用时）和 `IMAGE_PENDING`（JUMP_TO_APP 时）
- `IMAGE_VALID` 只能由 APP 写入，APP 确认自身初始化成功后标记
- `IMAGE_PENDING` 掉电重启后 Bootloader 不会跳转（单次尝试），防止半完成状态死循环
```

---

### 2.2 ERROR（地址 0x01，只读 1 字节）

ERROR 寄存器记录最近一次错误码。仅在 `STATUS == ERROR` 时有效；`STATUS != ERROR` 时返回 `0x00`。

ERROR 值与响应帧 `Payload[0]` 的错误码保持**完全一致**，主机可通过两种方式获取：

- 快速诊断：`STATUS == ERROR` 时直接读 ERROR 寄存器
- 权威来源：读完整响应帧的 `Payload[0]`

| 合法值 | 名称 | 说明 |
|--------|------|------|
| `0x00` | `OK` | 无错误 |
| `0x01` | `CRC_ERROR` | 请求帧 CRC16 校验失败 |
| `0x02` | `FRAME_ERROR` | Magic 不匹配 / PayloadLen 超限 / Version 不匹配 |
| `0x03` | `UNSUPPORTED_CMD` | 不支持的命令码 |
| `0x04` | `ADDR_ERROR` | Flash 地址超出 `[APP_ADDR, APP_ADDR + APP_MAX_SIZE)` |
| `0x05` | `FLASH_ERROR` | Flash 擦除或写入操作失败 |
| `0x06` | `BUSY_ERROR` | 当前状态不允许此操作（如非 IDLE 时写 COMMIT） |
| `0x07` | `SEQ_ERROR` | 帧序号重复或非法（当前未实现） |
| `0x08` | `APP_INVALID` | APP 向量表检查不通过（栈顶/ResetHandler/CRC 不匹配） |

---

### 2.3 CTRL（地址 0x02，只写 1 字节）

主机通过写 CTRL 寄存器控制 Bootloader 行为。CTRL 值不保留——写入后立即生效，不提供读取。

| 合法值 | 名称 | 说明 |
|--------|------|------|
| `0xA5` | `COMMIT` | 提交 MAILBOX 内容给 Boot 解析执行。`STATUS == BUSY` 时忽略 |
| `0x5A` | `CLEAR` | 主机已读完响应帧，Boot 清状态回 `IDLE`。可在 `RESP_READY` 或 `ERROR` 状态下使用 |
| `0xC3` | `ABORT` | 放弃当前操作，无条件回到 `IDLE`。丢弃任何未读的响应 |

**注意**：写入 `0xA5` / `0x5A` / `0xC3` 以外的值被忽略。

---

### 2.4 TX_LEN（地址 0x06，只读 2 字节）

TX_LEN 指示响应帧在 MAILBOX 中的字节数，**小端**（低字节在前）。

| 条件 | 返回值 |
|------|--------|
| `STATUS == RESP_READY` | 有效帧长度（`10 ~ 530`） |
| `STATUS != RESP_READY` | `0x0000` |

**读取方法**：一次 I2C 读事务读取 2 字节，先低后高：

```text
S + SLA(W) + 0x06 + Sr + SLA(R) + len_l + len_h + P
len = len_l | (len_h << 8)
```

---

### 2.5 MAILBOX（地址 0x20 ~ 0x231，读写 530 字节）

MAILBOX 是帧数据窗口。主机通过写 MAILBOX 发送请求帧，通过读 MAILBOX 获取响应帧。

**地址映射**：`0x20` = MAILBOX[0]，`0x21` = MAILBOX[1]，...，`0x231` = MAILBOX[529]。

**写入规则**（主机 → Boot）：

- 仅 `STATUS == IDLE` 时允许写入。非 IDLE 时写入数据被丢弃。
- 主机可写入 `0x20 ~ 0x231` 范围内任意起始地址。同一 I2C 事务内连续字节地址自动增量。
- 写入同一地址会覆盖该位置已有数据。多次写入不同地址段互相独立。
- 写入内容在 CTRL = COMMIT 之前不会被解析。

**读取规则**（Boot → 主机）：

- 仅 `STATUS == RESP_READY` 时数据有效。非 `RESP_READY` 时返回 `0x00`。
- 从任意偏移开始读取均可，正常流程从 `0x20` 读取完整响应帧。

**自动增量示例**：

```text
写操作：S + SLA(W) + 0x20 + [8B Header] + [Payload] + [2B CRC] + P
                        ↑                                      ↑
                    地址 0x20                             地址 0x20+N+9
             每个字节地址自动 +1，从 0x20 递增到 0x20+N+9

读操作：S + SLA(W) + 0x20 + Sr + SLA(R) + [TX_LEN 字节] + P
                        ↑
                    地址 0x20，读满 TX_LEN 个字节自动停止
```

---

## 3. 帧格式

### 3.1 请求帧

**定长 8 字节 Header + 可变 Payload + 2 字节 CRC16**。

```
Offset  Size  Name        说明
  0      1    Magic0      固定 0x6D
  1      1    Magic1      固定 0xAC
  2      1    Version     协议版本，当前 0x01
  3      1    Cmd         命令码
  4      1    Seq         帧序号，主机自增，Boot 回显
  5      1    Flags       选项位，当前固定 0x00
  6      2    PayloadLen  Payload 字节数，小端，范围 0~512
  8     N     Payload     命令参数，内容由 Cmd 决定
  8+N   2     CRC16       校验 Header[0..7] + Payload[0..N-1]
```

**解析规则**：

```c
payload_len = MAILBOX[6] | (MAILBOX[7] << 8);
crc_offset  = 8 + payload_len;                     // CRC 在 Payload 之后
crc_recv    = MAILBOX[crc_offset] | (MAILBOX[crc_offset + 1] << 8);
crc_calc    = CRC16(MAILBOX, crc_offset);          // 覆盖 Header + Payload
```

**校验顺序**：
1. `PayloadLen` 合法（`0` ~ `IAP_PAYLOAD_MAX` = `4 + FLASH_DATA_MAX`）
2. Magic 匹配
3. Version 匹配
4. Flags 为 `0x00`
5. CRC16 通过

### 3.2 响应帧

同样的 8 字节 Header + Payload + CRC16 结构。

```
Offset  Size  Name        说明
  0      1    Magic0      固定 0x6D
  1      1    Magic1      固定 0xAC
  2      1    Version     协议版本
  3      1    Cmd         回显请求 Cmd
  4      1    Seq         回显请求 Seq
  5      1    Flags       选项位，固定 0x00（保留）
  6      2    PayloadLen  Payload 字节数，小端
  8     N     Payload     响应数据，内容由 Cmd 决定
  8+N   2     CRC16       校验 Header + Payload
```

**结果通过 Payload[0] 表示**：

所有响应帧 `PayloadLen >= 1`，`Payload[0]` 为结果码，值与 `ERROR` 寄存器一致：

| Payload[0] | 含义 |
|-----------|------|
| `0x00` | OK，无错误 |
| `0x01` ~ `0x08` | 对应 ERROR 码 |

`PayloadLen = 1` 时为纯错误响应。`PayloadLen > 1` 时 `Payload[0]` 仍为结果码，`Payload[1..]` 为命令返回数据。

**各命令响应 Payload（成功时）**：

| Cmd | PayloadLen | Payload 内容 |
|------|-----------|------|
| HANDSHAKE | 4 | `[0]=OK` `[1]=协议版本` `[2:3]=每包最大固件数据(=512)` |
| ERASE_FLASH | 1 | `[0]=OK` |
| APP_DOWNLOAD | 1 | `[0]=OK` |
| CRC_FLASH | 3 | `[0]=OK` `[1:2]=Flash CRC16` |
| JUMP_TO_APP | 1 | `[0]=OK` |

**所有命令失败时**：`PayloadLen = 1`，`Payload[0] = 错误码`（值与 ERROR 寄存器一致）。

---

## 4. CRC16 算法

与现有 UART Bootloader `HC32_CalCrc16()` 一致。

| 参数 | 值 |
|------|------|
| 初始值 | `0xA28C` |
| 多项式 | `0x1021` (CRC-CCITT)，右移实现用反射多项式 `0x8408` |
| 处理 | LSB-first，每字节 `crc ^= byte` 后迭代 8 次 |
| 输出 | `~crc`（按位取反） |
| 帧内字节序 | 小端，低字节在前 |

```c
static uint16_t IAP_Crc16(const uint8_t *data, uint32_t len)
{
    uint8_t  i;
    uint16_t crc = 0xA28Cu;

    while (len-- != 0u) {
        crc ^= *data++;
        for (i = 0u; i < 8u; i++) {
            if (crc & 0x0001u)
                crc = (crc >> 1) ^ 0x8408u;
            else
                crc >>= 1;
        }
    }
    return (uint16_t)(~crc);
}
```

---

## 5. 命令定义

### 5.1 命令总表

| Cmd | 名称 | 由谁实现 | Payload | PayloadLen | 帧总长 |
|------|------|---------|---------|-----------|--------|
| `0x20` | HANDSHAKE | Boot | 无 | 0 | 10 |
| `0x21` | JUMP_TO_APP | Boot | 无 | 0 | 10 |
| `0x22` | APP_DOWNLOAD | Boot | FlashAddr(4) + 固件数据 | 4+N | 14+N |
| `0x23` | JUMP_TO_BOOT | **APP** | 无 | 0 | 10 |
| `0x24` | ERASE_FLASH | Boot | AppSize(4) | 4 | 14 |
| `0x25` | CRC_FLASH | Boot | AppSize(4) | 4 | 14 |

> **注意**：`JUMP_TO_BOOT` 由 **APP 固件**（而非 Bootloader）实现。APP 处于运行状态时，主机发送该命令通知 APP 进入 Bootloader 模式准备升级。

### 5.2 各命令 Payload 结构

**HANDSHAKE**：

```
Payload: 无 (PayloadLen = 0)
```

**ERASE_FLASH**：

```
Payload[0:3]  AppSize  uint32 LE  固件长度（= app_size）
```

擦除目标固定为 `APP_ADDR`。Boot 内部做扇区对齐——实际擦除 `ceil(AppSize / 512)` 个扇区。

**APP_DOWNLOAD**：

```
Payload[0:3]  FlashAddr  uint32 LE  写入目标地址
Payload[4:N]  Firmware   bytes      固件数据，N = PayloadLen - 4
```

**CRC_FLASH**：

```
Payload[0:3]  AppSize  uint32 LE  固件长度（= app_size）
```

校验起始地址固定为 `APP_ADDR`，校验范围 `[APP_ADDR, APP_ADDR + AppSize)`。

**JUMP_TO_APP**：

```
Payload: 无 (PayloadLen = 0)
```

**JUMP_TO_BOOT**（由 APP 固件实现）：

```
Payload: 无 (PayloadLen = 0)
```

**作用**：通知正在运行的 APP 固件复位进入 Bootloader，以便主机进行固件升级。

**APP 侧实现**：

```c
// APP 固件 I2C 中断中收到 JUMP_TO_BOOT 命令后的处理流程：
void APP_I2C_Process(void)
{
    if (cmd == CMD_JUMP_TO_BOOT) {
        // 1. 发响应帧（OK），通知主机已收到
        BuildResponse(tx_mailbox, &tx_len, CMD_JUMP_TO_BOOT, seq, Ok, NULL, 0);

        // 2. 写 Boot 参数区 state = UPDATE_REQUEST
        BootParam_WriteState(IMAGE_STATE_UPDATE_REQUEST);

        // 3. 等待主机 CLEAR（同标准事务流程）
        //    （延时等待 CLEAR 或直接进入）
        Delay_ms(5);

        // 4. 系统复位进入 Bootloader
        NVIC_SystemReset();
    }
}
```

**主机侧流程**：

```text
1.  主机写 MAILBOX request (JUMP_TO_BOOT, PayloadLen=0)
2.  主机写 CTRL = COMMIT
3.  主机等 STATUS == RESP_READY
4.  主机读响应帧（确认 APP 已收到）
5.  主机写 CTRL = CLEAR
6.  → APP 复位，MCU 进入 Bootloader
7.  主机检测 I2C 无响应（APP 正在复位）→ 延时等待重启
8.  MCU 重启后 Bootloader 读取参数区 state == UPDATE_REQUEST
9.  Bootloader 停留在 IDLE 状态等待主机命令
10. 主机从 HANDSHAKE 开始升级流程
```

> **掉电保护**：如果主机在发送 JUMP_TO_BOOT 后掉电，重新上电时 Bootloader 读到 `UPDATE_REQUEST`，会停留在 Boot 等待主机重新发起升级。

---

## 6. 命令事务流程

每条命令遵循统一的 I2C 事务序列。以下均为 **Master 视角**。

### 6.1 单条命令标准事务

```text
1.  Master Read STATUS
    S + SLA(W) + 0x00 + Sr + SLA(R) + status + P
    要求 STATUS == IDLE

2.  Master Write MAILBOX request
    S + SLA(W) + 0x20 + request_frame[frame_len] + P
    可一次写完或分多次写入（从对应偏移地址开始）

3.  Master Write CTRL = COMMIT
    S + SLA(W) + 0x02 + 0xA5 + P

4.  Master Poll STATUS
    S + SLA(W) + 0x00 + Sr + SLA(R) + status + P
    STATUS == BUSY      → 延时后重试（Flash 操作时允许短时 NACK）
    STATUS == RESP_READY → 下一步
    STATUS == ERROR     → 读 ERROR，终止或重试

5.  Master Read TX_LEN
    S + SLA(W) + 0x06 + Sr + SLA(R) + tx_len_l + tx_len_h + P
    检查 TX_LEN >= 10 且 TX_LEN <= 530

6.  Master Read MAILBOX response
    S + SLA(W) + 0x20 + Sr + SLA(R) + response_frame[TX_LEN] + P

7.  校验响应 CRC16、Cmd、Seq

8.  Master Write CTRL = CLEAR
    S + SLA(W) + 0x02 + 0x5A + P
```

### 6.2 轮询期间的异常处理

Flash 操作期间 CPU Stall 导致 I2C 短时无响应，**不应立即判定失败**：

| 观察 | 处理 |
|------|------|
| I2C NACK | 按 BUSY 处理，延时 ≥ 5ms 后重试 |
| I2C timeout | 同上 |
| STATUS == ERROR | 读 ERROR 寄存器，判断是否可恢复 |
| 总超时耗尽 | 判定命令失败，ABORT 后重新开始 |

---

## 7. 升级流程

升级流程分为两种场景：

### 7.1 APP → Bootloader（前置步骤）

如果 MCU 正在运行 APP 固件，需要先用 JUMP_TO_BOOT 让 APP 复位进入 Bootloader：

```text
1. 主机通过 I2C 向 APP 发送 JUMP_TO_BOOT 命令
2. APP 写参数区 state = UPDATE_REQUEST → NVIC_SystemReset()
3. MCU 重启 → Bootloader 读到 UPDATE_REQUEST → 停留在 IDLE 等待
```

### 7.2 Bootloader 启动决策

Bootloader 上电后读取参数区 state，按以下逻辑决策：

```text
magic 不匹配? ──→ 参数区未预烧录 ──→ 留在 Bootloader（不做任何初始化）
                        │
    magic 匹配，检查 state:
                        │
    IMAGE_VALID ────────→ CRC 校验 ──→ OK ──→ 跳 APP
                        │              │
                        │              └── 失败 ──→ 留在 Bootloader
                        │
    UPDATE_REQUEST ─────→ APP 请求升级 ──→ 停在 Bootloader 等待 IAP
    IMAGE_PENDING ──────→ 前次升级跳 APP 后掉电 ──→ 停在 Bootloader（不重试）
```

> **注意**：即使 `IMAGE_VALID` 状态表示前次固件已验证，Bootloader 每次冷启动仍会重新计算 APP Flash 区域的 CRC16，与参数区 `app_crc` 比对。CRC 通过后才跳转，失败则停留在 Bootloader 等待主机处理。这防止了参数区 `state` 因 Flash 比特翻转或编程错误导致误跳。`IMAGE_PENDING` 在掉电重启后不会跳转——这是单次尝试策略，防止升级断电后半完成状态反复跳转失败。

### 7.3 标准升级流程（Bootloader 已运行）

此时参数区 state 为 `UPDATE_REQUEST`（从 JUMP_TO_BOOT 或掉电前写入）。

```text
1. HANDSHAKE
   获取协议版本和 FLASH_DATA_MAX（每包最大固件数据）
   参数区不变，state 保持 UPDATE_REQUEST

2. ERASE_FLASH
   AppSize = app_size
   Boot 内部做扇区对齐，擦除 >= app_size 的最小扇区数
   只擦 APP Flash 区域，参数区不变，state 保持 UPDATE_REQUEST

3. APP_DOWNLOAD × N
   offset = 0
   while offset < app_size:
       chunk_len = min(app_size - offset, FLASH_DATA_MAX)
       Payload = FlashAddr(4) + app_bin[offset : offset + chunk_len]
       offset += chunk_len
   参数区不变，state 保持 UPDATE_REQUEST

4. CRC_FLASH
   AppSize = app_size
   Boot 计算 Flash CRC → 存 app_size/app_crc 到参数区
   返回 CRC 给主机比对
   参数区 state 保持 UPDATE_REQUEST（未改变）

5. JUMP_TO_APP
   Boot 重算 CRC → 与参数区 app_crc 比对 → 向量表检查 → 写 IMAGE_PENDING → 等 CLEAR → 跳转
   这是升级全过程中 state 第一次改变（UPDATE_REQUEST → IMAGE_PENDING）
```

---

## 8. 帧示例

### 8.1 HANDSHAKE

请求帧（10 字节，一次 I2C 写入）：

```text
S + SLA(W) + 0x20 +
  6D AC        Magic
  01           Version
  20           Cmd = HANDSHAKE
  01           Seq
  00           Flags
  00 00        PayloadLen = 0
  ## ##        CRC16
+ P
```

响应帧（14 字节）：

```text
S + SLA(W) + 0x20 + Sr + SLA(R) +
  6D AC        Magic
  01           Version
  20           Cmd (回显)
  01           Seq (回显)
  00           Flags
  04 00        PayloadLen = 4
  00           Payload[0] = OK
  01           Payload[1] = 协议版本 0x01
  00 02        Payload[2:3] = 每包最大固件数据 = 512
  ## ##        CRC16
+ P
```

### 8.2 ERASE_FLASH

请求帧（14 字节）：

```text
S + SLA(W) + 0x20 +
  6D AC        Magic
  01           Version
  24           Cmd = ERASE_FLASH
  02           Seq
  00           Flags
  04 00        PayloadLen = 4
  00 50 00 00  Payload[0:3] AppSize = app_size（例如 20KB = 0x5000）
  ## ##        CRC16
+ P
```

响应帧（11 字节）：

```text
S + SLA(W) + 0x20 + Sr + SLA(R) +
  6D AC 01 24 02 00 01 00 00 ## ##
  ↑              ↑  ↑     ↑  ↑
  Header(6B)     PL=1 OK   CRC16
+ P
```

### 8.3 APP_DOWNLOAD（256 字节数据）

请求帧（270 字节）：

```text
S + SLA(W) + 0x20 +
  6D AC        Magic
  01           Version
  22           Cmd = APP_DOWNLOAD
  05           Seq
  00           Flags
  04 01        PayloadLen = 260 (= 4 + 256)
  00 20 00 00  Payload[0:3] FlashAddr = 0x00002000
  [256 bytes]  Payload[4:259] 固件数据
  ## ##        CRC16
+ P
```

也可以分两次写入（每包 128 字节数据 + 4 字节 FlashAddr = 132 字节 payload）：

```text
Part1: S + SLA(W) + 0x20 +  [Header(8) + FlashAddr(4) + Firmware[0:127]]   + P
                            ↑ 从 0x20 写，自动增量到 0xAB
Part2: S + SLA(W) + 0xAC +  [Firmware[128:255] + CRC16(2)]                  + P
                            ↑ 从 0xAC 继续写
```

### 8.4 CRC_FLASH

请求帧（14 字节）：

```text
S + SLA(W) + 0x20 +
  6D AC        Magic
  01           Version
  25           Cmd = CRC_FLASH
  06           Seq
  00           Flags
  04 00        PayloadLen = 4
  00 50 00 00  Payload[0:3] AppSize = app_size（例如 20KB = 0x5000）
  ## ##        CRC16
+ P
```

响应帧（13 字节）：

```text
S + SLA(W) + 0x20 + Sr + SLA(R) +
  6D AC        Magic
  01           Version
  25           Cmd (回显)
  06           Seq (回显)
  00           Flags
  03 00        PayloadLen = 3
  00           Payload[0] = OK
  ## ##        Payload[1:2] = Flash CRC16 小端
  ## ##        CRC16
+ P
```

### 8.5 JUMP_TO_APP

请求帧（10 字节）：

```text
S + SLA(W) + 0x20 +
  6D AC 01 21 07 00 00 00 ## ##
  ↑                        ↑
  Header(8B) PayloadLen=0  CRC16
+ P
```

响应帧（11 字节）：

```text
S + SLA(W) + 0x20 + Sr + SLA(R) +
  6D AC 01 21 07 00 01 00 00 ## ##
+ P

Master Write CTRL = CLEAR:
S + SLA(W) + 0x02 + 0x5A + P

→ Boot 延时 5ms，复位外设，跳 APP。此后无 Bootloader 响应。
```

### 8.6 错误响应示例（ERASE_FLASH 地址未对齐）

```text
S + SLA(W) + 0x20 + Sr + SLA(R) +
  6D AC        Magic
  01           Version
  24           Cmd (回显)
  02           Seq (回显)
  00           Flags
  01 00        PayloadLen = 1
  04           Payload[0] = ADDR_ERROR
  ## ##        CRC16
+ P
```

---

## 9. 寄存器读写事务格式汇总

| 操作 | I2C 序列 |
|------|----------|
| 读 STATUS | `S + SLA(W) + 0x00 + Sr + SLA(R) + 1B + P` |
| 读 ERROR | `S + SLA(W) + 0x01 + Sr + SLA(R) + 1B + P` |
| 写 CTRL | `S + SLA(W) + 0x02 + 1B + P` |
| 读 TX_LEN | `S + SLA(W) + 0x06 + Sr + SLA(R) + 2B + P` |
| 写 MAILBOX | `S + SLA(W) + 0x20 + NB + P` |
| 读 MAILBOX | `S + SLA(W) + 0x20 + Sr + SLA(R) + NB + P` |

所有多字节数据传输均小端，地址自动增量。

---

## 10. 命令码空间

| 范围 | 用途 |
|------|------|
| `0x20` ~ `0x2F` | 控制类命令（HANDSHAKE, JUMP_TO_APP, JUMP_TO_BOOT 等） |
| `0x22` | APP_DOWNLOAD |
| `0x23` | JUMP_TO_BOOT |
| `0x24` | ERASE_FLASH |
| `0x25` | CRC_FLASH |
| `0x30` ~ `0xFF` | 保留 |

---

## 11. 约束与限制

### 11.1 Flash 容量与地址

```
FLASH_SIZE     = 64KB = 65536 bytes (0x10000) 地址范围: 0x0000 ~ 0xFFFF
BOOT_SIZE      =  8KB =  8192 bytes (0x2000)  地址范围: 0x0000 ~ 0x1FFF, 16 sectors
BOOT_PARAM     =        512 bytes  (0x200)    地址范围: 0x1E00 ~ 0x1FFF, boot 区域最后一扇区
APP_ADDR       = 0x2000
APP_MAX_SIZE   = FLASH_SIZE - BOOT_SIZE - FLASH_SECTOR_SIZE
               = 65536 - 8192 - 512 = 56832 bytes (0xDE00) ≈ 55.5KB
               = 111 个扇区
```

### 11.2 协议限制

| 项目 | 限制 | 说明 |
|------|------|------|
| MAILBOX 容量 | 530 字节 | PayloadLen ≤ 512，Header 8 + CRC 2 = 10，总 = 8+512+2 = 522 |
| IAP_FLASH_DATA_MAX | 512 字节 | 每包最大固件数据，HANDSHAKE 时返回给主机 |
| IAP_PAYLOAD_MAX | 516 字节 | = 4(FlashAddr) + 512(固件数据) |
| 帧最大长度 | 526 字节 | Header(8) + Payload(516) + CRC(2) |
| Flash 扇区大小 | 512 字节 | 擦除最小单元，ERASE_FLASH 按扇区对齐 |
| 轮询超时 | ≥ 300ms | Flash 擦写/CRC 操作期间 |

### 11.3 最大 APP 下载包数

当固件大小达到 `APP_MAX_SIZE = 56832 字节` 时：

```
总包数 = ceil(APP_MAX_SIZE / IAP_FLASH_DATA_MAX)
       = ceil(56832 / 512)
       = 111 包

最后一包固件数据 = 56832 - (110 × 512) = 512 字节
（恰好填满，无余数）
```

### 11.4 实测耗时（MCU @ 48MHz）

以下数据基于最大 APP 固件（56832 字节 = 111 包）测试。每个阶段的时间为 **主机写 COMMIT 到 STATUS 变为 RESP_READY** 的全程，即 Bootloader 内部处理 + I2C SCL Stretch 等待时间之和。

| 阶段 | 耗时 | 说明 |
|------|------|------|
| ERASE_FLASH | ≈ 288 ms | 擦除 111 个扇区（APP 区域），约 2.6ms/扇区 |
| APP_DOWNLOAD × 1 包 | ≈ 25 ms | 写 512 字节（Flash 字节编程 + 回读校验） |
| APP_DOWNLOAD × 111 包 | ≈ 2775 ms | 全部固件数据写入，25ms × 111 |
| CRC_FLASH | ≈ 247 ms | 从 Flash 读取 56832 字节计算 CRC16 |
| JUMP_TO_APP | ≈ 247 ms | 重算 CRC（同 CRC_FLASH）+ 向量表检查 + 跳转 |

**完整升级总耗时**：≈ 288 + 2775 + 247 + 247 ≈ **3.6 秒**（不含主机侧 I2C 传输时间，也不含 HANDSHAKE / JUMP_TO_BOOT 等辅助命令）。

**冷启动额外耗时**：`IMAGE_VALID` 状态下每次上电执行 CRC 校验（`IAP_VerifyAppCrc`），读取 APP Flash 区域计算 CRC16，耗时与 APP 固件大小成正比。最大固件（56832 字节）约 **247ms**。CRC 通过后立即跳转。用户侧感知的启动延迟：

```
冷启动 → 4MHz 默认时钟 → HC32_SysClockInit(48MHz) → IAP_UpdateCheck
  → IMAGE_VALID → 串口打印(≈7ms) + CRC 校验(≈247ms@最大固件) → OK → 跳 APP
  → APP 初始化 → 串口输出 "E6_APP boot 0x55AAAA55 IMAGE_VALID"
总耗时约 260ms（含时钟切换、串口打印、CRC 校验、跳转）
```

> 小固件时 CRC 更快，例如 6272 字节固件 CRC 仅约 27ms，此时串口打印（7ms）占比相对明显，总冷启动约 40ms。上述 247ms 为最大固件（55.5KB）的保守估值。

> 串口打印采用 115200-8N1 轮询模式，每字节耗时 86.8μs。Bootloader 在跳 APP 前共输出约 85 字节（约 7.4ms），这部分延迟在 CRC 校验（247ms）期间被消化，对整体冷启动影响可忽略。

**主机侧轮询建议**：

上述 Flash 操作时间长（≥ 247ms），且在操作期间 I2C ISR 被阻塞，SCL Stretching 会使主机 I2C 适配器持续等待。部分 USB-I2C 适配器在长时间 Stretch 时可能触发超时。

建议主机在写 COMMIT 后先延时 **500ms**，再开始轮询 STATUS：

| 阶段 | COMMIT 后建议等待 | 原因 |
|------|-------------------|------|
| ERASE_FLASH | 500ms | 擦除约 288ms，500ms 足够完成 |
| CRC_FLASH | 500ms | CRC 约 247ms，500ms 足够 |
| JUMP_TO_APP | 500ms | CRC 重算约 247ms，500ms 足够 |
| APP_DOWNLOAD | 50ms | 每包写入约 25ms，50ms 足够完成后首次轮询即读到 RESP_READY |

> **注意**：所有命令 COMMIT 后都先延时再轮询，避免 SCL 长时间 Stretch 导致 USB-I2C 适配器超时。

**说明**：

- Bootloader 在处理命令时（Flash 擦写/CRC），I2C ISR 无法响应主机轮询。HC32L021 I2C 硬件通过 SCL Clock Stretching 自动拉低 SCL 等待 CPU 恢复。因此主机看到的 "COMMIT → RESP_READY" 时间就是 Bootloader 的纯处理时间，主机 I2C 适配器的传输速度不影响这个计时。
- CRC 计算（Flash 读取 + CRC16 运算）约 247ms = 4.35μs/字节（纯 CPU @ 48MHz，不含 Flash 等待）。
- APP_DOWNLOAD 每包约 25ms，其中 Flash 字节编程是主要开销（HC32L021 Flash 编程约 40~50μs/字节），加上 512 字节回读校验。

---

## 12. 从机内部实现要点

### 12.1 MAILBOX 写入处理

```c
// I2C ISR 中
void HSI2C_IRQHandler(void)
{
    uint32_t flag = HSI2Cx->SSR;

    // 接收数据
    if (flag & HSI2C_SLAVE_FLAG_RDF) {
        uint8_t data = HSI2Cx->SRDR;
        if (rx_mailbox_index < IAP_MAILBOX_SIZE)
            rx_mailbox[rx_mailbox_index++] = data;
    }

    // STOP 检测
    if (flag & HSI2C_SLAVE_FLAG_SDF) {
        if (rx_mailbox_index >= 10)
            status = IDLE;       // 等待 COMMIT
        else
            status = ERROR, error = FRAME_ERROR;
    }

    // 地址有效 — 记录寄存器地址
    if (flag & HSI2C_SLAVE_FLAG_AVF) {
        // 读 SASR 获取 slave address
        // 用 u8SubAddr[0] 获取寄存器地址
        if (sub_addr >= 0x20 && sub_addr <= 0x231)
            rx_mailbox_index = sub_addr - 0x20;  // 从指定偏移开始
    }
}
```

### 12.2 主循环

```c
void Boot_MainLoop(void)
{
    while (1) {
        if (ctrl_commit_pending && status == IDLE) {
            status = BUSY;
            en_result_t ret = ParseAndExecute();      // 帧解析 + Flash 操作
            BuildResponse(ret);                       // 构造 tx_mailbox
            tx_len = compute_tx_len();
            status = (ret == Ok) ? RESP_READY : ERROR;
        }

        if (ctrl_clear_pending && status == RESP_READY) {
            status = IDLE;
            error = OK;
            tx_len = 0;
        }

        if (ctrl_abort_pending) {
            status = IDLE;
            tx_len = 0;
        }

        if (jump_pending && cleared) {
            Delay_ms(5);
            IAP_ResetConfig();
            __disable_irq();
            IAP_JumpToApp(APP_ADDR);
        }
    }
}
```

### 12.3 掉电保护

掉电保护贯穿整个升级流程：

**① JUMP_TO_BOOT（前置步骤）**：

APP 收到 JUMP_TO_BOOT 后、复位前写入 `UPDATE_REQUEST`。如果主机之后掉电，重新上电时 Bootloader 读到 `UPDATE_REQUEST`，留在 Boot 等待主机命令，不会跳转到损坏的 APP。

**② ERASE_FLASH**：

ERASE_FLASH **不写参数区**。此时 Flash 中的 APP 区域虽然正在被擦除，但参数区 state 仍是 `UPDATE_REQUEST`（来自前一步），掉电重启后 Bootloader 读到 `UPDATE_REQUEST`，同样停留在 IDLE。

**③ CRC_FLASH**：

CRC_FLASH 写入 `app_size` / `app_crc`，但 state **未改变**（仍然是 `UPDATE_REQUEST`）。此时掉电重启不影响——Bootloader 仍因 `UPDATE_REQUEST` 停在 IDLE。

**④ JUMP_TO_APP**：

校验通过后写入 `IMAGE_PENDING`，然后等待主机 CLEAR。如果 CLEAR 后跳转前掉电，重启后 `IMAGE_PENDING` → Bootloader 不会跳转（单次尝试策略）。APP 成功启动后自行写入 `IMAGE_VALID`，下次冷启动才能直接跳转。

> **总结**：参数区 state 变化链很简单：
> - 预烧录时参数区自带 `IMAGE_VALID` 或 `UPDATE_REQUEST`
> - `JUMP_TO_BOOT`（APP 侧）：`(任意) → UPDATE_REQUEST`
> - `JUMP_TO_APP`（Boot 侧）：`UPDATE_REQUEST → IMAGE_PENDING`
> - APP 启动成功：`IMAGE_PENDING → IMAGE_VALID`
>
> ERASE_FLASH 只擦除 APP Flash 区域，不动参数区。

---

*协议版本 0x02，最后更新 2026-06-23。*
