#include <time.h>
#include <cjson/cJSON.h>

char* AnalizarCorrelacion(Region region, char* datoUno, char* datoDos, time_t fechaUno, time_t fechaDos);
float CalcularCoeficienteCorrelacionPearson(float sumaMultiplicacion, float sumaPotenciaUno, float sumaPotenciaDos);
float ElevarDiferencia(int* diferencia);
float MultiplicarDiferencias(int* diferenciaUno, int* diferenciaDos);
float* CalcularDiferenciaMedia(int* datos, int media);
float CalcularMedia(float* datos);
int* CrearArregloDatos(char* dato, cJSON* json);

cJSON* FiltrarDatos(char* variableUno, char* variableDos);
cJSON* ExtraerDatosSinRegion(time_t* fechaInicial, time_t* fechaFin);
cJSON* ExtraerDatosConRegion(char* region, time_t* fechaInicial, time_t* fechaFin);
int CompararFechas(time_t* fechaUno, time_t* fechaDos);