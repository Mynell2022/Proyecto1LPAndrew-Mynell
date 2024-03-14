#include "../cJSON/cJSON.h"

#ifndef PROCESAMIENTODATOS_H
#define PROCESAMIENTODATOS_H

int* CompletarDatosFaltantes();

float ObtenerMediaTemperatura();
float ObtenerMediaHumedad();
float ObtenerMediaPresionAtmosferica();
float ObtenerMediaVelocidadViento();
float ObtenerMediaPrecipitacion();

int ReemplazarTemperaturaFaltante(cJSON* JSON);
int ReemplazarHumedadFaltante(cJSON* JSON);
int ReemplazarPresionFaltante(cJSON* JSON);
int ReemplazarVelocidadVientoFaltante(cJSON* JSON);
int ReemplazarPrecipitacionFaltante(cJSON* JSON);

int EliminarDatosDuplicados();

int EliminarValoresAtipicos();
int EliminarTemperaturaAtipica();
int EliminarHumedadAtipica();
int EliminarPresionAtipica();
int EliminarVelocidadVientoAtipica();
int EliminarPrecipitacionAtipica();

#endif