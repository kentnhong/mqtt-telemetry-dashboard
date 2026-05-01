/**
 * @file button.h
 * @brief Parse button event messages from Pico.
 * 
 * Parses "BTN,count,timestamp" format messages received from the Pico.
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>

bool btn_parse(const char* msg, uint32_t* count, uint32_t* timestamp_ms);
