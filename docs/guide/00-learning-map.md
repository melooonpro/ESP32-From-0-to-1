# 学习地图

一句话先讲清楚：ESP32 是一块能接收现实信号、控制外部东西、再把结果传到网络上的小电脑。

本教程的口号是：把一个想法变成会感知、会控制、会联网的小设备。你不需要先成为 C 语言高手，也不需要先读完芯片手册；更好的路线是：先让板子跑起来，再用一个个可观察的小现象理解系统。

## 你会学到什么

<div class="lesson-grid">
  <div class="lesson-card">
    <h3>环境与工具链</h3>
    <p>知道 ESP-IDF、Python、Git、CMake、串口驱动各自负责什么，并能在 Windows 下完成一次完整编译和烧录。</p>
  </div>
  <div class="lesson-card">
    <h3>最小工程</h3>
    <p>理解 `app_main`、组件、`idf.py`、串口日志，让 Hello World 不只是“复制粘贴成功”。</p>
  </div>
  <div class="lesson-card">
    <h3>基础外设</h3>
    <p>按 GPIO、LEDC、I2C、ADC、UART、Touch、Wi-Fi 的顺序逐个实验，每个外设先独立跑通，再考虑组合。</p>
  </div>
  <div class="lesson-card">
    <h3>RTOS 与应用</h3>
    <p>理解任务调度、队列、互斥、定时器，再进入 ESP-Claw、边缘智能和设备自动化。</p>
  </div>
</div>

## 推荐学习节奏

第一周只追求“能跑”：安装环境、烧录 Hello World、看懂串口输出。第二周开始逐个外设实验，把它们理解成按钮、灯光、旋钮、传感器和通信接口，而不是一堆缩写。第三周进入 Wi-Fi、HTTP、NVS 和 OTA，让设备具备联网、保存配置和升级能力。第四周再系统学习 FreeRTOS，因为这时你已经见过“为什么需要多个任务”。

::: warning 不要一开始就追求大项目
初学者最常见的挫败感不是“不会”，而是同时处理太多未知：硬件接线、驱动 API、CMake、RTOS、网络、云平台。每章只增加一两个新概念，才是最快的路线。
:::

<div class="prompt-card">
<strong>本章提示词</strong>

我是一名没有嵌入式经验的大学生，准备学习 ESP32 和 ESP-IDF。请基于本章学习地图，为我制定 4 周学习计划：每周目标、必须完成的 demo、验收现象、常见坑、复盘问题，以及我应该如何判断自己真的理解了。
</div>
