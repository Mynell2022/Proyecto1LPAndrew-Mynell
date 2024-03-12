#include "../structs/clima.h"
#include "../cJSON/cJSON.h"

#ifndef DATOSCLIMATICOS_H
#define DATOSCLIMATICOS_H
Clima *climas = NULL;
int tamanoClimas = 0;
int idActual = 0;

cJSON *AgregarFecha(char *fecha, char *hora);
cJSON *AgregarElemento(char* linea);
char *IncluirLote(char* url);
cJSON *ExtraerDatosClimatologicosJSON();
void CargarHaciaJSON(cJSON *json);
void CargarDatosClimatológicos();
time_t TransformarFecha(cJSON *fechaHora);
void ExtraerDatosArregloJSON(cJSON *item, int indice);
void CargarDatosClimatológicos();

#endif