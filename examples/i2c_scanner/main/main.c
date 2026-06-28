#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "i2c_scanner";

void app_main(void)
{
    i2c_master_bus_handle_t bus_handle;
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = CONFIG_I2C_SDA_GPIO,
        .scl_io_num = CONFIG_I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));
    ESP_LOGI(TAG, "Scanning I2C bus, SDA=%d, SCL=%d", CONFIG_I2C_SDA_GPIO, CONFIG_I2C_SCL_GPIO);

    while (1) {
        int found = 0;

        for (uint8_t address = 0x03; address < 0x78; address++) {
            esp_err_t ret = i2c_master_probe(bus_handle, address, 50);
            if (ret == ESP_OK) {
                ESP_LOGI(TAG, "Found device at 0x%02X", address);
                found++;
            }
        }

        if (found == 0) {
            ESP_LOGW(TAG, "No I2C device found");
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
