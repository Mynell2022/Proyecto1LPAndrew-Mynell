#include "busquedadatos.h"
#include <string.h>
#include <math.h>
#include "../gestion/gestionregiones.h"
#include "../gestion/datosclimaticos.h"


/// @brief Transforma los datos recopilados en texto
/// @param lista Lista de datos con indices
/// @param index Tamano de la lista
/// @return Texto con datos
char* Buscar(int* lista, int* index){
    char* texto= (char*)malloc(tamanoClimas*500*sizeof(char));
    texto[0]='\0';
    if((*index) == 0){return "\nNo hay datos que mostrar\n\n";}
    for (int i = 0; i < (*index); i++) {
        if(lista[i]<tamanoClimas){
            char* aux= ToString(&climas[lista[i]]);
            strcat(texto,aux);
            free(aux);
        }
    }return texto;
}

/// @brief Busca los indices de la Regiones Exactamente iguales a la region
/// @param region Region a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorRegionExacta(char *region,int *lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].Region,region)==0){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices de la Regiones aproximadamente iguales a la region
/// @param region Region a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
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

/// @brief Busca los indices con la temperatura Exactamente igual a la temperatura a buscar
/// @param temperatura Temperatura a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorTemperaturaExacta(float temperatura,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Temperatura==temperatura){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices con la temperatura aproximadamente igual a la temperatura a buscar
/// @param temperatura Temperatura a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
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

/// @brief Busca los indices con la Direccion de Viento Exactamente igual a la Direccion de Viento a buscar
/// @param dViento Direccion de Viento a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorDireccionVientoExacta(char* dViento,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].DireccionViento,dViento)){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices con la Direccion de Viento aproximadamente igual a la Direccion de Viento a buscar
/// @param dViento Direccion de Viento a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorDireccionVientoAprox(char* dViento,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(strpbrk(climas[i].DireccionViento,dViento)!=NULL){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices con la presion Exactamente igual a la presion a buscar
/// @param presion presion a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorPresionExacta(float presion, int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Presion==presion){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices con la presion aproximadamente igual a la presion a buscar
/// @param presion presion a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
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

/// @brief Busca los indices con la precipitacion exactamente igual a la precipitacion a buscar
/// @param precipitacion precipitacion a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
void BuscarPorPrecipitacionExacta(float precipitacion,int* lista, int* index){
    for (int i = 0; i < tamanoClimas; i++) {
        if(climas[i].Precipitacion==precipitacion){
            lista[(*index)++]=i;
        }
    }
}

/// @brief Busca los indices con la precipitacion aproximadamente igual a la precipitacion a buscar
/// @param precipitacion precipitacion a Buscar
/// @param lista Lista de indices
/// @param index Tamano de lista
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

/// @brief Elimina los elemento del arreglo 1 que no tenga el arreglo 2
/// @param arreglo1 arreglo principal
/// @param arreglo1 arreglo secundario
/// @param longitud1 largo de arreglo principal
/// @param longitud2 largo de arreglo secundario
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

/// @brief Elimina los elementos duplicados de la lista
/// @param lista lista a tratar
/// @param largo Largo de la lista
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
