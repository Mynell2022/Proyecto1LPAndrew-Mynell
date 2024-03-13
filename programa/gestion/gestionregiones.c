#include "../gestion/gestionregiones.h"
#include "../structs/region.h"

/**
 * Esta funcion agrega una nueva region al programa.
 * 
 * @param nombre El nombre dela region.
 * @param coordX La coordenada X de la region.
 * @param coordY La coordenada Y de la region.
 * @param descripcion La descripcion de la region.
*/
int CrearRegion(char* nombre, float coordX, float coordY, char* descripcion){
    Region region = {nombre, coordX, coordY, descripcion};
    if(!VerificarExistenciaRegion(&region)){
        ActualizarJSONRegiones(&region);
        regiones[tamanoRegion] = region;
        tamanoRegion++;
        return 1;
    }
    return 0;
}

/**
 * Verifica que una region exista.
 * 
 * @param region La region que se quiere verificar.
*/
int VerificarExistenciaRegion(Region *region){
    for(int i=0;i<tamanoRegion;i++){
        if (strcmp(regiones[i].nombre, region->nombre) == 0
            && (regiones[i].x==region->x
            && regiones[i].y==region->y))
            return 1;
    }return 0;
}

/**
 * Elimina una region.
 * 
 * @param nombre El nombre de la region a eliminar.
*/
int EliminarRegion(char* nombre){
    cJSON *json = ExtraerJSONRegiones();
    int tamano = cJSON_GetArraySize(json);
    for(int indice = 0; indice < tamano; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        cJSON *nombreObjeto = cJSON_GetObjectItem(item, "nombre");
        char *nombreGuardado = cJSON_GetStringValue(nombreObjeto);
        if(strcmp(nombreGuardado, nombre)){
            cJSON_DeleteItemFromArray(json, indice);
            GuardarJSONRegion(json);
            CargarRegiones();
            return 1;
        }
    }
    return 0;
    }

/**
 * Muestra todas las regiones.
 * 
 * @returns Todas las regiones guardadas.
*/
char* MostrarRegiones(){
    if(tamanoRegion == 0){
        return "\nNo hay regiones que mostrar\n\n";
    }
    char* datos= (char*)malloc(tamanoRegion*100*sizeof(char));
    datos[0]='\0';
    char aux[6];
    for(int i=0;i<tamanoRegion;i++){
        strcat(datos,"Nombre: ");
        strcat(datos,regiones[i].nombre);
        strcat(datos,"\nCoordenadas: (");
        sprintf(aux,"%.2f",regiones[i].x);
        strcat(datos,aux);
        strcat(datos,",");
        sprintf(aux,"%.2f",regiones[i].y);
        strcat(datos,aux);
        strcat(datos,")\nDescripcion:\n");
        strcat(datos,regiones[i].descripcion);
        strcat(datos,"\n ~+~\n\n");
    }return datos;
}

/**
 * Guarda el JSON de las regiones.
 * 
 * @param json El JSON que contiene a las regiones.
*/
void GuardarJSONRegion(cJSON *json){
    FILE *file = fopen("./gestion/regiones.json", "w");
    char *stringJSON = cJSON_Print(json);
    fprintf(file, "%s\n", stringJSON);
    fclose(file);
    free(stringJSON);
    cJSON_Delete(json);
}

/**
 * Actualiza las regiones que contiene el JSON.
 * 
 * @param region La region que se insertara al JSON
*/
void ActualizarJSONRegiones(Region* region){
    cJSON *arregloJSON = ExtraerJSONRegiones();
    cJSON *nuevoJSON = cJSON_CreateObject();
    cJSON_AddItemToObject(nuevoJSON, "nombre", cJSON_CreateString(region->nombre));
    cJSON_AddItemToObject(nuevoJSON, "descripcion", cJSON_CreateString(region->descripcion));
    cJSON_AddItemToObject(nuevoJSON, "x", cJSON_CreateNumber(region->x));
    cJSON_AddItemToObject(nuevoJSON, "y", cJSON_CreateNumber(region->y));
    cJSON_AddItemToArray(arregloJSON, nuevoJSON);
    GuardarJSONRegion(arregloJSON);
}

/**
 * Extrae el arreglo de regiones que se encuentra en el JSON.
*/
cJSON* ExtraerJSONRegiones(){
    FILE *file = fopen("./gestion/regiones.json", "r");
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
 * Carga todos las regiones que fueron guaradas en el JSON
*/
void CargarRegiones(){
    cJSON *json = ExtraerJSONRegiones();
    int tamano = cJSON_GetArraySize(json);
    regiones = malloc((tamano + 1000) * sizeof(Region));
    tamanoRegion = 0;
    for(int indice = 0; indice < tamano; indice++){
        cJSON *item = cJSON_GetArrayItem(json, indice);
        char *nombre = cJSON_GetStringValue(cJSON_GetObjectItem(item, "nombre"));
        char *descripcion = cJSON_GetStringValue(cJSON_GetObjectItem(item, "descripcion"));
        regiones[indice].nombre = malloc(100 * sizeof(char));
        regiones[indice].descripcion = malloc(100 * sizeof(char));
        strcpy(regiones[indice].nombre, nombre);
        strcpy(regiones[indice].descripcion, descripcion);
        regiones[indice].x = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "x"));
        regiones[indice].y = cJSON_GetNumberValue(cJSON_GetObjectItem(item, "y"));
        tamanoRegion++;
    }
    cJSON_Delete(json);
}