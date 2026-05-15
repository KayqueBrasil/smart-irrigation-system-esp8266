#ifndef SENSORES_H
#define SENSORES_H

// === Sensors ===
// Moisture sensor, definition functions
float medirUmidadeSolo();
void iniciarUmidadeSolo();

// Temperature and humidity from DHT22 sensor, definition functions
void iniciarDHT();
float medirTemperatura();
float medirUmidadeAr();

#endif