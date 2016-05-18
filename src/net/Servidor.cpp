#include "Servidor.h"
#include <iostream>
void Servidor::conectar(){
	accepter.open(5008,4);
}
void Servidor::correr(){
	conectar();
	agregarJugadores();
}
void Servidor::agregarJugadores(){
	aceptarJugadores = true;
	while(aceptarJugadores){
		try{
			ChannelSocket* channel = accepter.acceptConnection();
			std::string id_usuario = channel->receiveUntilNl();
			std::cout<<id_usuario<<std::endl;
			ProxyJugador* nuevo = new ProxyJugador(id_usuario, channel);
			nuevo->enviarListaJugadores(proxies);
			notificarLlegada(nuevo);
			proxies.insert(nuevo);
		}catch(...){}
	}
}
void Servidor::notificarLlegada(ProxyJugador* jugador){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarLlegada(jugador);
	}
}
