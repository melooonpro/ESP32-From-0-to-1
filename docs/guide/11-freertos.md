# FreeRTOS 深入理解

ESP-IDF 应用运行在 FreeRTOS 之上。你写的 `app_main` 本身就是一个任务。理解 RTOS 的关键不是背 API，而是理解“多个事情如何共享一个 CPU”。

## 直觉

没有 RTOS 时，程序常常写成一个巨大的 `while (1)`。当读取外设、刷新显示、处理网络和保存配置的节奏不同，大循环会越来越难维护。任务的价值是把不同节奏的工作拆开。

## 准备工作

先确保你已经能独立运行一个外设例程。FreeRTOS 本章不引入新硬件，只用按键和 LED 观察任务之间如何传递消息。

## 最小例程

对应工程：`examples/freertos_queue`。

```c
typedef struct {
    int button_level;
    int64_t timestamp_ms;
} app_event_t;
```

按键任务向队列发送事件，LED 任务从队列取事件并改变状态。队列让程序从“谁改了这个全局变量”变成“谁发送了这个消息”。

## 常见错误

任务不是越多越好。每个任务都需要栈空间，优先级也会影响调度。互斥锁只保护共享资源，不要把长时间网络请求放在互斥锁里面。

## 官方资料

- [ESP-IDF FreeRTOS 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/freertos_idf.html)
- [ESP-IDF 系统 API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/index.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我把一个 ESP32 外设 demo 改造成 FreeRTOS 结构：说明任务划分、优先级、栈大小、队列消息、互斥锁使用场景和阻塞风险，并给出如何用串口日志验证任务之间的数据流。
</div>
