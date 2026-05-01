#include "uart.h"
#include "button.h"
#include "mqtt.h"
#include <driver/uart.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static constexpr const char* TAG = "UART";
static constexpr uart_port_t UART_PORT = UART_NUM_1;
static constexpr int RX_PIN = 4;
static constexpr int BAUD = 115200;
static constexpr int BUF_SIZE = 1024;

static void read_task(void* arg) {
    uint8_t* data = (uint8_t*)malloc(BUF_SIZE);
    char line[128] = {0};
    int line_idx = 0;
    
    while (1) {
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (len > 0) {
            for (int i = 0; i < len; i++) {
                char c = (char)data[i];
                if (c == '\n') {
                    line[line_idx] = '\0';
                    
                    uint32_t count = 0, ts = 0;
                    if (btn_parse(line, &count, &ts)) {
                        ESP_LOGI(TAG, "Parsed: count=%lu, ts=%lu", count, ts);
                        if (mqtt_is_connected()) {
                            mqtt_publish_button(count, ts);
                        }
                    } else {
                        ESP_LOGW(TAG, "Parse failed: %s", line);
                    }
                    
                    line_idx = 0;
                } else if (c != '\r' && line_idx < (int)sizeof(line) - 1) {
                    line[line_idx++] = c;
                }
            }
        }
    }
    
    free(data);
}

void uart_init() {
    const uart_config_t cfg = {
        .baud_rate = BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
    
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT, UART_PIN_NO_CHANGE, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, nullptr, 0));
    
    ESP_LOGI(TAG, "Initialized on GPIO%d at %u baud", RX_PIN, BAUD);
}

void uart_start_task() {
    xTaskCreate(read_task, "uart_read", 4096, nullptr, 5, nullptr);
    ESP_LOGI(TAG, "Reader task started");
}
