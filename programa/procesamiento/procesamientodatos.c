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
    if(tamanoClimas == 0){
        return NULL;
    }
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

/**
 * Cuenta la cantidad de elementos de un arreglo de números flotantes.
 * 
 * @param arreglo El arreglo que se debe contar.
 * @return La cantidad de elementos.
*/
int ContarArregloFlotante(float *arreglo){
    int cantidad = 0;
    while(!isnan(arreglo[cantidad])){
        cantidad++;
    }
    return cantidad;
}

/**
 * Intercambia dos elementos de posición
 * 
 * @param a El primer elemento.
 * @param b El segundo elemento.
*/
void Intercambiar(float *a, float *b) {
    float temporal = *a;
    *a = *b;
    *b = temporal;
}

/**
 * Ordena el arreglo.
 * 
 * @param arreglo El arreglo a ordenar.
*/
void OrdenarArreglo(float *arreglo) {
    int longitud = ContarArregloFlotante(arreglo);
    for (int indice = 0; indice < longitud - 1; indice++) {
        for (int j = 0; j < longitud - indice - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                Intercambiar(&arreglo[j], &arreglo[j + 1]);
            }
        }
    }
    arreglo[longitud] = NAN;
}

/**
 * Crear un arreglo que contiene los datos de temperatura.
 * 
 * @return El arreglo de datos de temperatura.
*/
float *CrearArregloTemperatura(){
    int tamanoArreglo;
    float *arreglo = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceArreglo = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        float temperatura = climas[indice].Temperatura;
        if(!isnan(temperatura)){
            arreglo[indiceArreglo] = temperatura;
            indiceArreglo++;
            arreglo[indiceArreglo] = NAN;
        }
    }
    OrdenarArreglo(arreglo);
    return arreglo;
}

/**
 * Crear un arreglo que contiene los datos de humedad.
 * 
 * @return El arreglo de datos de humedad.
*/
float *CrearArregloHumedad(){
    int tamanoArreglo;
    float *arreglo = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceArreglo = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        float humedad = climas[indice].Humedad;
        if(!isnan(humedad)){
            arreglo[indiceArreglo] = humedad;
            indiceArreglo++;
            arreglo[indiceArreglo] = NAN;
        }
    }
    OrdenarArreglo(arreglo);
    return arreglo;
}

/**
 * Crear un arreglo que contiene los datos de presion.
 * 
 * @return El arreglo de datos de presion.
*/
float *CrearArregloPresion(){
    int tamanoArreglo;
    float *arreglo = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceArreglo = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        float presion = climas[indice].Presion;
        if(!isnan(presion)){
            arreglo[indiceArreglo] = presion;
            indiceArreglo++;
            arreglo[indiceArreglo] = NAN;
        }
    }
    OrdenarArreglo(arreglo);
    return arreglo;
}

/**
 * Crear un arreglo que contiene los datos de velocidad de viento.
 * 
 * @return El arreglo de datos de viento.
*/
float *CrearArregloVelocidadTiempo(){
    int tamanoArreglo;
    float *arreglo = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceArreglo = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        float velocidadViento = climas[indice].VelocidadViento;
        if(!isnan(velocidadViento)){
            arreglo[indiceArreglo] = velocidadViento;
            arreglo[indiceArreglo + 1] = NAN;
            indiceArreglo++;
        }
    }
    OrdenarArreglo(arreglo);
    return arreglo;
}

/**
 * Crear un arreglo que contiene los datos de precipitacion.
 * 
 * @return El arreglo de datos de precipitacion.
*/
float *CrearArregloPrecipitacion(){
    int tamanoArreglo;
    float *arreglo = malloc((tamanoClimas + 1) * sizeof(float));
    int indiceArreglo = 0;
    for (int indice = 0; indice < tamanoClimas; indice++){
        float precipitacion = climas[indice].Precipitacion;
        if(!isnan(precipitacion)){
            arreglo[indiceArreglo] = precipitacion;
            indiceArreglo++;
            arreglo[indiceArreglo] = NAN;
        }
    }
    OrdenarArreglo(arreglo);
    return arreglo;
}

/**
 * Calcula el rango de los datos típicos.
 * 
 * @param arreglo El arreglo que se utilizará para los cálculos.
 * @return Un arreglo de longitud 2 con el rango.
*/
float *CalcularRangoAtípico(float *arreglo){
    int tamano = ContarArregloFlotante(arreglo);
    int indiceMediana = (tamano - 1) / 2;
    float mediana = (arreglo[indiceMediana] + arreglo[indiceMediana + 1]) / 2;
    int indiceQ1 = (tamano - 1) * 0.25;
    float q1 = (arreglo[indiceQ1] + arreglo[indiceQ1]) / 2;
    int indiceQ3 = (tamano - 1) * 0.75;
    float q3 = (arreglo[indiceQ3] + arreglo[indiceQ3 + 1]) / 2;
    float rangoIntercuartil = (q3 - q1) * 3;
    float *rangos = malloc(2 * sizeof(float));
    rangos[0] = q1 - rangoIntercuartil;
    rangos[1] = q3 + rangoIntercuartil;
    return rangos;
}

