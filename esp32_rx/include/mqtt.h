/**
 * @file mqtt.h
 * @brief MQTT client for publishing button events to broker.
 * 
 * Manages MQTT connection and publishes button events as JSON to the broker.
 */
#pragma once

#include <stdint.h>

void mqtt_init();
bool mqtt_is_connected();
void mqtt_publish_button(uint32_t count, uint32_t timestamp_ms);
