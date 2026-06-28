# NVS、OTA 与工程化

当 demo 走向真实产品，你会遇到三个新问题：配置如何保存，固件如何升级，工程如何长期维护。本章先建立基本概念，不急着做完整商用方案。

## NVS：保存小配置

NVS 是 Non-Volatile Storage，适合保存 Wi-Fi 配置、设备名称、计数器、校准参数等小数据。它不是用来保存大文件的数据库，也不适合频繁高强度写入。

示例 `examples/nvs_counter` 每次启动读取计数器，加一后写回 NVS。这个例子很小，但它让你看到“掉电后数据还在”的效果。

## OTA：让设备升级自己

OTA 是 Over-the-Air update。最小理解是：设备从网络下载新固件，写入备用分区，重启后运行新版本。真正产品里还要处理签名校验、回滚、断电恢复、版本管理和发布流程。

初学阶段先阅读官方 OTA 示例，理解分区表和状态机；不要一开始就把 OTA 接到公网生产服务。

## 工程化目录建议

当例程变大后，可以按职责拆目录：

```text
main/
components/
  board/
  app_storage/
  app_network/
  app_sensors/
docs/
tests/
```

`main` 负责组装应用，`components` 负责可复用模块，`docs` 记录设计和接线，`tests` 放单元测试或硬件测试脚本。不要把所有代码永远堆在一个 `main.c` 里。

## 发布前检查

发布前至少检查：是否硬编码密钥，是否记录固件版本，是否能恢复默认配置，是否有错误日志，是否说明分区表，是否能重复构建。课程项目也应该有 README 和接线图。

## 官方资料

- [NVS Flash API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/storage/nvs_flash.html)
- [OTA API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/ota.html)
- [分区表](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/partition-tables.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我把一个 ESP32-S3 demo 推向工程化：用 NVS 保存启动次数或配置，解释 OTA 的分区和回滚流程，并给出目录拆分、发布前检查清单、隐私检查和故障恢复建议。
</div>
