#include <Arduino.h>
#include "sensores.h"
#include "rele.h"

bool statusRele = 0;
int tempoAnterior;

enum ESTADO {
  MONITORANDO,
  IRRIGANDO,
  ESPERANDO  
};

ESTADO estadoAtual = MONITORANDO;

void setup() {
  Serial.begin(9600);
  iniciarRele();
  iniciarDHT();
  iniciarUmidadeSolo();
}

void loop() {
  switch (estadoAtual)
  {
    case MONITORANDO:
    {
      float umidadeSolo = medirUmidadeSolo();
      float temperatura = medirTemperatura();
      float umidadeAr = medirUmidadeAr();

      if (umidadeSolo > 65.0) // If the soil moisture is less than or equal to 65%
      { 
        tempoAnterior = millis(); // Store the current time
        statusRele = 1;           // Status to turn on the relay
        estadoAtual = IRRIGANDO;  // Transition to irrigating state
        ativacaoRele(statusRele); // Control the relay based on the status
      }
      Serial.print("=== Monitorando ===\n");
      Serial.print("Umidade do solo: ");
      Serial.print(umidadeSolo);
      Serial.println(" % - ");
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C - ");
      Serial.print("Umidade do ar: ");
      Serial.print(umidadeAr);
      Serial.println(" %");
      Serial.print("Rele: ");
      Serial.println(statusRele ? "ON" : "OFF");
      Serial.print("\n");
      break;
    }

    case IRRIGANDO:
    {
      if (millis() - tempoAnterior >= 2000) // Check if 2 seconds have passed
      {
        statusRele = 0;           // Status to turn off the relay
        tempoAnterior = millis(); // Update the time for the next check
        estadoAtual = ESPERANDO;  // Transition to waiting state
      }
      ativacaoRele(statusRele); // Control the relay based on the status
      Serial.print("=== Irrigando ===\n");
      Serial.print("Rele: ");
      Serial.println(statusRele ? "ON" : "OFF");
      Serial.print("\n");
      break;
    }

    case ESPERANDO:
    {
      if (millis() - tempoAnterior >= 1000) // Check if 1 second has passed
      {
        float umidadeSolo = medirUmidadeSolo(); // Measure soil moisture again
        if (umidadeSolo <= 40.0) // If the soil moisture is less than or equal to 40%
        {
          statusRele = 0;            // Status to turn off the relay
          estadoAtual = MONITORANDO; // Transition back to monitoring state
        }
        else
        {
          tempoAnterior = millis(); // Update the time for the next check
          statusRele = 1;            // Status to turn on the relay
          estadoAtual = IRRIGANDO;  // Transition back to irrigating state
        }
      }
      Serial.print("=== Esperando ===\n");
      Serial.print("Umidade do solo: ");
      Serial.print(medirUmidadeSolo());
      Serial.println(" %");
      Serial.print("Rele: ");
      Serial.println(statusRele ? "ON" : "OFF");
      Serial.print("\n");
      break;
    }
    default:
    {
      break;
    }
  }
}


/*
millis();
Serial.print("----------------------------------\n");
Serial.print("Umidade do solo: ");
Serial.print(umidadeSolo);
Serial.println("%");
Serial.print("----------------------------------\n");

millis();
Serial.print("----------------------------------\n");
Serial.print("Temperatura: ");
Serial.print(temperatura);
Serial.println("°C");
Serial.print("----------------------------------\n");

millis();
Serial.print("----------------------------------\n");
Serial.print("Umidade do ar: ");
Serial.print(umidadeAr);
Serial.println("%");
Serial.print("----------------------------------\n");

Soil Moisture: 0.00% == WET
Soil Moisture: 100.00% == DRY

// Based on the soil moisture reading, control the relay for irrigation
if (umidadeSolo <= 25.0) // If the soil moisture is less than or equal to 25%
{ 
statusRele = 0; // Turn off the relay
}  
if (umidadeSolo > 55.0) // If the soil moisture is greater than 55%
{ 
statusRele = 1; // Turn on the relay
while (true)
{
ativacaoRele(statusRele); // Control the relay based on the status
delay(2000); // Wait 2 seconds for the soil to absorb the water

ativacaoRele(0); // Turn off the relay to avoid over-irrigation
delay(1000); // Wait 1 second to check the soil moisture again

float umidadeSolo = medirUmidadeSolo();
Serial.print("Umidade do solo: ");
Serial.print(umidadeSolo);
Serial.println("%");

if (umidadeSolo <= 25.0)
{
statusRele = 0;
break; // Exit the loop if the soil moisture is less than or equal to 25%
}
}
*/