# ESP32 从 0 到 1

把一个想法，变成会感知、会控制、会联网的小设备。

这是一个面向非工科读者和无经验大学生的中文网页版教程。它不要求你先读懂芯片手册，而是先让你看见 ESP32 能做什么：点亮一颗灯、读取一个按钮或旋钮、连接一个传感器、发起一次网络请求，最后把这些能力组合成可以演示的小应用。

技术主线仍然是 ESP32 和 ESP-IDF，但每章会先回答“这件事在现实里有什么用”，再进入命令、代码和官方资料。

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
