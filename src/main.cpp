#include <Arduino.h>
#include "sensores.h"
#include "rele.h"

bool statusRele = 0;

void setup() {
  Serial.begin(9600);
  iniciarRele();
  iniciarDHT();
}

void loop() {
  float umidadeSolo = medirUmidadeSolo();
  float temperatura = medirTemperatura();
  float umidadeAr = medirUmidadeAr();

  Serial.print("Umidade do solo: ");
  Serial.print(umidadeSolo);
  Serial.println("%");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  Serial.print("Umidade do ar: ");
  Serial.print(umidadeAr);
  Serial.println("%");

  if (umidadeSolo < 30.0) {
    if (!statusRele) {
      statusRele = 1;
      Serial.println("Relé ativado: Irrigação ligada.");
    }
  } else {
    if (statusRele) {
      statusRele = 0;
      Serial.println("Relé desativado: Irrigação desligada.");
    }
  }

  ativacaoRele(statusRele); // Controla o relé com base no status

  delay(2000); // Aguarda 2 segundos antes de medir novamente
}
