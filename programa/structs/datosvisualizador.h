#ifndef DATOSVISUALIZADOR_H
#define DATOSVISUALIZADOR_H

typedef struct{
    float VarianzaTemperatura;
    float *RangoTemperatura;
    float VarianzaHumedad;
    float *RangoHumedad;
    float VarianzaPresion;
    float *RangoPresion;
    float VarianzaVelocidadViento;
    float *RangoVelocidadViento;
    float VarianzaPrecipitacion;
    float *RangoPrecipitacion;
} DatosVisualizador;

#endif