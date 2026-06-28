# 术语表

## ESP32

乐鑫的一系列 SoC，常用于 IoT、HMI、音频、边缘 AI 等场景。不同型号的外设、内存和无线能力会有差异，写代码前要确认目标芯片。

## ESP-IDF

Espressif IoT Development Framework，乐鑫官方开发框架。它包含驱动、协议栈、构建系统、示例和文档。

## SoC

System on Chip，片上系统。ESP32 芯片不只是一个 CPU，还集成了无线、内存控制器、外设控制器等模块。

## GPIO

General Purpose Input/Output，通用输入输出引脚。可以读按键，也可以控制 LED。

## PWM

Pulse Width Modulation，脉宽调制。通过快速切换高低电平并改变占空比，让 LED 呈现不同亮度或控制舵机。

## I2C

一种常见双线总线，使用 SCL 和 SDA 连接多个低速外设。

## ADC

Analog to Digital Converter，模数转换器。它把输入电压转换成数字，常用于读取电位器、光敏电阻、模拟传感器等。

## UART

通用异步收发器，常见串口通信方式。通常需要 TX、RX 和 GND，双方波特率等参数必须一致。

## NVS

Non-Volatile Storage，非易失性存储。适合保存少量配置和状态，例如设备名、Wi-Fi 配置、启动次数。

## OTA

Over-the-Air update，空中升级。设备通过网络下载新固件并切换启动分区。

## FreeRTOS

实时操作系统。ESP-IDF 应用运行在 FreeRTOS 上，任务、队列、互斥锁、定时器都是常用概念。

## ESP-Claw

乐鑫开源的边缘智能体项目，用于探索设备能力、脚本、事件和智能体之间的协作方式。
