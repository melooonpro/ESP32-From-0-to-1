# ADC 与 UART

GPIO、I2C、Wi-Fi 之后，最值得补上的两个基础能力是 ADC 和 UART。ADC 让芯片读取模拟世界，UART 让芯片和其他串口设备对话。

## ADC：把电压变成数字

ADC 的全称是 Analog to Digital Converter。它读取的是电压，不是“温度”“光照”这些物理量。传感器模块会先把物理变化转换成电压，ESP32-S3 再用 ADC 把电压转换成数字。

示例 `examples/adc_oneshot` 使用 ESP-IDF 的 ADC oneshot 驱动读取原始值。初学阶段先观察原始值变化，再学习校准、电压换算和噪声处理。

<div class="prompt-card">
<strong>本节提示词</strong>

请解释 ESP32-S3 ADC 读取“电位器”的完整链路：电位器如何产生电压，ADC 如何采样，原始值为什么会抖动，以及我应该如何用多次平均让读数更稳定。
</div>

## ADC 实验方法

把电位器两端接 3.3 V 和 GND，中间滑动端接 ADC 引脚。转动旋钮时，串口里的原始值应该随之变化。不要把高于 3.3 V 的电压直接接入 GPIO。

如果读数一直不变，先检查引脚是否支持 ADC，再检查 `menuconfig` 中的 ADC 通道是否和实际接线一致。

<div class="prompt-card">
<strong>本节提示词</strong>

我用 ESP32-S3 读取 ADC，串口值一直是 0 或一直满量程。请帮我从引脚能力、接线、电压范围、衰减配置、通道配置和代码循环六个方面排查。
</div>

## UART：最朴素也最常用的通信

UART 是异步串口通信，常用于 GPS、蓝牙串口模块、AT 指令模块、调试接口。它至少需要 TX、RX 和 GND。TX 要接对方 RX，RX 要接对方 TX。

示例 `examples/uart_echo` 使用 UART1 做回显：电脑或另一个串口设备发什么，ESP32-S3 就回什么。这个实验能帮助你理解波特率、收发缓冲区和串口接线。

<div class="prompt-card">
<strong>本节提示词</strong>

请用 ESP-IDF 写一个 UART 回显 demo。要求说明 TX/RX 交叉连接、波特率、数据位、停止位、校验位分别是什么意思，并给出如何用 USB-TTL 模块验证。
</div>

## 从 UART 走向协议

真实项目里，UART 通常只是底层通道，上面还会有协议。例如 AT 指令以换行结束，GPS 常见 NMEA 语句，某些传感器会有帧头、长度、校验和。先跑通回显，再解析协议。

<div class="prompt-card">
<strong>本节提示词</strong>

我有一个 UART 传感器协议：帧头 0xAA，长度 1 字节，数据 N 字节，最后 1 字节校验和。请帮我设计 ESP32-S3 接收状态机，并解释如何处理半包、粘包和校验失败。
</div>

## 官方资料

- [ADC Oneshot 驱动](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/adc_oneshot.html)
- [UART API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/uart.html)
