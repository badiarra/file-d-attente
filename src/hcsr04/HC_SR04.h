#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>
#include "mesures/Mesure.h"

class HC_SR04
{
private:

    int trigPin;
    int echoPin;

    QueueHandle_t queue = nullptr;
    TaskHandle_t taskHandle = nullptr;

    static void taskWrapper(void *parameter);

    void run();

public:

    HC_SR04(int trig, int echo);

    void init();

    void setQueue(QueueHandle_t q);

    void start();
};

#endif
