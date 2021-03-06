#include "Receptor.h"
#include <sstream>
#include <iostream>
#include "../../common/Lock.h"
#include "../../common/exceptions.h"
#include <ctime>
#include "Buffer.h"
#include <set>
Receptor::Receptor(const ChannelSocket& chan, RecepcionRotaCallback* c_rota):
								channel(chan),
								recibiendo(true),
								recepcion_sana(true),
								call_rota(c_rota){
}
void Receptor::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(callbacks.count(tipo_mensaje)==0)
		throw CustomException("No hay un callback para el tipo de mensaje "+tipo_mensaje);
	callbacks[tipo_mensaje]->recepcion(tipo_mensaje,resto_mensaje);
}
void Receptor::run(){
	while(seguirRecibiendo() && getRecepcionSana()){
		try{
			std::string tipo, mensaje;
			recibirTipoMensaje(tipo);
			int largo = recibirLargo();
			if(largo>0){
				recibirString(mensaje,largo);
			}
			ejecutarMensaje(tipo,mensaje);
		}catch(const std::exception& e){
			setRecepcionRota();
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
	std::istringstream stream(mensaje);
	std::string tipo_mensaje;
	
	stream>>tipo_mensaje;
	
	std::string resto_mensaje;
	if(stream.tellg()>0){
		resto_mensaje = stream.str().substr(stream.tellg());
	}
	
	ejecutarMensaje(tipo_mensaje,resto_mensaje);
}

Receptor::~Receptor(){
	join();
	std::map<std::string,CallbackReceptor*>::iterator it;
	std::set<CallbackReceptor*> borrados;
	for(it=callbacks.begin(); it !=callbacks.end(); ++it){
		CallbackReceptor* a_borrar = it->second;
		if(borrados.count(a_borrar)==0){
			borrados.insert(a_borrar);
			delete a_borrar;
		}
	}
	delete call_rota;
}
bool Receptor::setRecepcionRota(){
	Lock l(m_recepcion_sana);
	std::cerr<<"La recepcion acaba de romperse"<<std::endl;
	if(call_rota!=NULL){
		call_rota->notificar();
	}
	recepcion_sana = false;
}
bool Receptor::getRecepcionSana(){
	Lock l(m_recepcion_sana);
	return recepcion_sana;
}

void Receptor::recibirTipoMensaje(std::string& poner_en){
	try{
		Buffer buf(3);
		channel.receiveFixed(buf);
		poner_en = buf.asString();
	}catch(const CException& e){
		std::cerr<<"Falla esperada en la recepción"<<std::endl;
	}
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

void Receptor::agregarCallback(const std::string& tipo_mensaje,CallbackReceptor* callback){
	Lock l(m_callbacks);
	callbacks[tipo_mensaje]=callback;
}
