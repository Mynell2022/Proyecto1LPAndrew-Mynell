#include "busquedadatos.h"
#include <string.h>
#include "../gestion/datosclimaticos.h"

char* BuscarPorRegion(char* region){
    char* texto= (char*)malloc(tamanoClimas*100*sizeof(char));
    texto[0]='\0';
    char aux[10];
    if(tamanoClimas == 0){
        return "\nNo hay datos que mostrar\n\n";
    }
    for (int i = 0; i < tamanoClimas; i++) {
        if(strcmp(climas[i].Region,region)==1){
            strcat(texto,"ID: ");
            sprintf(aux,"%d",climas[i].ID);
            strcat(texto,aux);
            strcat(texto,"\nRegion: ");
            strcat(texto,climas[i].Region);
            strcat(texto,"\nTiempo: ");
            strftime(aux,sizeof(aux),"%c", localtime(&climas->Tiempo));
            strcat(texto,aux);
            strcat(texto,"\nTemperatura: ");
            sprintf(aux,"%.2f",climas[i].Temperatura);
            strcat(texto,aux);
            strcat(texto,"\nHumedad: ");
            sprintf(aux,"%.2f",climas[i].Humedad);
            strcat(texto,aux);
            strcat(texto,"\nPresion: ");
            sprintf(aux,"%.2f",climas[i].Presion);
            strcat(texto,aux);
            strcat(texto,"\nVelocidad del Viento: ");
            sprintf(aux,"%d",climas[i].VelocidadViento);
            strcat(texto,aux);
            strcat(texto,"\nDireccion del Viento: ");
            strcat(texto,climas[i].DireccionViento);
            strcat(texto,"\nPrecipitacion: ");
            sprintf(aux,"%d",climas[i].Precipitacion);
            strcat(texto,aux);
            strcat(texto,"\n ~+~\n\n");
        }
    }return texto;
}