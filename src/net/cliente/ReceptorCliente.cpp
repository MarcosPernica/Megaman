#include "ReceptorCliente.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../defines_protocolo.h"
ReceptorCliente::ReceptorCliente(const ChannelSocket& chan, Cliente& cli):
								Receptor(chan),
								cliente(cli){}


void ReceptorCliente::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(tipo_mensaje==MENSAJE_ESTABA){
		cliente.agregarEstaba(resto_mensaje);
	}
	if(tipo_mensaje==MENSAJE_LLEGA){
		cliente.agregarLlega(resto_mensaje);
	}
	if(tipo_mensaje==MENSAJE_SOS_PRIMERO){
		cliente.definirSoyPrimero(true);
	}
	if(tipo_mensaje==MENSAJE_NO_SOS_PRIMERO){
		cliente.definirSoyPrimero(false);
	}
	if(tipo_mensaje==MENSAJE_INICIAR){
		cliente.iniciar();
	}
}
