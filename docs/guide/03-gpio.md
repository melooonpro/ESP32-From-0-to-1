<script setup>
import { withBase } from 'vitepress'
</script>

# GPIO 数字输入输出

这一章让 ESP32 学会最基础的“看”和“动”：看按钮有没有被按下，动手把灯打开或关掉。

GPIO 是最适合入门的外设：它只表达两种逻辑状态，高电平或低电平。输出时，程序把某个引脚驱动到接近 3.3 V 或接近 GND；输入时，程序读取引脚当前被外部电路拉到了哪一边。很多看起来复杂的设备，第一步其实都是从一个输入和一个输出开始。

GPIO 的全称是 General Purpose Input / Output，也就是“通用输入输出接口”。简单说，它就是主控芯片和外部硬件沟通的引脚：按键、红外接收、温湿度模块可以通过 GPIO 把状态传给主控；LED、蜂鸣器、继电器、电机驱动模块也可以通过 GPIO 接收控制信号，实现亮灭、报警、开关或转动。

<figure class="doc-figure">
  <img :src="withBase('/generated/gpio-principle.svg')" alt="ESP32-S3 GPIO 输入输出、上下拉、开漏和中断原理示意图">
  <figcaption>GPIO 不是一根“直通 CPU 的铜线”，而是由 IO MUX / GPIO Matrix、输出驱动、输入缓冲、上下拉和中断检测共同组成。程序配置这些开关后，引脚才表现为输出、输入、开漏或中断源。</figcaption>
</figure>

## 从外部状态到外设动作

GPIO 看起来只是一个小小的引脚，但它连接的是整个硬件系统的输入与输出。做项目时，可以把它拆成一条非常朴素的链路：

<div class="lesson-grid">
  <div class="lesson-card">
    <h3>1. 外部世界</h3>
    <p>按键被按下、红外被遮挡、温湿度模块给出状态，这些变化先在外部电路里变成电平或脉冲。</p>
  </div>
  <div class="lesson-card">
    <h3>2. GPIO 输入</h3>
    <p>输入缓冲把引脚上的电平读成逻辑 0 或 1，程序通过 <code>gpio_get_level()</code> 看到外部状态。</p>
  </div>
  <div class="lesson-card">
    <h3>3. 主控处理</h3>
    <p>ESP32 根据输入做判断：切换 LED、记录事件、发送网络请求，或把任务交给其他外设继续处理。</p>
  </div>
  <div class="lesson-card">
    <h3>4. GPIO 输出</h3>
    <p>程序通过 <code>gpio_set_level()</code> 输出高低电平，让 LED、蜂鸣器、继电器或驱动模块收到控制信号。</p>
  </div>
</div>

STM32、ESP32、Arduino、树莓派这些开发板都会反复用到 GPIO。它不是某一种板子的专属概念，而是嵌入式、物联网和单片机项目里最常见的“入口”和“出口”。

## 直觉

把 GPIO 想成一扇小门。输出模式下，程序决定门外是高电平还是低电平；输入模式下，程序观察门外现在是什么状态。真正的芯片内部比“小门”更复杂：同一个焊盘前面还有复用器、输入缓冲、输出驱动、上下拉电阻和中断检测逻辑。

Espressif 文档说明，ESP32-S3 的 GPIO 可以作为通用输入输出，也可以连接到内部外设信号；GPIO Matrix、IO MUX 和 RTC IO MUX 负责把外设输入输出路由到引脚。入门时你先使用普通 GPIO API，等到 I2C、UART、LEDC 这类章节，再把同一根引脚交给专用外设。

## 常见输入/输出模式

很多 STM32 资料会把 GPIO 工作方式拆成“输入四类”和“输出四类”：输入看默认电平怎么来，输出看谁负责驱动引脚。ESP32/ESP-IDF 的 API 名称不完全相同，但理解这些模式有助于迁移到不同开发板。

<figure class="doc-figure">
  <img :src="withBase('/generated/gpio-io-modes.svg')" alt="GPIO 输入四类和输出四类模式示意图">
  <figcaption>输入模式重点看引脚在没有外部驱动时是否有确定默认电平；输出模式重点看 GPIO 是主动拉高/拉低，还是只拉低并依赖上拉电阻，以及控制权是普通 GPIO 还是 UART、I2C、LEDC 等复用外设。</figcaption>
