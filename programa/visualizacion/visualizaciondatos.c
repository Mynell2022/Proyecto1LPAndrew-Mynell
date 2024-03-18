#include "../visualizacion/visualizaciondatos.h"
#include <math.h>

/// @brief Esta función controla la visualización de datos.
/// @param posicionX La posición X aproximada.
/// @param posicionY La posición Y aproximada.
/// @return Un struct con los datos del rango y la varianza.
DatosVisualizador VisualizarDatos(float posicionX, float posicionY){
    DatosVisualizador datos = {NAN, NULL, NAN, NULL, NAN, NULL, NAN, NULL, NAN, NULL};
    if(tamanoRegion == 0){
        return datos;
    }
    Region regionCercana = BuscarRegionCercana(posicionX, posicionY);
    Clima *datosClimas = BuscarClimasRegion(regionCercana.nombre);
    int longitudClimas = ContarTamanoDatos(datosClimas);
    if(longitudClimas == 0){
        return datos;
    }
    float *datosTemperatura = ObtenerDatosTemperatura(datosClimas, longitudClimas);
    float *datosHumedad = ObtenerDatosHumedad(datosClimas, longitudClimas);
    float *datosPresion = ObtenerDatosPresion(datosClimas, longitudClimas);
    float *datosVelocidadViento = ObtenerDatosVelocidadViento(datosClimas, longitudClimas);
    float *datosPrecipitacion = ObtenerDatosPrecipitacion(datosClimas, longitudClimas);
    return ArmarDatosVisualizador(datosTemperatura, datosHumedad, datosPresion, datosVelocidadViento, datosPrecipitacion);
}

/// @brief Esta función ingresa todos los datos al struct que se envía a la vista.
/// @param datosTemperatura Los datos de la temperatura.
/// @param datosHumedad Los datos de la humedad.
/// @param datosPresion Los datos de la presión atmosférica.
/// @param datosVelocidadViento Los datos de la velocidad del viento.
/// @param datosPrecipitacion Los datos de la precipitación.
/// @return Un struct con los datos del rango y la varianza.
DatosVisualizador ArmarDatosVisualizador(float *datosTemperatura, float *datosHumedad, float *datosPresion, float *datosVelocidadViento, float *datosPrecipitacion){
    DatosVisualizador datos = {NAN, NULL, NAN, NULL, NAN, NULL, NAN, NULL, NAN, NULL};
    if(datosTemperatura != NULL){
        datos.VarianzaTemperatura = CalcularVarianza(datosTemperatura);
        datos.RangoTemperatura = CalcularRango(datosTemperatura);
    }
    if(datosHumedad != NULL){
        datos.VarianzaHumedad = CalcularVarianza(datosHumedad);
        datos.RangoHumedad = CalcularRango(datosHumedad);
    }
    if(datosPresion != NULL){
        datos.VarianzaPresion = CalcularVarianza(datosPresion);
        datos.RangoPresion = CalcularRango(datosPresion);
    }
    if(datosVelocidadViento != NULL){
        datos.VarianzaVelocidadViento = CalcularVarianza(datosVelocidadViento);
        datos.RangoVelocidadViento = CalcularRango(datosVelocidadViento);
    }
    if(datosPrecipitacion != NULL){
        datos.VarianzaPrecipitacion = CalcularVarianza(datosPrecipitacion);
        datos.RangoPrecipitacion = CalcularRango(datosPrecipitacion);
    }
    return datos;
}

/// @brief Esta función busca la región más cercana que a los puntos que dio el usuario.
/// @param posicionX La posición X aproximada.
/// @param posicionY La posición Y aproximada.
/// @return La región más cerca.
Region BuscarRegionCercana(float posicionX, float posicionY){
    Region regionCercana = regiones[0];
    float distanciaUno = sqrt(pow(regionCercana.x - posicionX, 2) + pow(regionCercana.y - posicionY, 2));
    for(int indice = 0; indice < tamanoRegion; indice++){
        Region regionActual = regiones[indice];
        float distanciaDos = sqrt(pow(regionActual.x - posicionX, 2) + pow(regionActual.y - posicionY, 2));
        if(distanciaUno > distanciaDos){
            regionCercana = regionActual;
            distanciaUno = distanciaDos;
        }
    }
    return regionCercana;
}

