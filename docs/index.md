---
layout: home

hero:
  name: ESP32 从 0 到 1
  text: 从 Windows 环境到应用案例
  tagline: 面向无经验大学生的中文教程，用书本式节奏把 ESP-IDF、独立外设实验、RTOS、AI 提示词和 ESP-Claw 串起来。
  image:
    src: /official/espressif-logo.svg
    alt: Espressif
  actions:
    - theme: brand
      text: 开始学习
      link: /guide/00-learning-map
    - theme: alt
      text: 查看示例工程
      link: /reference/examples

features:
  - title: 从能跑开始
    details: 先装好 ESP-IDF，再完成 Hello World、串口监视、GPIO 点灯，不把初学者卡在抽象概念里。
  - title: 把外设讲成模型
    details: GPIO、LEDC、I2C、ADC、UART、Touch、Wi-Fi 分章讲解，每个实验先独立跑通。
  - title: RTOS 不再神秘
    details: 从任务、队列、互斥和定时器出发，建立嵌入式并发的直觉。
  - title: AI 时代的学习方法
    details: 每章末尾给出一份综合提示词，训练“让 AI 帮你生成、解释、验证 demo”的能力。
---

<script setup>
import { withBase } from 'vitepress'
</script>

<div class="hero-board">
  <div>
    <h2>这不是一页速查表，而是一条学习路径</h2>
    <p>本教程默认你是第一次接触嵌入式：不知道串口是什么、不熟悉 CMake、不确定芯片和开发板的关系，都没关系。每章会先建立直觉，再写最小可运行代码，最后用提示词把本章知识变成可继续探索的 demo。</p>
  </div>
  <img :src="withBase('/official/esp-claw-logo.jpg')" alt="ESP-Claw 官方标识">
</div>
