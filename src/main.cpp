#include <Arduino.h>
#include "sensores.h"
#include "rele.h"

bool statusRele = 0;

void setup() {
  Serial.begin(9600);
  iniciarRele();
  iniciarDHT();
  iniciarUmidadeSolo();
}

void loop() {
  float umidadeSolo = medirUmidadeSolo();
  float temperatura = medirTemperatura();
  float umidadeAr = medirUmidadeAr();

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
  /*
  Soil Moisture: 0.00% == WET
  Soil Moisture: 100.00% == DRY
  */
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
        break; // Exit the loop if the soil moisture is less than or equal to 25%
      }
    }
  } 

  delay(30000); // Aguarda 30 segundos antes de medir novamente
}
