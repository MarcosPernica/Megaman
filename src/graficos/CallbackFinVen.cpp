#include "CallbackFinVen.h"
#include <sstream>
#include <glibmm/main.h>
#include "VentanaJuego.h"
#include "../net/cliente/Cliente.h"
#include "../net/defines_protocolo.h"

void CallbackFinVen::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &CallbackFinVen::informarRecepcion));
}
bool CallbackFinVen::informarRecepcion(){
	ventana.mostrarPantallaSeleccion();
	return false;
}
