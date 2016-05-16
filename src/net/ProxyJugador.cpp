#include "ProxyJugador.h"
#include <iostream>
ProxyJugador::ProxyJugador(Megaman* con, VentanaJuego& ventana):controlado(con){
	ventana.getWindow().signal_key_press_event().connect(
			sigc::mem_fun(*this, &ProxyJugador::detectarPresionTecla));
}
bool ProxyJugador::detectarPresionTecla(GdkEventKey* evento){
	controlado->saltar();
	std::cout<<"se apreto una tecla"<<std::endl;
	return true;
}
