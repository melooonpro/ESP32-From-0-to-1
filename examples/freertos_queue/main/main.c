#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

typedef struct {
    int level;
    int64_t timestamp_ms;
} button_event_t;

static const char *TAG = "rtos_queue";
static QueueHandle_t button_queue;

static void button_task(void *arg)
{
    int last_level = 1;

    while (1) {
        int level = gpio_get_level(CONFIG_BUTTON_GPIO);

        if (last_level == 1 && level == 0) {
            button_event_t event = {
                .level = level,
                .timestamp_ms = esp_timer_get_time() / 1000,
            };
            xQueueSend(button_queue, &event, pdMS_TO_TICKS(10));
            vTaskDelay(pdMS_TO_TICKS(40));
        }

        last_level = level;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void led_task(void *arg)
{
    int led_on = 0;
    button_event_t event;

    while (1) {
        if (xQueueReceive(button_queue, &event, portMAX_DELAY) == pdTRUE) {
            led_on = !led_on;
            gpio_set_level(CONFIG_LED_GPIO, led_on);
            ESP_LOGI(TAG, "button at %lld ms, LED %s", event.timestamp_ms, led_on ? "ON" : "OFF");
        }
    }
}

void app_main(void)
{
    gpio_reset_pin(CONFIG_LED_GPIO);
    gpio_set_direction(CONFIG_LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_reset_pin(CONFIG_BUTTON_GPIO);
    gpio_set_direction(CONFIG_BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_BUTTON_GPIO, GPIO_PULLUP_ONLY);

    button_queue = xQueueCreate(8, sizeof(button_event_t));
    if (button_queue == NULL) {
        ESP_LOGE(TAG, "failed to create queue");
        return;
    }

    xTaskCreate(button_task, "button_task", 2048, NULL, 5, NULL);
    xTaskCreate(led_task, "led_task", 2048, NULL, 4, NULL);
}
