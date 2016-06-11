#include "CallbackPosicion.h"
#include <sstream>
#include <glibmm/main.h>
#include "../../graficos/VentanaJuego.h"
#include "Cliente.h"
CallbackPosicion::CallbackPosicion(VentanaJuego& ven,Cliente& cli):ventana(ven),cliente(cli){}
void CallbackPosicion::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	std::istringstream ss(resto_mensaje);
	ss>>posicion;
	cliente.definirPosicion(posicion);
	Glib::signal_idle().connect(sigc::mem_fun(*this, &CallbackPosicion::informarRecepcion));//los milis son arbitrarios
}
bool CallbackPosicion::informarRecepcion(){
	ventana.setPrimero(posicion==0);
	return false;
}
