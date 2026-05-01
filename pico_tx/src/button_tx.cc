#include "button_tx.h"

// Configuration defaults
static const uint32_t DEFAULT_DEBOUNCE_MS = 50;

// Module state
static volatile uint32_t s_event_count = 0;
static volatile uint32_t s_last_event_ms = 0;
static volatile uint32_t s_prev_event_ms = 0;
static volatile bool s_event_pending = false;
static uint32_t s_debounce_ms = DEFAULT_DEBOUNCE_MS;
static uint8_t s_button_pin = 0;
static HardwareSerial* s_uart = nullptr;

// Buffer for message formatting
static char s_msg_buf[96];

// ISR - minimal work
void s_handle_button_isr() {
  uint32_t now = millis();
  if ((now - s_last_event_ms) < s_debounce_ms) return;
  s_prev_event_ms = s_last_event_ms;
  s_last_event_ms = now;
  s_event_count++;
  s_event_pending = true;
}

void button_tx_init(uint8_t button_pin, HardwareSerial* uart, uint32_t baud) {
  s_button_pin = button_pin;
  s_uart = uart;

  if (s_uart) s_uart->begin(baud);

  pinMode(25, OUTPUT); // on-board LED
  // Button wired from GP15 to GND with a 10k pull-up to 3V3(OUT).
  // Use the internal pull-up too, so the pin stays HIGH when idle and goes LOW on press.
  pinMode(s_button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(s_button_pin), s_handle_button_isr, FALLING);

  Serial.begin(115200);
  Serial.println("button_tx: initialized");
}

void button_tx_process() {
  if (!s_event_pending) return;

  // Capture shared state
  noInterrupts();
  uint32_t count = s_event_count;
  uint32_t ts = s_last_event_ms;
  uint32_t prev = s_prev_event_ms;
  s_event_pending = false;
  interrupts();

  int len = snprintf(s_msg_buf, sizeof(s_msg_buf), "BTN,%lu,%lu\n", (unsigned long)count, (unsigned long)ts);
  if (len > 0 && s_uart) {
    s_uart->write((const uint8_t*)s_msg_buf, len);
    Serial.print("BTN: ");
    Serial.print(count);
    if (prev == 0) {
      Serial.println(" <Elapsed Time: first press>");
    } else {
      Serial.print(" <Elapsed Time: ");
      Serial.print((unsigned long)(ts - prev));
      Serial.println("ms>");
    }
  }

  // Blink LED to indicate activity
  digitalWrite(25, HIGH);
  delay(60);
  digitalWrite(25, LOW);
}
