#include <cjson/cJSON.h>

int CompletarDatosFaltantes();

float ObtenerMediaTemperatura(cJSON* JSON);
float ObtenerMediaHumedad(cJSON* JSON);
float ObtenerModaPresionAtmosferica(cJSON* JSON);
float ObtenerModaVelocidadViento(cJSON* JSON);
float ObtenerMedianaPrecipitacion(cJSON* JSON);

int ReemplazarTemperaturaFaltante(cJSON* JSON);
int ReemplazarHumedadFaltante(cJSON* JSON);
int ReemplazarPresionFaltante(cJSON* JSON);
int ReemplazarVelocidadVientoFaltante(cJSON* JSON);
int ReemplazarPrecipitacionFaltante(cJSON* JSON);

cJSON ObtenerDatosJSON();
int GuardarDatosJSON(cJSON* JSON);

int EliminarDatosDuplicados();
int EliminarValoresAtipicos();
int EliminarTemperaturaAtipica();
int EliminarHumedadAtipica();
int EliminarPresionAtipica();
int EliminarVelocidadVientoAtipica();
int EliminarPrecipitacionAtipica();
