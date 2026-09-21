#include "DHT22Sensor.h"

// CONSTRUCTEUR

DHT22Sensor::DHT22Sensor(int pin)
    : dht(pin, DHT22)
{}

// INITIALISATION

void DHT22Sensor::init()
{
    dht.begin();
}

// ASSOCIER LA QUEUE

void DHT22Sensor::setQueue(QueueHandle_t q)
{
    queue = q;
}

// WRAPPER FREERTOS

void DHT22Sensor::taskWrapper(void *parameter)
{
    DHT22Sensor *instance = static_cast<DHT22Sensor *>(parameter);
    instance->run();
}

// TÂCHE DHT22

void DHT22Sensor::run()
{
    Mesure mesure;

    while (true)
    {
        // Lecture

        float temperature = dht.readTemperature();
        float humidite = dht.readHumidity();

        // Vérification

        if (!isnan(temperature) && !isnan(humidite))
        {
            mesure.type = MESURE_DHT22;
            mesure.distance = 0;
            mesure.temperature = temperature;
            mesure.humidite = humidite;

            // MÊME QUEUE QUE LE HC-SR04

            if (xQueueSend(queue, &mesure, 0) != pdPASS) // Pas d'attente ici
            {
                Serial.println( "Queue pleine : DHT22");
            }
        }

        vTaskDelay( pdMS_TO_TICKS(2000));
    }
}


// CRÉATION DE LA TÂCHE

void DHT22Sensor::start()
{
    xTaskCreate(
        taskWrapper,
        "DHT22",
        2048,
        this,
        1,
        &handle
    );
}
