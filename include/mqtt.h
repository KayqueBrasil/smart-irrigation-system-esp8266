#ifndef MQTT_H
#define MQTT_H

void conectarMQTT();
void publicarMQTT(const char* sufixo, const char* mensagem);
void verificarMQTT();
void reconectarMQTT();

#endif