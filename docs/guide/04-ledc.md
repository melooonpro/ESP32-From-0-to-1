# LEDC PWM 输出

这一章让 ESP32 不只会“开”和“关”，还能控制“亮一点、暗一点、快一点、慢一点”。

LEDC 是 ESP-IDF 中常用的 PWM 外设。PWM 不是真的输出“半个电压”，而是在很短时间内快速切换高低电平，让 LED、蜂鸣器或电机驱动看到一个平均效果。你可以先把它理解成调光旋钮的程序版本。

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

## 速率与边界

LEDC 的频率和分辨率是互相牵制的：分辨率越高，一个周期里可分的占空比档位越多；频率越高，留给每个周期计数的时间越少。课堂入门用 5 kHz、10 位分辨率控制 LED 很直观。

如果只是 LED 亮度，几百 Hz 到几 kHz 通常够用；如果是蜂鸣器，频率本身就是音调；如果是舵机，要按舵机要求设置特定脉宽，不要照搬呼吸灯参数。更复杂的电机控制通常需要驱动芯片和更完整的保护电路。

## 应用场景

LEDC 常用于 LED 调光、蜂鸣器音调、风扇或小电机驱动信号、背光亮度和简单舵机控制。它适合“周期性波形”，不适合传输数据包，也不适合需要复杂编码的红外或灯带协议。

## 常见错误

如果 LED 只亮不变暗，检查是否调用了 `ledc_update_duty`。如果闪烁明显，尝试提高 PWM 频率。控制舵机时不要直接套用 LED 的频率和占空比范围，舵机需要专门的脉宽设置。

## 官方资料

- [LEDC API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/ledc.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我写一个 ESP32 LEDC 呼吸灯 demo。要求解释 PWM 频率、占空比分辨率、定时器、通道和 GPIO 的关系，并根据我的 LED 接线给出 `menuconfig` 参数、验证现象和排错步骤。
</div>
