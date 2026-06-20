# I2C IAP Bootloader 代码实现计划

> 基于 [I2C_IAP_Bootloader_Protocol.md](I2C_IAP_Bootloader_Protocol.md) 协议文档，
> 将现有 UART Bootloader 重构为 I2C 从机 Bootloader。

---

## 一、改造总览

```
现有通信:  LPUART1 (PA01/PA02)  →  目标通信:  HSI2C 从机 (PA03/PA04 或其他 I2C 引脚)
现有帧格式: 6B Shell + 10B 指令段  →  目标帧格式: 8B 统一 Header + Payload + CRC16
现有命令: 7 条                     →  目标命令: 5 条（去掉 UPLOAD/START_UPDATE）
现有参数区: 单 FLAG 值             →  目标参数区: stc_boot_param_t 五状态机
```

## 二、文件变更清单

### 2.1 新增文件

| 文件 | 职责 |
|------|------|
| `source/boot_param.h` | Boot 参数区结构体 + 状态枚举 + API 声明 |
| `source/boot_param.c` | 参数区读写、状态迁移、Flash 操作封装 |

### 2.2 修改文件

| 文件 | 变更程度 | 内容 |
|------|----------|------|
| `source/utils.h` | 中 | 新增 Boot 参数区/状态/I2C 从机地址等宏，修改中断映射为 HSI2C |
| `source/modem.h` | 大 | 新协议常量和 API 声明 |
| `source/modem.c` | 大 | I2C 从机中断 + 虚拟寄存器 + 新帧解析 + 5 条命令实现 |
| `source/iap.h` | 小 | 声明可能微调 |
| `source/iap.c` | 大 | 状态机 IAP_UpdateCheck + CRC 自验证 + 参数区写入 |
| `source/config_hc32l021.h` | 中 | 新增 HSI2C 从机初始化/反初始化声明 |
| `source/config_hc32l021.c` | 中 | 替换 LPUART1 → HSI2C，保留 BTIM0 |
| `source/main.c` | 小 | 可能微调流程 |

### 2.3 不修改的文件

| 文件 | 原因 |
|------|------|
| `common/` 所有文件 | 硬件无关，不动 |
| `driver/` 所有文件 | DDL 库，不动 |
| `EWARM/` `MDK/` | IDE 工程文件，编译时自动关联 |

---

## 三、分模块设计

### 模块 A：`utils.h` — 宏定义更新

**新增内容：**

