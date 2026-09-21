#include "HC_SR04.h"

// CONSTRUCTEUR

HC_SR04::HC_SR04(int trig, int echo)
{
    trigPin = trig;
    echoPin = echo;
}

// INITIALISATION

void HC_SR04::init()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// ASSOCIER LA QUEUE

void HC_SR04::setQueue(QueueHandle_t q)
{
    queue = q;
}

// WRAPPER POUR FREERTOS

void HC_SR04::taskWrapper(void *parameter)
{
    HC_SR04 *instance = static_cast<HC_SR04 *>(parameter);
    instance->run();
}


float HC_SR04::measureDistance()
{
    // Déclenchement

    digitalWrite(trigPin, LOW);

    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10);

    digitalWrite(trigPin,LOW);


    // Lecture du temps de retour

    long duree = pulseIn(echoPin, HIGH, 30000);

    // Pas de mesure valide

    if (duree <= 0)
    {
        return -1.0;
    }

    // Calcul de la distance en cm

    float distance = duree * 0.0343 / 2.0;

    return distance;
}


// TÂCHE HC-SR04

void HC_SR04::run()
{
    Mesure mesure;

    while (true)
    {
        float distance = measureDistance();

        if (distance >= 0)
        {
            mesure.type = MESURE_HCSR04;
            mesure.distance = distance;

            mesure.temperature = 0;
            mesure.humidite = 0;

            // Envoi dans la queue

            if (xQueueSend(queue, &mesure,0 ) != pdPASS)
            {
                Serial.println("Queue pleine : HC-SR04");
            }
        }

        // Attendre 500 ms
        vTaskDelay( pdMS_TO_TICKS(500));
    }
}


// CRÉATION DE LA TÂCHE

void HC_SR04::start()
{
    xTaskCreate(
        taskWrapper,
        "HC_SR04",
        2048,
        this,
        1,
        &handle
    );
}
