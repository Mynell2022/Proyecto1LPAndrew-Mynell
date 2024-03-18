#include "../structs/region.h"
#include "../structs/clima.h"
#include "../gestion/gestionregiones.h"
#include "../gestion/datosclimaticos.h"
#include "../structs/datosvisualizador.h"

#ifndef VISUALIZACIONDATOS_H
#define VISUALIZACIONDATOS_H

DatosVisualizador VisualizarDatos(float posicionX, float posicionY);
DatosVisualizador ArmarDatosVisualizador(float *datosTemperatura, float *datosHumedad, float *datosPresion, float *datosVelocidadViento, float *datosPrecipitacion);
Region BuscarRegionCercana(float posicionX, float posicionY);
Clima *BuscarClimasRegion(char *nombre);
float *CalcularRango(float *datos);
float CalcularVarianza(float *datos);
float CalcularSumatoria(float *datos, int cantidad, int media);
float CalcularMedia(float *datos, int cantidad);
int ContarTamanoDatos(Clima *datosClimas);
float *ObtenerDatosTemperatura(Clima *datosClima, int tamano);
float *ObtenerDatosHumedad(Clima *datosClima, int tamano);
float *ObtenerDatosPresion(Clima *datosClima, int tamano);
float *ObtenerDatosVelocidadViento(Clima *datosClima, int tamano);
float *ObtenerDatosPrecipitacion(Clima *datosClima, int tamano);
int ContarArreglo(float *arreglo);
void IntercambiarNumeros(float *a, float *b);
void OrdenarArregloFlotante(float *arreglo);

#endif