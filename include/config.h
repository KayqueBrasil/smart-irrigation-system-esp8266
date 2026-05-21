#ifndef CONFIG_H
#define CONFIG_H

// === Geral Config ===
//MQTT broker configuration
#define MQTT_BROKER "192.16"      // IP address of the MQTT broker
#define MQTT_PORT 1883                  // MQTT broker port
#define MQTT_TOPIC "irrigacao/sensor"   // MQTT topic for publishing sensor data and receiving commands
#define MQTT_CLIENT_ID "ESP8266_Irrigacao" // Unique client ID for MQTT connection

// WiFi credentials
#define WIFI_SSID ""          // WiFi network name
#define WIFI_PASSWORD ""// WiFi network password

// Pin defitions to sensors and actuators
// INPUTS
#define SENSOR_UMIDSOLO A0  // Moisture sensor connected to analog pin A0
#define DHT_PIN 5           // DHT sensor connected to digital pin 5
#define DHT_TYPE DHT22      // Type of DHT sensor

// OUTPUTS
#define RELEPIN 13          // Relay pin for irrigation control
#define UMID_SOLO_VCC 4     // Power pin for soil moisture sensor

#endif 