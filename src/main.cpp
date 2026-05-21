#include <Arduino.h>
#include <sensores.h>
#include <rele.h>
#include <wifi.h>
#include <mqtt.h>


// Global variables
bool statusRele = 0;
unsigned long tempoIrrigacao = 0;
unsigned long tempoEspera = 0;
unsigned long tempoPublicar = 0;
unsigned long tempoSensores = 0;
float umidadeSolo;
float temperatura;
float umidadeAr;

const float LIMITE_SECO = 65.0;
const float LIMITE_UMIDO = 40.0;

const unsigned long INTERVALO_PUBLICACAO = 10000; 
const unsigned long TEMPO_IRRIGACAO = 2000;
const unsigned long TEMPO_ESPERA = 10000;
const unsigned long TEMPO_MQTT = 10000;
const unsigned long TEMPO_LEITURA_SENSORES = 2000;

// Define the states of the system
enum ESTADO {
  MONITORANDO,
  IRRIGANDO,
  ESPERANDO
};
ESTADO estadoAtual = MONITORANDO;

void publicarDadosMQTT(); // Function prototype for publishing data to MQTT
void estadoMonitorando(); // Function prototype for monitoring state
void estadoIrrigando();   // Function prototype for irrigating state
void estadoEsperando();   // Function prototype for waiting state
void estadoPublicando();  // Function prototype for publishing state
void atualizarSensores();   // Function prototype for updating sensor readings

void setup() 
{
  Serial.begin(9600);
  iniciarRele();
  iniciarDHT();
  iniciarUmidadeSolo();
  iniciarWiFi();
  conectarMQTT();
}

void loop() {
  verificarMQTT(); // Check MQTT connection and process incoming messages

  atualizarSensores(); // Update sensor readings at regular intervals

  publicarDadosMQTT();

  switch (estadoAtual)
  {
    case MONITORANDO:
    {
      estadoMonitorando();
      break;
    }

    case IRRIGANDO:
    {
      estadoIrrigando();
      break;
    }

    case ESPERANDO:
    {
      estadoEsperando();
      break;
    }

    default:
    {
      break;
    }
  }
}

void estadoMonitorando() 
{
  if (umidadeSolo > LIMITE_SECO) // If the soil moisture is greater than 65%
  { 
    tempoIrrigacao = millis(); // Store the current time
    statusRele = utilizarRele(true); // Turn on the relay to start irrigation
    estadoAtual = IRRIGANDO;  // Transition to irrigating state
  }
}

void estadoIrrigando() 
{
  if (millis() - tempoIrrigacao >= TEMPO_IRRIGACAO) // Check if 2 seconds have passed
      {
        statusRele = utilizarRele(false);           // Turn off the relay
        tempoEspera = millis(); // Update the time for the next check
        estadoAtual = ESPERANDO;  // Transition to waiting state
      }
}

void estadoEsperando() 
{
  if (millis() - tempoEspera >= TEMPO_ESPERA) // Check if 10 seconds have passed
      {
        
        umidadeSolo = medirUmidadeSolo(); // Measure soil moisture again
        if (umidadeSolo <= LIMITE_UMIDO) // If the soil moisture is less than or equal to 40%
        {
          statusRele = utilizarRele(false);        // Turn off the relay
          estadoAtual = MONITORANDO; // Transition back to monitoring state
        }
        else
        {
          tempoIrrigacao = millis(); // Update the time for the next check
          statusRele = utilizarRele(true);        // Turn on the relay again
          estadoAtual = IRRIGANDO;  // Transition back to irrigating state
        }
      }
}


void atualizarSensores() 
{
  if (millis() - tempoSensores >= TEMPO_LEITURA_SENSORES) // Check if 2 seconds have passed
  {
    tempoSensores = millis(); // Update the time for the next check
    
    umidadeSolo = medirUmidadeSolo();
    temperatura = medirTemperatura();
    umidadeAr = medirUmidadeAr();
  }
}

void publicarDadosMQTT()
{
  if(millis() - tempoPublicar >= INTERVALO_PUBLICACAO)
  {
    tempoPublicar = millis(); // Update the time for the next publication

    char mensagem[128];
    snprintf(mensagem, sizeof(mensagem), "{\"umidade_solo\": %.2f}", umidadeSolo);
    publicarMQTT("umidade_solo", mensagem);

    snprintf(mensagem, sizeof(mensagem), "{\"temperatura\": %.2f}", temperatura);
    publicarMQTT("temperatura", mensagem);

    snprintf(mensagem, sizeof(mensagem), "{\"umidade_ar\": %.2f}", umidadeAr);
    publicarMQTT("umidade_ar", mensagem);
  }
}