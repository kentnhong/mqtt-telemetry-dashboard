#include "mqtt.h"
#include <mqtt_client.h>
#include <esp_log.h>
#include <cJSON.h>
#include <string.h>
#include <stdlib.h>

static constexpr const char* TAG = "MQTT";
static constexpr const char* BROKER_URI = "mqtt://10.0.0.34:1883";
static constexpr const char* TOPIC_BUTTON = "cecs346/lab12/pico/button";

static esp_mqtt_client_handle_t g_mqtt = nullptr;
static bool g_connected = false;

static void on_mqtt_event(void* handler_args, esp_event_base_t base, int32_t event_id, void* event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "Connected");
            g_connected = true;
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "Disconnected");
            g_connected = false;
            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "Error");
            break;

        default:
            break;
    }
}

void mqtt_init() {
    if (g_mqtt) {
        return;
    }

    esp_mqtt_client_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.broker.address.uri = BROKER_URI;

    g_mqtt = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_register_event(g_mqtt, MQTT_EVENT_ANY, on_mqtt_event, nullptr);
    esp_mqtt_client_start(g_mqtt);

    ESP_LOGI(TAG, "Initialized, topic: %s", TOPIC_BUTTON);
}

bool mqtt_is_connected() {
    return g_connected;
}

void mqtt_publish_button(uint32_t count, uint32_t timestamp_ms) {
    if (!g_connected) {
        ESP_LOGW(TAG, "Not connected");
        return;
    }

    cJSON* doc = cJSON_CreateObject();
    cJSON_AddNumberToObject(doc, "count", count);
    cJSON_AddNumberToObject(doc, "timestamp_ms", timestamp_ms);

    char* json_str = cJSON_PrintUnformatted(doc);

    int msg_id = esp_mqtt_client_publish(
        g_mqtt,
        TOPIC_BUTTON,
        json_str,
        strlen(json_str),
        0,
        0
    );

    ESP_LOGI(TAG, "Published button (msg_id=%d): %s", msg_id, json_str);

    cJSON_Delete(doc);
    free(json_str);
}