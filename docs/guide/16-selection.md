<script setup>
import { withBase } from 'vitepress'
</script>

# 选型方法

做一个 ESP32 项目时，不要先问“哪颗芯片最强”，而要先问“这个产品必须完成什么事”。芯片选型的核心，是把产品需求翻译成几个硬指标：无线连接、算力、内存、外设接口、功耗、封装尺寸、成本和供货周期。

乐鑫官方的 [Product Selector](https://products.espressif.com/#/product-selector?names=) 很适合做第一轮筛选。先用它把 Wi-Fi、Bluetooth、Thread/Zigbee、USB、PSRAM、Flash、GPIO 数量这些条件过滤掉，再回到具体模组和开发板文档确认硬件连接方式。

## 先定产品，再定芯片

选型时可以按这个顺序走：

1. 先写产品场景：语音交互、传感器采集、低功耗联网、屏幕交互，还是简单控制。
2. 再写无线需求：只要 2.4 GHz Wi-Fi，还是需要 5 GHz Wi-Fi 6、BLE、Thread/Zigbee。
3. 再看算力和内存：是否跑语音唤醒、屏幕 UI、音频流、模型推理或较大的协议栈。
4. 再核对外设：麦克风、扬声器、屏幕、摄像头、传感器、USB、I2C、SPI、UART、ADC、PWM 是否够用。
5. 最后看工程因素：模块是否自带认证，天线空间是否够，量产焊接是否容易，供应是否稳定。

初学阶段建议优先选模组或开发板，而不是裸芯片。模组已经把 Flash、晶振、射频匹配和天线处理好，能把问题集中在软件和应用验证上。

## 产品一：喵伴 / ESP-VoCat

<figure class="doc-figure">
  <img :src="withBase('/official/esp-vocat-black-front.png')" alt="ESP-VoCat 喵伴实物图">
  <figcaption>ESP-VoCat 喵伴实物图，图片来自 Espressif ESP-VoCat 官方用户指南。</figcaption>
</figure>

喵伴对应乐鑫官方开发套件 ESP-VoCat，定位是 AI 语音交互开发套件。官方文档说明它面向玩具、智能音箱、智能中控等需要大模型能力的语音交互产品，板上包含 ESP32-S3-WROOM-1 模组、圆形触摸屏、双麦克风阵列，并支持离线语音唤醒和声源定位。

这类产品优先选择 **ESP32-S3**，原因很直接：

- 它同时有 Wi-Fi 和 Bluetooth LE，适合联网、配网和手机附近交互。
- 它面向 AIoT 场景，适合语音唤醒、音频处理、屏幕 UI、边缘侧控制这类组合任务。
- ESP-VoCat 使用带较大 Flash/PSRAM 的 ESP32-S3-WROOM-1 模组，能给语音、屏幕和应用逻辑留下余量。
- 生态成熟，ESP-SR、ESP-ADF、ESP-IDF 示例更容易找到，适合作为语音产品原型的第一块板。

如果你的目标是做“会说话、能联网、有屏幕或触摸交互”的桌面设备，ESP32-S3 是很稳的起点。它不是为了最低成本，而是为了把语音、显示、连接和交互同时跑起来。

## 产品二：ESP-SensairShuttle

<figure class="doc-figure">
  <img :src="withBase('/official/esp-sensairshuttle-mainboard-front.png')" alt="ESP-SensairShuttle 实物图">
  <figcaption>ESP-SensairShuttle 主板实物图，图片来自 Espressif ESP-SensairShuttle 官方用户指南。</figcaption>
</figure>

ESP-SensairShuttle 是乐鑫与 Bosch Sensortec 联合推出的传感器与大模型人机交互开发板，面向运动感知、多模态传感和智能交互场景。官方文档说明它使用 **ESP32-C5-WROOM-1-N16R8** 模组作为主控，并提供 Bosch Sensortec Shuttle Board 接口、麦克风/扬声器接口和电池供电接口。

这类产品优先选择 **ESP32-C5**，关键在无线和传感器扩展：

- ESP32-C5 支持 2.4 GHz 与 5 GHz 双频 Wi-Fi 6，适合需要更好网络兼容性和更现代无线链路的设备。
- 它同时支持 Bluetooth LE、Zigbee 和 Thread，适合智能家居、多协议传感器网关和 Matter 相关原型。
- SensairShuttle 的传感器子板接口适合快速替换气体、温湿度、姿态、磁场等传感器，芯片选型要给多传感器数据流和无线协议栈留空间。
- 选择 ESP32-C5 的重点不是“更适合语音屏幕”，而是“更适合多协议联网 + 多传感器验证”。

如果你的目标是做“能感知环境、能接入智能家居网络、可能同时面对 Wi-Fi 与 Thread/Zigbee”的设备，ESP32-C5 比 ESP32-S3 更贴近产品方向。

## 快速判断

| 场景 | 优先考虑 | 理由 |
| --- | --- | --- |
| 语音交互、屏幕、AI 玩具、智能中控 | ESP32-S3 | 生态成熟，适合音频、UI、联网和边缘侧控制组合 |
| 多传感器采集、智能家居、多协议联网 | ESP32-C5 | 双频 Wi-Fi 6，并支持 BLE、Zigbee、Thread |
| 低成本联网开关、简单传感器 | ESP32-C3 / ESP32-C2 | 成本和功耗更友好，功能边界清晰 |
| Thread/Zigbee 低功耗节点 | ESP32-H2 / ESP32-C6 / ESP32-C5 | 根据是否需要 Wi-Fi 共同存在来选择 |

一个实用判断是：如果产品像“会说话的小终端”，先看 ESP32-S3；如果产品像“接很多传感器的无线节点或网关”，先看 ESP32-C5。Product Selector 用来缩小范围，开发板用户指南用来确认真实硬件能不能支撑你的产品结构。

## 资料来源

- [Espressif Product Selector](https://products.espressif.com/#/product-selector?names=)
- [ESP-VoCat User Guide](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp-vocat/user_guide_v1.2.html)
- [ESP-SensairShuttle User Guide](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c5/esp-sensairshuttle/user_guide_v1.0.html)
- [ESP32-S3 Product Page](https://www.espressif.com/en/products/socs/esp32-s3)
- [ESP32-C5 Product Page](https://www.espressif.com/en/products/socs/esp32-c5)
