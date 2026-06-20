# I2C IAP Bootloader —— JumpToAPP 前必要检查项说明

## 一、协议要求

根据 [I2C_IAP_Bootloader_Protocol.md](I2C_IAP_Bootloader_Protocol.md) 第 7 章：

```text
5. JUMP_TO_APP
   Boot 重算 CRC → 与参数区 app_crc 比对 → 向量表检查 → 写 IMAGE_PENDING → 跳转
```

协议明确要求在真正跳转到 APP 之前完成三项检查：

1. **Boot 自验证 CRC**：对 Flash 中的 APP 固件重新计算 CRC16，与参数区保存的 `app_crc` 对比。
2. **向量表检查**：读取 APP 向量表首字（栈顶 SP）和第二个字（ResetHandler），判断其合法性。
3. **写 IMAGE_PENDING**：校验通过后，将参数区状态置为 `IMAGE_PENDING`，表示进入一次性的跳转尝试。

## 二、当前代码实现

### 2.1 `CmdJumpToApp()`（I2C 命令入口）

位于 [source/modem.c](source/modem.c#L658-L706)。

| 检查项 | 当前实现 | 状态 |
|--------|----------|------|
| PayloadLen == 0 | `if (u16PayloadLen != 0u)` | ✅ |
| `app_size` 非零 | `if (0u == stcParam.app_size)` | ✅ |
| 重算 CRC 并与 `app_crc` 比较 | `HC32_CalCrc16(APP_ADDR, 0, app_size)` vs `app_crc` | ✅ |
| 栈顶 SP 在 SRAM 范围内 | `u32StackTop > SRAM_BASE && u32StackTop <= SRAM_BASE + RAM_SIZE` | ✅ |
| ResetHandler 地址合法性 | 未检查 | ❌ 待补充 |
| 参数区 magic/header_crc 有效性 | 未检查 | ❌ 待补充 |
| 写 IMAGE_PENDING | `BootParam_WriteState(IMAGE_PENDING)` | ✅ |

### 2.2 `IAP_JumpToApp()`（实际跳转函数）

位于 [source/iap.c](source/iap.c#L142-L158)。

| 检查项 | 当前实现 | 状态 |
|--------|----------|------|
| 栈顶 SP 在 SRAM 范围内 | `u32StackTop > SRAM_BASE && u32StackTop <= SRAM_BASE + RAM_SIZE` | ✅ |
| ResetHandler 地址合法性 | 未检查 | ❌ 待补充 |
| CRC 自验证 | 未执行 | ⚠️ 已在 `CmdJumpToApp` 完成 |

注意：`IAP_JumpToApp` 被两个地方调用：

- `IAP_Main()`：JUMP_TO_APP 命令后调用，此时已通过 `CmdJumpToApp()` 完成 CRC 校验。
- `IAP_UpdateCheck()`：上电冷启动时根据参数区状态直接跳转，**未做 CRC 校验**。

## 三、建议补充的检查项

### 3.1 ResetHandler 地址检查

`IAP_JumpToApp()` 在读取栈顶后，应继续读取 `u32Addr + 4` 的 ResetHandler 地址，并判断：

```c
uint32_t u32ResetHandler = *((volatile uint32_t *)(u32Addr + 4));

/* ResetHandler 必须指向 Flash 区域内（APP 区域） */
if ((u32ResetHandler < APP_ADDR) || (u32ResetHandler >= (APP_ADDR + APP_MAX_SIZE)) ||
    ((u32ResetHandler & 0x1u) != 0u))  /* Thumb 指令地址 LSB=1 */
{
    return Error;
}
```

> 注：Thumb 地址最低位为 1。如果 APP 编译时 ResetHandler 表项未设置 LSB=1，跳转后会产生 HardFault。

### 3.2 参数区完整性检查（`CmdJumpToApp`）

`CmdJumpToApp()` 直接读取参数区就使用 `app_size` 和 `app_crc`，建议先验证：

```c
if (stcParam.magic != BOOT_PARAM_MAGIC)
{
    return ERROR_CODE_APP_INVALID;
}

uint16_t u16HeaderCrc = BootParam_CalcHeaderCrc(&stcParam);
if (u16HeaderCrc != stcParam.header_crc)
{
    return ERROR_CODE_APP_INVALID;
}
```

### 3.3 冷启动 IMAGE_VALID 路径增加 CRC 校验（可选）

如果要求上电后直接跳 APP 也足够安全，可在 `IAP_UpdateCheck()` 的 `IMAGE_VALID` 分支中：

```c
case BOOT_PARAM_STATE_IMAGE_VALID:
{
    uint16_t u16Crc = HC32_CalCrc16((uint8_t *)APP_ADDR, 0u, stcParam.app_size);
    if ((u16Crc != stcParam.app_crc) || (Error == IAP_JumpToApp(APP_ADDR)))
    {
        BootParam_WriteState(BOOT_PARAM_STATE_IMAGE_INVALID);
    }
    break;
}
```

代价：每次上电多花 CRC 计算时间，对较大固件可能延迟几十毫秒。

## 四、当前代码的强弱项

| 强项 | 说明 |
|------|------|
| CRC 校验闭环 | `CmdJumpToApp` 重算 CRC，不信任主机传参 |
| 栈顶范围检查 | 防止跳转到非法 RAM 地址 |
| IMAGE_PENDING 一次性尝试 | 失败后不重试，符合协议 |
| 跳转失败状态迁移 | `IAP_UpdateCheck` 跳转失败后写 `IMAGE_INVALID` |

| 弱项 | 风险 |
|------|------|
| ResetHandler 未检查 | APP 损坏时可能跳转到无效代码入口 |
| 参数区 magic/header_crc 未检查 | 参数区损坏时可能用错误尺寸计算 CRC |
| 冷启动 `IMAGE_VALID` 不校验 CRC | APP 被异常改写后仍可能尝试跳转 |

## 五、是否必须修复

| 检查项 | 是否必须 | 建议 |
|--------|----------|------|
| ResetHandler 地址检查 | **建议必须** | 简单、成本低、显著提高安全性 |
| 参数区 magic/header_crc 检查 | **建议必须** | 防止参数区损坏导致误跳 |
| 冷启动 IMAGE_VALID CRC 校验 | 可选 | 安全要求高时加上，否则依赖命令路径校验 |

## 六、相关文件

- [source/modem.c](source/modem.c) — I2C 命令处理
- [source/iap.c](source/iap.c) — 跳转入口与状态机
- [source/boot_param.c](source/boot_param.c) — 参数区读写
- [source/utils.h](source/utils.h) — 地址与状态宏定义
- [I2C_IAP_Bootloader_Protocol.md](I2C_IAP_Bootloader_Protocol.md) — 协议规格

---
*文档版本: 2026-06-20*