```c
/* I2C 从机地址 */
#define I2C_SLAVE_ADDR          (0x30u)   // 7-bit I2C 从机地址，可配置

/* Boot 参数区 */
#define BOOT_PARAM_ADDR         (FLASH_START_ADDR + BOOT_SIZE - FLASH_SECTOR_SIZE)
#define BOOT_PARAM_MAGIC        ((uint32_t)0x48434C42u)  // "HCLB" = HC32L Boot

/* 参数区状态枚举 */
#define IMAGE_STATE_EMPTY          ((uint32_t)0xFFFFFFFFu)
#define IMAGE_STATE_UPDATE_REQUEST ((uint32_t)0xA5A55A5Au)
#define IMAGE_STATE_PENDING        ((uint32_t)0x5AA55AA5u)
#define IMAGE_STATE_VALID          ((uint32_t)0x55AAAA55u)
#define IMAGE_STATE_INVALID        ((uint32_t)0xDEAD0001u)

/* 协议常量 */
#define IAP_MAILBOX_SIZE         (530u)
#define IAP_PAYLOAD_MAX          (512u)
#define IAP_HEADER_SIZE          (8u)
#define IAP_CRC_SIZE             (2u)
#define IAP_FRAME_MIN            (10u)   // Header 8 + CRC 2
#define IAP_FRAME_MAX            (522u)  // Header 8 + Payload 512 + CRC 2
#define IAP_PROTOCOL_VERSION     (0x01u)

/* 虚拟寄存器地址 */
#define REG_STATUS               (0x00u)
#define REG_ERROR                (0x01u)
#define REG_CTRL                 (0x02u)
#define REG_TX_LEN               (0x06u)
#define REG_MAILBOX_START        (0x20u)
#define REG_MAILBOX_END          (0x231u)

/* CTRL 寄存器值 */
#define CTRL_COMMIT              (0xA5u)
#define CTRL_CLEAR               (0x5Au)
#define CTRL_ABORT               (0xC3u)

/* STATUS 寄存器值 */
#define STATUS_IDLE              (0x00u)
#define STATUS_BUSY              (0x02u)
#define STATUS_RESP_READY        (0x03u)
#define STATUS_ERROR             (0x04u)

/* ERROR 码 - 与响应帧 Payload[0] 一致 */
#define ERROR_CODE_OK              (0x00u)  // 复用 Ok=0
#define ERROR_CODE_CRC             (0x01u)
#define ERROR_CODE_FRAME           (0x02u)
#define ERROR_CODE_UNSUPPORTED     (0x03u)
#define ERROR_CODE_ADDR            (0x04u)
#define ERROR_CODE_FLASH           (0x05u)
#define ERROR_CODE_BUSY            (0x06u)
#define ERROR_CODE_SEQ             (0x07u)
#define ERROR_CODE_APP_INVALID     (0x08u)

/* 命令码 */
#define CMD_HANDSHAKE              (0x20u)
#define CMD_JUMP_TO_APP            (0x21u)
#define CMD_APP_DOWNLOAD           (0x22u)
#define CMD_ERASE_FLASH            (0x24u)
#define CMD_CRC_FLASH              (0x25u)

/* 中断映射改为 HSI2C */
#define MODEM_I2cIrqHandler(void)  HSI2C_IRQHandler(void)
```

**删除内容：**
- `APP_FLAG` 宏（改为使用参数区状态值）
- 旧 UART 中断映射
- 旧帧格式宏（FRAME_HEAD_L, FRAME_SHELL_SIZE 等——移到 modem.c 删除）

---

### 模块 B：`boot_param.h` / `boot_param.c` — Boot 参数区

**`boot_param.h` 核心定义：**

```c
// Boot 参数区结构体（16 字节，对齐 Flash 写入最小单元）
typedef struct {
    uint32_t magic;        // BOOT_PARAM_MAGIC
    uint32_t state;        // 五状态值
    uint32_t app_addr;     // APP 首地址
    uint32_t app_size;     // APP 固件长度
    uint32_t app_crc;      // APP 固件 CRC16
    uint32_t boot_count;   // 保留（不递增）
    uint32_t app_version;  // APP 版本号
    uint32_t header_crc;   // 前 28 字节的 CRC 校验
} stc_boot_param_t;

void    BootParam_Init(void);
void    BootParam_Read(stc_boot_param_t *param);
en_result_t BootParam_Write(const stc_boot_param_t *param);
en_result_t BootParam_WriteState(uint32_t state);
en_result_t BootParam_WriteAppInfo(uint32_t size, uint16_t crc);
void    BootParam_Erase(void);
```

**`boot_param.c` 实现要点：**

- `BootParam_Init()`：读取 BOOT_PARAM_ADDR，如果 magic 不匹配则初始化为全 FF（含 magic 写入）
- `BootParam_Read()`：直接从 Flash 地址 memcpy 出来
- `BootParam_Write()`：先擦除整个参数区扇区，再逐字节写回（Cortex-M0+ Flash 按字节编程）
- `BootParam_WriteState()`：只改 state 字段，按 Flash 编程时序写入单字
- `BootParam_WriteAppInfo()`：写入 app_size 和 app_crc 两字段
- 使用 `HC32_FlashEraseSector` / `HC32_FlashWriteBytes`（复用现有驱动）
- 计算 `header_crc`：对结构体前 28 字节做 CRC16，保护参数区完整性

