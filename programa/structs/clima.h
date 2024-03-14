#include <time.h>

#ifndef CLIMA_H
#define CLIMA_H

typedef struct{
    int ID;
    char* Region;
    time_t Tiempo;
    float Temperatura,Humedad,Presion,
    Precipitacion,VelocidadViento;
    char* DireccionViento;
}Clima;
#endif