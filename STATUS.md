# I2C IAP Bootloader 代码状态总结

## 编译状态

**Release 构建通过** — 0 Error(s), 0 Warning(s)

```
Program Size: Code=6042 RO-data=478 RW-data=4 ZI-data=2140
Build: MDK/iap_boot_Release (ARMCC V6.10.1)
```

## 系统架构

```
main()
  ├─ HC32_SysClockInit(48MHz)
  ├─ IAP_UpdateCheck()    // 参数区状态检查，可能直接跳 APP
  ├─ IAP_Init()           // 外设初始化 (I2C + Timer)
  ├─ IAP_Main()           // 进入 I2C 主循环
  └─ while(1)
```

## 跳转保护（双层）

### 冷启动路径 (IAP_UpdateCheck → IMAGE_VALID)

1. **CRC 自校验** (`IAP_VerifyAppCrc`) — 重新计算 APP Flash 区域完整 CRC16，与参数区 `app_crc` 比对
2. **向量表保护** (`IAP_JumpToApp`)：
   - Stack Pointer 必须在 SRAM 范围 `[0x20000000, 0x20001800)`
   - ResetHandler 必须在 APP Flash 范围 `[0x2000, 0x2000 + APP_MAX_SIZE)` 且 LSB=1（Thumb 地址）

### IAP 路径 (CMD_JUMP_TO_APP)

`CmdJumpToApp` 中依次执行：

1. Magic 校验 → header_crc 校验 → app_size > 0
2. 重新计算 APP Flash CRC16，比对 app_crc
3. 向量表 SP 合法性检查
4. **写入 `IMAGE_PENDING`** 到参数区（单次尝试策略）
5. 等待主机 CLEAR → `MODEM_Process()` 返回 `Ok` → `IAP_Main()` 调用 `IAP_JumpToApp()`

### 掉电保护

| 阶段 | 参数区 state | 掉电后果 |
|------|-------------|---------|
| 预烧录 | `IMAGE_VALID` / `UPDATE_REQUEST` | 正常启动或停在 Boot |
| JUMP_TO_BOOT (APP 侧) | → `UPDATE_REQUEST` | 重启后 Boot 等待 IAP |
| ERASE_FLASH | 不变 | 仍为 `UPDATE_REQUEST` |
| CRC_FLASH | 不变（仅写 app_size/app_crc） | 仍为 `UPDATE_REQUEST` |
| JUMP_TO_APP 写 PENDING 后掉电 | `IMAGE_PENDING` | Boot 不跳转（单次尝试） |
| APP 启动成功 | → `IMAGE_VALID` | 下次冷启动直接跳 |

## 通信方案

| 项目 | 规格 |
|------|------|
| 通信接口 | HSI2C 从机 |
| I2C 从机地址 | 0x32 (7-bit) |
| I2C 引脚 | PA06(SDA) / PA07(SCL), 开漏输出 |
| SCL Stretch | TXDSTALL + RXSTALL + ACKSTALL |
| 时钟 | 上电 4MHz → Boot 初始化 48MHz |
| 虚拟寄存器映射 | `s_au8RegFile[0x20]` — sub-addr 0x00~0x1F 直接查表 |
| MAILBOX | 0x20~0x231 (530 字节) |
| 调试串口 | LPUART1 TX PA01, 115200-8N1, **发布版关闭** (`BOOT_DBG_ENABLE=0`) |

## 固件版本号

| 寄存器 | 值 | 说明 |
|--------|-----|------|
| `REG_FW_VERSION_HIGH` (0x05) | `0x81` | bit15=1 标识 Boot + v1.0 高字节 |
| `REG_FW_VERSION_LOW` (0x04) | `0x00` | v1.0 低字节 |
| 16-bit 合成值 | `0x8100` | Boot firmware v1.0 |

## Flash 布局

| 区域 | 起始地址 | 结束地址 | 大小 | 扇区 |
|------|---------|---------|------|------|
| BOOT 程序 | `0x00000000` | `0x00001DFF` | 7.5KB (0x1E00) | 0~14 |
| BOOT 参数区 | `0x00001E00` | `0x00001FFF` | 512B (0x200) | 15 |
| APP 区 | `0x00002000` | `0x0000FDFF` | 55.5KB (0xDE00) | 16~126 |
| 保留 | `0x0000FE00` | `0x0000FFFF` | 512B (0x200) | 127 |

## 命令支持

| 命令 | 码值 | Payload | 说明 |
|------|------|---------|------|
| HANDSHAKE | `0x20` | 无 | 协议握手，返回版本和 FLASH_DATA_MAX |
| JUMP_TO_APP | `0x21` | 无 | CRC 校验 → 写 PENDING → 等 CLEAR → 跳转 |
| APP_DOWNLOAD | `0x22` | FlashAddr(4) + 数据 | 写固件数据到 Flash |
| ERASE_FLASH | `0x24` | AppSize(4) | 擦除 APP 区域扇区 |
| CRC_FLASH | `0x25` | AppSize(4) | 计算并存储 Flash CRC16 |

## 关键源文件

| 文件 | 功能 |
|------|------|
| `source/main.c` | 入口，调用顺序控制 |
| `source/iap.c` | 状态机、CRC 校验、跳转逻辑 |
| `source/modem.c` | I2C 从机 ISR、虚拟寄存器、命令处理 |
| `source/utils.h` | 宏定义（寄存器地址、命令码、状态值等） |
| `source/boot_param.c` | 参数区读写、状态管理 |
| `source/config_hc32l021.c` | 外设初始化（时钟、I2C、GPIO、Timer、Flash 驱动） |
| `source/boot_param.h` | 参数区结构体定义 |
| `source/modem.h` | MODEM API 声明 |
| `source/iap.h` | IAP API 声明 |

## RAM 定义

```c
#define SRAM_BASE ((uint32_t)0x20000000)
#define RAM_SIZE  (0x1800u)   /* 6KB */
```

SP 检查范围：`0x20000000` ~ `0x20001800`。
