# GPIO 数字输入输出

GPIO 是最适合入门的外设：它只表达两种状态，高电平或低电平。输出时，你让 LED 亮灭；输入时，你读取按键是否被按下。

## 直觉

把 GPIO 想成一扇小门。输出模式下，程序决定门外是高电平还是低电平；输入模式下，程序观察门外现在是什么状态。入门阶段先不要急着处理中断，轮询就足够看清“读”和“写”的关系。

## 准备工作

准备一个 LED、一个限流电阻、一个按键和若干杜邦线。LED 串联限流电阻后接到一个可用 GPIO，按键一端接 GPIO，另一端接 GND，并在程序中打开内部上拉。

如果你的开发板自带 LED，也可以直接使用板载 LED。不同开发板的 LED 引脚不一定相同，示例工程通过 `menuconfig` 配置引脚。

## 最小例程

对应工程：`examples/gpio_button_led`。

```c
gpio_set_direction(CONFIG_LED_GPIO, GPIO_MODE_OUTPUT);
gpio_set_direction(CONFIG_BUTTON_GPIO, GPIO_MODE_INPUT);
gpio_set_pull_mode(CONFIG_BUTTON_GPIO, GPIO_PULLUP_ONLY);
```

运行后按下按键，LED 状态会切换，串口会打印 `LED ON` 或 `LED OFF`。如果没有反应，先确认按键是否接到 GND，再确认 `menuconfig` 里的 GPIO 编号。

## 常见错误

输入脚悬空会导致读数乱跳，所以按键输入要有上拉或下拉。LED 不亮时，不要只怀疑代码，也要检查 LED 极性、限流电阻和开发板实际引脚。

## 官方资料

- [GPIO API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/gpio.html)

<div class="prompt-card">
<strong>本章提示词</strong>

我想用 ESP32 学习 GPIO。请根据我的开发板型号和接线，帮我设计一个按键切换 LED 的最小 ESP-IDF demo，并解释输入上拉、按键消抖、LED 极性、串口验证方法和常见接线错误。
</div>
