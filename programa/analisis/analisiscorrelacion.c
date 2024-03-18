#include "./analisiscorrelacion.h"
#include <string.h>
#include <math.h>
#include "../gestion/datosclimaticos.h"


float AnalizarCorrelacion(char *region, char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos){
    if(tamanoClimas == 0){
        return NAN;
    }
    if(strlen(region) == 0){
        return AnalizarCorrelacionSinRegion(datoUno, datoDos, fechaUno, fechaDos);
    }
    else{
        return AnalizarCorrelacionConRegion(region, datoUno, datoDos, fechaUno, fechaDos);
    }
}

float AnalizarCorrelacionSinRegion(char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos){
    float *datosUno = NULL;
    float *datosDos = NULL;
    if(strcmp(datoUno, "temperatura"))
        datosUno = ExtraerTemperaturaSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoUno, "humedad"))
        datosUno = ExtraerHumedadSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoUno, "presion"))
        datosUno = ExtraerPresionSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoUno, "velocidadViento"))
        datosUno = ExtraerVelocidadVientoSinRegion(fechaUno, fechaDos);
    else 
        datosUno = ExtraerPrecipitacionSinRegion(fechaUno, fechaDos);
    if(strcmp(datoDos, "temperatura"))
        datosDos = ExtraerTemperaturaSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoDos, "humedad"))
        datosDos = ExtraerHumedadSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoDos, "presion"))
        datosDos = ExtraerPresionSinRegion(fechaUno, fechaDos);
    else if(strcmp(datoDos, "velocidadViento"))
        datosDos = ExtraerVelocidadVientoSinRegion(fechaUno, fechaDos);
    else 
        datosDos = ExtraerPrecipitacionSinRegion(fechaUno, fechaDos);
    return RealizarCalculos(datosUno, datosDos);
}

float AnalizarCorrelacionConRegion(char *region, char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos){
    float *datosUno = NULL;
    float *datosDos = NULL;
    if(strcmp(datoUno, "temperatura"))
        datosUno = ExtraerTemperaturaConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoUno, "humedad"))
        datosUno = ExtraerHumedadConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoUno, "presion"))
        datosUno = ExtraerPresionConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoUno, "velocidadViento"))
        datosUno = ExtraerVelocidadVientoConRegion(region, fechaUno, fechaDos);
    else 
        datosUno = ExtraerPrecipitacionConRegion(region, fechaUno, fechaDos);
    if(strcmp(datoDos, "temperatura"))
        datosDos = ExtraerTemperaturaConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoDos, "humedad"))
        datosDos = ExtraerHumedadConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoDos, "presion"))
        datosDos = ExtraerPresionConRegion(region, fechaUno, fechaDos);
    else if(strcmp(datoDos, "velocidadViento"))
        datosDos = ExtraerVelocidadVientoConRegion(region, fechaUno, fechaDos);
    else 
        datosDos = ExtraerPrecipitacionConRegion(region, fechaUno, fechaDos);
    return RealizarCalculos(datosUno, datosDos);
}

int ContarDatosAnalisis(float *datos){
    int contador = 0;
    for(int indice = 0; !isnan(datos[indice]); indice++)
        contador++;
    return contador;
}

float RealizarCalculos(float *datosUno, float *datosDos){
    if(datosUno == NULL || datosDos == NULL){
        return NAN;
    }
    int longitudUno = ContarDatosAnalisis(datosUno);
    int longitudDos = ContarDatosAnalisis(datosDos);
    if(longitudUno == 0 || longitudDos == 0 || longitudUno != longitudDos){
        return NAN;
    }
    float mediaUno = CalcularMediaAnalisis(datosUno);
    float mediaDos = CalcularMediaAnalisis(datosDos);
    float numerador = MultiplicarDiferencias(datosUno, datosDos, mediaUno, mediaDos, longitudUno);
    float denominador = sqrt(ElevarDiferencia(datosUno, mediaUno, longitudUno)
        * ElevarDiferencia(datosDos, mediaDos, longitudDos));
    return numerador / denominador;

}


float ElevarDiferencia(float* datos, float media, int tamano){
    float sumatoria = 0;
    for(int indice = 0; indice < tamano; indice++){
        sumatoria += pow(datos[indice] - media, 2);
    }
    return sumatoria;
}

float MultiplicarDiferencias(float* datosUno, float* datosDos, float mediaUno, float mediaDos, int tamano){
    float sumatoria = 0;
    for(int indice = 0; indice < tamano; indice++){
        sumatoria += (datosUno[indice] - mediaUno) * (datosDos[indice] - mediaDos);
    }
    return sumatoria;
}

float CalcularMediaAnalisis(float* datos){
    int cantidad = ContarDatosAnalisis(datos);
    int sumatoria = 0;
    for(int indice = 0; indice < cantidad; indice++){
        sumatoria += datos[indice];
    }
    return sumatoria / cantidad;
}

float *ExtraerTemperaturaSinRegion(time_t fechaUno, time_t fechaDos){
    float *datos = malloc(tamanoClimas * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Temperatura;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerHumedadSinRegion(time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Humedad;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerPresionSinRegion(time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Presion;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerVelocidadVientoSinRegion(time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].VelocidadViento;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerPrecipitacionSinRegion(time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Precipitacion;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerTemperaturaConRegion(char *region, time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Temperatura;
        char *regionActual = climas[indice].Region;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)
            && strcmp(region, regionActual)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerHumedadConRegion(char *region, time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Humedad;
        char *regionActual = climas[indice].Region;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)
            && strcmp(region, regionActual)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerPresionConRegion(char *region, time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Presion;
        char *regionActual = climas[indice].Region;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)
            && strcmp(region, regionActual)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerVelocidadVientoConRegion(char *region, time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].VelocidadViento;
        char *regionActual = climas[indice].Region;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)
            && strcmp(region, regionActual)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}

float *ExtraerPrecipitacionConRegion(char *region, time_t fechaUno, time_t fechaDos){
    float *datos = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceDatos = 0;
    datos[0] = NAN;
    for(int indice = 0; indice < tamanoClimas; indice++){
        time_t tiempo = climas[indice].Tiempo;
        float dato = climas[indice].Precipitacion;
        char *regionActual = climas[indice].Region;
        if(tiempo >= fechaUno && tiempo <= fechaDos && !isnan(dato)
            && strcmp(region, regionActual)){
            datos[indiceDatos] = dato;
            indiceDatos++;
            datos[indiceDatos] = NAN;
        }
    }
    return datos;
}