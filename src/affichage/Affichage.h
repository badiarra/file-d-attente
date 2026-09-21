#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <Arduino.h>

#include "mesures/Mesure.h"
#include "led/Led.h"

class Affichage
{
private:

    Led &ledVerte;
    Led &ledRouge;

    QueueHandle_t queue = nullptr; //Pas besoin de le mettre dans le constructeur
    TaskHandle_t taskHandle = nullptr;

    static void taskWrapper(void *parameter);

    void run();

public:

    Affichage(
        Led &verte,
        Led &rouge
    );


    void setQueue(
        QueueHandle_t q
    );


    void start();
};

#endif
