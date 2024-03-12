#include "./datosclimaticos.h"
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Este metodo agrega la fecha guardada en el csv en un objeto JSON
 * 
 * @param fecha La fecha guardada en el csv.
 * @param hora La hora guardada en el csv.
 * @returns Un objeto JSON con las fecha.
*/
cJSON *AgregarFecha(char *fecha, char *hora){
    cJSON *fechaJSON = cJSON_CreateObject();
    cJSON_AddStringToObject(fechaJSON, "anio", strtok(fecha, "-"));
    cJSON_AddStringToObject(fechaJSON, "mes", strtok(NULL, "-"));
    cJSON_AddStringToObject(fechaJSON, "dia", strtok(NULL, "-"));
    cJSON_AddStringToObject(fechaJSON, "hora", strtok(hora, ":"));
    cJSON_AddStringToObject(fechaJSON, "minuto", strtok(NULL, ":"));
    return fechaJSON;
}

/**
 * Este metodo convierte una linea del csv en un objeto JSON.
 * 
 * @param linea La linea del csv.
 * @returns El objeto JSON con la informacion de lote.
*/
cJSON *AgregarElemento(char* linea){
    cJSON *clima = cJSON_CreateObject();
    cJSON_AddNumberToObject(clima, "ID", idActual);
    cJSON_AddStringToObject(clima, "region", strtok(linea, ","));
    char *fecha = strtok(NULL, ",");
    char *hora = strtok(NULL, ",");
    cJSON_AddStringToObject(clima, "temperatura", strtok(NULL, ","));
    cJSON_AddStringToObject(clima, "humedad", strtok(NULL, ","));
    cJSON_AddStringToObject(clima, "presion", strtok(NULL, ","));
    cJSON_AddStringToObject(clima, "velocidadViento", strtok(NULL, ","));
    cJSON_AddStringToObject(clima, "direccionViento", strtok(NULL, ","));
    cJSON_AddStringToObject(clima, "precipitacion", strtok(NULL, "\n"));
    cJSON_AddItemToObject(clima, "fechaHora", AgregarFecha(fecha, hora));
    return clima;
}

/**
 * Este metodo incluye un lote segun el url proporcionado por el usuario.
 * 
 * @param url La direccion del archivo csv. Lo ideal es que se encuentre en
 * misma carpata del programa.
 * @returns Devuelve la cantidad de elementos agregados. Devuelve un mensaje
 * de error si el archivo no existe.
*/
char *IncluirLote(char *url){
    cJSON *arregloJSON = ExtraerDatosClimatologicosJSON();
    FILE *fp;
    int MAXCHAR = 1000;
    char row[MAXCHAR];
    char *token;
    fp = fopen(url,"r");
    if(fp == NULL){
        fclose(fp);
        return "\nEl archivo no existe\n\n";
    }
    int datosIngresados = 0;
    while (fgets(row, MAXCHAR, fp) != NULL){
        cJSON_AddItemToArray(arregloJSON, AgregarElemento(row));
        datosIngresados++;
        idActual++;
    }
    CargarHaciaJSON(arregloJSON);
    CargarDatosClimatologicos();
    char *mensaje = malloc(70 * sizeof(char));
    strcat(mensaje, "Lotes agregados: ");
    char buffer[20];
    sprintf(buffer, "%d", datosIngresados);
    strcat(mensaje, buffer);
    fclose(fp);
    return mensaje;
}

/**
 * Extrae el JSON que se encuentra almacenado en el archivo datosclimatologicos.json
 * 
 * @returns El objeto JSON extraido.
*/
cJSON *ExtraerDatosClimatologicosJSON(){
    FILE *file = fopen("./gestion/datosclimatologicos.json", "r");
    if (file == NULL){
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file) + 500;
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(fileSize * sizeof(char));
    fread(buffer, sizeof(char), fileSize, file); 
    fclose(file);
    cJSON *datos = cJSON_Parse(buffer);
    free(buffer);
    return datos;
}

/**
 * Guarda un objeto JSON en la carpeta datosclimatologicos.json
 * 
 * @param json El objeto JSON a guardar.
*/
void  CargarHaciaJSON(cJSON *json){
    FILE *file = fopen("./gestion/datosclimatologicos.json", "w");
    char *stringJSON = cJSON_Print(json);
    fprintf(file, "%s\n", stringJSON);
    fclose(file);
    free(stringJSON);
    cJSON_Delete(json);
}

/**
 * Transforma la fecha guardada en el archivo JSON en un time_t.
 * 
 * @param fechaHora El item que contiene la fecha y hora del lote.
 * @returns La fecha y hora en forma time_h
*/
time_t TransformarFecha(cJSON *fechaHora){
    cJSON *anio = cJSON_GetObjectItem(fechaHora, "anio");
    cJSON *mes = cJSON_GetObjectItem(fechaHora, "mes");
    cJSON *dia = cJSON_GetObjectItem(fechaHora, "dia");
    cJSON *hora = cJSON_GetObjectItem(fechaHora, "hora");
    cJSON *minuto = cJSON_GetObjectItem(fechaHora, "minuto");
    struct tm fecha = {0};
    fecha.tm_year = cJSON_GetNumberValue(anio);
    fecha.tm_mon = cJSON_GetNumberValue(mes);
    fecha.tm_mday =cJSON_GetNumberValue(dia);
    fecha.tm_hour = cJSON_GetNumberValue(hora);
    fecha.tm_min = cJSON_GetNumberValue(minuto);
    return mktime(&fecha);
}

/**
 * Extrae los datos del lote del item del lote.
 * 
 * @param item El objeto JSON que contiene la informacion del lote.
 * @param indice El indice del arreglo de climas en el que se debe guardar el lote actual.
*/
void ExtraerDatosArregloJSON(cJSON *item, int indice){
    climas[indice].ID = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "ID"));
    climas[indice].Region = malloc(100 * sizeof(char));
    char *nombre = cJSON_GetStringValue(cJSON_GetObjectItem(item, "region"));
    strcpy(climas[indice].Region, nombre);
    climas[indice].Tiempo = TransformarFecha(cJSON_GetObjectItem(item, "fechaHora"));
    climas[indice].Temperatura = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "temperatura"));
    climas[indice].Humedad = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "humedad"));
    climas[indice].Presion = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "presion"));
    climas[indice].VelocidadViento = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "velocidadViento"));
    climas[indice].DireccionViento = cJSON_GetStringValue(cJSON_GetObjectItem(item, "direccionViento"));
    climas[indice].Precipitacion = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "precipitacion"));
}

/**
 * Este metodo carga los datos climatologicos guardados en el archivo JSON
 * hacia la memoria del programa.
*/
void CargarDatosClimatologicos(){
    cJSON *arregloJSON = ExtraerDatosClimatologicosJSON();
    int tamano = cJSON_GetArraySize(arregloJSON);
    climas = malloc((tamano + 1000) * sizeof(Clima));
    tamanoClimas = 0;
    for(int indice = 0; indice < tamano; indice++){
        cJSON *item = cJSON_GetArrayItem(arregloJSON, indice);
        ExtraerDatosArregloJSON(item, indice);
        tamanoClimas++;
    }
    idActual = climas[tamanoClimas - 1].ID + 1;
    cJSON_Delete(arregloJSON);
}