/// @brief Busca todos los registros de clima que pertenecen a la región.
/// @param nombre El nombre de la región que se utiliza.
/// @return Los climas que le corresponden a la región.
Clima *BuscarClimasRegion(char* nombre){
    Clima *datosClimas = malloc((tamanoClimas + 1) * sizeof(Clima));
    int indiceClimas = 0;
    datosClimas[0].Region = NULL;
    for(int indice = 0; indice < tamanoClimas; indice++){
        Clima climaActual = climas[indice];
        if(strcmp(nombre, climaActual.Region) == 0){
            datosClimas[indiceClimas] = climaActual;
            indiceClimas++;
            datosClimas[indiceClimas].Region = NULL;
        }
    }
    return datosClimas;
}

/// @brief Cuenta la cantidad de registros de climas que contiene la región.
/// @param datosClimas Los climas de la región.
/// @return La cantidad de registros que posee la región.
int ContarTamanoDatos(Clima *datosClimas){
    int contador = 0;
    for(int indice = 0; datosClimas[indice].Region != NULL; indice++)
        contador++;
    return contador;
}

/// @brief Crea un arreglo de float con los datos de la temperatura de la región.
/// @param datosClima Los registros de clima.
/// @param tamano La cantidad de registros.
/// @return El arreglo de temperaturas.
float *ObtenerDatosTemperatura(Clima *datosClima, int tamano){
    float *datosTemperatura = malloc(tamano * sizeof(float));
    int indiceDatos = 0;
    for(int indice = 0; indice < tamano; indice++){
        float temperatura = datosClima[indice].Temperatura;
        if(!isnan(temperatura)){
            datosTemperatura[indiceDatos] = temperatura;
            indiceDatos++;
            datosTemperatura[indiceDatos] = NAN;
        }
    }
    return datosTemperatura;
}

/// @brief Crea un arreglo de float con los datos de la humedad de la región.
/// @param datosClima Los registros de clima.
/// @param tamano La cantidad de registros.
/// @return El arreglo de humedades.
float *ObtenerDatosHumedad(Clima *datosClima, int tamano){
    float *datosHumedad = malloc(tamano * sizeof(float));
    int indiceDatos = 0;
    for(int indice = 0; indice < tamano; indice++){
        float humedad = datosClima[indice].Humedad;
        if(!isnan(humedad)){
            datosHumedad[indiceDatos] = humedad;
            indiceDatos++;
            datosHumedad[indiceDatos] = NAN;
        }
    }
    return datosHumedad;
}

/// @brief Crea un arreglo de float con los datos de la presión atmosférica de la región.
/// @param datosClima Los registros de clima.
/// @param tamano La cantidad de registros.
/// @return El arreglo de las presiones atmosféricas.
float *ObtenerDatosPresion(Clima *datosClima, int tamano){
    float *datosPresion = malloc((tamano + 1) * sizeof(float));
    int indiceDatos = 0;
    for(int indice = 0; indice < tamano; indice++){
        float presion = datosClima[indice].Presion;
        if(!isnan(presion)){
            datosPresion[indiceDatos] = presion;
            indiceDatos++;
            datosPresion[indiceDatos] = NAN;
        }
    }
    return datosPresion;
}

