# ESP32 从 0 到 1

这是一个面向无经验大学生的中文网页版教程，以 ESP32 和 ESP-IDF 为主线，从 Windows 环境搭建、Hello World、基础外设、Touch、FreeRTOS，到 AI 时代的提示词协作和 ESP-Claw 应用方向。

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

## 发布到 GitHub Pages

仓库包含 `.github/workflows/deploy-docs.yml`。推送到 `main` 后，GitHub Actions 会自动构建并发布 VitePress 站点。

如需本地模拟 GitHub Pages 项目页路径：

```powershell
$env:VITEPRESS_BASE="/ESP32-From-0-to-1/"
npm run docs:build
Remove-Item Env:VITEPRESS_BASE
```

## 示例工程

`examples/` 下每个目录都是一个独立 ESP-IDF 小工程。进入目录后执行：

```powershell
# 代码示例以 ESP32-S3 为目标芯片
idf.py set-target esp32s3
idf.py menuconfig
idf.py build flash monitor
```

教程内容优先引用乐鑫官方公开资料和示例。
