# ESP32-S3 从 0 到 1

这是一个面向无经验大学生的中文网页版教程，以 ESP32-S3 和 ESP-IDF 为主线，从 Windows 环境搭建、Hello World、基础外设、FreeRTOS，到 AI 时代的提示词协作和 ESP-Claw 应用方向。

## 本地预览

```powershell
npm install
npm run docs:dev
```

## 构建静态站点

```powershell
npm run docs:build
```

构建产物位于 `docs/.vitepress/dist`。

## 示例工程

`examples/` 下每个目录都是一个独立 ESP-IDF 小工程。进入目录后执行：

```powershell
idf.py set-target esp32s3
idf.py menuconfig
idf.py build flash monitor
```

教程内容优先引用乐鑫官方公开资料和示例；内部资料仅用于学习路径组织，不写入隐私或非技术内容。
