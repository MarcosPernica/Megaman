#ifndef SIMULADOR
#define SIMULADOR
/**
 * Actualiza el Mundo periódicamente
 * Hay que renombrarlo a SimuladorConVentana
 * */
#include "Mundo.h"

#include <gdkmm/general.h>

class Simulador{
	public:
	sigc::connection conexion;
	Simulador(Mundo& mundo, uint milisPorActualizacion);
	bool on_actualizar();
	void desconectar();
	private:
	Mundo& mundo;
	uint milisPorActualizacion;
};

#endif