</figure>

## GPIO 的硬件结构

### 引脚、焊盘和复用器

你在代码里写的 `GPIO_NUM_4` 是逻辑编号，开发板丝印可能写成 `IO4`、`D4` 或别的名字。芯片内部的焊盘先进入 IO MUX / GPIO Matrix：如果配置成普通 GPIO，信号由 GPIO 外设控制；如果配置成 UART、I2C、LEDC 等复用功能，信号会被路由到对应外设。

这也是为什么同一个引脚不能随便同时做两件互相冲突的事。比如一个引脚被 LEDC 占用输出 PWM，就不要再把它当普通按键输入读；一个引脚被 USB-JTAG、Flash、PSRAM 或启动绑带使用时，也要先查开发板原理图和芯片引脚表。

### 输出驱动：推挽和开漏

推挽输出可以主动拉高，也可以主动拉低。把它想成上、下两个电子开关：输出 1 时，上面的开关接通到 3.3 V；输出 0 时，下面的开关接通到 GND。它适合直接控制 LED、片选信号、使能脚这类小电流数字信号，但不能给电机、继电器、灯带这类大负载直接供电。

开漏输出只负责拉低，不主动拉高。总线为高电平时依赖上拉电阻，某个器件需要表达 0 时才把线拉到 GND。它适合多个器件共享一根线的场景，例如告警线、线与逻辑，I2C 的 SDA/SCL 也属于类似思想。没有上拉时，开漏线会悬空，读数和波形都不可靠。

### 输入缓冲与逻辑阈值

输入模式不是在“测电压大小”，而是在判断外部电压处于逻辑 0 还是逻辑 1。电压低到足够接近 GND 时读为 0，高到足够接近供电电压时读为 1，中间区域不应该长期停留。不同芯片的阈值以数据手册为准，所以教程里不要把 GPIO 当 ADC 用。

按键输入最常见的问题是悬空：按钮没按下时，如果引脚既没有接到 3.3 V，也没有接到 GND，它就像一根天线，会被手、导线、电源噪声影响，读数乱跳。解决办法是使用内部上拉/下拉，或在外部加电阻给它一个默认状态。

### 上拉、下拉和按键

上拉电阻把引脚“轻轻拉向高电平”，下拉电阻把引脚“轻轻拉向低电平”。轻轻的意思是阻值较大，只负责定义默认状态，不适合给负载供电。

本章示例采用“内部上拉 + 按键接地”的接法：没有按下时，内部上拉让输入读到 1；按下时，按键把引脚直接接到 GND，输入读到 0。这种接法很常见，因为按键只需要连接到 GPIO 和 GND，不需要把 3.3 V 拉到面包板上。

### 中断：让边沿变成事件

轮询是程序定时读 `gpio_get_level()`；中断是硬件发现电平边沿后通知 CPU。按键按下、传感器触发、脉冲计数都可以用中断，但中断回调里只做很短的事情，例如发队列消息，不要在里面打印大量日志、访问网络或做长计算。

机械按键还有一个真实现象叫抖动：按下和松开的瞬间，触点会在几毫秒内反复接触和断开。硬件中断能捕捉边沿，但不会自动理解“这是一次按键”。实际项目通常要做软件消抖，例如记录触发时间，忽略太近的重复边沿，或把事件交给任务延时确认。

## ESP32-S3 上要特别注意的引脚

ESP32-S3 文档列出了 GPIO0 到 GPIO21、GPIO26 到 GPIO48 等物理 GPIO，但“有编号”不等于“开发板上随便用”。GPIO0、GPIO3、GPIO45、GPIO46 是启动绑带相关引脚；GPIO19 和 GPIO20 默认用于 USB-JTAG；GPIO26 到 GPIO32 通常用于 SPI Flash / PSRAM，某些带 Octal Flash 或 Octal PSRAM 的模组还会占用 GPIO33 到 GPIO37。

初学阶段最稳妥的做法是：优先使用开发板文档推荐的普通 IO；示例工程通过 `menuconfig` 配置引脚；每次换板子都重新确认板载 LED、按键、USB、Flash、PSRAM 和外接模块是否占用了同一引脚。

## 准备工作

准备一个 LED、一个限流电阻、一个按键和若干杜邦线。LED 串联限流电阻后接到一个可用 GPIO，按键一端接 GPIO，另一端接 GND，并在程序中打开内部上拉。

