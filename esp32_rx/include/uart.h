/**
 * @file uart.h
 * @brief UART interface for receiving Pico messages.
 * 
 * Initializes UART1 on GPIO4 and manages async read task for incoming data.
 */
#pragma once

void uart_init();
void uart_start_task();
