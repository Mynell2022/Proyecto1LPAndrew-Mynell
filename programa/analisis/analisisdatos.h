#include "../gestion/datosclimaticos.h"
#include <time.h>

float* AnalizarDatos(char*, time_t, time_t, int);
float ObtenerMedia(float*,int);
float ObtenerDesviacionEstandar(float*,int);
float ObtenerModa(float*,int);
float ObtenerMediana(float*,int);