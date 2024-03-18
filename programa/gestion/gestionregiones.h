#include "../structs/region.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

#ifndef GESTIONREGIONES_H
#define GESTIONREGIONES_H

#include "../cJSON/cJSON.h"

Region *regiones = NULL;
int tamanoRegion = 0;

int CrearRegion(char* nombre, float coordX, float coordY, char* descripcion);
int VerificarExistenciaRegion(Region *region);
Region ObtenerRegion(char* nombre);
int EliminarRegion(char* nombre);
char* MostrarRegiones();
void GuardarJSONRegion(cJSON *json);
void ActualizarJSONRegiones(Region* region);
cJSON* ExtraerJSONRegiones();
void CargarRegiones();

#endif