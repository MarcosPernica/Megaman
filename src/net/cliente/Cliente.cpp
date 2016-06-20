#include "Cliente.h"
#include <iostream>
#include "../sockets/Buffer.h"
#include <cstdlib>
#include "../defines_protocolo.h"
#include "../../common/Lock.h"
#include "../../graficos/VentanaJuego.h"
#include "../../mundo/Mundo.h"
#include "../../mundo/Simulador.h"
#include "Jugador.h"
#include "../../common/exceptions.h"
#include "../Debug.h"
#include "../../graficos/VentanaJuego.h"
void Cliente::conectarse(const std::string& nombre){
	#ifndef DEBUG
	socket.connectTo(SJuego::preconf.ip,SJuego::preconf.port);
	#endif
	emisor.enviar(MENSAJE_ID,nombre);
	this->nombre = nombre;
	receptor.start();
}

void Cliente::agregarEstaba(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Estaba el usuario "<<usuario<<std::endl;
}
void Cliente::agregarLlega(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Llega el usuario "<<usuario<<std::endl;
}
void Cliente::definirPosicion(int pos){
	if( pos<0 || pos>3){
		throw CustomException("Las posiciones deben estar entre 0 y 3");
	}
	Lock l(m_posicion);
	posicion = pos;
}
int Cliente::obtenerPosicion(){
	#ifndef DEBUG
	Lock l(m_posicion);
	return posicion;
	#else
	return 0;
	#endif
}
void Cliente::iniciar(){
	Lock l(m_iniciado);
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	Lock l(m_iniciado);
	return flag_iniciado;
}
const std::string& Cliente::obtenerNombre(){
	return nombre;
}
Jugador* Cliente::configurarNivel(VentanaJuego& ventana ,Mundo& mundo){
	Jugador* jugador = new Jugador(mundo.obtenerMegaman(obtenerPosicion()), ventana, emisor);
	#ifndef DEBUG
	receptor.inyectarFullSnapshotsA(&mundo);
	#endif
	return jugador;
}

Cliente::Cliente():
			receptor(socket,*this),
			emisor(socket){
	posicion=-1;
	flag_iniciado=false;
}

void Cliente::agregarCallback(const std::string& tipo_mensaje, CallbackReceptor* callback){
	receptor.agregarCallback(tipo_mensaje, callback);
}

void Cliente::enviarIniciar(int nivel){
	std::ostringstream oss;
	oss<<nivel;
	emisor.enviar(MENSAJE_INICIAR,oss.str());
}

Cliente::~Cliente(){
	std::cout<<"Cerrando el socket desde ~Cliente"<<std::endl;
	socket.closeS();
}

void Cliente::terminarMundo(){
	receptor.inyectarFullSnapshotsA(NULL);
}
