#include "region.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cjson/cJSON.h>

Region regiones[1000];
int tamanoRegion=0;

int CrearRegion(char* nombre, float coordX, float coordY, char* descripcion){
    Region nuevaRegion= {nombre,coordX,coordY,descripcion};
    regiones[tamanoRegion++]= nuevaRegion;
}
int VerificarExistenciaRegion(Region region){
    for(int i=0;i<tamanoRegion;i++){
        if (regiones[i].nombre==region.nombre
            && regiones[i].x==region.x
            && regiones[i].y==region.y
            && strcmp(regiones[i].descripcion,region.descripcion))
            {return 1;}
    }return 0;
}
int EliminarRegion(char* nombre){
    int encontrado=0;
    for(int i=0;i<tamanoRegion;i++){
        if(regiones[i].nombre==nombre){encontrado=1;}
        if(encontrado){regiones[i]=regiones[i+1];}
    }return encontrado;
}
char* MostrarRegiones(){
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
        strcat(datos,"\n ~+~\n");
    }return datos;
}
void ActualizarJSONRegiones(Region* regiones);
//cJSON* ExtraerJSONRegiones();