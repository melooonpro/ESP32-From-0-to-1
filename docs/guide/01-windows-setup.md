# Windows 环境搭建

环境搭建的目标只有一个：你能在 Windows 终端里执行 `idf.py build`，并把程序烧录到 ESP32-S3。先不要急着理解所有工具，先知道它们的分工。

## 工具链分工

ESP-IDF 是乐鑫官方 IoT 开发框架，里面包含构建系统、驱动、网络协议栈、示例工程和文档。Windows 上通常使用 ESP-IDF Tools Installer，它会帮你安装 Python、Git、编译器、OpenOCD 等工具。

开发板通过 USB 连接电脑后，会出现一个串口。烧录是把固件写入 Flash，监视是从串口读取日志。很多问题其实不是代码错，而是串口号、驱动、数据线或目标芯片选错了。

<div class="prompt-card">
<strong>本节提示词</strong>

请用初学者能理解的方式解释 ESP-IDF、Python、Git、CMake、交叉编译器、OpenOCD、串口驱动在 Windows 开发 ESP32-S3 时分别负责什么。请用“做饭厨房”的类比，但不要牺牲准确性。
</div>

## 安装步骤

1. 打开乐鑫官方 ESP-IDF Windows 安装说明。
2. 使用 ESP-IDF Tools Installer 安装推荐版本。
3. 安装完成后，打开 “ESP-IDF PowerShell” 或 “ESP-IDF Command Prompt”。
4. 执行 `idf.py --version`，确认命令可用。
5. 用 USB 数据线连接 ESP32-S3 开发板，在设备管理器中确认串口号。

如果你看到 `idf.py` 无法识别，通常是没有打开 ESP-IDF 专用终端，或环境变量没有加载。先从开始菜单打开安装器创建的终端，而不是普通 PowerShell。

```powershell
idf.py --version
python --version
git --version
```

<div class="prompt-card">
<strong>本节提示词</strong>

我在 Windows 上安装 ESP-IDF。请根据我贴出的 `idf.py --version`、`python --version`、设备管理器串口截图文字，判断环境是否正常，并给出下一步最小验证命令。
</div>

## 连接开发板

ESP32-S3-DevKitC-1 常见连接方式是 USB 数据线直连开发板。注意“能充电”的线不一定能传数据。如果烧录时一直连接失败，优先换数据线、换 USB 口，再检查 BOOT/RESET 按键。

第一次烧录建议先降低复杂度：只连接开发板，不外接面包板和传感器，避免外部电路影响启动模式。

<div class="prompt-card">
<strong>本节提示词</strong>

我使用 ESP32-S3-DevKitC-1，Windows 设备管理器里看到了一个 COM 口，但 `idf.py flash` 失败。请按优先级列出排查步骤，每一步说明为什么这样查，以及我应该观察什么现象。
</div>

## 官方资料

- [ESP-IDF ESP32-S3 快速入门](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/get-started/index.html)
- [ESP-IDF Windows 平台工具链标准设置](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/get-started/windows-setup.html)
