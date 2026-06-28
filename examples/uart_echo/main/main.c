#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#define UART_PORT UART_NUM_1
#define BUF_SIZE 256

static const char *TAG = "uart_echo";

void app_main(void)
{
    uart_config_t uart_config = {
        .baud_rate = CONFIG_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT, CONFIG_UART_TX_GPIO, CONFIG_UART_RX_GPIO,
                                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    uint8_t data[BUF_SIZE];
    ESP_LOGI(TAG, "UART echo started, TX=%d, RX=%d, baud=%d",
             CONFIG_UART_TX_GPIO, CONFIG_UART_RX_GPIO, CONFIG_UART_BAUD_RATE);

    while (1) {
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE, pdMS_TO_TICKS(1000));
        if (len > 0) {
            uart_write_bytes(UART_PORT, (const char *)data, len);
            ESP_LOGI(TAG, "echoed %d bytes", len);
        }
    }
}
