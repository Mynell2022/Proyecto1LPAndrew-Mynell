#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../gestion/gestionregiones.h"
#include "../gestion/gestionregiones.c"
#include "../gestion/datosclimaticos.h"
#include "../gestion/datosclimaticos.c"

/**
 * Esta funcion limpia el buffer despues de una lectura.
*/
void LimpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

float LeerFlotante(){
    float entrada;
    int resultado = scanf("%f", &entrada);
    LimpiarBuffer();
    if(resultado < 0){
        return -1.0;
    }
    return entrada;
}

/**
 * Esta funcion lee numeros enteros desde el teclado.
 * 
 * @returns El numero ingresado desde el teclado, en caso de falla devuelve -1.
*/
int LeerEntero(){
    int entrada;
    int resultado = scanf("%d", &entrada);
    LimpiarBuffer();
    if (resultado < 0){
        return -1;
    }
    return entrada;
}

/**
 * Esta funcion lee la cadena de caracteres ingresados desde el teclado.
 * 
 * @returns La cadena de caracteres ingresado desde el teclado, si hay un error devuelve null.
*/
char *LeerString(){
    char *entrada = malloc(200 * sizeof(char));
    int resultado = scanf("%[^\n]%*c", entrada);
    if(resultado < 0){
        return NULL;
    }
    return entrada;
}

/**
 * Solicita la informacion para enviar a realizar el analisis de correlacion
*/
void SolicitarDatosAnalisisCorrelacion(){
    printf("Ingrese la region: ");
    char *region = LeerString();
    printf("Ingrese el dato uno a analizar: ");
    char *datoUno = LeerString();
    printf("Ingrese el dato dos a analizar: ");
    char *datoDos = LeerString();
    printf("Ingrese el dia de la fecha inicial: ");
    int diaInicial = LeerEntero();
    if(diaInicial < 1 || diaInicial > 31){
        printf("\nEl dia de la fecha debe estar entre 1 y 31\n\n");
        return;
    }
    printf("Ingrese el mes de la fecha inicial: ");
    int mesInicial = LeerEntero();
    if(mesInicial < 1 || mesInicial > 12){
        printf("\nEl mes de la fecha debe estar entre 1 y 12");
        return;
    }
    printf("Ingrese el año de la fecha inicial: ");
    int anioInicial = LeerEntero();
    if(anioInicial < 1900 || anioInicial > 3000){
        printf("\nEl  año inicial debe estar entre 1900 y 3000");
        return;
    }
    printf("Ingrese el dia de la fecha final: ");
    int diaFinal = LeerEntero();
    if(diaFinal < 1 || diaFinal > 31){
        printf("\nEl dia de la fecha debe estar entre 1 y 31\n\n");
        return;
    }
    printf("Ingrese el mes de la fecha final: ");
    int mesFinal = LeerEntero();
    if(mesFinal < 1 || mesFinal > 12){
        printf("\nEl mes de la fecha debe estar entre 1 y 12");
        return;
    }
    printf("Ingrese el año de la fecha final: ");
    int anioFinal = LeerEntero();
    if(anioFinal < 1900 || anioFinal > 3000){
        printf("\nEl  año inicial debe estar entre 1900 y 3000");
        return;
    }
    struct tm fechaInicial = {0};
    fechaInicial.tm_year = anioInicial;
    fechaInicial.tm_mon = mesInicial;
    fechaInicial.tm_mday = diaInicial;
    struct tm fechaFinal = {0};
    fechaFinal.tm_year = anioFinal;
    fechaFinal.tm_mon = mesFinal;
    fechaFinal.tm_mday = diaFinal;

}

/**
 * Este metodo ejecuta el menu para enviar a hacer un analisis de datos.
*/
void EjecutarMenuAnalisisDatos(){
    printf("Ingrese la region: ");
    char *region = LeerString();
    printf("Ingrese el dia de la fecha inicial: ");
    int diaInicial = LeerEntero();
    if(diaInicial < 1 || diaInicial > 31){
        printf("\nEl dia de la fecha debe estar entre 1 y 31\n\n");
        return;
    }
    printf("Ingrese el mes de la fecha inicial: ");
    int mesInicial = LeerEntero();
    if(mesInicial < 1 || mesInicial > 12){
        printf("\nEl mes de la fecha debe estar entre 1 y 12");
        return;
    }
    printf("Ingrese el año de la fecha inicial: ");
    int anioInicial = LeerEntero();
    if(anioInicial < 1900 || anioInicial > 3000){
        printf("\nEl  año inicial debe estar entre 1900 y 3000");
        return;
    }
    printf("Ingrese el dia de la fecha final: ");
    int diaFinal = LeerEntero();
    if(diaFinal < 1 || diaFinal > 31){
        printf("\nEl dia de la fecha debe estar entre 1 y 31\n\n");
        return;
    }
    printf("Ingrese el mes de la fecha final: ");
    int mesFinal = LeerEntero();
    if(mesFinal < 1 || mesFinal > 12){
        printf("\nEl mes de la fecha debe estar entre 1 y 12");
        return;
    }
    printf("Ingrese el año de la fecha final: ");
    int anioFinal = LeerEntero();
    if(anioFinal < 1900 || anioFinal > 3000){
        printf("\nEl  año inicial debe estar entre 1900 y 3000");
        return;
    }
    struct tm fechaInicial = {0};
    fechaInicial.tm_year = anioInicial;
    fechaInicial.tm_mon = mesInicial;
    fechaInicial.tm_mday = diaInicial;
    struct tm fechaFinal = {0};
    fechaFinal.tm_year = anioFinal;
    fechaFinal.tm_mon = mesFinal;
    fechaFinal.tm_mday = diaFinal;
    printf("Ingrese el dato que desea analizar: ");
    char *dato = LeerString();
}

