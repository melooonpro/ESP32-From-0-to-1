# OTA 固件升级

OTA 是 Over-The-Air update，意思是设备通过网络下载新固件并切换到新版本。它不是第一个联网 demo，而是产品长期维护时必须理解的能力。

## 直觉

最小 OTA 可以理解成三步：下载新固件，写入另一个应用分区，重启后从新分区启动。为了避免升级失败变砖，真实产品还会加入版本校验、签名、回滚和发布管理。

## 准备工作

你需要先完成 Wi-Fi 章节，并理解分区表。初学阶段建议先阅读官方 OTA 示例和分区说明，在本地测试服务器或受控网络中练习，不要直接连接生产服务。

## 最小例程

本章先以官方 `native_ota_example` 为最小参考。核心 API 是 `esp_https_ota`：

```c
esp_http_client_config_t config = {
    .url = CONFIG_FIRMWARE_UPGRADE_URL,
};
esp_err_t ret = esp_https_ota(&config);
```

先观察升级成功、URL 错误、网络断开三种日志。能解释每一种失败发生在哪个阶段，比盲目追求一次成功更重要。

## 常见错误

OTA 需要匹配分区表；如果只有一个应用分区，就没有地方写入新固件。HTTPS 需要处理证书。升级流程中不要硬编码内部服务器地址、账号或密钥。

## 官方资料

- [OTA API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/ota.html)
- [分区表](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/partition-tables.html)
- [ESP-IDF OTA 示例](https://github.com/espressif/esp-idf/tree/master/examples/system/ota)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我理解 ESP32 OTA 升级。要求解释 OTA 分区表、下载流程、HTTPS 证书、版本校验、失败回滚和串口日志判断方法，并给出一个适合课堂演示的最小升级实验方案。
</div>
