#include "../structs/region.h"
#include "../structs/clima.h"
#include <stdbool.h>

char* Buscar(int*,int*);
void BuscarPorRegionExacta(char*,int*,int*);
void BuscarPorRegionAprox(char*,int*,int*);
void BuscarPorTemperaturaExacta(float,int*,int*);
void BuscarPorTemperaturaAprox(float,int*,int*);
void BuscarPorDireccionVientoExacta(char*,int*,int*);
void BuscarPorDireccionVientoAprox(char*,int*,int*);
void BuscarPorPresionExacta(float,int*,int*);
void BuscarPorPresionAprox(float,int*,int*);
void BuscarPorPrecipitacionExacta(float,int*,int*);
void BuscarPorPrecipitacionAprox(float,int*,int*);
int* ProcesarBusqueda(int*,int*,int*,int*);
int* EliminarBusquedasDuplicadas(int*, int);