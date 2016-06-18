#ifndef CallbackFinVenDEVENTANAJUEGO
#define CallbackFinVenDEVENTANAJUEGO
#include <string>
#include "../net/sockets/CallbackReceptor.h"
#include "../net/cliente/Cliente.h"
class CallbackFinVen : public CallbackReceptor{
	private:
	Cliente& cliente;
	VentanaJuego& ventana;
	std::string nombre;
	public:
	CallbackFinVen(VentanaJuego& ven, Cliente& cli):cliente(cli),ventana(ven){}
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	bool informarRecepcion();
};
#endif
