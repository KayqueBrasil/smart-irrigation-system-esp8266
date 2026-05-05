#include <Arduino.h>
#include "sensor.h"
#include "rele.h"

bool statusRele = 0;

void setup() {
  Serial.begin(9600);
  iniciarRele();
}

void loop() {
  float umidade = medirUmidade();
  Serial.print("Umidade do solo: ");
  Serial.print(umidade);
  Serial.println("%");

  if (umidade < 30.0) {
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
