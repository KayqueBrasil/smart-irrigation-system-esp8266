#ifndef CONFIG_H
#define CONFIG_H

// === Geral Config ===
// Pin defitions to sensors and actuators
// INPUTS
#define SENSOR_UMIDSOLO A0  // Moisture sensor connected to analog pin A0
#define DHT_PIN 5           // DHT sensor connected to digital pin 5
#define DHT_TYPE DHT22      // Type of DHT sensor

// OUTPUTS
#define RELEPIN 13          // Relay pin for irrigation control

#endif 