#ifndef CALLBACKESTABALLEGA
#define CALLBACKESTABALLEGA
#include <string>
#include "../net/sockets/CallbackReceptor.h"
#include "../net/cliente/Cliente.h"
class CallbackEstabaLlega : public CallbackReceptor{
	private:
	Cliente& cliente;
	VentanaJuego& ventana;
	std::string nombre;
	public:
	CallbackEstabaLlega(VentanaJuego& ven, Cliente& cli):cliente(cli),ventana(ven){}
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	bool informarRecepcion();
};
#endif
