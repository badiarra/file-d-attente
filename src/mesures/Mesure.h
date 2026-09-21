#ifndef MESURE_H
#define MESURE_H

#define MESURE_HCSR04  1
#define MESURE_DHT22   2

struct Mesure
{
    int type;

    float distance;

    float temperature;
    float humidite;
};

#endif
