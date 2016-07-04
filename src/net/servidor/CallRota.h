#ifndef CALLROTA
#define CALLROTA
#include "../sockets/RecepcionRotaCallback.h"
#include "ProxyJugador.h"
class CallRota : RecepcionRotaCallback{
	private:
	ProxyJugador& proxy;
	public:
	virtual void notificar();
	CallRota(ProxyJugador& p);
};
#endif
