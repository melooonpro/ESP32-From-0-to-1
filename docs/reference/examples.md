# 示例工程索引

所有示例都位于仓库 `examples/`。每个目录都是独立 ESP-IDF 工程。

## 通用命令

```powershell
cd examples/hello_world
idf.py set-target esp32s3
idf.py menuconfig
idf.py build flash monitor
```

## 当前示例

| 目录 | 目标 | 对应章节 |
| --- | --- | --- |
| `examples/hello_world` | 验证编译、烧录、串口日志 | 第一个 Hello World |
| `examples/gpio_button_led` | 按键切换 LED | GPIO 与 LEDC |
| `examples/ledc_fade` | PWM 呼吸灯 | GPIO 与 LEDC |
| `examples/i2c_scanner` | 扫描 I2C 设备地址 | I2C 与传感器 |
| `examples/adc_oneshot` | 读取 ADC 原始值 | ADC 与 UART |
| `examples/uart_echo` | UART1 串口回显 | ADC 与 UART |
| `examples/freertos_queue` | 用队列连接按键任务和 LED 任务 | FreeRTOS 深入理解 |
| `examples/nvs_counter` | 用 NVS 保存启动次数 | NVS、OTA 与工程化 |
| `examples/wifi_station_http` | 连接 Wi-Fi 并发起 HTTP GET | Wi-Fi 与 HTTP |

## 例程风格

这些例程刻意保持短小：少封装、少宏魔法、少业务逻辑。真正上项目时可以再拆组件、做错误恢复、增加测试。

<div class="prompt-card">
<strong>本节提示词</strong>

请根据 `examples/` 里的工程风格，帮我新增一个 ESP32-S3 ADC 采样 demo。要求保持短小，使用 menuconfig 配置 ADC 通道，并给出教程章节草稿。
</div>
