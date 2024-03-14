#include "../structs/clima.h"
#include "../cJSON/cJSON.h"

#ifndef DATOSCLIMATICOS_H
#define DATOSCLIMATICOS_H
extern Clima *climas;
extern int tamanoClimas;
int idActual = 0;

cJSON *AgregarFecha(char *fecha, char *hora);
cJSON *AgregarElemento(char* linea);
char *IncluirLote(char* url);
cJSON *ExtraerDatosClimatologicosJSON();
void CargarHaciaJSON(cJSON *json);
void CargarDatosClimatologicos();
time_t TransformarFecha(cJSON *fechaHora);
void ExtraerDatosArregloJSON(cJSON *item, int indice);
void CargarDatosClimatologicos();
char* ToString(Clima*);

#endif