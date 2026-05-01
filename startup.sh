#!/usr/bin/env bash

set -e

LAB_ROOT="$HOME/Labs_346/lab12_346"

MOSQUITTO_EXE="/c/Program Files/mosquitto/mosquitto.exe"
MOSQUITTO_CONF="/c/Users/kentn/mosquitto-local.conf"
GIT_BASH="/c/Program Files/Git/git-bash.exe"
FLASK_PY="python"

echo "Starting Lab 12 in separate Git Bash terminals..."

"$GIT_BASH" -c "echo -ne '\033]0;MQTT Broker\007'; \"$MOSQUITTO_EXE\" -c \"$MOSQUITTO_CONF\" -v; exec bash" &

sleep 2

"$GIT_BASH" -c "echo -ne '\033]0;Flask Dashboard\007'; cd \"$LAB_ROOT/flask_dashboard\" && \"$FLASK_PY\" app.py; exec bash" &

sleep 5

start http://127.0.0.1:5000

sleep 1

"$GIT_BASH" -c "echo -ne '\033]0;ESP32 Monitor\007'; cd \"$LAB_ROOT/esp32_rx\" && pio device monitor -b 115200; exec bash" &

echo "Lab 12 started."