<script setup>
import { withBase } from 'vitepress'
</script>

# Touch 触摸感应

Touch 外设读取的不是“按下/松开”的机械状态，而是触摸电极附近的电容变化。它适合做无机械磨损的按键、滑条、触摸唤醒和防水面板。

<figure class="doc-figure">
  <img :src="withBase('/generated/touch-principle.png')" alt="ESP32 Touch 电容触摸原理示意图">
  <figcaption>触摸焊盘和周围环境形成电容。手指靠近时电场分布改变，触摸外设测到的原始值会偏离基线，再由阈值判断是否触摸。</figcaption>
</figure>

## 直觉

普通 GPIO 看的是电平，Touch 看的是电容。你可以把触摸焊盘想成一块很小的金属片：没有手指时，它有一个稳定基线；手指靠近后，人体引入额外电容，原始读数发生变化。

Touch 不是 I2C 触摸芯片，也不是普通按键。它不需要外部开关，但对电极形状、面板材料、接地、噪声和湿度更敏感。

## 准备工作

准备一块支持 Touch 的开发板，或者把一小片铜箔、触摸弹簧、金属片连接到支持触摸功能的 GPIO。触摸电极不要直接接 5 V，也不要和普通 LED 电路混接。

初学时先只接一个触摸通道，并在串口里观察原始值。确认变化方向和幅度后，再设置触摸阈值。

## 最小例程

对应工程：`examples/touch_read`。

```c
touch_sensor_handle_t sensor;
touch_channel_handle_t channel;

ESP_ERROR_CHECK(touch_sensor_new_controller(&sensor_cfg, &sensor));
ESP_ERROR_CHECK(touch_sensor_new_channel(sensor, CONFIG_TOUCH_CHANNEL_ID, &channel_cfg, &channel));
```

运行后打开串口，先记录没有触摸时的基线，再用手指靠近触摸电极。原始值会发生明显变化。不要急着把阈值写死，先观察多次触摸、松开、环境变化后的范围。

## 速率与边界

Touch 面向人机输入，不适合高速数据通信。实际响应速度取决于采样配置、滤波策略、阈值判断和系统任务调度。课堂实验可以把它当作几十毫秒量级的人手输入，而不是微秒级信号。

如果你需要可靠机械确认，用普通按键；需要防水、无孔面板或隐藏式按键，可以考虑 Touch；需要多点触控屏幕，应该使用专门触摸控制器。

## 常见错误

触摸不稳定时，先检查电极面积是否太小、连线是否太长、附近是否有强干扰、电源和地是否稳定。阈值设置过紧会误触发，设置过松会不灵敏。

## 官方资料

- [ESP-IDF 触摸传感器文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/cap_touch_sens.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我设计一个 ESP32 Touch 触摸按键实验。要求解释电容触摸原理、触摸通道选择、电极形状、基线采样、阈值设置、抗干扰方法、串口验证现象和适合的应用场景。
</div>
