# Smart Irrigation System (ESP8266)

IoT-based smart irrigation system using ESP8266, a capacitive soil moisture sensor, and a DHT22 environmental sensor.

The system automatically controls irrigation based on calibrated soil moisture levels while monitoring ambient temperature and air humidity.

---

## Overview

This project implements an embedded smart irrigation system capable of monitoring:

* Soil moisture
* Ambient temperature
* Air humidity

Based on the soil moisture level, the system automatically activates or deactivates irrigation using a relay module.

Currently, irrigation is simulated using:

* Relay module
* LED indicator

The firmware was developed using a modular embedded architecture with non-blocking timing logic based on millis().

The project also implements a complete IoT monitoring architecture using MQTT, Mosquitto Broker, and Node-RED Dashboard for real-time wireless monitoring.
---

## Features

* Calibrated soil moisture monitoring
* Temperature monitoring with DHT22
* Air humidity monitoring with DHT22
* Automatic irrigation control
* Relay-based irrigation simulation
* MQTT communication support
* GPIO-powered soil sensor protection
* Hysteresis-based irrigation control
* Non-blocking timing system using millis()
* Modular firmware architecture
* Real-time Node-RED dashboard
* Wireless monitoring via local network
* MQTT publish/subscribe architecture
* Mobile dashboard access
* Real-time telemetry visualization
---

## Control Logic

The system uses hysteresis to avoid constant relay switching and unstable irrigation behavior.

### Moisture Scale

* 0%   = Wet Soil
* 100% = Dry Soil

### Irrigation Thresholds

* Soil Moisture > 65%  → Irrigation ON
* Soil Moisture <= 40% → Irrigation OFF

### Irrigation Pulse System

Instead of keeping irrigation continuously active, the system operates using irrigation pulses:

* Relay ON  → 2 seconds
* Relay OFF → 10 second
* Re-evaluate soil moisture

### This strategy helps:

* Prevent over-irrigation
* Allow water absorption by the soil
* Improve moisture reading accuracy
* Reduce unnecessary relay activation

---

## Sensor Calibration
The soil moisture sensor uses calibrated values instead of the raw ADC range.

This improves measurement accuracy because analog soil sensors typically do not use the full ADC range of the ESP8266.

---

### GPIO-Powered Soil Sensor

The capacitive soil moisture sensor is powered directly from a GPIO pin instead of remaining permanently connected to VCC.

The sensor is energized only during measurements.

Advantages
* Reduces sensor corrosion
* Minimizes electrolysis
* Improves sensor lifespan
* Reduces power consumption

---
## MQTT Communication

The system supports MQTT communication for remote monitoring and IoT integration.

Sensor data currently published:

* Soil moisture
* Ambient temperature
* Air humidity

This enables integration with:

* Home Assistant
* Node-RED
* IoT dashboards
* Cloud monitoring systems

## MQTT Architecture

ESP8266 -> Mosquitto Broker -> Node-RED Dashboard

### Example MQTT Topics

* irrigacao/sensor/umidade_solo
* irrigacao/sensor/temperatura
* irrigacao/sensor/umidade_ar

---

## Node-RED Dashboard

A real-time dashboard was developed using Node-RED Dashboard.

The dashboard provides:

* Real-time soil moisture visualization
* Ambient temperature monitoring
* Air humidity monitoring
* Mobile access through local network
* Real-time MQTT updates

<img width="958" height="943" alt="image" src="https://github.com/user-attachments/assets/ef9f1ca3-a28d-4d02-9411-4515a908b4cd" />

---

## MQTT Broker

The system uses Eclipse Mosquitto as the MQTT broker for message distribution.

The broker is responsible for:

* Receiving sensor data from ESP8266
* Managing MQTT topics
* Delivering messages to Node-RED subscribers
* Enabling real-time IoT communication

---

## IoT Architecture

The project follows a distributed IoT architecture composed of:

* Embedded sensing device (ESP8266)
* MQTT communication layer
* Broker-based messaging system
* Real-time dashboard visualization

This architecture improves scalability, modularity, and future cloud integration possibilities.

---

## Technologies Used

* ESP8266 (NodeMCU 1.0 ESP-12E)
* Arduino Framework
* C++
* PlatformIO
* MQTT Protocol
* Eclipse Mosquitto
* Node-RED
* Capacitive Soil Moisture Sensor
* DHT22 Sensor
* Relay Module

---

## Project Structure

```
.
├── src/
│   ├── main.cpp
│   ├── sensores.cpp
│   ├── rele.cpp
│   ├── mqtt.cpp
│   └── wifi.cpp
│
├── include/
│   ├── config.h
│   ├── sensores.h
│   ├── rele.h
│   ├── mqtt.h
│   └── wifi.h
│
├── .gitignore
├── platformio.ini
└── README.md
```

---

## Hardware Setup

### Components:

* ESP8266 (NodeMCU 1.0 - ESP-12E)
* Capacitive Soil Moisture Sensor
* DHT22 Temperature and Humidity Sensor
* Relay module
* LED (simulation)
* BreadBoard
* Jumpers
* Resistor

---

## System Workflow

1. Read soil moisture
2. Read ambient temperature
3. Read air humidity
4. Publish sensor data via MQTT
5. Update Node-RED dashboard
6. Compare soil moisture against thresholds
7. Active irrigation if soil is dry
8. Continuosly re-avaluate mosutre during irrigation
9. Stop irrigation when sage moisture levels are reached

---



## Future Improvements

* Real water pump integration
* StreamLit Dashboards with Python
* Data logging
* Finite State Machine (FSM) architecture

---

## Demonstration

><img width="741" height="1600" alt="physical circuit" src="https://github.com/user-attachments/assets/828da583-816c-4625-ac16-9a3de651f333" />


---

## Related Project

https://wokwi.com/projects/462011896573960193

