#include <time.h>

typedef struct{
    int ID;
    char* Region;
    time_t Tiempo;
    float Temperatura,Humedad,Presion;
    int VelocidadViento;
    char* DireccionViento;
    int Precipitacion;
}Clima;
