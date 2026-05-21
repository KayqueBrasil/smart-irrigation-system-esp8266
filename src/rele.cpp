#include <Arduino.h>
#include "config.h"

void iniciarRele() {
    pinMode(RELEPIN, OUTPUT);
    digitalWrite(RELEPIN, LOW); // Grants the relay is off at the start
}

bool utilizarRele(bool estado) {
    digitalWrite(RELEPIN, estado ? HIGH : LOW); // Turn on the relay if estado is true, otherwise turn it off
    return estado; // Return the current state of the relay
}   