#include "../structs/region.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

#ifndef GESTIONREGIONES_H
#define GESTIONREGIONES_H

Region *regiones = NULL;
int tamanoRegion = 0;

int CrearRegion(char* nombre, float coordX, float coordY, char* descripcion);
int VerificarExistenciaRegion(Region *region);
int EliminarRegion(char* nombre);
char* MostrarRegiones();
void GuardarJSONRegion(cJSON *json);
void ActualizarJSONRegiones(Region* region);
cJSON* ExtraerJSONRegiones();
void CargarRegiones();

#endif