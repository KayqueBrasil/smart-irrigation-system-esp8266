#include <Arduino.h>
#include <config.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long ultimoReconnectMQTT = 0;

void conectarMQTT() 
{
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT); // Set the MQTT broker and port
}

void reconectarMQTT()
{
    if (millis() - ultimoReconnectMQTT > 5000)
    {
        ultimoReconnectMQTT = millis();

        Serial.println("Tentando conectar MQTT...");

        if (mqttClient.connect(MQTT_CLIENT_ID))
        {
            Serial.println("MQTT conectado");

            mqttClient.subscribe("irrigacao/sensor");
        }
        else
        {
            Serial.print("Falha MQTT. rc=");
            Serial.println(mqttClient.state());
        }
    }
}

void publicarMQTT(const char* sufixo, const char* mensagem) {
  if (!mqttClient.connected())
    {
    reconectarMQTT(); // Ensure we are connected to the MQTT broker before publishing    
    }

    mqttClient.loop(); // Process any incoming messages and maintain the connection
    char topico[100];

    snprintf(topico, sizeof(topico), "%s/%s", MQTT_TOPIC, sufixo); // Create the full topic by appending the subtopic to the base topic

    if (mqttClient.publish(topico,mensagem))
    {
        Serial.println("Message published successfully");
    }
    else
    {
        Serial.println("Failed to publish message");
    }
}

void verificarMQTT()
{
    if (!mqttClient.connected())
    {
        reconectarMQTT();
    }

    mqttClient.loop();
}

