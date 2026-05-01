# Mission Event Dashboard (Embedded Telemetry System)

A multi-platform embedded system that captures physical button events on a Raspberry Pi Pico, transmits them over UART to an ESP32-C6, publishes them via MQTT, and visualizes the data in a real-time Flask web dashboard.

---

## Overview

This project demonstrates a full embedded-to-cloud-style telemetry pipeline:
Pico (GPIO Interrupt)
↓ UART
ESP32-C6 (Parser + MQTT Client)
↓ Wi-Fi
MQTT Broker (Mosquitto)
↓
Flask Server (Subscriber)
↓
Web Dashboard (Real-Time UI)

---

## Features

- Interrupt-driven event capture on Raspberry Pi Pico  
- UART communication between Pico and ESP32-C6  
- MQTT publishing using ESP-IDF (`esp_mqtt_client`)  
- Local MQTT broker using Mosquitto  
- Flask-based real-time dashboard  
- JSON-based telemetry messages  
- Dark “mission control” UI with live updates  
- Automated launch script for full system startup  

---

## Hardware

- Raspberry Pi Pico  
- ESP32-C6 Dev Board  
- Pushbutton + pull-up resistor  
- Breadboard + jumper wires  

### Wiring

| Pico | ESP32 |
|------|------|
| TX   | RX (GPIO4) |
| GND  | GND |

Button:
GP15 → Button → GND (with pull-up)
---

## Software Stack

- C++ (Arduino / ESP-IDF style)
- Python (Flask + Paho MQTT)
- MQTT (Mosquitto)
- PlatformIO
- Git Bash (automation script)

---

## Message Format

UART message (Pico → ESP32):
BTN,<count>,<timestamp_ms>
MQTT payload (ESP32 → Broker):

```json
{
  "count": 12,
  "timestamp_ms": 483920
}
Topic structure:

cecs346/lab12/pico/button
Setup
1. Clone repo
git clone https://github.com/yourusername/your-repo.git
cd your-repo
2. Install dependencies
Python
cd flask_dashboard
python -m venv .venv
source .venv/Scripts/activate
pip install flask paho-mqtt
MQTT (Mosquitto)

Install from:
https://mosquitto.org/download/

Running the System
🔥 One-command startup
./start_lab12.sh

This launches:

MQTT broker
Flask dashboard
ESP32 serial monitor
Web browser
Manual startup (optional)
Start MQTT broker:
mosquitto -v
Run Flask dashboard:
cd flask_dashboard
python app.py
Flash + monitor ESP32:
cd esp32_rx
pio run -t upload
pio device monitor
Flash Pico:
cd pico_tx
pio run -t upload
Dashboard

Access at:

http://127.0.0.1:5000

Displays:

Latest event count
Pico timestamp
MQTT topic
Recent event history
Reset Behavior
Pico reset → resets event count and timestamp
Flask restart → clears dashboard history
ESP32 reset → reconnects MQTT client
Example Output
BTN,1,120
BTN,2,450
BTN,3,890

Dashboard updates in real-time with each press.

Troubleshooting
No MQTT data
Check ESP32 Wi-Fi connection
Verify broker IP in mqtt.cc
Ensure Mosquitto is running
No UART data
Verify TX → RX wiring
Confirm baud rate (115200)
Check shared GND
Flask not loading
Ensure Python dependencies installed
Confirm correct port (5000)
Restart Flask
Future Improvements
Bidirectional MQTT control (reset from dashboard)
Multiple sensor inputs
Data logging to database
Authentication for dashboard
WebSocket-based updates (no polling)
Author

Kent Hong
Computer Engineering Student
Embedded Systems & Flight Software Focus

License

MIT License
