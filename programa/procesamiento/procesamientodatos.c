#include "procesamientodatos.h"
#include "../gestion/datosclimaticos.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Esta es la función inicial que completa los datos faltantes.
 * 
 * @return Las cantidades de datos que fueron cambiados.
*/
int* CompletarDatosFaltantes(){
    cJSON *json = ExtraerDatosClimatologicosJSON();
    int temperaturaFaltante = ReemplazarTemperaturaFaltante(json);
    int humedadFaltante = ReemplazarHumedadFaltante(json);
    int presionFaltante = ReemplazarPresionFaltante(json);
    int velocidadVientoFaltante = ReemplazarVelocidadVientoFaltante(json);
    int precipitacionFaltante = ReemplazarPrecipitacionFaltante(json);
    CargarHaciaJSON(json);
    CargarDatosClimatologicos();
    int *datos = malloc(5 * sizeof(int));
    datos[0] = temperaturaFaltante;
    datos[1] = humedadFaltante;
    datos[2] = presionFaltante;
    datos[3] = velocidadVientoFaltante;
    datos[4] = precipitacionFaltante;
    return datos;
}

/**
 * Esta función cambia el valor de las llaves temperatura de null al de la media.
 * 
 * @param JSON El objeto JSON que contiene los datos.
*/
int ReemplazarTemperaturaFaltante(cJSON* JSON){
    int tamanoJSON = cJSON_GetArraySize(JSON);
    float media = ObtenerMediaHumedad();
    int cambiados = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *lote = cJSON_GetArrayItem(JSON, indice);
        cJSON *item = cJSON_GetObjectItem(lote, "temperatura");
        float numero = cJSON_GetNumberValue(item);
        if(isnan(numero)){
            cJSON_DeleteItemFromObject(lote, "temperatura");
            cambiados++;
            cJSON_AddNumberToObject(lote, "temperatura", media);
        }
    }
    return cambiados;
}

/**
 * Esta función cambia el valor de las llaves humedad de null al de la media.
 * 
 * @param JSON El objeto JSON que contiene los datos.
*/
int ReemplazarHumedadFaltante(cJSON* JSON){
    int tamanoJSON = cJSON_GetArraySize(JSON);
    float media = ObtenerMediaHumedad();
    int cambiados = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *lote = cJSON_GetArrayItem(JSON, indice);
        cJSON *item = cJSON_GetObjectItem(lote, "humedad");
        float numero = cJSON_GetNumberValue(item);
        if(isnan(numero)){
            cJSON_DeleteItemFromObject(lote, "humedad");
            cambiados++;
            cJSON_AddNumberToObject(lote, "humedad", media);
        }
    }
    return cambiados;
}

/**
 * Esta función cambia el valor de las llaves presion de null al de la media.
 * 
 * @param JSON El objeto JSON que contiene los datos.
*/
int ReemplazarPresionFaltante(cJSON* JSON){
    int tamanoJSON = cJSON_GetArraySize(JSON);
    float media = ObtenerMediaHumedad();
    int cambiados = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *lote = cJSON_GetArrayItem(JSON, indice);
        cJSON *item = cJSON_GetObjectItem(lote, "presion");
        float numero = cJSON_GetNumberValue(item);
        if(isnan(numero)){
            cJSON_DeleteItemFromObject(lote, "presion");
            cambiados++;
            cJSON_AddNumberToObject(lote, "presion", media);
        }
    }
    return cambiados;
}

/**
 * Esta función cambia el valor de las llaves velocidadViento de null al de la media.
 * 
 * @param JSON El objeto JSON que contiene los datos.
*/
int ReemplazarVelocidadVientoFaltante(cJSON* JSON){
    int tamanoJSON = cJSON_GetArraySize(JSON);
    float media = ObtenerMediaHumedad();
    int cambiados = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *lote = cJSON_GetArrayItem(JSON, indice);
        cJSON *item = cJSON_GetObjectItem(lote, "velocidadViento");
        float numero = cJSON_GetNumberValue(item);
        if(isnan(numero)){
            cJSON_DeleteItemFromObject(lote, "velocidadViento");
            cambiados++;
            cJSON_AddNumberToObject(lote, "velocidadViento", media);
        }
    }
    return cambiados;
}

/**
 * Esta función cambia el valor de las llaves precipitación de null al de la media.
 * 
 * @param JSON El objeto JSON que contiene los datos.
*/
int ReemplazarPrecipitacionFaltante(cJSON* JSON){
    int tamanoJSON = cJSON_GetArraySize(JSON);
    float media = ObtenerMediaHumedad();
    int cambiados = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *lote = cJSON_GetArrayItem(JSON, indice);
        cJSON *item = cJSON_GetObjectItem(lote, "precipitacion");
        float numero = cJSON_GetNumberValue(item);
        if(isnan(numero)){
            cJSON_DeleteItemFromObject(lote, "precipitacion");
            cambiados++;
            cJSON_AddNumberToObject(lote, "precipitacion", media);
        }
    }
    return cambiados;
}

/**
 * Esta función obtiene la media de todos los valores válidos de temperatura.
 * 
 * @returns La media de la temperatura
*/
float ObtenerMediaTemperatura(){
    float media = 0;
    int cantidadNumeros = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        if(!isnan(climas[indice].Temperatura)){
            media += climas[indice].Temperatura;
            cantidadNumeros++;
        }
    }
    return media / cantidadNumeros;
}

