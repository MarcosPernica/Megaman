#ifndef SIMULADORSINVENTANA
#define SIMULADORSINVENTANA
/**
 * Actualiza el Mundo periódicamente, sin hacer uso de las librerías de gtkmm
 * Es un Thread.
 * */
 #include "Mundo.h"
 #include "../common/Thread.h"
 #include "../common/Mutex.h"
 #include "../net/servidor/ContenedorProxies.h"
class CallbackFinMundo{
	public:
	virtual void fin(EstadoMundo estado) = 0;
};
class SimuladorSinVentana: public Thread{
	public:
	SimuladorSinVentana(Mundo& mundo, uint milisPorActualizacion, ContenedorProxies& contenedor, CallbackFinMundo* call);
	~SimuladorSinVentana();
	private:
	Mundo& mundo;
	CallbackFinMundo* callbackFinMundo;
	ContenedorProxies& contenedor;
	void run();
	void end();
	bool continuar;
	Mutex m_continuar;
	bool getContinuar();
	
	float segundosPorActualizacion;
	
	
};

#endif
