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

int *EliminarDatosDuplicados();

int EliminarValoresAtipicos();
int EliminarTemperaturaAtipica(cJSON *json);
int EliminarHumedadAtipica(cJSON *json);
int EliminarPresionAtipica(cJSON *json);
int EliminarVelocidadVientoAtipica(cJSON *json);
int EliminarPrecipitacionAtipica(cJSON *json);

#endif