/// @brief Crea un arreglo de float con los datos de la velocida del viento de la región.
/// @param datosClima Los registros de clima.
/// @param tamano La cantidad de registros.
/// @return El arreglo de las velocidades del viento.
float *ObtenerDatosVelocidadViento(Clima *datosClima, int tamano){
    float *datosVelocidadViento = malloc((tamano + 1) * sizeof(float));
    int indiceDatos = 0;
    for(int indice = 0; indice < tamano; indice++){
        float velocidadViento = datosClima[indice].VelocidadViento;
        if(!isnan(velocidadViento)){
            datosVelocidadViento[indiceDatos] = velocidadViento;
            indiceDatos++;
            datosVelocidadViento[indiceDatos] = NAN;
        }
    }
    return datosVelocidadViento;
}

/// @brief Crea un arreglo de float con los datos de la precipitación de la región.
/// @param datosClima Los registros de clima.
/// @param tamano La cantidad de registros.
/// @return El arreglo de las precipitaciones.
float *ObtenerDatosPrecipitacion(Clima *datosClima, int tamano){
    float *datosPrecipitacion = malloc((tamano + 1) * sizeof(float));
    int indiceDatos = 0;
    for(int indice = 0; indice < tamano; indice++){
        float precipitacion = datosClima[indice].Precipitacion;
        if(!isnan(precipitacion)){
            datosPrecipitacion[indiceDatos] = precipitacion;
            indiceDatos++;
            datosPrecipitacion[indiceDatos] = NAN;
        }
    }
    return datosPrecipitacion;
}

/**
 * Cuenta la cantidad de elementos de un arreglo de números flotantes.
 * 
 * @param arreglo El arreglo que se debe contar.
 * @return La cantidad de elementos.
*/
int ContarArreglo(float *arreglo){
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
void IntercambiarNumeros(float *a, float *b) {
    float temporal = *a;
    *a = *b;
    *b = temporal;
}

/**
 * Ordena el arreglo.
 * 
 * @param arreglo El arreglo a ordenar.
*/
void OrdenarArregloFlotante(float *arreglo) {
    int longitud = ContarArreglo(arreglo);
    for (int indice = 0; indice < longitud - 1; indice++) {
        for (int j = 0; j < longitud - indice - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                IntercambiarNumeros(&arreglo[j], &arreglo[j + 1]);
            }
        }
    }
    arreglo[longitud] = NAN;
}


/// @brief Calcula el rango de los registros del clima de la región.
/// @param datos Los datos de los registros.
/// @return Un arreglo de float con el mínimo y el máximo.
float *CalcularRango(float* datos){
    OrdenarArregloFlotante(datos);
    int longitud = ContarArreglo(datos);
    if(longitud != 0){
        float minimo = datos[0];
        float maximo = datos[longitud - 1];
        float *rango = malloc(2 * sizeof(float));
        rango[0] = minimo;
        rango[1] = maximo;
        return rango;
    }
    return NULL;
}

/// @brief Calcula la varianza de los datos de los registros de la región.
/// @param datos Los datos de los registros.
/// @return La varianza de los registros.
float CalcularVarianza(float *datos){
    int longitud = ContarArreglo(datos);
    float media = CalcularMedia(datos, longitud);
    float sumatoria = CalcularSumatoria(datos, longitud, media);
    float varianza = sumatoria / (longitud - 1);
    return varianza;
}

/// @brief Calcula la sumatoria de para calcular la varianza
/// @param datos Los datos de los registros.
/// @param cantidad La cantidad de registros.
/// @param media La media de los registros.
/// @return La sumatoria de los registros.
float CalcularSumatoria(float *datos, int cantidad, int media){
    float sumatoria = 0;
    for(int indice = 0; indice < cantidad; indice++){
        float dato = datos[indice];
        sumatoria += pow(dato - media, 2);
    }
    return sumatoria;
}

/// @brief Calcula la media de los registros de la región.
/// @param datos Los datos de los registros.
/// @param cantidad La cantidad de registros.
/// @return La media de los datos.
float CalcularMedia(float *datos, int cantidad){
    float sumatoria = 0;
    for(int indice = 0; indice < cantidad; indice++){
        sumatoria += datos[indice];
    }
    return sumatoria / cantidad;
}