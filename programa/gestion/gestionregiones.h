#include "region.h"
#include <cjson/cJSON.h>

Region regiones[1000];

int CrearRegion(char* nombre, float coordX, float coordY, char* descripcion);
int VerificarExistenciaRegion(Region region);
int EliminarRegion(char* nombre);
char* MostrarRegiones();
void ActualizarJSONRegiones(Region* regiones);
cJSON* ExtraerJSONRegiones();