#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "button_led";

void app_main(void)
{
    gpio_reset_pin(CONFIG_LED_GPIO);
    gpio_set_direction(CONFIG_LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_reset_pin(CONFIG_BUTTON_GPIO);
    gpio_set_direction(CONFIG_BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_BUTTON_GPIO, GPIO_PULLUP_ONLY);

    int led_on = 0;
    int last_button = 1;

    ESP_LOGI(TAG, "LED GPIO=%d, button GPIO=%d", CONFIG_LED_GPIO, CONFIG_BUTTON_GPIO);

    while (1) {
        int button = gpio_get_level(CONFIG_BUTTON_GPIO);

        if (last_button == 1 && button == 0) {
            led_on = !led_on;
            gpio_set_level(CONFIG_LED_GPIO, led_on);
            ESP_LOGI(TAG, "LED %s", led_on ? "ON" : "OFF");
            vTaskDelay(pdMS_TO_TICKS(40));
        }

        last_button = button;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
