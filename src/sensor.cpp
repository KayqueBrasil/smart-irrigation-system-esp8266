#include <Arduino.h>
#include "config.h"

// Função para medir a umidade do solo
float medirUmidade() {
    // Lê o valor analógico do sensor de umidade do solo
    int valorAnalogico = analogRead(SENSOR_UMIDSOLO);

    // Converte o valor analógico para um valor de umidade (0 a 100%)
    float umidade = 100.0 - (valorAnalogico / 1023.0) * 100.0;

    return umidade;
}