#ifndef CALLBACKPOSICION
#define CALLBACKPOSICION
#include <string>
#include "../sockets/CallbackReceptor.h"
class VentanaJuego;
class Cliente;

class CallbackPosicion :public CallbackReceptor{
	private:
	VentanaJuego& ventana;
	Cliente& cliente;
	int posicion;
	public:
	CallbackPosicion(VentanaJuego& ven,Cliente& cli);
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	bool informarRecepcion();
};
#endif
