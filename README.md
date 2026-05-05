# Smart Irrigation System (ESP8266)

IoT-based smart irrigation system using ESP8266 and a soil moisture sensor.
This project automatically activates irrigation (currently simulated with a relay + LED) based on soil humidity levels.

---

## Overview

This system monitors soil moisture and controls irrigation automatically.

When the soil becomes too dry (below a defined threshold), the system activates a relay, simulating the irrigation process. When the soil moisture returns to acceptable levels, the system turns irrigation off.

Currently, irrigation is represented by an LED connected to a relay module.

---

## Features

* Soil moisture monitoring
* Automatic relay control (irrigation simulation)
* Serial output for debugging and monitoring
* ESP8266-based embedded system

---

## Control Logic

The irrigation decision is based on a simple threshold:

* If soil moisture **< 30% → Irrigation ON**
* If soil moisture **≥ 30% → Irrigation OFF**

---

## Technologies Used

* ESP8266
* Arduino Framework
* Soil Moisture Sensor (analog)
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
* Relay module
* LED (for simulation)
* BreadBoard

### Behavior:

* Sensor reads soil moisture
* ESP8266 processes the value
* Relay is triggered based on threshold
* LED indicates irrigation status

---

## How It Works

1. The system reads soil moisture using `medirUmidade()`
2. Compares with threshold (30%)
3. Updates relay state:
   
   * Activates irrigation if soil is dry
   * Deactivates when moisture is sufficient
     
4. Prints status via Serial Monitor

---

## Future Improvements

* Add water pump (real irrigation)
* Wi-Fi monitoring (ESP8266)
* MQTT integration
* Include DHT22 (temperature and air umidity)
* Adjustable threshold via app
* Data logging

---

## Demonstration

><img width="741" height="1600" alt="physical circuit" src="https://github.com/user-attachments/assets/828da583-816c-4625-ac16-9a3de651f333" />


---

## Related Project

https://wokwi.com/projects/462011896573960193

