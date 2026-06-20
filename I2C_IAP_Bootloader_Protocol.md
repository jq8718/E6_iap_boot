# HC32L021 I2C IAP Bootloader 协议规格

> 基于 `I2C_IAP_Bootloader_Design.md` 讨论迭代后的最终协议规格。

---

## 1. I2C 从机配置

### 1.1 硬件要求

| 参数 | 值 | 说明 |
|------|------|------|
| Sub-address | **1 字节** | `u8SubAddrSize = 1`，用于虚拟寄存器寻址 |
| SCL Stall | **必须启用** | `TXDSTALL`, `RXSTALL`, `ACKSTALL` 全部使能 |
| 从机地址 | 自定义 | 7-bit 或 10-bit，不与总线其他器件冲突 |
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
| `0x02` | `REG_CTRL` | W | 1 | 主机写 | 控制命令（COMMIT/CLEAR/ABORT） |
| `0x03`~`0x05` | *保留* | R | — | — | 读返回 `0x00`，写忽略 |
| `0x06` | `REG_TX_LEN` | R | 2 LE | 主机读 | 响应帧长度（仅 `RESP_READY` 有效） |
| `0x07`~`0x0F` | *保留* | R | — | — | 读返回 `0x00`，写忽略 |
| `0x10`~`0x1F` | *保留* | R/W | — | — | 预留，当前无功能 |
| `0x20`~`0x231` | `REG_MAILBOX` | W/R | 530 | 主机读写 | 请求帧写入 / 响应帧读取 |

**实现代码定义**（`source/utils.h`）：

```c
/* 寄存器地址 */
#define REG_STATUS        (0x00u)
#define REG_ERROR         (0x01u)
#define REG_CTRL          (0x02u)
#define REG_TX_LEN        (0x06u)
#define REG_MAILBOX_START (0x20u)
#define REG_MAILBOX_END   (0x231u)

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
IDLE ──(COMMIT)──→ BUSY ──(成功)──→ RESP_READY ──(CLEAR)──→ IDLE
                     │                                       │
                     └──(失败)──→  ERROR  ──(CLEAR/ABORT)──→ IDLE
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
1. `PayloadLen` 合法（`0` ~ `IAP_PAYLOAD_MAX`）
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
| HANDSHAKE | 4 | `[0]=OK` `[1]=协议版本` `[2:3]=PAYLOAD_MAX` |
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

| Cmd | 名称 | Payload | PayloadLen | 帧总长 |
|------|------|---------|-----------|--------|
| `0x20` | HANDSHAKE | 无 | 0 | 10 |
| `0x24` | ERASE_FLASH | AppSize(4) | 4 | 14 |
| `0x22` | APP_DOWNLOAD | FlashAddr(4) + 固件数据 | 4+N | 14+N |
| `0x25` | CRC_FLASH | AppSize(4) | 4 | 14 |
| `0x21` | JUMP_TO_APP | 无 | 0 | 10 |

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

```text
1. HANDSHAKE
   获取协议版本和 PAYLOAD_MAX

2. ERASE_FLASH
   AppSize = app_size
   Boot 内部做扇区对齐，擦除 >= app_size 的最小扇区数

3. APP_DOWNLOAD × N
   offset = 0
   while offset < app_size:
       chunk_len = min(app_size - offset, PAYLOAD_MAX - 4)
       Payload = FlashAddr(4) + app_bin[offset : offset + chunk_len]
       offset += chunk_len

4. CRC_FLASH
   AppSize = app_size
   Boot 计算 CRC → 存 app_size/app_crc 到参数区 → 返回 CRC
   主机比对 Flash CRC 与本地 CRC

5. JUMP_TO_APP
   Boot 重算 CRC → 与参数区 app_crc 比对 → 向量表检查 → 写 IMAGE_PENDING → 跳转
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
  00 02        Payload[2:3] = PAYLOAD_MAX = 512
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
APP固件长度，APP固件CRC，应该记录在bootload中，CRC_FLASH时下发APP固件长度，boot计算CRC后
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
| `0x20` ~ `0x2F` | 控制类命令（HANDSHAKE, JUMP_TO_APP 等） |
| `0x22` | APP_DOWNLOAD |
| `0x24` | ERASE_FLASH |
| `0x25` | CRC_FLASH |
| `0x30` ~ `0xFF` | 保留 |

---

## 11. 约束与限制

| 项目 | 限制 | 说明 |
|------|------|------|
| MAILBOX 容量 | 530 字节 | PayloadLen ≤ 512，Header 8 + CRC 2 = 10，总 = 8+512+2 = 522 |
| Payload 上限 | 512 字节 | 主机通过 HANDSHAKE 获取实际值 |
| APP_DOWNLOAD 单包数据 | ≤ 508 字节 | PayloadLen(512) - FlashAddr(4) |
| 帧最小长度 | 10 字节 | Header 8 + CRC 2，PayloadLen = 0 |
| 帧最大长度 | 522 字节 | Header 8 + Payload(512) + CRC 2 |
| Flash 地址对齐 | 512 字节 | ERASE_FLASH 要求 |
| 轮询超时 | ≥ 100ms | Flash 操作期间 |

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

ERASE_FLASH 执行前，Boot 内部自动写入 Boot 参数区 `UPDATE_REQUEST`：

```c
// ERASE_FLASH 命令执行
if (param.state != UPDATE_REQUEST) {
    BootParam_WriteState(UPDATE_REQUEST);
}
// 然后擦除
for (each sector) {
    HC32_FlashEraseSector(sector_addr);
}
```

重新上电时读到 `UPDATE_REQUEST` → 留在 Boot → 主机重新发起升级。

---

*协议版本 0x02，最后更新 2026-06-20。*
