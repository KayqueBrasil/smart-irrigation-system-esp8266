#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "config.h"

void iniciarWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Connect to the specified WiFi network
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the local IP address assigned to the ESP8266
}