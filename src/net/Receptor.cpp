#include "Receptor.h"
#include <sstream>
#include <iostream>
Receptor::Receptor(const ChannelSocket& chan):
								channel(chan),
								recibir(true){}

void Receptor::run(){
	while(seguirRecibiendo()){
		try{
			std::string recibido = channel.receiveUntilNl();
			//std::cout<<"recibi algo!"<<std::endl;
			decodificarMensaje(recibido);
			//std::cout<<"decodifique"<<std::endl;
			pararDeRecibir();
		}catch(...){}
	}
}

void Receptor::end(){
	pararDeRecibir();
}
bool Receptor::seguirRecibiendo(){
	//LOCKKKKK!!!!!!!!!!!!!!!!!!!!!!!!
	return recibir;
}

void Receptor::pararDeRecibir(){
	//LOCKKKKK!!!!!!!!!!!!!!!!!!!!!!!!
	recibir = false;
}

void Receptor::decodificarMensaje(const std::string& mensaje){
	std::cout<<mensaje<<std::endl;
	std::istringstream stream(mensaje);
	std::string tipo_mensaje;
	
	stream>>tipo_mensaje;
	std::string resto_mensaje(stream.str().substr(stream.tellg()));
	
	ejecutarMensaje(tipo_mensaje,resto_mensaje);
	/*
	if(tipo_mensaje==MENSAJE_LLEGA){
		cliente.agregarLlega(resto_mensaje);
	}else if(tipo_mensaje == MENSAJE_ESTABA){
		cliente.agregarEstaba(resto_mensaje);
	}
	*/
	//std::cout<<tipo_mensaje<<" - "<<resto_mensaje<<std::endl;
}
