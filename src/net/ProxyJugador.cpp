#include "ProxyJugador.h"
#include <iostream>
#include "../graficos/VentanaJuego.h"
#include "ServerProxy.h"
ProxyJugador(Megaman* controlado, VentanaJuego& ventana, ServerProxy& serv):
					controlado(con),
					server_proxy(serv){
	ventana.getWindow().signal_key_press_event().connect(
			sigc::mem_fun(*this, &ProxyJugador::detectarPresionTecla));
}
bool ProxyJugador::detectarPresionTecla(GdkEventKey* evento){
	controlado->saltar();
	std::cout<<"se apreto una tecla"<<std::endl;
	server_proxy.enviarEvento(CODIGO_EVENTO_SALTO);
	return false;
}
ProxyJugador::ProxyJugador(Megaman* controlado): controlado(con){}

void recibirMensajeDeCliente(CodigoEvento evento){
	if(evento==CODIGO_EVENTO_SALTO){
		controlado->saltar;
	}
}
