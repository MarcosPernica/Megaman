#ifndef SIMULADOR
#define SIMULADOR
/**
 * Actualiza el Mundo periódicamente
 * Hay que renombrarlo a SimuladorConVentana
 * */
 #include "Mundo.h"
class Simulador{
	public:
	Simulador(Mundo& mundo, uint milisPorActualizacion);
	void run();
	bool on_actualizar();
	private:
	Mundo& mundo;
	uint milisPorActualizacion;
};

#endif
