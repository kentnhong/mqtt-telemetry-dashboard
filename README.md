# Multi-Platform MQTT Dashboard

## What it Does

This project builds a simple multi-platform embedded system:

- A button press is detected on a **Raspberry Pi Pico**
- The Pico sends data over **UART** to an **ESP32-C6**
- The ESP32 publishes the data to an **MQTT broker**
- A **Flask dashboard** subscribes to the data and displays it in real time

## Sample Output

![Dashboard Screenshot](images/dashboard_example.png)

---

## Hardware Prerequisites

- Raspberry Pi Pico  
- ESP32-C6-DevKitC-1 Board
- Pushbutton  
- Jumper wires  
- Breadboard
- 10K Ohm Resistor

---

## Software Prerequisites

- VS Code + PlatformIO  
- Python 3  
- Flask (`pip install flask`)  
- Paho MQTT (`pip install paho-mqtt`)  
- Mosquitto MQTT Broker
- Zadig

---

## Wiring

### Pico → ESP32 (UART)

| Pico | ESP32 |
|------|------|
| TX (GP0)   | RX (GPIO4) |
| GND  | GND |

> Both boards must share a common ground.

---

### Button Wiring (Pico)


GP15 → Button → GND


- Use internal pull-up (`INPUT_PULLUP`)

---

## Message Flow


Pico → UART → ESP32 → MQTT → Flask → Browser


---

## Running


```bash
./startup.sh
```

---

## Pico USB Driver Setup (Zadig)

If your Raspberry Pi Pico is not recognized correctly on Windows (e.g., shows up as `RP2 Boot` or does not appear as a COM port), install the USB driver using Zadig.

### Install Zadig

Download Zadig from:
https://zadig.akeo.ie/

Run Zadig as Administrator.

---

### Install Driver for Pico

1. Hold the **BOOTSEL** button on the Pico  
2. Plug the Pico into your computer  
3. Release BOOTSEL  

The device should appear as:


RP2 Boot


4. Open Zadig  
5. Click **Options → List All Devices**  
6. Select **RP2 Boot** from the dropdown  
7. In the driver box, select:


WinUSB


8. Click **Install Driver**

---

### After Installation

- Unplug and reconnect the Pico normally (without holding BOOTSEL)  
- It should now appear as a **COM port**  
- PlatformIO should detect it automatically  

---

### Notes

- BOOTSEL mode is only for flashing firmware  
- Normal operation should show the Pico as a serial device (COM port)  
- If the Pico is not detected, repeat the steps above  

