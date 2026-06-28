# Wi-Fi 与 HTTP

当 ESP32 连上 Wi-Fi，它就不只是“会点灯的板子”，而是网络中的一个节点。网络章节的关键是理解事件：连接开始、获得 IP、断开、重连，都不是一行阻塞代码完成的。

## 直觉

Wi-Fi station 模式就是让开发板像手机一样连接路由器。HTTP 则是在联网之后向服务器发出请求，获取状态码和响应内容。

## 准备工作

准备一个 2.4 GHz Wi-Fi 网络。SSID、密码和请求 URL 通过 `menuconfig` 配置，不写死在公开代码中。第一次实验建议使用稳定的本地网络，不要一上来就叠加 HTTPS、JSON 和云平台。

## 最小例程

对应工程：`examples/wifi_station_http`。

```c
esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
esp_wifi_start();
```

联网流程通常包括初始化 NVS、初始化网络接口、创建默认事件循环、配置 Wi-Fi、等待 IP 事件，再发起 HTTP GET。串口中看到 IP 地址和 HTTP 状态码，就说明网络闭环跑通。

## 速率与边界

Wi-Fi 的吞吐和延迟不只由芯片决定，还受路由器、距离、信道拥塞、加密、TCP 重传和服务器响应影响。教程里的 HTTP GET 只验证“能连上并能请求”，不代表已经完成稳定产品网络设计。

初学阶段不要把 HTTP 请求写成永远阻塞的函数。网络任务要有超时、错误日志和重试策略，并且不能影响采样、按键或安全相关任务。

## 应用场景

Wi-Fi 适合局域网控制、HTTP/MQTT 数据上传、网页配置、OTA 升级和云平台接入。它不适合极低功耗常久在线设备；电池项目要重点学习睡眠、唤醒和短连接。

## 常见错误

连不上时先检查路由器是否是 2.4 GHz、密码是否正确、信号是否稳定。HTTP 请求失败时，再看 DNS、URL、超时和证书问题。不要把 Wi-Fi 密码提交到仓库。

## 官方资料

- [Wi-Fi API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/network/esp_wifi.html)
- [HTTP Client API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/protocols/esp_http_client.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我写一个 ESP32 Wi-Fi station + HTTP GET demo。要求 SSID、密码和 URL 通过 `menuconfig` 配置，并解释 NVS、事件循环、获得 IP、HTTP 状态码、超时和 HTTPS 升级注意事项。
</div>
