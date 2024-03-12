#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../gestion/gestionregiones.h"
#include "../gestion/gestionregiones.c"
#include "../gestion/datosclimaticos.h"
#include "../gestion/datosclimaticos.c"

/**
 * Esta funcion limpia el buffer después de una lectura.
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
 * Esta función lee numeros enteros desde el teclado.
 * 
 * @returns El número ingresado desde el teclado, en caso de falla devuelve -1.
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
 * Esta función lee la cadena de caracteres ingresados desde el teclado.
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
 * Solicita la información para enviar a realizar el análisis de correlación
*/
void SolicitarDatosAnalisisCorrelacion(){
    printf("Ingrese la región: ");
    char *region = LeerString();
    printf("Ingrese el dato uno a analizar: ");
    char *datoUno = LeerString();
    printf("Ingrese el dato dos a analizar: ");
    char *datoDos = LeerString();
    printf("Ingrese el día de la fecha inicial: ");
    int diaInicial = LeerEntero();
    if(diaInicial < 1 || diaInicial > 31){
        printf("\nEl día de la fecha debe estar entre 1 y 31\n\n");
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
    printf("Ingrese el día de la fecha final: ");
    int diaFinal = LeerEntero();
    if(diaFinal < 1 || diaFinal > 31){
        printf("\nEl día de la fecha debe estar entre 1 y 31\n\n");
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
 * Este método ejecuta el menú para enviar a hacer un análisis de datos.
*/
void EjecutarMenuAnalisisDatos(){
    printf("Ingrese la región: ");
    char *region = LeerString();
    printf("Ingrese el día de la fecha inicial: ");
    int diaInicial = LeerEntero();
    if(diaInicial < 1 || diaInicial > 31){
        printf("\nEl día de la fecha debe estar entre 1 y 31\n\n");
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
    printf("Ingrese el día de la fecha final: ");
    int diaFinal = LeerEntero();
    if(diaFinal < 1 || diaFinal > 31){
        printf("\nEl día de la fecha debe estar entre 1 y 31\n\n");
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
 * Imprime el menú de procesamiento de datos.
*/
void ImprimirMenuProcesamientoDatos(){
    printf("****Menu procesamiento de datos****\n\t1. Completar datos faltantes");
    printf("\n\t2. Eliminar datos duplicados\n\t3. Eliminar valores atípicos");
    printf("\nEscriba una opcion");
}

/**
 * Ejecuta el menú de procesamiento de datos.
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
        printf("\n***Opción incorrecta***\n\n");
        break;
    }
}

/**
 * Esta función solicita la url del archivo csv y envia a cargar los datos.
*/
void EjecutarMenuGestionClima(){
    printf("Ingrese la url del archivo: ");
    char *url = LeerString();
    printf("\n%s\n\n", IncluirLote(url));
}

/**
 * Imprime el menú que se encarga de gestión de regiones.
*/
void ImprimirMenuGestionRegion(){
    printf("\n****Menu Gestión de Regiones****\n\t1. Crear región\n\t2. Eliminar región\n\t3. Mostrar regiones\nElija una opción: ");
}

/**
 * Solicita los datos que se utilizan para crear la región.
*/
void SolicitarDatosRegion(){
    printf("\n****Creando region****\nIngrese el nombre de la region: ");
    char *nombre = LeerString();
    if (strlen(nombre) == 0){
        printf("\n***No se permiten nombres en blanco***\n\n");
        return;
    }
    printf("Ingrese la descripcion de la región: ");
    char *descripcion = LeerString();
    if (strlen(descripcion) == 0){
        printf("\n***No se permiten nombres en blanco***\n\n");
        return;
    }
    printf("Ingrese la coordenada X de la región: ");
    float x = LeerFlotante();
    if(x == -1){
        printf("\n***El número no es válido***\n\n");
        return;
    }
    printf("Ingrese la coordenada y de la región: ");
    float y = LeerFlotante();
    if(y == -1){
        printf("\n***El número no es válido***\n\n");
        return;
    }
    int resultado = CrearRegion(nombre, x, y, descripcion);
    if(resultado){
        printf("\nSe ha agregado la región\n\n");
    }
    else{
        printf("\nLa región ya existe.\nEl nombre o las coordenadas están repetidas.\n\n");
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
        printf("\nSe ha eliminado la región.\n\n");
    }
    else{
        printf("\nNo se encontró la región\n\n");
    }
}

/**
 * Ejecuta el menú que se encarga de gestión de regiones.
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
        printf("%s", "\n***Opción incorrecta***\n\n");
        break;
    }
}

/**
 * Esta función imprime las opciones del menú principal.
*/
void ImprimirMenuPrincipal(){
    printf("*****Menú Principal*****\n\t1. Gestión de regiones\n\t2. Gestión de datos climáticos\n\t3. Procesamiento de datos");
    printf("\n\t4. Análisis de datos\n\t5. Análisis de correlación\n\t6. Visualización de datos\n\t7. Búsqueda de datos");
    printf("\n\t8. Estadísticas\n\t9. Salir\nEscriba una opción: ");
}

/**
 * Ejecuta el menú principal de la aplicacion.
*/
void EjecutarMenuPrincipal(){
    CargarRegiones();
    CargarDatosClimatológicos();
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
            printf("\n**Opción incorrecta. Intente de nuevo**\n\n");
            break;
        }
    } while (!salir);
}