/**
 * Imprime el menu de procesamiento de datos.
*/
void ImprimirMenuProcesamientoDatos(){
    printf("****Menu procesamiento de datos****\n\t1. Completar datos faltantes");
    printf("\n\t2. Eliminar datos duplicados\n\t3. Eliminar valores atipicos");
    printf("\nEscriba una opcion");
}

/**
 * Ejecuta el menu de procesamiento de datos.
*/
void EjecutarMenuProcesamientoDatos(){
    ImprimirMenuProcesamientoDatos();
    int opcion = LeerEntero();
    switch (opcion)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        printf("\n***Opcion incorrecta***\n\n");
        break;
    }
}

/**
 * Esta funcion solicita la url del archivo csv y envia a cargar los datos.
*/
void EjecutarMenuGestionClima(){
    printf("Ingrese la url del archivo: ");
    char *url = LeerString();
    printf("\n%s\n\n", IncluirLote(url));
}

/**
 * Imprime el menu que se encarga de gestion de regiones.
*/
void ImprimirMenuGestionRegion(){
    printf("\n****Menu Gestion de Regiones****\n\t1. Crear region\n\t2. Eliminar region\n\t3. Mostrar regiones\nElija una opcion: ");
}

/**
 * Solicita los datos que se utilizan para crear la region.
*/
void SolicitarDatosRegion(){
    printf("\n****Creando region****\nIngrese el nombre de la region: ");
    char *nombre = LeerString();
    if (strlen(nombre) == 0){
        printf("\n***No se permiten nombres en blanco***\n\n");
        return;
    }
    printf("Ingrese la descripcion de la region: ");
    char *descripcion = LeerString();
    if (strlen(descripcion) == 0){
        printf("\n***No se permiten nombres en blanco***\n\n");
        return;
    }
    printf("Ingrese la coordenada X de la region: ");
    float x = LeerFlotante();
    if(x == -1){
        printf("\n***El numero no es valido***\n\n");
        return;
    }
    printf("Ingrese la coordenada y de la region: ");
    float y = LeerFlotante();
    if(y == -1){
        printf("\n***El numero no es valido***\n\n");
        return;
    }
    int resultado = CrearRegion(nombre, x, y, descripcion);
    if(resultado){
        printf("\nSe ha agregado la region\n\n");
    }
    else{
        printf("\nLa region ya existe.\nEl nombre o las coordenadas estan repetidas.\n\n");
    }
}

void SolicitarDatosEliminarRegion(){
    printf("\n****Eliminando region****\nIngrese el nombre de la region: ");
    char *nombre = LeerString();
    if (strlen(nombre) == 0){
        printf("\n***No se permiten nombres en blanco***\n\n");
        return;
    }
    int resultado = EliminarRegion(nombre);
    if(resultado){
        printf("\nSe ha eliminado la region.\n\n");
    }
    else{
        printf("\nNo se encontro la region\n\n");
    }
}

/**
 * Ejecuta el menu que se encarga de gestion de regiones.
*/
void EjecutarMenuGestionRegion(){
    ImprimirMenuGestionRegion();
    int entrada = LeerEntero();
    switch (entrada)
    {
    case 1:
        SolicitarDatosRegion();
        break;
    case 2:
        SolicitarDatosEliminarRegion();
        break;
    case 3:
        printf("%s", MostrarRegiones());
        break;
    default:
        printf("%s", "\n***Opcion incorrecta***\n\n");
        break;
    }
}

/**
 * Esta funcion imprime las opciones del menu principal.
*/
void ImprimirMenuPrincipal(){
    printf("*****Menu Principal*****\n\t1. Gestion de regiones\n\t2. Gestion de datos climaticos\n\t3. Procesamiento de datos");
    printf("\n\t4. Analisis de datos\n\t5. Analisis de correlacion\n\t6. Visualizacion de datos\n\t7. Busqueda de datos");
    printf("\n\t8. Estadisticas\n\t9. Salir\nEscriba una opcion: ");
}

/**
 * Ejecuta el menu principal de la aplicacion.
*/
void EjecutarMenuPrincipal(){
    CargarRegiones();
    CargarDatosClimatologicos();
    int salir = 0;
    do{
        ImprimirMenuPrincipal();
        int opcion = LeerEntero();
        switch (opcion){
        case 1:
            EjecutarMenuGestionRegion();
            break;
        case 2:
            EjecutarMenuGestionClima();
            break;
        case 3:
            EjecutarMenuProcesamientoDatos();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            salir = 1;
            break;
        default:
            printf("\n**Opcion incorrecta. Intente de nuevo**\n\n");
            break;
        }
    } while (!salir);
}