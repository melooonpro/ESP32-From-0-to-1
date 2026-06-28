# 第一个 Hello World

Hello World 的价值不是打印一句话，而是验证整条链路：源码能被编译，固件能被烧录，芯片能启动，串口能看到日志。

## 工程结构

一个最小 ESP-IDF 工程通常包含：

```text
hello_world/
  CMakeLists.txt
  main/
    CMakeLists.txt
    main.c
```

根目录 `CMakeLists.txt` 声明这是 ESP-IDF 工程，`main/CMakeLists.txt` 声明源文件，`main.c` 里写 `app_main`。你可以把 `app_main` 想成嵌入式世界里的程序入口。

## 编译、烧录、监视

进入示例目录：

```powershell
cd examples/hello_world
idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```

如果串口输出中看到周期性日志，说明你已经完成第一次闭环。退出监视器通常使用 `Ctrl+]`。

```c
void app_main(void)
{
    while (1) {
        ESP_LOGI("hello", "Hello ESP32-S3");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```

这里的 `vTaskDelay` 来自 FreeRTOS。现在你只需要记住：它让当前任务睡一会儿，把 CPU 时间让给系统里的其他任务。

## 常见错误

如果 `set-target` 选错，工程可能能编译但无法正常运行。目标芯片要与手上的开发板一致。如果烧录失败，先确认串口号、数据线和开发板是否进入下载模式。

如果监视器里出现乱码，通常是串口波特率不一致。ESP-IDF 默认日志波特率常见为 `115200`。

## 官方资料

- [ESP-IDF Hello World 示例](https://github.com/espressif/esp-idf/tree/master/examples/get-started/hello_world)
- [ESP-IDF 构建系统](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/build-system.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我完成并理解 ESP-IDF Hello World。要求先解释工程结构和 `app_main`，再把程序改成每秒打印启动秒数，最后根据我贴出的编译、烧录、串口日志判断问题发生在哪个阶段。
</div>
