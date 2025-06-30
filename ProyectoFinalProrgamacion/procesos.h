#ifndef PROCESOS_H
#define PROCESOS_H
extern int numLista;
void buscarVehiculo();
void log_error (const char *message);
void procesarIngreso();
void listarVehiculos();
float calcularMatricula( char placa [], float avaluo, int anio, int edad, int revisiones, int tipo);
#endif
