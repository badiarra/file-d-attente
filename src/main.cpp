#include <Arduino.h>

#include "mesures/Mesure.h"
#include "led/Led.h"
#include "hcsr04/HC_SR04.h"
#include "dht22/DHT22.h"
#include "affichage/Affichage.h"

// BROCHES

#define TRIG_PIN       5
#define ECHO_PIN       18

#define DHT_PIN        4

#define LED_VERTE_PIN  25
#define LED_ROUGE_PIN  26

// QUEUE

QueueHandle_t queueMesures;

// OBJETS

Led ledVerte(LED_VERTE_PIN);

Led ledRouge(LED_ROUGE_PIN);

HC_SR04 hc(TRIG_PIN, ECHO_PIN);

DHT22Sensor dht(DHT_PIN);

Affichage affichage(ledVerte, ledRouge);

// SETUP

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("Demarrage ESP32...");

    // CRÉATION DE LA QUEUE

    queueMesures = xQueueCreate(10, sizeof(Mesure));

    if (queueMesures == nullptr)
    {
        Serial.println("ERREUR : impossible de creer la queue");

        while (true)
        {
            delay(1000);
        }
    }

    // DONNER LA QUEUE AUX OBJETS

    hc.setQueue(queueMesures);

    dht.setQueue(queueMesures);

    affichage.setQueue(queueMesures);

    // INITIALISATION

    hc.init();

    dht.init();

    ledVerte.init()

    ledRouge.init()

    // DÉMARRAGE DES TÂCHES

    hc.start();

    dht.start();

    affichage.start();

    Serial.println("Tâches demarrées.");
}


// LOOP

void loop()
{
    // Rien à faire ici.
    // Les tâches FreeRTOS font tout le travail.

    vTaskDelay(portMAX_DELAY);
}
