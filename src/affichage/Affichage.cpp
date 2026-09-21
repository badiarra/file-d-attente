#include "Affichage.h"

//Constructeur

Affichage::Affichage(Led &verte,Led &rouge)  // Les Leds sont pré-créées et on utilise leur adresse
    : ledVerte(verte), ledRouge(rouge)//Forme obligée pour les Leds car la reference doit etre initilaisée ainsi
{}


// ASSOCIER LA QUEUE

void Affichage::setQueue(QueueHandle_t q)
{
    queue = q;
}


// WRAPPER FREERTOS

void Affichage::taskWrapper(void *parameter) //Fonction de type classe (static)
{
    Affichage *instance = static_cast<Affichage *>(parameter);
    instance->run();
}


// TÂCHE D'AFFICHAGE

void Affichage::run()
{
    Mesure mesure;
    while (true)
    {
        if (xQueueReceive(queue, &mesure, portMAX_DELAY) == pdPASS) // ATTENDRE UNE MESURE
        {
            // HC-SR04
            if (mesure.type == MESURE_HCSR04)
            {
                Serial.print("HC-SR04 : ");
                Serial.print(mesure.distance);
                Serial.println(" cm");

                ledVerte.on();
                vTaskDelay( pdMS_TO_TICKS(100));
                ledVerte.off();
            }
            // DHT22
            else if (mesure.type == MESURE_DHT22)
            {
                Serial.print("DHT22 : ");
                Serial.print(mesure.temperature);
                Serial.print(" C | Humidite : ");
                Serial.print(mesure.humidite);
                Serial.println(" %");

                ledRouge.on();
                vTaskDelay(pdMS_TO_TICKS(100));
                ledRouge.off();
            }
        }
    }
}

// CRÉATION DE LA TÂCHE

void Affichage::start()
{
    xTaskCreate(
        taskWrapper,
        "Affichage",
        2048,
        this,
        1,
        &handle
    );
}
