#include "ProxyJugador.h"
#include <iostream>
#include "../graficos/VentanaJuego.h"
#include "../mundo/Megaman.h"
#include "Buffer.h"
#include "defines_protocolo.h"
#include "../common/exceptions.h"
/*
ProxyJugador::ProxyJugador(const std::string& id, ChannelSocket* chan)
							:channel(chan),
							id_usuario(id){}
*/
void ProxyJugador::enviarListaJugadores(const std::set<ProxyJugador*>& lista){
	std::set<ProxyJugador*>::iterator it;
	for( it=lista.begin(); it != lista.end(); ++it){
		notificarEstaba(*it);
	}
}

void ProxyJugador::notificarLlegada(ProxyJugador* jugador){
	Buffer buf = Buffer::createString(MENSAJE_LLEGA + std::string(" ")+ jugador->getUsuario());
	try{
		channel->sendFixed(buf);
	}catch(CException& e){
		informarEstaRota();
	}
	//std::cout<<"enviando llega "<<jugador->getUsuario()<<std::endl;
}
void ProxyJugador::notificarEstaba(ProxyJugador* jugador){
	Buffer buf = Buffer::createString(MENSAJE_ESTABA +std::string(" ")+ jugador->getUsuario());
	try{
		channel->sendFixed(buf);
	}catch(CException& e){
		informarEstaRota();
	}
	//std::cout<<"enviando esta "<<jugador->getUsuario()<<std::endl;
}
/*
const std::string& ProxyJugador::getUsuario(){
	return id_usuario;
}
*/
void ProxyJugador::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(tipo_mensaje == MENSAJE_ID){
		////lock de ID!!!!!!!!!!!!!!!!!!
		id_usuario = resto_mensaje;
	}
}

ProxyJugador::ProxyJugador(ChannelSocket* chan)
							:Receptor(*chan),
							 channel(chan){}
							 
bool ProxyJugador::tengoUsuario(){
	//lock de ID!!!!!!!!!!!!!!!
	return (id_usuario.length()>0);
}
const std::string& ProxyJugador::getUsuario(){
	while(!tengoUsuario()){
		//std::cout<<"El programa esta bloqueado mientras espero el nombre de usuario. Que lastima!"<<std::endl;
		//bloqueo el programa!	
		//...y entonces el hilo mágico nos saca de este loop
	}
	return id_usuario;
}

ProxyJugador::~ProxyJugador(){
	delete channel;
}
bool ProxyJugador::getEstaSana(){
	//LOCK DE SANA---------------------------------------------
	return coneccion_sana;
}

void ProxyJugador::informarEstaRota(){
	//LOCK DE SANA--------------------------------------------
	coneccion_sana = false;
}

void ProxyJugador::enviarSosPrimero(){
	Buffer buf = Buffer::createString(std::string(MENSAJE_SOS_PRIMERO)+"\n");
	channel->sendFixed(buf);
}
void ProxyJugador::enviarNoSosPrimero(){
	Buffer buf = Buffer::createString(std::string(MENSAJE_NO_SOS_PRIMERO)+"\n");
	channel->sendFixed(buf);
}
