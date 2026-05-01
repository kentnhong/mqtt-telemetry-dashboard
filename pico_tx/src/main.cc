#include <Arduino.h>
#include "button_tx.h"

// Change these pins as needed for your wiring
static const uint8_t APP_BUTTON_PIN = 15; // button to GND
// Note: use &Serial1 for Pico UART0 default pins (TX=0, RX=1)

void setup() {
  // USB serial for debugging
  Serial.begin(115200);

  // Initialize the button transmitter module
  button_tx_init(APP_BUTTON_PIN, &Serial1, 115200);
}

void loop() {
  // Process any pending button events (sends over UART)
  button_tx_process();

  // Keep main loop light
  delay(10);
}