---

### 模块 C：`config_hc32l021.c` / `.h` — 外设初始化改造

**关键改动：**

1. **删除** `HC32_Lpuart1Init()` / `HC32_Lpuart1DeInit()`
2. **删除** GPIO PA01/PA02 初始化
3. **新增** `HC32_I2cSlaveInit()`：
   ```c
   void HC32_I2cSlaveInit(void)
   {
       // 1. GPIO: PA03=SCL, PA04=SDA (或其他 I2C 引脚)
       //    - 配置为 HSI2C 功能复用
       // 2. HSI2C_SlaveStcInit(&stcSlaveInit)       // 结构体默认值
       // 3. stcSlaveInit.u8SubAddrSize = 1
       // 4. stcSlaveInit.u32SlaveAddr0 = I2C_SLAVE_ADDR
       // 5. stcSlaveInit.stcSlaveConfig1.u32FuncSelect =
       //        HSI2C_SLAVE_TXDSTALL_ENABLE |
       //        HSI2C_SLAVE_RXSTALL_ENABLE  |
       //        HSI2C_SLAVE_ACKSTALL_ENABLE
       // 6. HSI2C_SlaveInit(HSI2Cx, &stcSlaveInit, SYS_CLK_INIT_HZ)
       // 7. 使能中断: HSI2C_SLAVE_INT_AVIE | SDIE | RDIE | TDIE | FEIE | BEIE
       // 8. NVIC: EnableNvic(HSI2C_IRQn, ...)
   }
   ```
4. **新增** `HC32_I2cSlaveDeInit()`：时钟关 + 模块复位
5. **保留** `HC32_Btim0Init/DeInit`（超时监测定时器）
6. **保留** `HC32_SysClockInit/DeInit`、`HC32_CalCrc16`、Flash 驱动

**注意**：I2C 引脚需要查阅 HC32L021 数据手册确认——PA03/PA04 通常可复用为 SCL/SDA，用 `GPIO_PIN_SEL` 设置功能复用。

---

### 模块 D：`modem.c` / `.h` — 通信协议层（核心重构）

这是工作量最大的模块，完全重写。

#### D.1 静态变量

```c
// 虚拟寄存器
static volatile uint8_t  reg_status;     // STATUS
static volatile uint8_t  reg_error;      // ERROR
static volatile uint16_t reg_tx_len;     // TX_LEN

// MAILBOX 双缓冲
static uint8_t  rx_mailbox[IAP_MAILBOX_SIZE];  // 接收（主机写入）
static uint8_t  tx_mailbox[IAP_MAILBOX_SIZE];  // 发送（主机读取）
static volatile uint16_t rx_mailbox_idx;       // 当前写入位置
static volatile uint16_t tx_mailbox_len;       // 有效发送长度

// I2C 状态
static volatile uint8_t  hsi2c_sub_addr;       // 当前 sub-address
static volatile bool     ctrl_commit;          // COMMIT 请求标志
static volatile bool     ctrl_clear;           // CLEAR 请求标志
static volatile bool     ctrl_abort;           // ABORT 请求标志
static volatile bool     jump_pending;         // 跳转待执行
static volatile bool     cleared_after_jump;   // JUMP_TO_APP 后收到 CLEAR
```

#### D.2 I2C 从机 ISR (`MODEM_I2cIrqHandler`)

状态机处理的 I2C 事件（参考协议 12.1 节伪代码）：

