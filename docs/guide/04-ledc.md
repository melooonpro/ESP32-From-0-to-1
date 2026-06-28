# LEDC PWM 输出

LEDC 是 ESP-IDF 中常用的 PWM 外设。PWM 不是真的输出“半个电压”，而是在很短时间内快速切换高低电平，让 LED、蜂鸣器或电机驱动看到一个平均效果。

## 直觉

一个 PWM 周期里，高电平占的比例叫占空比。占空比越大，LED 看起来越亮；频率越高，肉眼越不容易看到闪烁。LEDC 的核心对象是定时器和通道：定时器决定频率和分辨率，通道决定哪个 GPIO 输出 PWM。

## 准备工作

准备一个 LED 和限流电阻，接到可输出 PWM 的 GPIO。先不要接舵机或电机，入门阶段用 LED 观察亮度变化最直观，也最安全。

## 最小例程

对应工程：`examples/ledc_fade`。

```c
ledc_timer_config_t timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .freq_hz = 5000,
};
```

示例使用 10 位分辨率，占空比范围是 `0` 到 `1023`。程序循环增加和减少占空比，LED 会呈现呼吸灯效果。

## 常见错误

如果 LED 只亮不变暗，检查是否调用了 `ledc_update_duty`。如果闪烁明显，尝试提高 PWM 频率。控制舵机时不要直接套用 LED 的频率和占空比范围，舵机需要专门的脉宽设置。

## 官方资料

- [LEDC API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/ledc.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我写一个 ESP32 LEDC 呼吸灯 demo。要求解释 PWM 频率、占空比分辨率、定时器、通道和 GPIO 的关系，并根据我的 LED 接线给出 `menuconfig` 参数、验证现象和排错步骤。
</div>
