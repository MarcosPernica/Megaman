#include "Receptor.h"
#include <sstream>
#include <iostream>
#include "../../common/Lock.h"
#include "../../common/exceptions.h"
#include <ctime>
#include "Buffer.h"
Receptor::Receptor(const ChannelSocket& chan):
								channel(chan),
								recibiendo(true),
								recepcion_sana(true){
	start();
}

void Receptor::run(){
	while(seguirRecibiendo() && getRecepcionSana()){
		try{
			/*
			std::string recibido = channel.receiveUntilNl(0.01);
			decodificarMensaje(recibido);
			*/
			std::string tipo, mensaje;
			recibirTipoMensaje(tipo);
			int largo = recibirLargo();
			if(largo>0){
				recibirString(mensaje,largo);
			}
			ejecutarMensaje(tipo,mensaje);
		}//catch(RecvException& e){}
		 catch(RecvTimeOutException &e){
			 setRecepcionRota();
			 throw e;////////////////////POR AHORA NO HAGO NINGUN MANEJO ESPECIAL DE ESTA SITUACION!!
			 /////////////////////////-----------------
		 }
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
	
	std::string resto_mensaje;
	if(stream.tellg()>0){
		resto_mensaje = stream.str().substr(stream.tellg());
	}
	
	ejecutarMensaje(tipo_mensaje,resto_mensaje);
	//std::cout<<tipo_mensaje<<" - "<<resto_mensaje<<std::endl;
}

Receptor::~Receptor(){
	join();
}
bool Receptor::setRecepcionRota(){
	Lock l(m_recepcion_sana);
	std::cout<<"La recepcion acaba de romperse"<<std::endl;
	recepcion_sana = false;
}
bool Receptor::getRecepcionSana(){
	Lock l(m_recepcion_sana);
	return recepcion_sana;
}

void Receptor::recibirTipoMensaje(std::string& poner_en){
	Buffer buf(3);
	channel.receiveFixed(buf);
	poner_en = buf.asString();
}

int Receptor::recibirLargo(){
	Buffer buf(sizeof(int));
	channel.receiveFixed(buf);
	return buf.asNumber();
}

void Receptor::recibirString(std::string& poner_en, int tamanio){
	Buffer buf(tamanio);
	channel.receiveFixed(buf);
	poner_en = buf.asString();
}