如果你的开发板自带 LED，也可以直接使用板载 LED。不同开发板的 LED 引脚和有效电平不一定相同：有些板子是 GPIO 输出高电平 LED 亮，有些板子是输出低电平 LED 亮。观察现象时要把电路极性一起考虑进去。

## 最小例程

对应工程：`examples/gpio_button_led`。

```c
gpio_set_direction(CONFIG_LED_GPIO, GPIO_MODE_OUTPUT);
gpio_set_direction(CONFIG_BUTTON_GPIO, GPIO_MODE_INPUT);
gpio_set_pull_mode(CONFIG_BUTTON_GPIO, GPIO_PULLUP_ONLY);
```

运行后按下按键，LED 状态会切换，串口会打印 `LED ON` 或 `LED OFF`。如果没有反应，先确认按键是否接到 GND，再确认 `menuconfig` 里的 GPIO 编号和板载 LED 的有效电平。

## 读写背后的 API 含义

`gpio_set_direction()` 决定这个引脚当前作为输入、输出，还是输入输出同时打开。`gpio_set_pull_mode()` 配置内部上拉或下拉。`gpio_get_level()` 只返回逻辑 0 或 1；如果引脚没有配置为输入，官方文档明确提示读到的值不代表真实输入。`gpio_set_level()` 则只对输出模式有意义。

如果要一次性配置方向、上下拉和中断类型，ESP-IDF 也提供 `gpio_config()`。入门阶段分开写更容易看清每一步；项目变大后，用结构体集中配置会更清楚。

## 速率与边界

GPIO 的“速度”不是一个固定答案，它取决于 CPU、驱动调用方式、中断负载、日志输出、是否运行 RTOS，以及信号是否交给专用外设。对初学者来说，GPIO 最适合做人机输入、状态输出、低速控制和事件触发。

如果你要做几十 Hz 到几 kHz 的 LED 闪烁或按键读取，GPIO 完全够用。如果你要做稳定 PWM，用 LEDC；要发精确定时脉冲，用 RMT；要高速连续数据，用 SPI、I2S 或专用外设。不要用 `while` 循环手搓高速协议，这会让系统很难稳定。

电气边界也很重要：GPIO 是数字引脚，不是电源输出。不要让外部电压超过芯片允许范围，不要把 5 V 模块的输出直接接到不支持 5 V 容忍的 IO，不要用 GPIO 直接驱动大电流负载。负载稍大时，应使用三极管、MOSFET、驱动芯片、继电器模块或光耦等接口电路。

## 应用场景

GPIO 常见场景包括板载 LED、按键、继电器使能、传感器中断脚、芯片片选脚、电源控制脚和故障告警脚。它的优点是简单直接；缺点是只能表达电平，不能自己完成复杂时序，也不能表达“电压是多少”。

当你开始连接外设时，可以先问三个问题：这个信号是输入还是输出？默认状态需要上拉还是下拉？它只是一个慢速开关，还是应该交给 I2C、SPI、UART、LEDC、RMT 这样的专用外设？

## 常见错误

输入脚悬空会导致读数乱跳，所以按键输入要有上拉或下拉。LED 不亮时，不要只怀疑代码，也要检查 LED 极性、限流电阻、开发板实际引脚和有效电平。

中断重复触发时，先考虑按键抖动，而不是马上怀疑 ESP-IDF。开漏输出没有高电平时，先检查上拉电阻。换开发板后示例失效时，先查原理图，因为同一个 GPIO 编号在不同板上的用途可能完全不同。

## 参考资料

- [ESP-IDF GPIO & RTC GPIO 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/gpio.html)
- [ESP32-S3 技术参考手册](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_cn.pdf)
- [ESP32-S3 数据手册](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_cn.pdf)
- [ST AN4899：STM32 GPIO 硬件设置与低功耗建议](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf)
- [CSDN：一文带你搞懂有关于 GPIO 的一切](https://blog.csdn.net/joker520522/article/details/142768029)

<div class="prompt-card">
<strong>本章提示词</strong>

我想用 ESP32 学习 GPIO。请根据我的开发板型号和接线，帮我设计一个按键切换 LED 的最小 ESP-IDF demo，并解释输入上拉、按键消抖、LED 极性、串口验证方法和常见接线错误。
</div>
