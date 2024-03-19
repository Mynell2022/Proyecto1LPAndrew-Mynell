#include "../gestion/datosclimaticos.h"
#include <time.h>
#ifndef ANALISISDATOS_H
#define ANALISISDATOS_H

float* AnalizarDatos(char*, time_t, time_t, int,int*);
float ObtenerMedia(float*,int);
float ObtenerDesviacionEstandar(float*,int);
float ObtenerModa(float*,int);
float ObtenerMediana(float*,int);

#endif