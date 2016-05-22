#ifndef SIMULADOR
#define SIMULADOR
/**
 * Actualiza el Mundo periódicamente
 * Hay que renombrarlo a SimuladorConVentana
 * */
#include "Mundo.h"

class Camara;

class Simulador{
	public:
	Simulador(Mundo& mundo, Camara &camara, uint milisPorActualizacion);
	bool on_actualizar();
	private:
	Mundo& mundo;
	Camara &camara;
	uint milisPorActualizacion;
};

#endif
