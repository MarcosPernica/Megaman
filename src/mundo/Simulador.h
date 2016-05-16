#ifndef SIMULADOR
#define SIMULADOR
/**
 * Actualiza el Mundo periódicamente
 * */
class Simulador{
	public:
	Simulador(Mundo& mundo, uint milisPorActualizacion);
	bool on_actualizar();
	private:
	Mundo& mundo;
	uint milisPorActualizacion;
}

#endif
