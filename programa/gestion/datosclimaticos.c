#include "datosclimaticos.h"
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../cJSON/cJSON.c"

Clima *climas = NULL;
int tamanoClimas = 0;


/**
 * Este metodo agrega la fecha guardada en el csv en un objeto JSON
 * 
 * @param fecha La fecha guardada en el csv.
 * @param hora La hora guardada en el csv.
 * @returns Un objeto JSON con las fecha.
*/
cJSON *AgregarFecha(char *fecha, char *hora){
    cJSON *fechaJSON = cJSON_CreateObject();
    cJSON_AddNumberToObject(fechaJSON, "anio", atoi(strtok(fecha, "-")));
    cJSON_AddNumberToObject(fechaJSON, "mes", atoi(strtok(NULL, "-")));
    cJSON_AddNumberToObject(fechaJSON, "dia", atoi(strtok(NULL, "-")));
    cJSON_AddNumberToObject(fechaJSON, "hora", atoi(strtok(hora, ":")));
    cJSON_AddNumberToObject(fechaJSON, "minuto", atoi(strtok(NULL, ":")));
    return fechaJSON;
}

/**
 * Hace un split a un char* utilizando las comas como separadores.
 * 
 * @param linea La linea que tiene la infomación del lote.
*/
char **SplitLotes(char *linea){
    int cantidad = 1;
    int tamano = strlen(linea);
    for(int indice = 0; indice < tamano; indice++){
        if(linea[indice] == ','){
            cantidad++;
        }
    }
    char **arreglo = malloc(cantidad * sizeof(char *));
    int indiceArreglo = 1;
    bool hayComa = false;
    arreglo[0] = linea;
    for(int indice = 0; indice < tamano; indice++){
        if(hayComa){
            if(*(linea + indice) == ','){
                arreglo[indiceArreglo] = NULL;
            }
            else{
                arreglo[indiceArreglo] = linea + indice;
                hayComa = false;
            }
            indiceArreglo++;
        }
        if(*(linea + indice) == ',' || *(linea + indice) == '\n'){
            *(linea + indice) = '\0';
            hayComa = true;
        }
    }
    return arreglo;
}

/**
 * Inserta un valor al item JSON.
 * 
 * @param item El item JSON en el que se guarda la información.
 * @param tipoDato El tipo de dato que se insertará en el JSON.
 * @param llave El nombre de la llave.
 * @param valor El valor que se guardará en el item.
*/
void InsertarElementoEnJSON(cJSON *item, char tipoDato, char *llave, char *valor){
    if (valor == NULL){
        cJSON_AddNullToObject(item, llave);
    }
    else if(tipoDato == 's'){
        cJSON_AddStringToObject(item, llave, valor);
    }
    else{
        cJSON_AddNumberToObject(item, llave, atof(valor));
    }
}

/**
 * Este metodo convierte una linea del csv en un objeto JSON.
 * 
 * @param linea La linea del csv.
 * @returns El objeto JSON con la informacion de lote.
*/
cJSON *AgregarElemento(char* linea){
    cJSON *clima = cJSON_CreateObject();
    char **splitLinea = SplitLotes(linea);
    cJSON_AddNumberToObject(clima, "ID", idActual);
    InsertarElementoEnJSON(clima, 's', "region", splitLinea[0]);
    cJSON_AddItemToObject(clima, "fechaHora", AgregarFecha(splitLinea[1], splitLinea[2]));
    InsertarElementoEnJSON(clima, 'i', "temperatura", splitLinea[3]);
    InsertarElementoEnJSON(clima, 'i', "humedad", splitLinea[4]);
    InsertarElementoEnJSON(clima, 'i', "presion", splitLinea[5]);
    InsertarElementoEnJSON(clima, 'i', "velocidadViento", splitLinea[6]);
    InsertarElementoEnJSON(clima, 's', "direccionViento", splitLinea[7]);
    InsertarElementoEnJSON(clima, 'i', "precipitacion", splitLinea[8]);
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
void CargarHaciaJSON(cJSON *json){
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
    fecha.tm_year = cJSON_GetNumberValue(anio) - 1900;
    fecha.tm_mon = cJSON_GetNumberValue(mes) - 1;
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

char* ToString(Clima* clima){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    char aux[10];
    strcat(texto,"ID: ");
    sprintf(aux,"%d",clima->ID);
    strcat(texto,aux);
    strcat(texto,"\nRegion: ");
    strcat(texto,clima->Region);
    strcat(texto,"\nTiempo: ");
    strftime(aux,sizeof(aux),"%c", localtime(clima->Tiempo));
    strcat(texto,aux);
    strcat(texto,"\nTemperatura: ");
    sprintf(aux,"%.2f",clima->Temperatura);
    strcat(texto,aux);
    strcat(texto,"\nHumedad: ");
    sprintf(aux,"%.2f",clima->Humedad);
    strcat(texto,aux);
    strcat(texto,"\nPresion: ");
    sprintf(aux,"%.2f",clima->Presion);
    strcat(texto,aux);
    strcat(texto,"\nVelocidad del Viento: ");
    sprintf(aux,"%d",clima->VelocidadViento);
    strcat(texto,aux);
    strcat(texto,"\nDireccion del Viento: ");
    strcat(texto,clima->DireccionViento);
    strcat(texto,"\nPrecipitacion: ");
    sprintf(aux,"%d",clima->Precipitacion);
    strcat(texto,aux);
    strcat(texto,"\n ~+~\n\n");
    return texto;
}