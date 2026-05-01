#ifndef BUTTON_TX_H
#define BUTTON_TX_H

#include <Arduino.h>

// Initialize the button transmitter module.
// - button_pin: GPIO with button (wired to GND, use internal pull-up)
// - uart: pointer to the HardwareSerial to use for TX (e.g., &Serial1)
// - baud: UART baud rate
void button_tx_init(uint8_t button_pin, HardwareSerial* uart, uint32_t baud = 115200);

// Call from the main `loop()` to process pending events and send messages.
void button_tx_process();

#endif // BUTTON_TX_H
