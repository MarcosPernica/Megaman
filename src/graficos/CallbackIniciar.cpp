#include "CallbackIniciar.h"
#include <sstream>
#include <glibmm/main.h>
#include "VentanaJuego.h"
#include "../net/cliente/Cliente.h"
#include "../net/defines_protocolo.h"
#include <iostream>
void CallbackIniciar::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	std::cout<<"Me llega la senial de inicio"<<std::endl;
	Glib::signal_idle().connect(sigc::mem_fun(*this, &CallbackIniciar::informarRecepcion));//los milis son arbitrarios
}
bool CallbackIniciar::informarRecepcion(){
	ventana.iniciarNivel();
	return false;
}
