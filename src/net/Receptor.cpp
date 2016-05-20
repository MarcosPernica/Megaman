#include "Receptor.h"
#include <sstream>
#include <iostream>
#include "../common/Lock.h"
#include "../common/exceptions.h"
#include <ctime>
Receptor::Receptor(const ChannelSocket& chan):
								channel(chan),
								recibiendo(true){
	start();
}

void Receptor::run(){
	while(seguirRecibiendo()){
		try{
			std::string recibido = channel.receiveUntilNl(1);
			decodificarMensaje(recibido);
		}catch(RecvException& e){}
	}
}

void Receptor::end(){
	Lock l(m_recibir);
	recibiendo = false;
}
bool Receptor::seguirRecibiendo(){
	Lock l(m_recibir);
	return recibiendo;
}

void Receptor::decodificarMensaje(const std::string& mensaje){
	//std::cout<<mensaje<<std::endl;
	std::istringstream stream(mensaje);
	std::string tipo_mensaje;
	
	stream>>tipo_mensaje;
	std::string resto_mensaje(stream.str().substr(stream.tellg()));
	
	ejecutarMensaje(tipo_mensaje,resto_mensaje);
	//std::cout<<tipo_mensaje<<" - "<<resto_mensaje<<std::endl;
}

Receptor::~Receptor(){
	join();
}
