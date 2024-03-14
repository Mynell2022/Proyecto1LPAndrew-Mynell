#include "busquedadatos.h"
#include <string.h>
#include <math.h>
#include "../gestion/gestionregiones.h"
#include "../gestion/datosclimaticos.h"

char* BuscarPorRegionExacta(char* region){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].Region,region)==1){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorRegionAprox(char* region){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    int mejorIndice=0;
    float mejorDistancia=__FLT_MAX__,distancia;
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        Region region1= ObtenerRegion(climas[i].Region), region2= ObtenerRegion(region);
        if(region1.nombre!=NULL&&region2.nombre!=NULL){
            distancia= sqrt(((region1.x-region2.x)*(region1.x-region2.x))+((region1.y-region2.y)*(region1.y-region2.y)));
            if(distancia<mejorDistancia){
                mejorDistancia=distancia;
                mejorIndice=i;
            }
        }
    }strcat(texto,ToString(&climas[mejorIndice]));
    return texto;
}

char* BuscarPorTemperaturaExacta(float temperatura){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Temperatura==temperatura){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorTemperaturaAprox(float temperatura){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Temperatura-temperatura);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }strcat(texto,ToString(&climas[mejorIndice]));
    return texto;
}

char* BuscarPorDireccionVientoExacta(char* dViento){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].DireccionViento,dViento)){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorDireccionVientoAprox(char* dViento){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(strpbrk(climas[i].DireccionViento,dViento)!=NULL){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorPresionExacta(float presion){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Presion==presion){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorPresionAprox(float presion){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Presion-presion);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }strcat(texto,ToString(&climas[mejorIndice]));
    return texto;
}

char* BuscarPorPrecipitacionExacta(float precipitacion){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Precipitacion==precipitacion){
            strcat(texto,ToString(&climas[i]));
        }
    }return texto;
}

char* BuscarPorPrecipitacionAprox(float precipitacion){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    int mejorIndice=0;
    float mejorCerca=__FLT_MAX__,cerca;
    if(tamanoClimas == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < tamanoClimas; i++) {
        cerca= fabs(climas[i].Precipitacion-precipitacion);
        if(cerca<mejorCerca){
            mejorCerca=cerca;
            mejorIndice=i;
        }
    }strcat(texto,ToString(&climas[mejorIndice]));
    return texto;
}
