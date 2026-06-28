---
layout: home

hero:
  name: ESP32 从 0 到 1
  text: 把一个想法，变成会感知、会控制、会联网的小设备
  tagline: 不先讲芯片手册，先用按钮、灯光、传感器和 Wi-Fi，让你看见 ESP32 到底能做什么。
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
  - title: ESP32 是什么
    details: 一块能接按钮、灯、传感器和网络的小板子。它让软件不只停在屏幕里，而是能碰到真实世界。
  - title: 先看见结果
    details: 每章先做一个能观察的现象：灯亮、按键触发、旋钮变数值、联网拿到响应，再解释背后的名字。
  - title: 从零件到作品
    details: 把输入、控制、通信、保存和升级一步步拼起来，最后变成一个能演示、能复盘的小应用。
  - title: AI 帮你少卡住
    details: 每章给一段可直接复制的提示词，让 AI 帮你检查接线、解释报错、扩展 demo，但不替你蒙混过关。
---

<script setup>
import { withBase } from 'vitepress'
</script>

<div class="hero-board">
  <div>
    <h2>先记住一句话</h2>
    <p>ESP32 就是把“我想做一个会自动感知和反应的东西”变成现实的起点。你可以从一颗 LED 开始，慢慢做出会读传感器、会连 Wi-Fi、会保存设置、会被 AI 调用的小设备。</p>
  </div>
  <img :src="withBase('/official/esp-claw-logo.jpg')" alt="ESP-Claw 官方标识">
</div>
