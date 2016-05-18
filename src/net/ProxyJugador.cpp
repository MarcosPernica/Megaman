#include "ProxyJugador.h"
#include <iostream>
#include "../graficos/VentanaJuego.h"
#include "ServerProxy.h"
#include "../mundo/Megaman.h"
#include "Buffer.h"
#include "defines_protocolo.h"
ProxyJugador::ProxyJugador(const std::string& id, ChannelSocket* chan)
							:channel(chan),
							id_usuario(id){}

void ProxyJugador::enviarListaJugadores(const std::set<ProxyJugador*>& lista){
	std::set<ProxyJugador*>::iterator it;
	for( it=lista.begin(); it != lista.end(); ++it){
		notificarEstaba(*it);
	}
}

void ProxyJugador::notificarLlegada(ProxyJugador* jugador){
	Buffer buf = Buffer::createString(MENSAJE_LLEGA + jugador->getUsuario());
	channel->sendFixed(buf);
}
void ProxyJugador::notificarEstaba(ProxyJugador* jugador){
	Buffer buf = Buffer::createString(MENSAJE_ESTABA + jugador->getUsuario());
	channel->sendFixed(buf);
}

const std::string& ProxyJugador::getUsuario(){
	return id_usuario;
}
/*
void ProxyJugador::recibirMensajeDeCliente(CodigoEvento evento){
	if(evento==CODIGO_EVENTO_SALTO){
		controlado->saltar();
	}
}
*/
