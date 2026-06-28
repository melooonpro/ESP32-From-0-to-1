# FreeRTOS 深入理解

ESP-IDF 应用运行在 FreeRTOS 之上。你写的 `app_main` 本身就是一个任务。理解 RTOS 的关键不是背 API，而是理解“多个事情如何共享一个 CPU”。

## 任务：把大循环拆开

很多初学代码会写成一个巨大的 `while (1)`：读按键、闪 LED、读传感器、联网、上传数据全塞在一起。任务的意义是把这些不同节奏的工作分开。

```c
xTaskCreate(sensor_task, "sensor", 4096, NULL, 5, NULL);
xTaskCreate(led_task, "led", 2048, NULL, 4, NULL);
```

任务不是越多越好。每个任务都需要栈空间，优先级也会影响调度。初学阶段建议只创建 2 到 3 个任务，并给每个任务一个清晰职责。

## 队列：任务之间传消息

如果一个任务读传感器，另一个任务负责联网，它们不能随便共享全局变量。队列提供了一种更清晰的方式：生产者把数据放进队列，消费者从队列取数据。

```c
typedef struct {
    int button_level;
    int64_t timestamp_ms;
} app_event_t;
```

队列让程序从“谁改了这个变量”变成“谁发送了这个消息”。这也是很多嵌入式系统稳定性的来源。

## 互斥与临界区

当两个任务可能同时访问同一资源，比如同一个 I2C 总线、同一块显示屏、同一个全局缓冲区，就需要互斥。互斥锁的目标不是让程序“更高级”，而是让共享资源一次只被一个任务使用。

不要用长时间互斥包住网络请求或复杂计算，否则其他任务会一直等。互斥范围越短越好。

## 本章实验

- `examples/freertos_queue`：按键任务向队列发送事件，LED 任务消费事件。

扩展任务：加入一个串口日志任务，让所有任务都通过队列发送日志请求，观察系统结构是否更清楚。

## 官方资料

- [ESP-IDF FreeRTOS 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/freertos_idf.html)
- [ESP-IDF 系统 API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/index.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我把一个 ESP32-S3 外设 demo 改造成 FreeRTOS 结构：说明任务划分、优先级、栈大小、队列消息、互斥锁使用场景和阻塞风险，并给出如何用串口日志验证任务之间的数据流。
</div>
