#include "busquedadatos.h"
#include <string.h>
#include <math.h>
#include "../gestion/gestionregiones.h"
#include "../gestion/datosclimaticos.h"

char* Buscar(int* lista, int* index){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if((*index) == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < (*index); i++) {
        strcat(texto,ToString(&climas[lista[i]]));
    }return texto;
}

void BuscarPorRegionExacta(char *region,int *lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].Region,region)==0){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorRegionAprox(char* region,int* lista, int* index){
    int mejorIndice=0;
    float mejorDistancia=__FLT_MAX__,distancia;
    for (int i = 0; i < tamanoClimas; i++) {
        Region region1= ObtenerRegion(climas[i].Region), region2= ObtenerRegion(region);
        if(region1.nombre!=NULL&&region2.nombre!=NULL){
            float distancia= sqrt(((region1.x-region2.x)*(region1.x-region2.x))+((region1.y-region2.y)*(region1.y-region2.y)));
            if(distancia<mejorDistancia){
                mejorDistancia=distancia;
                mejorIndice=i;
            }
        }
    }lista[(*index)++]=mejorIndice;
}

void BuscarPorTemperaturaExacta(float temperatura,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Temperatura==temperatura){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorTemperaturaAprox(float temperatura,int* lista, int* index){
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Temperatura-temperatura);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }lista[(*index)++]=mejorIndice;
}

void BuscarPorDireccionVientoExacta(char* dViento,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].DireccionViento,dViento)){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorDireccionVientoAprox(char* dViento,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strpbrk(climas[i].DireccionViento,dViento)!=NULL){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorPresionExacta(float presion, int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Presion==presion){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorPresionAprox(float presion,int* lista, int* index){
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Presion-presion);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }lista[(*index)++]=mejorIndice;
}

void BuscarPorPrecipitacionExacta(float precipitacion,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Precipitacion==precipitacion){
            lista[(*index)++]=i;
        }
    }
}

void BuscarPorPrecipitacionAprox(float precipitacion,int* lista, int* index){
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Precipitacion-precipitacion);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }lista[(*index)++]=mejorIndice;
}

int* ProcesarBusqueda(int* arreglo1,int* arreglo2, int* longitud1, int* longitud2) {
    int* arregloInterseccion = NULL;
    int longitudInterseccion = 0;
    for (int i = 0; i < *longitud1; i++) {
        int cond=1;
        for (int j = 0; j < *longitud2; j++) {
            if (arreglo1[i] == arreglo2[j]) {
                arregloInterseccion = (int*)realloc(arregloInterseccion, (longitudInterseccion) * sizeof(int));
                arregloInterseccion[(longitudInterseccion)++] = arreglo1[i];
                cond=0;
                break;
            }
        }if(cond){
            arregloInterseccion = (int*)realloc(arregloInterseccion, (longitudInterseccion) * sizeof(int));
            arregloInterseccion[(longitudInterseccion)] = arreglo1[i];
        }
    }(*longitud1)=longitudInterseccion;
    return arregloInterseccion;
}

int* EliminarBusquedasDuplicadas(int* lista, int largo){
    int* nuevo = (int*)malloc(largo * sizeof(int));
    int indice = 0;
    for (int i = 0; i < largo; i++) {
        int duplicado = 0;
        for (int j = 0; j < indice; j++) {
            if (lista[i] == nuevo[j]) {
                duplicado = 1;
                break;
            }
        }if (!duplicado) {
            nuevo[indice++] = lista[i];
        }
    }return realloc(nuevo, indice * sizeof(int));
}