```
1. 读取 HSI2Cx->SSR 获取中断标志

2. AVF (Address Valid):
   - 读取 sub-address → hsi2c_sub_addr = u8SubAddr[0]
   - 清零 rx_mailbox_idx = 0（新事务开始）
   - 如果进入 MAILBOX 范围(0x20~0x231)，设置 rx_mailbox_idx = sub_addr - 0x20

3. RDF (Receive Data Flag):
   - data = HSI2C_SlaveReadData()
   - 根据 hsi2c_sub_addr 路由：
     * CTRL(0x02):  根据值设置 ctrl_commit/ctrl_clear/ctrl_abort
     * MAILBOX(0x20~0x231): 写入 rx_mailbox[rx_mailbox_idx++]
     * 非 MAILBOX: 忽略或作为保留寄存器处理
   - 边界检查：rx_mailbox_idx >= IAP_MAILBOX_SIZE 时丢弃（但不崩溃）

4. TDF (Transmit Data Flag):
   - 根据 hsi2c_sub_addr 决定发送内容：
     * STATUS(0x00):   HSI2C_SlaveWriteData(reg_status)
     * ERROR(0x01):    HSI2C_SlaveWriteData(reg_error)
     * TX_LEN(0x06):   按序发送 reg_tx_len 低字节、高字节
     * MAILBOX(0x20~): 发送 tx_mailbox[offset] 并递增 offset

5. SDF (STOP Detect):
   - I2C 事务结束
   - 读 STATUS 或 ERROR 的事务：无操作
   - 写 CTRL 的事务：已在上面的 RDF 中设置了标志
   - 写 MAILBOX 的事务：rx_mailbox_idx 保留，等待 COMMIT

6. FEF (FIFO Error) / BEF (Bit Error):
   - 记录错误，可能触发状态回退

7. 清除中断标志
```

#### D.3 `MODEM_Process()` — 主循环处理

```c
en_result_t MODEM_Process(void)
{
    if (ctrl_commit) {
        ctrl_commit = false;

        // 基本帧校验
        if (rx_mailbox_idx < IAP_FRAME_MIN) {  // 至少 Header+CRC, PayloadLen=0
            reg_status = STATUS_ERROR;
            reg_error  = ERROR_CODE_FRAME;
            return OperationInProgress;
        }

        // 解析帧头部
        uint8_t  cmd         = rx_mailbox[3];
        uint8_t  seq         = rx_mailbox[4];
        uint8_t  flags       = rx_mailbox[5];
        uint16_t payload_len = rx_mailbox[6] | (rx_mailbox[7] << 8);
        uint16_t crc_offset  = 8 + payload_len;
        uint16_t crc_recv    = rx_mailbox[crc_offset] | (rx_mailbox[crc_offset+1] << 8);
        uint16_t crc_calc    = HC32_CalCrc16(rx_mailbox, 0, crc_offset);

        // 校验：Magic + Version + PayloadLen + CRC
        if (rx_mailbox[0] != 0x6D || rx_mailbox[1] != 0xAC ||
            rx_mailbox[2] != IAP_PROTOCOL_VERSION ||
            payload_len > IAP_PAYLOAD_MAX || flags != 0x00 ||
            crc_recv != crc_calc) {
            reg_status = STATUS_ERROR;
            reg_error  = ERROR_CODE_FRAME;
            return OperationInProgress;
        }

        reg_status = STATUS_BUSY;

        // 命令分发
        en_result_t ret = Error;
        switch (cmd) {
            case CMD_HANDSHAKE:    ret = IAP_HandleHandshake(seq);     break;
            case CMD_ERASE_FLASH:  ret = IAP_HandleEraseFlash(seq);   break;
            case CMD_APP_DOWNLOAD: ret = IAP_HandleAppDownload(seq);  break;
            case CMD_CRC_FLASH:    ret = IAP_HandleCrcFlash(seq);     break;
            case CMD_JUMP_TO_APP:  ret = IAP_HandleJumpToApp(seq);    break;
            default:
                reg_status = STATUS_ERROR;
                reg_error  = ERROR_CODE_UNSUPPORTED;
                return OperationInProgress;
        }

        // 构建响应帧 → tx_mailbox
        BuildResponse(tx_mailbox, &tx_mailbox_len, cmd, seq, ret, ...);
        reg_tx_len = tx_mailbox_len;

        if (ret == Ok) {
            reg_status = STATUS_RESP_READY;
            if (cmd == CMD_JUMP_TO_APP) {
                jump_pending = true;   // 等待 CLEAR 后跳转
            }
        } else {
            reg_status = STATUS_ERROR;
        }
    }

    // JUMP_TO_APP: 等主机发 CLEAR 后执行跳转
    if (jump_pending && cleared_after_jump) {
        // Boot 内部 CRC 验证（已在 HandleJumpToApp 中完成并写 IMAGE_PENDING）
        // 向量表检查
        IAP_ResetConfig();
        IAP_JumpToApp(APP_ADDR);  // 不返回
    }

    // CLEAR / ABORT 处理
    if (ctrl_clear && reg_status == STATUS_RESP_READY) {
        reg_status = STATUS_IDLE;
        reg_error  = ERROR_CODE_OK;
        reg_tx_len = 0;
        ctrl_clear = false;
        if (jump_pending) cleared_after_jump = true;
    }
    if (ctrl_abort) {
        reg_status = STATUS_IDLE;
        reg_tx_len = 0;
        ctrl_abort = false;
    }

    return OperationInProgress;  // 升级进行中
}
```

