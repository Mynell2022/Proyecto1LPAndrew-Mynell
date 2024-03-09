#include <time.h>
#include <cjson/cJSON.h>

char* AnalizarDatos(char* region, time_t fechaInicio, time_t fechaFin, char* dato);
cJSON ObtenerDatosJSON();
char* VerMedia();
char* VerDesviacionEstandar();
char* VerModa();
char* VerMediana();