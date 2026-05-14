#include <Arduino.h>
#include <config.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// Function to return soil moisture percentage
float medirUmidadeSolo() {
    // Reads the analog value from the soil moisture sensor
    int valorAnalogico = analogRead(SENSOR_UMIDSOLO);

    // Converts the analog value to a moisture percentage (0 to 100%)
    float umidade = 100.0 - (valorAnalogico / 1023.0) * 100.0;

    return umidade;
}

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// DHT sensor functions
void iniciarDHT() {
    // Initialize the DHT sensor
    dht.begin();
}

// Function to return temperature reading from DHT sensor
float medirTemperatura() {
    // Reads the temperature from the DHT sensor
    float temperatura = dht.readTemperature();
    return temperatura;
}

// Function to return humidity reading from DHT sensor
float medirUmidadeAr() {
    // Reads the humidity from the DHT sensor
    float umidade = dht.readHumidity();
    return umidade;
}
