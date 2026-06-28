# 术语表

## ESP32-S3

乐鑫的一款 Wi-Fi + Bluetooth LE SoC，常用于 IoT、HMI、音频、边缘 AI 等场景。本教程以 ESP32-S3-DevKitC-1 这类开发板为默认对象。

## ESP-IDF

Espressif IoT Development Framework，乐鑫官方开发框架。它包含驱动、协议栈、构建系统、示例和文档。

## SoC

System on Chip，片上系统。ESP32-S3 不只是一个 CPU，还集成了无线、内存控制器、外设控制器等模块。

## GPIO

General Purpose Input/Output，通用输入输出引脚。可以读按键，也可以控制 LED。

## PWM

Pulse Width Modulation，脉宽调制。通过快速切换高低电平并改变占空比，让 LED 呈现不同亮度或控制舵机。

## I2C

一种常见双线总线，使用 SCL 和 SDA 连接多个低速外设。

## FreeRTOS

实时操作系统。ESP-IDF 应用运行在 FreeRTOS 上，任务、队列、互斥锁、定时器都是常用概念。

## ESP-Claw

乐鑫开源的边缘智能体项目，用于探索设备能力、脚本、事件和智能体之间的协作方式。