/**
 * Esta función obtiene la media de todos los valores válidos de humedad.
 * 
 * @returns La media de la humedad
*/
float ObtenerMediaHumedad(){
    float media = 0;
    int cantidadNumeros = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        float humedad = climas[indice].Humedad;
        if(!isnan(climas[indice].Humedad)){
            media += climas[indice].Humedad;
            cantidadNumeros++;
        }
    }
    return media / cantidadNumeros;
}

/**
 * Esta función obtiene la media de todos los valores válidos de presion.
 * 
 * @returns La media de la presion
*/
float ObtenerMediaPresionAtmosferica(){
    float media = 0;
    int cantidadNumeros = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        if(!isnan(climas[indice].Presion)){
            media += climas[indice].Presion;
            cantidadNumeros++;
        }
    }
    return media / cantidadNumeros;
}

/**
 * Esta función obtiene la media de todos los valores válidos de velocidadViento.
 * 
 * @returns La media de la velocidad del viento
*/
float ObtenerMediaVelocidadViento(){
    float media = 0;
    int cantidadNumeros = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        if(!isnan(climas[indice].VelocidadViento)){
            media += climas[indice].VelocidadViento;
            cantidadNumeros++;
        }
    }
    return media / cantidadNumeros;
}

/**
 * Esta función obtiene la media de todos los valores válidos de precipitacion.
 * 
 * @returns La media de la precipitacion
*/
float ObtenerMediaPrecipitacion(){
    float media = 0;
    int cantidadNumeros = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        if(!isnan(climas[indice].Precipitacion)){
            media += climas[indice].Precipitacion;
            cantidadNumeros++;
        }
    }
    return media / cantidadNumeros;
}

/**
 * Verifica si un lote ya ha sido agregado a al arreglo de lotes duplicados.
 * 
 * @param clima El lote que se desea verificar.
 * @param idsRepetidos El arreglo de lotes duplicados.
 * @param lotesRepetidos La cantidad de lotes repetidos.
 * 
 * @return True si lote se encuentra de los datos duplicados.
 * False si el lote no se encuentra de los datos duplicados.
*/
bool VerificarSiEsDuplicado(Clima clima, int *idsRepetidos, int lotesRepetidos){
    for(int indice = 0; indice < lotesRepetidos; indice++){
        if(clima.ID == idsRepetidos[indice]){
            return true;
        }
    }
    return false;
}

/**
 * Compara dos lotes para saber si son iguales y guardarlo dentro de los lotes duplicados.
 * 
 * @param lote El lote que se desea comparar.
 * @param idsRepetidos Los ids de los lotes duplicados.
 * @param lotesRepetidos La cantidad de lotes duplicados.
 * @return La cantidad de datos duplicados.
*/
int BuscarDuplicados(Clima lote, int *idsRepetidos, int lotesRepetidos){
    int duplicados = 0;
    for(int indice = 0; indice < tamanoClimas; indice++){
        Clima loteGuardado = climas[indice];
        if(lote.ID != loteGuardado.ID
            && strcmp(lote.Region, loteGuardado.Region) == 0
            && lote.Tiempo == loteGuardado.Tiempo
            && (lote.Humedad == loteGuardado.Humedad || (isnan(lote.Humedad) && isnan(loteGuardado.Humedad)))
            && (lote.Temperatura == loteGuardado.Temperatura || (isnan(lote.Temperatura) && isnan(loteGuardado.Temperatura)))
            && (lote.Presion == loteGuardado.Presion  || (isnan(lote.Presion) && isnan(loteGuardado.Presion)))
            && (lote.VelocidadViento == loteGuardado.VelocidadViento || (isnan(lote.VelocidadViento) && isnan(loteGuardado.VelocidadViento)))
            && (lote.Precipitacion == loteGuardado.Precipitacion || (isnan(lote.Precipitacion) && isnan(loteGuardado.Precipitacion)))
            && strcmp(lote.DireccionViento, loteGuardado.DireccionViento) == 0){

            idsRepetidos[lotesRepetidos + duplicados] = loteGuardado.ID;
            duplicados++;
        }
    }
    return duplicados;
}

/**
 * Se elimina los lotes duplicados del archivo JSON.
 * 
 * @param lotesAEliminar Los ids de los lotes a eliminar.
 * @param lotesRepetidos La cantidad de lotes duplicados.
*/
void EliminarRepetidosJSON(int *lotesAEliminar, int lotesRepetidos){
    cJSON *json = ExtraerDatosClimatologicosJSON();
    for(int indice = 0; indice < lotesRepetidos; indice++){
        int tamanoJSON = cJSON_GetArraySize(json);
        for(int indiceJSON = 0; indiceJSON < tamanoJSON; indiceJSON++){
            cJSON *item = cJSON_GetArrayItem(json, indiceJSON);
            cJSON *idJSON = cJSON_GetObjectItem(item, "ID");
            int id = cJSON_GetNumberValue(idJSON);
            if(id == lotesAEliminar[indice]){
                cJSON_DeleteItemFromArray(json, indiceJSON);
                break;
            }
        }
    }
    CargarHaciaJSON(json);
}

/**
 * Controlador para eliminar los datos duplicados.
*/
int EliminarDatosDuplicados(){
    int *lotesAEliminar = malloc(tamanoClimas * sizeof(int));
    int lotesRepetidos = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        if(!VerificarSiEsDuplicado(climas[indice], lotesAEliminar, lotesRepetidos)){
            lotesRepetidos += BuscarDuplicados(climas[indice], lotesAEliminar, lotesRepetidos);
        }
    }
    EliminarRepetidosJSON(lotesAEliminar, lotesRepetidos);
    return lotesRepetidos;
}