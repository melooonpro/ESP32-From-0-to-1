# UART 串口通信

UART 是最朴素也最常用的通信方式之一。GPS、蓝牙串口模块、AT 指令模块和很多调试接口都会用 UART。

## 直觉

UART 像两个人轮流说话：TX 负责发送，RX 负责接收。自己的 TX 要接对方 RX，自己的 RX 要接对方 TX，双方还要约定同样的波特率。

## 准备工作

准备一个 USB-TTL 模块或另一块开发板作为串口对端。连接 TX、RX 和 GND，不要忘记共地。确认对端电平是 3.3 V TTL，避免把 5 V 信号直接接入 GPIO。

## 最小例程

对应工程：`examples/uart_echo`。

```c
uart_driver_install(UART_NUM_1, 512, 0, 0, NULL, 0);
uart_param_config(UART_NUM_1, &uart_config);
uart_set_pin(UART_NUM_1, CONFIG_UART_TX_GPIO, CONFIG_UART_RX_GPIO,
             UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
```

运行后从对端串口发送任意字节，开发板会原样回传。这个回显实验能帮你确认波特率、TX/RX 交叉和缓冲区收发。

## 常见错误

没有数据时，先检查 TX/RX 是否交叉，GND 是否连接。乱码通常来自波特率不一致。真实项目中，UART 上层还会有协议：帧头、长度、校验和超时都需要单独设计。

## 官方资料

- [UART API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/uart.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我设计一个 ESP32 UART 回显实验。要求说明 TX/RX/GND 接线、波特率、缓冲区、超时、串口工具设置，并给出从回显走向简单协议解析的下一步练习。
</div>
