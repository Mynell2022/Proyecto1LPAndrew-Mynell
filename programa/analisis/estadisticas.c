#include "estadisticas.h"

/// @brief Compara la precipitacion de dos climas y decide cual es menor o mayor
/// @param a Primer clima
/// @param fechaDos Segundo clima
/// @return Numero entre 1 y -1
int SortPrecipitacion(const void *a, const void *b) {
    const Clima *pa = (const Clima *)a;
    const Clima *pb = (const Clima *)b;
    return (pb->Precipitacion - pa->Precipitacion);
}

/// @brief Compara la Velocidad del Viento de dos climas y decide cual es menor o mayor
/// @param a Primer clima
/// @param fechaDos Segundo clima
/// @return Numero entre 1 y -1
int SortVelocidadViento(const void *a, const void *b) {
    const Clima *pa = (const Clima *)a;
    const Clima *pb = (const Clima *)b;
    return (pb->VelocidadViento - pa->VelocidadViento);
}

/// @brief Obtiene el mes y anio de un tiempo
/// @param tiempo Tiempo a extraer datos
/// @param mes variable donde guardar mes
/// @param anio variable donde guardar anio
void ObtenerMesAnio(const time_t tiempo, int *mes, int *anio) {
    struct tm fecha_desglosada = *localtime(&tiempo);
    *mes = fecha_desglosada.tm_mon + 1;
    *anio = fecha_desglosada.tm_year + 1900;
}

/* Muestra el Top de Zonas con mayor Precipitacion*/
void TopPrecipitacion(int n) {
    printf("Top %d de zonas con mayor precipitación:\n", n);
    qsort(climas, tamanoClimas, sizeof(Clima), SortPrecipitacion);
    for (int i = 0; i < n && i < tamanoClimas; i++) {
        printf("%d. Zona: %s, Precipitación: %.2f\n", i + 1, climas[i].Region, climas[i].Precipitacion);
    }
    printf("\n");
}

/* Muestra el Top de Zonas con mayor Velocidad de Viento*/
void TopVelocidadViento(int n) {
    printf("Top %d de registros con mayor velocidad del viento:\n", n);
    qsort(climas, tamanoClimas, sizeof(Clima), SortVelocidadViento);
    for (int i = 0; i < n && i < tamanoClimas; i++) {
        printf("%d. Fecha: %s, Velocidad del viento: %.2f\n", i + 1, ctime(&climas[i].Tiempo), climas[i].VelocidadViento);
    }printf("\n");
}

/* Muestra el Top de Fechas con mas cantidad de registros*/
void TopMesAnio(int n) {
    printf("Top %d de mes-año con mayor cantidad de registros:\n", n);
    int registros_por_mes_y_anio[13][3000] = {0};
    for (int i = 0; i < tamanoClimas; i++) {
        int mes, anio;
        ObtenerMesAnio(climas[i].Tiempo, &mes, &anio);
        registros_por_mes_y_anio[climas[i].Tiempo][anio]++;
    }for (int i = 0; i < n; i++) {
        int max_registros = 0,mes_max = 0,anio_max = 0;
        for (int mes = 1; mes <= 12; mes++) {
            for (int anio = 1900; anio <= 2024; anio++) {
                if (registros_por_mes_y_anio[mes][anio] > max_registros) {
                    max_registros = registros_por_mes_y_anio[mes][anio];
                    mes_max = mes;
                    anio_max = anio;
                }
            }
        }if (max_registros == 0)break;
        printf("%d. Mes-año: %d-%d, Cantidad de registros: %d\n", i + 1, mes_max, anio_max, max_registros);
        registros_por_mes_y_anio[mes_max][anio_max] = 0;
    }
}