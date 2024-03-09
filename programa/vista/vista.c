#include <stdio.h>
#include <stdlib.h>

/**
 * Esta funcion limpia el buffer después de una lectura.
*/
void LimpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    int resultado = scanf("%[^\n]%c");
    if(resultado < 0){
        return NULL;
    }
    return entrada;
}

void SolicitarDatosAnalisisCorrelacion(){
    printf("Ingrese la región: ");
    char *region = LeerString();
    
}

void ImprimirMenuProcesamientoDatos(){
    printf("****Menu procesamiento de datos****\n\t1. Completar datos faltantes");
    printf("\n\t2. Eliminar datos duplicados\n\t3. Eliminar valores atípicos");
    printf("\nEscriba una opcion");
}

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
}

/**
 * Imprime el menú que se encarga de gestión de regiones.
*/
void ImprimirMenuGestionRegion(){
    printf("\n****Menu Gestión de Regiones****\n\t1. Crear región\n\t2. Eliminar región\n\t3. Mostrar regiones\nElija una opción: ");
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