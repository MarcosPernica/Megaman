#ifndef CALLBACKFIN
#define CALLBACKFIN
#include "../../mundo/SimuladorSinVentana.h"
class Servidor;
class CallbackFin: public CallbackFinMundo{
	private:
	Servidor& servidor;
	CallbackFin();
	public:
	CallbackFin(Servidor& servidor);
	virtual void fin(EstadoMundo estado);
};
#endif
