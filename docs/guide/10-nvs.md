# NVS 配置保存

这一章让 ESP32 学会“记住上一次的设置”，重启后不再像失忆一样从头开始。

NVS 是 Non-Volatile Storage，适合保存 Wi-Fi 配置、设备名称、计数器、校准参数等小数据。它不是大文件数据库，也不适合高频写入。

## 直觉

普通变量断电就消失，NVS 像一小块可以跨重启保存的笔记本。第一次启动读不到值，就写入默认值；之后每次启动都能读回上次保存的内容。

## 准备工作

本章不需要额外硬件，只需要能正常烧录和查看串口日志。先跑最小计数器，确认“重启后数值仍然增加”这个现象。

## 最小例程

对应工程：`examples/nvs_counter`。

```c
nvs_handle_t handle;
nvs_open("storage", NVS_READWRITE, &handle);
nvs_get_i32(handle, "boot_count", &boot_count);
nvs_set_i32(handle, "boot_count", boot_count + 1);
nvs_commit(handle);
```

烧录后多次按复位键，串口中的启动次数应持续增加。如果重新擦除 flash，计数会回到初始状态。

## 速率与边界

NVS 面向小配置和低频写入，不是高速日志系统。写 flash 有寿命和擦写粒度，频繁保存传感器采样会让系统变慢，也会缩短 flash 寿命。

课堂项目里，NVS 适合保存阈值、模式、校准值、设备名和启动次数。采样历史、图片、音频或大量日志应考虑文件系统、外部存储或上传到网络服务。

## 应用场景

NVS 常用于保存 Wi-Fi 配置、用户设置、工厂校准参数、设备序列号和上次运行状态。它让设备重启后还能记住配置，是从 demo 走向产品的第一步。

## 常见错误

写入后忘记 `nvs_commit`，重启后数据不会保存。NVS 适合小配置，不要用它保存大段日志或频繁采样数据。不同命名空间和 key 要有清晰含义，避免项目变大后混乱。

## 官方资料

- [NVS Flash API](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/storage/nvs_flash.html)

<div class="prompt-card">
<strong>本章提示词</strong>

请帮我写一个 ESP32 NVS 配置保存 demo。要求保存启动次数或用户阈值，解释命名空间、key、默认值、`commit`、擦除 flash 后的现象，以及什么时候不适合使用 NVS。
</div>
