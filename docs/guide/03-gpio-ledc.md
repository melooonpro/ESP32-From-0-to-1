# GPIO 与 LEDC

GPIO 是最容易观察的外设：一个引脚输出高电平或低电平，LED 就亮或灭。LEDC 是 LED PWM Controller，可以生成 PWM 波形，让 LED 变暗变亮，也可以控制舵机或蜂鸣器。

## GPIO：先学数字世界

数字输出只有两种状态：高电平和低电平。点灯 demo 的真正重点是三件事：选择引脚、配置方向、周期性改变电平。

```c
gpio_reset_pin(CONFIG_BLINK_GPIO);
gpio_set_direction(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
gpio_set_level(CONFIG_BLINK_GPIO, 1);
```

不要默认所有开发板都有同一个 LED 引脚。教程示例把 LED 引脚放到 `menuconfig`，让你按自己的板子修改。

## LEDC：用占空比表达“亮度”

PWM 的一个周期里，高电平所占比例叫占空比。占空比越大，LED 看起来越亮。LEDC 的关键配置包括定时器、通道、频率、分辨率和 GPIO。

```c
ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
```

初学时建议先用固定频率和 10 位分辨率。10 位意味着占空比范围是 `0` 到 `1023`，比百分比更适合程序计算。

## 本章实验

- `examples/gpio_button_led`：按键切换 LED 状态。
- `examples/ledc_fade`：用 LEDC 做呼吸灯。

完成后可以尝试把两个例程合并：按下按键后切换呼吸灯的速度。

## 官方资料

- [GPIO API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/gpio.html)
- [LEDC API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/ledc.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我设计一个 ESP32-S3 GPIO 与 LEDC 综合 demo：按键短按切换 LED，长按切换呼吸灯速度。请先说明硬件接线、输入上拉、消抖、PWM 频率和占空比，再给出 ESP-IDF 实现思路。
</div>
