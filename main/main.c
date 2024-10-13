#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "dht.h"

static const char *TAG = "DHT";

void dht_task(void *pvParameter)
{
    ESP_LOGI(TAG, "Starting DHT Task\n\n");
    dht_measurement_t measurement;

    while (1)
    {
        ESP_LOGI(TAG, "=== Reading DHT ===\n");
        dht_response_t ret = dht_read(&measurement);
        switch (ret) {
            case DHT_OK:
                ESP_LOGI(TAG, "Hum: %.1f Tmp: %.1f\n", measurement.humidity, measurement.temperature);
                break;
            case DHT_TIMEOUT_ERROR:
                ESP_LOGE(TAG, "DHT_TIMEOUT_ERROR");
                break;
            case DHT_CHECKSUM_ERROR:
                ESP_LOGE(TAG, "DHT_CHECKSUM_ERROR");
                break;
        }

        // -- wait at least 2 sec before reading again ------------
        // The interval of whole process must be beyond 2 seconds !!
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    esp_log_level_set("*", ESP_LOG_INFO);

    esp_rom_gpio_pad_select_gpio(GPIO_NUM_4);

    dht_set_gpio(GPIO_NUM_4);

    xTaskCreate(&dht_task, "dht_task", 2048, NULL, 5, NULL);
}
