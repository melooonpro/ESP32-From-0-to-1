# ADC 模拟采样

ADC 用来把电压转换成数字。它读到的不是“温度”或“光照”，而是一个与输入电压相关的原始值；传感器模块会先把物理变化转换成电压。

## 直觉

数字输入只能判断高低，ADC 则能观察连续变化。电位器是最适合入门的 ADC 外设：旋钮转动时，中间端电压变化，串口里的原始值也跟着变化。

## 准备工作

准备一个电位器。两端接 3.3 V 和 GND，中间滑动端接 ADC 引脚。不要把高于 3.3 V 的电压直接接入 GPIO。

## 最小例程

对应工程：`examples/adc_oneshot`。

```c
adc_oneshot_unit_init_cfg_t init_config = {
    .unit_id = ADC_UNIT_1,
};
adc_oneshot_new_unit(&init_config, &adc_handle);
```

运行后转动旋钮，串口里的原始值应随之变化。初学阶段先观察原始值，再学习校准、电压换算、衰减和平均滤波。

## 常见错误

读数一直不变时，检查所选 GPIO 是否支持 ADC。读数抖动不一定是代码错，模拟采样本来就会受噪声、接线长度、电源和输入阻抗影响。

## 官方资料

- [ADC Oneshot 驱动](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/adc_oneshot.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我写一个 ESP32 ADC 电位器采样 demo。要求说明接线、电压安全、ADC 通道选择、衰减、原始值抖动、平均滤波和串口验证方法。
</div>
