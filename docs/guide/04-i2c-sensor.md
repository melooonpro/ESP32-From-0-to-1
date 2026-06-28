# I2C 与传感器

I2C 适合连接低速外设，比如温湿度传感器、OLED 屏、触摸芯片、IO 扩展器。它只需要两根主要信号线：SCL 时钟线和 SDA 数据线。

## 先扫地址

初学 I2C 不要一上来就读传感器寄存器。第一步应该是扫描总线地址，确认接线、电源和上拉电阻基本正常。

```c
i2c_master_bus_config_t bus_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = CONFIG_I2C_SDA_GPIO,
    .scl_io_num = CONFIG_I2C_SCL_GPIO,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};
```

如果扫描不到设备，优先检查：VCC/GND 是否接对、SDA/SCL 是否接反、模块是否需要 3.3 V、地址是否被硬件引脚改变。

## 从地址到寄存器

扫描到地址后，才进入“读写寄存器”。大多数传感器的数据手册会告诉你某个寄存器地址代表什么。读传感器的过程通常是：写入寄存器地址，再读取返回字节，最后按数据手册换算成物理量。

不要把 I2C 看成“神奇的传感器接口”。它只是总线协议，真正的含义来自外设芯片的数据手册。

## 本章实验

- `examples/i2c_scanner`：扫描 I2C 地址。

扩展任务：接一个 SSD1306 OLED 或温湿度传感器，把扫描到的地址写入表格，并记录接线方式。

## 官方资料

- [I2C API 参考](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/peripherals/i2c.html)
- [ESP-IDF I2C 示例](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/i2c)

<div class="prompt-card">
<strong>本章提示词</strong>

我想用 ESP32-S3 学习 I2C 传感器。请先帮我做 I2C 地址扫描和接线排查，再根据我提供的数据手册寄存器表，提取初始化流程、读数流程、错误处理和最小 ESP-IDF demo。
</div>
