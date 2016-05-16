#ifndef SIMULADOR
#define SIMULADOR
/**
 * Actualiza el Mundo periódicamente
 * */
 #include "Mundo.h"
class Simulador{
	public:
	Simulador(Mundo& mundo, uint milisPorActualizacion);
	bool on_actualizar();
	private:
	Mundo& mundo;
	uint milisPorActualizacion;
};

#endif
