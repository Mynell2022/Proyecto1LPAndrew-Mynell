#include <time.h>

#ifndef CLIMA_H
#define CLIMA_H

typedef struct{
    int ID;
    char* Region;
    time_t Tiempo;
    float Temperatura,Humedad,Presion;
    float VelocidadViento;
    char* DireccionViento;
    float Precipitacion;
}Clima;
#endif