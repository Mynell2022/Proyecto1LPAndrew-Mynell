#include "analisisdatos.h"

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
float ObtenerMedia(float* datos,int tam){
    float suma = 0;
    for (int i = 0; i < tam; i++)
        suma += datos[i];
    return suma / tam;
}
float ObtenerDesviacionEstandar(float* datos,int tam){
    float media= ObtenerMedia(datos,tam),varianza=0;
    for (int i = 0; i < tam; i++)
        varianza += pow(datos[i] - media, 2);
    return sqrt(varianza/tam);
}

int comparar(const void *a, const void *b) {
    return (int)(*(float *)a - *(float *)b);
}

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
float ObtenerMediana(float* datos,int tam){
    qsort(datos, tam, sizeof(int), comparar);
    if (tam % 2 == 0) {
        return (datos[tam / 2 - 1] + datos[tam / 2]) / 2.0;
    } else {
        return datos[tam / 2];
    }
}