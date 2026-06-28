# Wi-Fi 与 HTTP

当 ESP32-S3 连上 Wi-Fi，它就不只是“会点灯的板子”，而是网络中的一个节点。网络章节的关键是理解事件：连接开始、获得 IP、断开、重连，都不是一行阻塞代码完成的。

## Wi-Fi station 模式

station 模式就是让开发板像手机一样连接路由器。ESP-IDF 中常见流程是：初始化 NVS、初始化网络接口、创建默认事件循环、配置 Wi-Fi、启动 Wi-Fi、等待连接事件。

```c
esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
esp_wifi_start();
```

SSID 和密码不要写死在公开仓库里。示例工程通过 `menuconfig` 配置，构建时写入本地 `sdkconfig`。

<div class="prompt-card">
<strong>本节提示词</strong>

请解释 ESP-IDF Wi-Fi station 示例中的 NVS、netif、event loop、event handler、IP_EVENT_STA_GOT_IP 各自作用。请用“设备加入校园网”的流程类比。
</div>

## HTTP 请求

联网后可以做 HTTP GET 请求，最小目标是访问一个公开 URL 并打印状态码。真正项目里还要考虑 TLS 证书、超时、重试、内存和 JSON 解析。

初学阶段建议先请求 HTTP 测试地址，确认网络链路，再升级到 HTTPS 和业务 API。

<div class="prompt-card">
<strong>本节提示词</strong>

请基于 ESP-IDF 写一个 ESP32-S3 Wi-Fi station + HTTP GET demo。要求 SSID、密码、URL 都通过 menuconfig 配置，代码里不能硬编码隐私信息，并说明 HTTPS 版本还需要注意什么。
</div>

## 本章实验

- `examples/wifi_station_http`：连接 Wi-Fi 后发起一次 HTTP GET。

扩展任务：把 HTTP 返回内容中的前 128 字节打印出来，再思考为什么不能无限制保存整个响应。

<div class="prompt-card">
<strong>本节提示词</strong>

我想把 HTTP 返回的 JSON 解析出来控制 LED。请帮我设计数据格式、错误处理和最小 demo，并提醒我哪些内容不能硬编码到仓库。
</div>

## 官方资料

- [Wi-Fi API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/network/esp_wifi.html)
- [HTTP Client API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/protocols/esp_http_client.html)
