#include <Arduino.h>
#include <config.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// Function to return soil moisture percentage
float medirUmidadeSolo() {
    digitalWrite(UMID_SOLO_VCC, HIGH); // Power on the soil moisture sensor
    delay(100); // Wait for the sensor to stabilize 
    int seco = 788;
    int molhado = 341;

    int valor = analogRead(SENSOR_UMIDSOLO);

    float umidade = ((float)(valor - seco) / (molhado - seco)) * 100.0;

    umidade = 100.0 - umidade;

    if (umidade > 100) umidade = 100;
    if (umidade < 0) umidade = 0;

    digitalWrite(UMID_SOLO_VCC, LOW); // Power off the soil moisture sensor
    return umidade;
}

void iniciarUmidadeSolo() {
    pinMode(UMID_SOLO_VCC, OUTPUT);
    digitalWrite(UMID_SOLO_VCC, LOW);
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
