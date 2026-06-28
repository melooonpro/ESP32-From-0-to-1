#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_sens.h"
#include "esp_check.h"
#include "esp_log.h"
#include "soc/soc_caps.h"

static const char *TAG = "touch_read";

#if SOC_TOUCH_SENSOR_VERSION != 2
#error "This tutorial example targets ESP32-S3 style Touch V2 hardware."
#endif

#define TOUCH_SAMPLE_CFG_DEFAULT() \
    { TOUCH_SENSOR_V2_DEFAULT_SAMPLE_CONFIG(500, TOUCH_VOLT_LIM_L_0V5, TOUCH_VOLT_LIM_H_2V2) }

#define TOUCH_CHAN_CFG_DEFAULT() \
    { \
        .active_thresh = {2000}, \
        .charge_speed = TOUCH_CHARGE_SPEED_7, \
        .init_charge_volt = TOUCH_INIT_CHARGE_VOLT_DEFAULT, \
    }

void app_main(void)
{
    touch_sensor_handle_t sensor = NULL;
    touch_channel_handle_t channel = NULL;

    touch_sensor_sample_config_t sample_cfg[TOUCH_SAMPLE_CFG_NUM] = TOUCH_SAMPLE_CFG_DEFAULT();
    touch_sensor_config_t sensor_cfg = TOUCH_SENSOR_DEFAULT_BASIC_CONFIG(TOUCH_SAMPLE_CFG_NUM, sample_cfg);
    ESP_ERROR_CHECK(touch_sensor_new_controller(&sensor_cfg, &sensor));

    touch_channel_config_t channel_cfg = TOUCH_CHAN_CFG_DEFAULT();
    ESP_ERROR_CHECK(touch_sensor_new_channel(sensor, CONFIG_TOUCH_CHANNEL_ID, &channel_cfg, &channel));

    touch_sensor_filter_config_t filter_cfg = TOUCH_SENSOR_DEFAULT_FILTER_CONFIG();
    ESP_ERROR_CHECK(touch_sensor_config_filter(sensor, &filter_cfg));

    ESP_ERROR_CHECK(touch_sensor_enable(sensor));
    for (int i = 0; i < 3; i++) {
        ESP_ERROR_CHECK(touch_sensor_trigger_oneshot_scanning(sensor, 2000));
    }
    ESP_ERROR_CHECK(touch_sensor_start_continuous_scanning(sensor));

    ESP_LOGI(TAG, "Touch channel %d started. Touch and release the pad to observe smooth data.",
             CONFIG_TOUCH_CHANNEL_ID);

    uint32_t data[TOUCH_SAMPLE_CFG_NUM] = {};
    while (1) {
        ESP_ERROR_CHECK(touch_channel_read_data(channel, TOUCH_CHAN_DATA_TYPE_SMOOTH, data));
        ESP_LOGI(TAG, "smooth data: %" PRIu32, data[0]);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