/**
 * Elimina los valores atípicos de la temperatura.
 * 
 * @param json El objeto JSON con los datos.
 * @return La cantidad de elementos eliminados.
*/
int EliminarTemperaturaAtipica(cJSON *json){
    float *arregloTemperatura = CrearArregloTemperatura();
    float *rangos = CalcularRangoAtípico(arregloTemperatura);
    int tamanoJSON =  cJSON_GetArraySize(json);
    int contador = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *temperaturaJSON = cJSON_GetObjectItem(item, "temperatura");
        float temperatura = cJSON_GetNumberValue(temperaturaJSON);
        if(!isnan(temperatura) && (temperatura < rangos[0] || temperatura > rangos[1])){
            cJSON_DetachItemFromObject(item, "temperatura");
            cJSON_AddNullToObject(item, "temperatura");
            contador++;
        }
    }
    return contador;
}

/**
 * Elimina los valores atípicos de la humedad.
 * 
 * @param json El objeto JSON con los datos.
 * @return La cantidad de elementos eliminados.
*/
int EliminarHumedadAtipica(cJSON *json){
    float *arregloHumedad = CrearArregloHumedad();
    float *rangos = CalcularRangoAtípico(arregloHumedad);
    int tamanoJSON =  cJSON_GetArraySize(json);
    int contador = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *humedadJSON = cJSON_GetObjectItem(item, "humedad");
        float humedad = cJSON_GetNumberValue(humedadJSON);
        if(!isnan(humedad) && (humedad < rangos[0] || humedad > rangos[1])){
            cJSON_DetachItemFromObject(item, "humedad");
            cJSON_AddNullToObject(item, "humedad");
            contador++;
        }
    }
    return contador;
}

/**
 * Elimina los valores atípicos de la presión atmosférica.
 * 
 * @param json El objeto JSON con los datos.
 * @return La cantidad de elementos eliminados.
*/
int EliminarPresionAtipica(cJSON *json){
    float *arregloPresion = CrearArregloPresion();
    float *rangos = CalcularRangoAtípico(arregloPresion);
    int tamanoJSON =  cJSON_GetArraySize(json);
    int contador = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *presionJSON = cJSON_GetObjectItem(item, "presion");
        float presion = cJSON_GetNumberValue(presionJSON);
        if(!isnan(presion) && (presion < rangos[0] || presion > rangos[1])){
            cJSON_DetachItemFromObject(item, "presion");
            cJSON_AddNullToObject(item, "presion");
            contador++;
        }
    }
    return contador;
}

/**
 * Elimina los valores atípicos de la velocidad del viento.
 * 
 * @param json El objeto JSON con los datos.
 * @return La cantidad de elementos eliminados.
*/
int EliminarVelocidadVientoAtipica(cJSON *json){
    float *arregloVelocidadViento = CrearArregloVelocidadTiempo();
    float *rangos = CalcularRangoAtípico(arregloVelocidadViento);
    int tamanoJSON = cJSON_GetArraySize(json);
    int contador = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *velocidadVientoJSON = cJSON_GetObjectItem(item, "velocidadViento");
        float velocidadViento = cJSON_GetNumberValue(velocidadVientoJSON);
        if(!isnan(velocidadViento) && (velocidadViento < rangos[0] || velocidadViento > rangos[1])){
            cJSON_DetachItemFromObject(item, "velocidadViento");
            cJSON_AddNullToObject(item, "velocidadViento");
            contador++;
        }
    }
    return contador;
}

/**
 * Elimina los valores atípicos de la precipitación.
 * 
 * @param json El objeto JSON con los datos.
 * @return La cantidad de elementos eliminados.
*/
int EliminarPrecipitacionAtipica(cJSON *json){
    float *arregloPrecipitacion = CrearArregloPrecipitacion();
    float *rangos = CalcularRangoAtípico(arregloPrecipitacion);
    int tamanoJSON =  cJSON_GetArraySize(json);
    int contador = 0;
    for(int indice = 0; indice < tamanoJSON; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *precipitacionJSON = cJSON_GetObjectItem(item, "precipitacion");
        float precipitacion = cJSON_GetNumberValue(precipitacionJSON);
        if(!isnan(precipitacion) && (precipitacion < rangos[0] || precipitacion > rangos[1])){
            cJSON_DetachItemFromObject(item, "precipitacion");
            cJSON_AddNullToObject(item, "precipitacion");
            contador++;
        }
    }
    return contador;
}

/**
 * Ejecuta todas las funciones para eliminar los valores atípicos.
 * 
 * @return Envía la cantidad de elementos eliminados por cada dato, si no hay datos, envía NULL.
*/
int *EliminarValoresAtipicos(){
    if(tamanoClimas != 0){
        cJSON *json = ExtraerDatosClimatologicosJSON();
        int *datos = malloc(5 * sizeof(int));
        datos[0] = EliminarTemperaturaAtipica(json);
        datos[1] = EliminarHumedadAtipica(json);
        datos[2] = EliminarPresionAtipica(json);
        datos[3] = EliminarVelocidadVientoAtipica(json);
        datos[4] = EliminarPrecipitacionAtipica(json);
        CargarHaciaJSON(json);
        CargarDatosClimatologicos();
        return datos;
    }
    return NULL;
}