#include "ProxyJugador.h"
#include <iostream>
#include "../../graficos/VentanaJuego.h"
#include "../../mundo/Megaman.h"
#include "../sockets/Buffer.h"
#include "../defines_protocolo.h"
#include "../../common/exceptions.h"
#include "../../common/Lock.h"
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
}
void ProxyJugador::notificarEstaba(ProxyJugador* jugador){
	Buffer buf = Buffer::createString(MENSAJE_ESTABA +std::string(" ")+ jugador->getUsuario());
	try{
		channel->sendFixed(buf);
	}catch(CException& e){
		informarEstaRota();
	}
}

void ProxyJugador::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(tipo_mensaje == MENSAJE_ID){
		Lock l(m_id);
		id_usuario = resto_mensaje;
	}else if(tipo_mensaje == MENSAJE_INICIAR){
		setQuiereIniciarPartida();
	}
}

ProxyJugador::ProxyJugador(ChannelSocket* chan)
							:Receptor(*chan),
							 channel(chan),
							 conexion_sana(true),
							 quiero_iniciar(false){}
							 
bool ProxyJugador::tengoUsuario(){
	Lock l(m_id);
	return (id_usuario.length()>0);
}
const std::string& ProxyJugador::getUsuario(){
	while(!tengoUsuario()){
		//std::cout<<"El programa esta bloqueado mientras espero el nombre de usuario. Que lastima!"<<std::endl;
		//bloqueo el programa!	
		//...y entonces el hilo mágico nos saca de este loop
	}
	Lock l(m_id);
	return id_usuario;
}

ProxyJugador::~ProxyJugador(){
	delete channel;
}
bool ProxyJugador::getEstaSana(){
	Lock l(m_conexion_sana);
	return conexion_sana && getRecepcionSana();
}

void ProxyJugador::informarEstaRota(){
	Lock l(m_conexion_sana);
	conexion_sana = false;
}

void ProxyJugador::enviarSosPrimero(){
	Buffer buf = Buffer::createString(std::string(MENSAJE_SOS_PRIMERO)+"\n");
	channel->sendFixed(buf);
}
void ProxyJugador::enviarNoSosPrimero(){
	Buffer buf = Buffer::createString(std::string(MENSAJE_NO_SOS_PRIMERO)+"\n");
	channel->sendFixed(buf);
}
bool ProxyJugador::quiereIniciarPartida(){
	Lock l(m_quiero_iniciar);
	return quiero_iniciar;
}
void ProxyJugador::setQuiereIniciarPartida(){
	Lock l(m_quiero_iniciar);
	quiero_iniciar = true;
}
void ProxyJugador::notificarInicio(){
	Buffer buf = Buffer::createString(std::string(MENSAJE_INICIAR)+"\n");
	channel->sendFixed(buf);
	Lock l(m_quiero_iniciar);
	quiero_iniciar = false;//esto prepara la próxima pantalla de selección de niveles
}
