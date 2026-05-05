#include <Arduino.h>
#include "config.h"

void iniciarRele() {
    pinMode(RELEPIN, OUTPUT);
    digitalWrite(RELEPIN, LOW); // Garante que o relé comece desligado
}

void ativacaoRele(bool estado) {
    digitalWrite(RELEPIN, estado ? 1 : 0);
}