<script setup>
import { withBase } from 'vitepress'
</script>

# GPIO 数字输入输出

GPIO 是最适合入门的外设：它只表达两种状态，高电平或低电平。输出时，你让 LED 亮灭；输入时，你读取按键是否被按下。

<figure class="doc-figure">
  <img :src="withBase('/generated/gpio-modes.png')" alt="GPIO 输出、输入、开漏和中断事件示意图">
  <figcaption>GPIO 不是只有“点灯”一种用法。常见逻辑可以分成推挽输出、输入上拉/下拉、开漏共享线和边沿事件。先分清角色，再写代码。</figcaption>
</figure>

## 直觉

把 GPIO 想成一扇小门。输出模式下，程序决定门外是高电平还是低电平；输入模式下，程序观察门外现在是什么状态。入门阶段先不要急着处理中断，轮询就足够看清“读”和“写”的关系。

## GPIO 的几种角色

推挽输出适合直接控制 LED、片选信号、使能脚这类简单开关。输出高电平时接近 3.3 V，输出低电平时接近 GND，但它不能给电机、继电器、灯带这类大负载直接供电。

输入模式适合读取按键、限位开关、模块的状态脚。输入脚不能悬空，必须通过外部电阻或内部上拉/下拉让它在“没人按、没人驱动”时也有确定电平。

开漏输出不会主动拉高，只负责把总线拉低，拉高依靠上拉电阻。它适合多个器件共享一根线的场景，例如告警线、线与逻辑，I2C 的 SDA/SCL 也属于类似思想。

中断输入适合捕捉边沿事件，例如按键按下、传感器触发、脉冲计数。中断回调里只做很短的事情，例如发队列消息，不要在里面打印大量日志、访问网络或做长计算。

## 准备工作

准备一个 LED、一个限流电阻、一个按键和若干杜邦线。LED 串联限流电阻后接到一个可用 GPIO，按键一端接 GPIO，另一端接 GND，并在程序中打开内部上拉。

如果你的开发板自带 LED，也可以直接使用板载 LED。不同开发板的 LED 引脚不一定相同，示例工程通过 `menuconfig` 配置引脚。

<figure class="doc-figure">
  <img :src="withBase('/generated/gpio-circuit.png')" alt="ESP32 LED 和按键接线示意图">
  <figcaption>最小 GPIO 电路建议一边做输出、一边做输入：LED 串电阻接输出脚，按键接输入脚和 GND，输入脚开启内部上拉。</figcaption>
</figure>

## 最小例程

对应工程：`examples/gpio_button_led`。

```c
gpio_set_direction(CONFIG_LED_GPIO, GPIO_MODE_OUTPUT);
gpio_set_direction(CONFIG_BUTTON_GPIO, GPIO_MODE_INPUT);
gpio_set_pull_mode(CONFIG_BUTTON_GPIO, GPIO_PULLUP_ONLY);
```

运行后按下按键，LED 状态会切换，串口会打印 `LED ON` 或 `LED OFF`。如果没有反应，先确认按键是否接到 GND，再确认 `menuconfig` 里的 GPIO 编号。

## 速率与边界

GPIO 的“速度”不是一个固定答案，它取决于 CPU、驱动调用方式、中断负载、日志输出和是否运行 RTOS。对初学者来说，GPIO 最适合做人机输入、状态输出、低速控制和事件触发。

如果你要做几十 Hz 到几 kHz 的 LED 闪烁或按键读取，GPIO 完全够用。如果你要做稳定 PWM，用 LEDC；要发精确定时脉冲，用 RMT；要高速连续数据，用 SPI、I2S 或专用外设。不要用 `while` 循环手搓高速协议，这会让系统很难稳定。

<figure class="doc-figure">
  <img :src="withBase('/generated/peripheral-speed.png')" alt="GPIO、UART、I2C、SPI 和 Wi-Fi 速率量级示意图">
  <figcaption>外设选型先看时间尺度：按键和 LED 是低速事件，UART/I2C 是中低速通信，SPI/RMT/I2S 更适合高速或精确定时，Wi-Fi 则进入网络协议栈。</figcaption>
</figure>

## 应用场景

GPIO 常见场景包括板载 LED、按键、继电器使能、传感器中断脚、芯片片选脚、电源控制脚和故障告警脚。它的优点是简单直接；缺点是只能表达电平，不能自己完成复杂时序。

<figure class="doc-figure">
  <img :src="withBase('/generated/application-scenes.png')" alt="ESP32 外设应用场景示意图">
  <figcaption>真实应用通常从 GPIO 开始，但很快会组合其他外设：PWM 控制亮度或风扇，I2C 读取传感器，UART 对接模块，Wi-Fi 上传状态。</figcaption>
</figure>

## 常见错误

输入脚悬空会导致读数乱跳，所以按键输入要有上拉或下拉。LED 不亮时，不要只怀疑代码，也要检查 LED 极性、限流电阻和开发板实际引脚。

## 官方资料

- [GPIO API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/gpio.html)

<div class="prompt-card">
<strong>本章提示词</strong>

我想用 ESP32 学习 GPIO。请根据我的开发板型号和接线，帮我设计一个按键切换 LED 的最小 ESP-IDF demo，并解释输入上拉、按键消抖、LED 极性、串口验证方法和常见接线错误。
</div>
