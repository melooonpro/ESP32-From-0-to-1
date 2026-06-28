<script setup>
import { withBase } from 'vitepress'
</script>

# 特殊章：ESP-Claw

ESP-Claw 是乐鑫面向边缘智能体和设备能力编排方向的开源项目。本章不要求你一上来读完整源码，而是先理解它把“设备、能力、脚本、事件、模型服务”组织在一起的方式。

<img :src="withBase('/official/esp-claw-logo.jpg')" alt="ESP-Claw 官方标识" style="max-width: 360px; width: 100%; border-radius: 8px;">

## 直觉

前面章节解决的是“我能不能控制硬件”。ESP-Claw 关注的是“设备能不能被更高层的智能体调用”。这会引入能力抽象、配置、文件系统、网络、模型 API、事件流和安全边界。

## 准备工作

先完成 Hello World、至少一个外设、Wi-Fi 和 FreeRTOS。然后阅读 ESP-Claw 官网快速开始，理解在线烧录、配置流程和设备能力的组织方式。

## 最小观察

从公开仓库看四类结构：

- `application/edge_agent`：边缘智能体应用入口。
- `components/claw_capabilities`：能力模块，例如系统、文件、HTTP、技能管理等。
- `components/lua_modules`：给脚本层使用的模块。
- `application/edge_agent/boards`：不同开发板适配信息。

先读结构，再改源码。这样你会知道“能力”应该放在哪里、板级适配在哪里、上层脚本如何调用。

## 与本教程的衔接

掌握 GPIO、I2C、Wi-Fi 和 FreeRTOS 后，可以尝试把一个外设能力封装成更高层接口。例如“读取温度”不再只是 I2C 读寄存器，而是一个可以被脚本或智能体调用的能力。

## 官方资料

- [ESP-Claw 官网](https://esp-claw.com/zh-cn/)
- [ESP-Claw GitHub 仓库](https://github.com/espressif/esp-claw)

<div class="prompt-card">
<strong>本章提示词</strong>

我已经掌握基础 ESP-IDF，想开始学习 ESP-Claw。请为我制定阅读和实验计划：解释 `edge_agent`、`capabilities`、`lua_modules`、`boards` 的作用，并把一个 I2C 温湿度读取功能改写成 ESP-Claw 风格的能力设计。
</div>
