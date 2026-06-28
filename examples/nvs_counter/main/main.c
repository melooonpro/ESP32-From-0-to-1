#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "nvs_counter";

static void init_nvs(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    } else {
        ESP_ERROR_CHECK(ret);
    }
}

void app_main(void)
{
    init_nvs();

    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open("app", NVS_READWRITE, &handle));

    int32_t boot_count = 0;
    esp_err_t ret = nvs_get_i32(handle, "boot_count", &boot_count);
    if (ret == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(TAG, "boot_count not found, start from 0");
    } else {
        ESP_ERROR_CHECK(ret);
    }

    boot_count++;
    ESP_ERROR_CHECK(nvs_set_i32(handle, "boot_count", boot_count));
    ESP_ERROR_CHECK(nvs_commit(handle));
    nvs_close(handle);

    while (1) {
        ESP_LOGI(TAG, "This firmware has booted %ld times", boot_count);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
