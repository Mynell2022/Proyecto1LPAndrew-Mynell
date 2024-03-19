#include "analisisdatos.h"

/// @brief Metodo que analiza datos y los almacena en una lista
/// @param region Region de referencia para el analisis
/// @param fechaInicio fecha de inicio del rango de fechas aceptable
/// @param fechaFin fecha final del rango de fechas aceptable
/// @param dato Tipo de dato que se va a guardar
/// @param index Tamano de la lista
/// @return Lista con los datos acumulados
float* AnalizarDatos(char* region, time_t fechaInicio, time_t fechaFin, int dato, int* index){
    float* valores= (float*)malloc(tamanoClimas*sizeof(float));
    for (int i = 0; i < tamanoClimas; i++) {
        time_t tiempo= climas[i].Tiempo;
        if (tiempo >= fechaInicio && tiempo <= fechaFin &&
            ((strcmp(region, "ALL") != 0 && strcmp(climas[i].Region, region) == 0) || (strcmp(region, "ALL") == 0))) {
            switch (dato) {
                case 0:
                    if(!isnan(climas[i].Temperatura))valores[(*index)++] = climas[i].Temperatura;
                    break;
                case 1:
                    if(!isnan(climas[i].Humedad))valores[(*index)++] = climas[i].Humedad;
                    break;
                case 2:
                    if(!isnan(climas[i].Presion))valores[(*index)++] = climas[i].Presion;
                    break;
                case 3:
                    if(!isnan(climas[i].VelocidadViento))valores[(*index)++] = climas[i].VelocidadViento;
                    break;
                case 4:
                    if(!isnan(climas[i].Precipitacion))valores[(*index)++] = climas[i].Precipitacion;
                    break;
            }
        }
    }
    return valores;
}

/// @brief Metodo que analiza datos y da la media de un conjunto de datos
/// @param datos Datos a analizar
/// @param tam tamano de la lista
/// @return La media generada
float ObtenerMedia(float* datos,int tam){
    float suma = 0;
    for (int i = 0; i < tam; i++)
        suma += datos[i];
    return suma / tam;
}

/// @brief Metodo que analiza datos y da la Desviacion estandar de un conjunto de datos
/// @param datos Datos a analizar
/// @param tam tamano de la lista
/// @return La desviacion generada
float ObtenerDesviacionEstandar(float* datos,int tam){
    float media= ObtenerMedia(datos,tam),varianza=0;
    for (int i = 0; i < tam; i++)
        varianza += pow(datos[i] - media, 2);
    return sqrt(varianza/tam);
}

/// @brief Comparador auxiliar para el qsort, muestra quien es mayor
/// @param a Un dato de la lista
/// @param b Un dato de la lista
/// @return Un numero entre 1 y -1
int comparar(const void *a, const void *b) {
    return (int)(*(float *)a - *(float *)b);
}

/// @brief Metodo que analiza datos y da la moda de un conjunto de datos
/// @param datos Datos a analizar
/// @param tam tamano de la lista
/// @return La moda generada
float ObtenerModa(float* datos,int tam){
    int maxFrecuencia=0,moda=-1,actual=0,valor=datos[0];
    qsort(datos,tam,sizeof(float),comparar);
    for(int i=0;i<tam;i++){
        if(datos[i]==valor)
            actual++;
        else{
            if(actual>maxFrecuencia){
                maxFrecuencia=actual;
                moda=valor;
            }actual=1;
            valor=datos[i];
        }
    }if(actual>maxFrecuencia){
        moda=valor;
    }return moda;
}

/// @brief Metodo que analiza datos y da la mediana de un conjunto de datos
/// @param datos Datos a analizar
/// @param tam tamano de la lista
/// @return La mediana generada
float ObtenerMediana(float* datos,int tam){
    qsort(datos, tam, sizeof(int), comparar);
    if (tam % 2 == 0) {
        return (datos[tam / 2 - 1] + datos[tam / 2]) / 2.0;
    } else {
        return datos[tam / 2];
    }
}