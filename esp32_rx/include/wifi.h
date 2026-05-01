/**
 * @file wifi.h
 * @brief WiFi connectivity management.
 * 
 * Handles WiFi connection to CECS network and triggers MQTT init on connect.
 */
#pragma once

void wifi_init();
bool wifi_is_connected();
