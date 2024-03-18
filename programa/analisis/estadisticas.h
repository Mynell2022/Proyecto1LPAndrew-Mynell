#include "../structs/clima.h"
#include "../gestion/datosclimaticos.h"

#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

int SortPrecipitacion(const void*, const void*);
int SortVelocidadViento(const void*, const void*);
void ObtenerMesAnio(const time_t,int*,int*);
void TopPrecipitacion(int);
void TopVelocidadViento(int);
void TopMesAnio(int);

#endif