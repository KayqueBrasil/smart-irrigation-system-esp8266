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

The system was developed using the ESP8266 platform with modularized firmware architecture.

---

## Features

* Calibrated soil moisture monitoring
* Temperature monitoring with DHT22
* Air humidity monitoring with DHT22
* Automatic irrigation control
* Relay-based irrigation simulation
* Serial Monitor debugging output
* Sensor-powered GPIO protection technique
* Hysteresis-based irrigation logic
* Modular embedded architecture

---

## Control Logic

The system uses hysteresis to avoid constant relay switching and unstable irrigation behavior.

### Moisture Scale

* 0%   = Wet Soil
* 100% = Dry Soil

### Irrigation Thresholds

* Soil Moisture > 55%  → Irrigation ON
* Soil Moisture <= 25% → Irrigation OFF

### Irrigation Pulse System

Instead of keeping irrigation continuously active, the system operates using irrigation pulses:

* Relay ON  → 2 seconds
* Relay OFF → 1 second
* Re-evaluate soil moisture

### This strategy helps:

* Prevent over-irrigation
* Allow water absorption by the soil
* Improve moisture reading accuracy
Reduce unnecessary relay activation

---

## Sensor Calibration
The soil moisture sensor uses calibrated values instead of the raw ADC range.

This improves measurement accuracy because analog soil sensors typically do not use the full ADC range of the ESP8266.

---

### GPIO-Powered Soil Sensor

The soil moisture sensor is powered directly by a GPIO pin instead of constant VCC power.

The sensor is energized only during measurements.

Advantages
* Reduces sensor corrosion
* Minimizes electrolysis
* Improves sensor lifespan
* Reduces power consumption

---

## Technologies Used

* ESP8266 (NodeMCU 1.0 ESP-12E)
* Arduino Framework
* Capacitive Soil Moisture Sensor
* DHT22 Sensor
* Relay Module
* C++
* PlatformIO

---

## Project Structure

```
.
├── src/
│   └── main.cpp
│   └── sensor.cpp
│   └── rele.cpp
├── include/
│   ├── config.h
│   ├── sensor.h
│   └── rele.h
├── platformio.ini
└── README.md
```

---

## Hardware Setup

### Components:

* ESP8266 (NodeMCU 1.0 - ESP12E)
* Capacitive Soil Moisture Sensor
* DHT22 Temperature and Humidity Sensor
* Relay module
* LED (for simulation)
* BreadBoard
* Jumpers and Resistor

---

## Behavior:

1. Read soil moisture
2. Read ambient temperature
3. Read air humidity
4. Compare soil moisture with thresholds
5. Activate irrigation if soil is dry
6. Continuously re-evaluate moisture during irrigation
7. Stop irrigation when moisture reahes safe levels

---



## Future Improvements

* Real water pump integration
* MQTT communication
* Data logging
* State machine architecture

---

## Demonstration

><img width="741" height="1600" alt="physical circuit" src="https://github.com/user-attachments/assets/828da583-816c-4625-ac16-9a3de651f333" />


---

## Related Project

https://wokwi.com/projects/462011896573960193

