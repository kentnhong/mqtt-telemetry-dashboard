from flask import Flask, render_template, jsonify
import paho.mqtt.client as mqtt
import json
import threading
import time

MQTT_HOST = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "cecs346/lab12/#"

app = Flask(__name__)

events = []
latest = {"topic": "", "count": None, "timestamp_ms": None, "received_time": None}


def on_connect(client, userdata, flags, rc):
    print("MQTT connected:", rc)
    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    global latest

    payload = msg.payload.decode(errors="replace")
    print(msg.topic, payload)

    try:
        data = json.loads(payload)
    except json.JSONDecodeError:
        data = {"raw": payload}

    event = {
        "topic": msg.topic,
        "count": data.get("count"),
        "timestamp_ms": data.get("timestamp_ms"),
        "received_time": time.strftime("%H:%M:%S"),
    }

    latest = event
    events.insert(0, event)

    if len(events) > 25:
        events.pop()


def mqtt_thread():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(MQTT_HOST, MQTT_PORT, 60)
    client.loop_forever()


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/events")
def get_events():
    return jsonify({"latest": latest, "events": events})


if __name__ == "__main__":
    threading.Thread(target=mqtt_thread, daemon=True).start()
    app.run(host="0.0.0.0", port=5000, debug=False)
