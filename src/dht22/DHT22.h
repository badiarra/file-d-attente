#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include "mesures/Mesure.h"

class DHT22Sensor
{
private:

    DHT dht;

    QueueHandle_t queue = nullptr;
    TaskHandle_t taskHandle = nullptr;

    static void taskWrapper(void *parameter);

    void run();

public:

    DHT22Sensor(int pin);

    void init();

    void setQueue(QueueHandle_t q);

    void start();
};

#endif