#### D.4 五个命令处理函数

**HANDSHAKE：**
```
响应: Payload = [OK, IAP_PROTOCOL_VERSION, IAP_PAYLOAD_MAX(LE16)]
      PayloadLen = 4
```

**ERASE_FLASH：**
```
Payload[0:3] = AppSize (uint32 LE)
1. 检查 AppSize 合法性（不超出 Flash 范围）
2. BootParam_WriteState(IMAGE_STATE_UPDATE_REQUEST)  ← 掉电保护
3. 计算扇区数 ceil(AppSize / FLASH_SECTOR_SIZE)
4. 从 APP_ADDR 开始逐个扇区擦除
5. 全部成功返回 OK
```

**APP_DOWNLOAD：**
```
Payload[0:3] = FlashAddr (uint32 LE)
Payload[4:N] = 固件数据
1. 检查 FlashAddr 范围 [APP_ADDR, FLASH_END]
2. HC32_FlashWriteBytes(FlashAddr, data, len)
3. 逐字节回读校验
```

**CRC_FLASH：**
```
Payload[0:3] = AppSize (uint32 LE)
1. 计算 Flash 区域 [APP_ADDR, APP_ADDR + AppSize) 的 CRC16
2. BootParam_WriteAppInfo(AppSize, crc16_result)
3. 响应: Payload = [OK, crc16_low, crc16_high]
```

**JUMP_TO_APP：**
```
1. 重算 Flash CRC 与参数区 app_crc 比对
2. 向量表检查（SP 和 ResetHandler 地址有效性）
3. 不通过 → APP_INVALID 错误
4. 通过 → BootParam_WriteState(IMAGE_STATE_PENDING)
5. 响应 Payload = [OK]
6. 等主机 CLEAR 后模块复位 + 跳转
```

#### D.5 旧代码删除清单（modem.c）

- 旧 `en_packet_cmd_t` 枚举（替换为新命令码宏）
- `PACKET_CMD_TYPE_DATA/CONTROL` 区分
- `FRAME_SHELL_SIZE`(6) 及相关宏
- `FRAME_HEAD_L/H`(0x6D/0xAC) — 保留值但改为 Header 中的 Magic
- `FRAME_NUM_XOR_BYTE`(0xFF) — 去掉序号异或校验
- `FRAME_RECV_TIMEOUT` — 保留超时机制但改为新协议
- `MODEM_UartIrqHandler` → `MODEM_I2cIrqHandler`
- `MODEM_UartSendData` → 去掉（I2C 从机不发主动数据）
- `PACKET_CMD_APP_UPLOAD`(0x23)、`PACKET_CMD_START_UPDATE`(0x26) — 去掉

