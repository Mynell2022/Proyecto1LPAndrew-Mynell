#include <time.h>
#include "../structs/region.h"

#ifndef ANALISISCORRELACION_H
#define ANALISISCORRELACION_H

float AnalizarCorrelacion(char *region, char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos);

float AnalizarCorrelacionConRegion(char *region, char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos);
float AnalizarCorrelacionSinRegion(char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos);

float ElevarDiferencia(float* datos, float media, int tamano);
float MultiplicarDiferencias(float* datosUno, float* datosDos, float mediaUno, float mediaDos, int tamano);
float CalcularMediaAnalisis(float* datos);

float RealizarCalculos(float *datosUno, float *datosDos);

float *ExtraerTemperaturaSinRegion(time_t fechaUno, time_t fechaDos);
float *ExtraerHumedadSinRegion(time_t fechaUno, time_t fechaDos);
float *ExtraerPresionSinRegion(time_t fechaUno, time_t fechaDos);
float *ExtraerVelocidadVientoSinRegion(time_t fechaUno, time_t fechaDos);
float *ExtraerPrecipitacionSinRegion(time_t fechaUno, time_t fechaDos);

float *ExtraerTemperaturaConRegion(char *region, time_t fechaUno, time_t fechaDos);
float *ExtraerHumedadConRegion(char *region, time_t fechaUno, time_t fechaDos);
float *ExtraerPresionConRegion(char *region, time_t fechaUno, time_t fechaDos);
float *ExtraerVelocidadVientoConRegion(char *region, time_t fechaUno, time_t fechaDos);
float *ExtraerPrecipitacionConRegion(char *region, time_t fechaUno, time_t fechaDos);

#endif