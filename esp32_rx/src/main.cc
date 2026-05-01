#include "wifi.h"
#include "mqtt.h"
#include "uart.h"
#include <esp_log.h>

extern "C" void app_main(void) {
    ESP_LOGI("MAIN", "=== ESP32-C6→MQTT ===");
    
    uart_init();
    uart_start_task();
    wifi_init();
    
    ESP_LOGI("MAIN", "Initialization complete");
}
