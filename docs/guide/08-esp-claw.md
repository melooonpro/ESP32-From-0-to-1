# 特殊章：ESP-Claw

ESP-Claw 是乐鑫面向边缘智能体和设备能力编排方向的开源项目。本章不要求你一上来读完整源码，而是先理解它把“设备、能力、脚本、事件、模型服务”组织在一起的方式。

<img src="/official/esp-claw-logo.jpg" alt="ESP-Claw 官方标识" style="max-width: 360px; width: 100%; border-radius: 8px;">

## 为什么把 ESP-Claw 放在进阶章

前面章节解决的是“我能不能控制硬件”。ESP-Claw 关注的是“设备能不能被更高层的智能体调用”。这会引入更多工程问题：能力抽象、配置、文件系统、网络、模型 API、事件流和安全边界。

如果你还没有完成 Hello World、GPIO、Wi-Fi 和 FreeRTOS，建议先回到前面章节。ESP-Claw 不是第一个 demo，而是把多个 demo 组织成系统的方法。

<div class="prompt-card">
<strong>本节提示词</strong>

请用初学者能理解的方式解释 ESP-Claw 和普通 ESP-IDF demo 的区别。请从“单一外设控制”和“设备能力被智能体调用”两个角度说明。
</div>

## 从仓库看结构

ESP-Claw 参考仓库中可以看到几类重要目录：

- `application/edge_agent`：边缘智能体应用入口。
- `components/claw_capabilities`：能力模块，例如系统、文件、HTTP、技能管理等。
- `components/lua_modules`：给脚本层使用的模块。
- `application/edge_agent/boards`：不同开发板适配信息。
- `docs/src/content/docs/zh-cn`：中文文档内容。

本教程的 ESP-Claw 章节会保持“读结构，不搬源码”的原则，只引用公开仓库中的技术结构和可验证路径。

<div class="prompt-card">
<strong>本节提示词</strong>

请帮我阅读 ESP-Claw 仓库结构。重点解释 `application/edge_agent`、`components/claw_capabilities`、`components/lua_modules`、`boards` 这几类目录分别解决什么问题，并给出初学者阅读顺序。
</div>

## 一个最小理解实验

建议先做三个观察：

1. 阅读 ESP-Claw 官网的快速开始，理解在线烧录和配置流程。
2. 在仓库中查看 `application/edge_agent/boards/espressif/esp32_S3_DevKitC_1`，理解开发板适配如何描述芯片和外设。
3. 查看一个能力模块的 `README` 或头文件，理解“能力”如何暴露给上层。

这样做比一上来改源码更稳，因为你先知道项目如何分层。

<div class="prompt-card">
<strong>本节提示词</strong>

我想学习 ESP-Claw，但只会基础 ESP-IDF。请为我制定一个 7 天阅读计划，每天指定一个目录或文档，说明我要回答什么问题，以及如何用小实验验证理解。
</div>

## 与本教程的衔接

当你掌握 GPIO、I2C、Wi-Fi 和 FreeRTOS 后，可以尝试把一个外设能力封装成更高层接口。例如“读取温度”不再只是 I2C 读寄存器，而是一个可以被脚本或智能体调用的能力。

进阶项目可以是：ESP32-S3 读取环境传感器，通过 Wi-Fi 上报状态，再让一个上层 agent 根据规则或提示词决定是否打开风扇。

<div class="prompt-card">
<strong>本节提示词</strong>

请把“ESP32-S3 读取 I2C 温湿度传感器并控制风扇”改写成 ESP-Claw 风格的能力设计。输出能力名称、输入参数、输出 JSON、错误处理、权限边界和最小测试脚本。
</div>

## 官方资料

- [ESP-Claw 官网](https://esp-claw.com/zh-cn/)
- [ESP-Claw GitHub 仓库](https://github.com/espressif/esp-claw)
