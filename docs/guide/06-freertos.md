# FreeRTOS 深入理解

ESP-IDF 应用运行在 FreeRTOS 之上。你写的 `app_main` 本身就是一个任务。理解 RTOS 的关键不是背 API，而是理解“多个事情如何共享一个 CPU”。

## 任务：把大循环拆开

很多初学代码会写成一个巨大的 `while (1)`：读按键、闪 LED、读传感器、联网、上传数据全塞在一起。任务的意义是把这些不同节奏的工作分开。

```c
xTaskCreate(sensor_task, "sensor", 4096, NULL, 5, NULL);
xTaskCreate(led_task, "led", 2048, NULL, 4, NULL);
```

任务不是越多越好。每个任务都需要栈空间，优先级也会影响调度。初学阶段建议只创建 2 到 3 个任务，并给每个任务一个清晰职责。

<div class="prompt-card">
<strong>本节提示词</strong>

请用 ESP32-S3 采集温度并闪烁 LED 的例子解释 FreeRTOS 任务、优先级、栈大小和 `vTaskDelay`。请指出初学者滥用任务会造成什么问题。
</div>

## 队列：任务之间传消息

如果一个任务读传感器，另一个任务负责联网，它们不能随便共享全局变量。队列提供了一种更清晰的方式：生产者把数据放进队列，消费者从队列取数据。

```c
typedef struct {
    int button_level;
    int64_t timestamp_ms;
} app_event_t;
```

队列让程序从“谁改了这个变量”变成“谁发送了这个消息”。这也是很多嵌入式系统稳定性的来源。

<div class="prompt-card">
<strong>本节提示词</strong>

请设计一个 ESP32-S3 FreeRTOS 队列 demo：按键任务发送事件，LED 任务接收事件并切换状态。先画出任务关系，再给出完整代码。
</div>

## 互斥与临界区

当两个任务可能同时访问同一资源，比如同一个 I2C 总线、同一块显示屏、同一个全局缓冲区，就需要互斥。互斥锁的目标不是让程序“更高级”，而是让共享资源一次只被一个任务使用。

不要用长时间互斥包住网络请求或复杂计算，否则其他任务会一直等。互斥范围越短越好。

<div class="prompt-card">
<strong>本节提示词</strong>

请解释 FreeRTOS 互斥锁和队列的区别。以“两个任务都要访问 I2C 传感器”为例，说明什么时候用互斥锁，什么时候用队列。
</div>

## 本章实验

- `examples/freertos_queue`：按键任务向队列发送事件，LED 任务消费事件。

扩展任务：加入一个串口日志任务，让所有任务都通过队列发送日志请求，观察系统结构是否更清楚。

<div class="prompt-card">
<strong>本节提示词</strong>

请帮我审查一个 ESP32-S3 FreeRTOS demo：我会贴出代码，请指出任务划分、队列长度、栈大小、优先级、共享变量和阻塞时间是否合理。
</div>

## 官方资料

- [ESP-IDF FreeRTOS 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/freertos_idf.html)
- [ESP-IDF 系统 API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/index.html)
