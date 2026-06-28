#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "hello";

void app_main(void)
{
    int seconds = 0;

    while (1) {
        ESP_LOGI(TAG, "Hello ESP32-S3, uptime: %d s", seconds++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
