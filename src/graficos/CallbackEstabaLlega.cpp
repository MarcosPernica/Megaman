#include "CallbackEstabaLlega.h"
#include <sstream>
#include <glibmm/main.h>
#include "VentanaJuego.h"
#include "../net/cliente/Cliente.h"
#include "../net/defines_protocolo.h"

void CallbackEstabaLlega::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	nombre = resto_mensaje;
	
	if(resto_mensaje==MENSAJE_LLEGA){
		cliente.agregarLlega(nombre);
	}else if (resto_mensaje==MENSAJE_ESTABA){
		cliente.agregarEstaba(nombre);
	}
	
	Glib::signal_idle().connect(sigc::mem_fun(*this, &CallbackEstabaLlega::informarRecepcion));//los milis son arbitrarios
}
bool CallbackEstabaLlega::informarRecepcion(){
	ventana.agregarJugador(nombre);
	return false;
}