---

### 模块 E：`iap.c` — 升级入口和跳转增强

**`IAP_UpdateCheck()` 改为：**

```c
void IAP_UpdateCheck(void)
{
    stc_boot_param_t param;
    BootParam_Read(&param);

    if (param.magic != BOOT_PARAM_MAGIC) {
        // 首次上电或参数区损坏 → 初始化参数区 → 直接跳 APP
        BootParam_Init();
        IAP_JumpToApp(APP_ADDR);
        return;
    }

    switch (param.state) {
    case IMAGE_STATE_VALID:          // 固件已验证 → 直接跳转
    case IMAGE_STATE_EMPTY:          // APP 区为空 → 留在 Boot
        IAP_JumpToApp(APP_ADDR);
        break;

    case IMAGE_STATE_UPDATE_REQUEST:  // 主机请求升级 → 留在 Boot
    case IMAGE_STATE_PENDING:         // 待验证（不重试）
    case IMAGE_STATE_INVALID:         // 标记无效 → 留在 Boot
    default:
        break;  // 留在 Bootloader，等待 I2C 通信
    }
}
```

**`IAP_JumpToApp()` 增强：**

```c
// 在原有栈顶检查基础上增加：
// 不擦除参数区（由主机通过 CLEAR 流程控制）
// 返回 Error 时调用者停止（while(1) 或重新进入 MODEM_Process）
```

**`IAP_Main()` 保持结构**：
```c
void IAP_Main(void)
{
    while (1) {
        enRet = MODEM_Process();
        if (Ok == enRet) {
            IAP_ResetConfig();
            IAP_JumpToApp(APP_ADDR);
        }
    }
}
```

---

### 模块 F：`main.c` — 入口调整

基本不变，保持：
```c
int32_t main(void)
{
    IAP_UpdateCheck();   // 检查参数区状态 — 可能直接跳 APP
    IAP_Init();          // 初始化外设（I2C + Timer）
    BootParam_Init();    // 初始化参数区（如果需要）
    IAP_Main();          // 进入 I2C 通信主循环
    while (1);
}
```

---

## 四、保留不变的内容

| 组件 | 说明 |
|------|------|
| `HC32_CalCrc16()` | 循环冗余校验算法完全不变 |
| `HC32_FlashEraseSector/WriteBytes/ReadBytes()` | Flash 驱动不变 |
| `HC32_Btim0Init/DeInit()` | 1ms 定时器保留，用于帧超时 |
| `MODEM_TimIrqHandler()` | 超时检测逻辑保留，适配新状态机 |
| `IAP_ResetConfig()` | 外设反初始化改名调用 I2C DeInit |
| `func_ptr_t` / `__set_MSP()` | 跳转机制不变 |

---

## 五、实现顺序

```
1. boot_param.c/h    — 参数区模块（独立，可单独测试）
2. utils.h           — 宏定义更新
3. config_hc32l021.c/h — I2C 外设初始化
4. modem.c/h         — 核心协议层（依赖 1~3）
5. iap.c             — 升级入口（依赖 1, 4）
6. main.c            — 整合（依赖全部）
```

---

## 六、验证要点

1. **参数区读写**：写入 → 断电 → 重新上电读出，验证数据完整性
2. **I2C 从机通信**：外接 I2C Master（PC 或另一 MCU）发送标准事务序列
3. **SCL Stretching**：Flash 擦写期间发 I2C 请求，确认不 NACK
4. **完整升级流程**：HANDSHAKE → ERASE → DOWNLOAD×N → CRC → JUMP_TO_APP
5. **掉电恢复**：ERASE_FLASH 中途断电 → 重新上电 → UPDATE_REQUEST → 主机重新升级
6. **异常路径**：无效帧/地址越界/CRC 错误 → 确认 ERROR 状态和错误码
7. **旧代码编译**：确认去掉的 UART 相关代码不会导致链接错误
