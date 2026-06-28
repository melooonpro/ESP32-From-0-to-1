# NVS、OTA 与工程化

当 demo 走向真实产品，你会遇到三个新问题：配置如何保存，固件如何升级，工程如何长期维护。本章先建立基本概念，不急着做完整商用方案。

## NVS：保存小配置

NVS 是 Non-Volatile Storage，适合保存 Wi-Fi 配置、设备名称、计数器、校准参数等小数据。它不是用来保存大文件的数据库，也不适合频繁高强度写入。

示例 `examples/nvs_counter` 每次启动读取计数器，加一后写回 NVS。这个例子很小，但它让你看到“掉电后数据还在”的效果。

<div class="prompt-card">
<strong>本节提示词</strong>

请解释 ESP-IDF NVS 适合保存什么、不适合保存什么。以“设备启动次数计数器”和“Wi-Fi 配置”为例，说明命名空间、键、提交和擦除。
</div>

## OTA：让设备升级自己

OTA 是 Over-the-Air update。最小理解是：设备从网络下载新固件，写入备用分区，重启后运行新版本。真正产品里还要处理签名校验、回滚、断电恢复、版本管理和发布流程。

初学阶段先阅读官方 OTA 示例，理解分区表和状态机；不要一开始就把 OTA 接到公网生产服务。

<div class="prompt-card">
<strong>本节提示词</strong>

请用流程图文字解释 ESP32-S3 OTA 的基本过程：当前运行分区、下载新固件、写入 OTA 分区、校验、设置启动分区、重启和回滚。请指出每一步可能失败的原因。
</div>

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

<div class="prompt-card">
<strong>本节提示词</strong>

我已经有一个 600 行的 ESP-IDF `main.c`，包含 Wi-Fi、I2C、LED、NVS 和 HTTP。请帮我设计组件拆分方案，说明每个组件的头文件接口、依赖关系和迁移顺序。
</div>

## 发布前检查

发布前至少检查：是否硬编码密钥，是否记录固件版本，是否能恢复默认配置，是否有错误日志，是否说明分区表，是否能重复构建。课程项目也应该有 README 和接线图。

<div class="prompt-card">
<strong>本节提示词</strong>

请为一个 ESP32-S3 课程项目生成发布前检查清单。要求覆盖源码、配置、隐私、构建、烧录、串口日志、README、接线图、演示视频和常见故障。
</div>

## 官方资料

- [NVS Flash API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/storage/nvs_flash.html)
- [OTA API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/ota.html)
- [分区表](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/partition-tables.html)
