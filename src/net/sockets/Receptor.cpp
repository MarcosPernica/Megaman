#include "Receptor.h"
#include <sstream>
#include <iostream>
#include "../../common/Lock.h"
#include "../../common/exceptions.h"
#include <ctime>
#include "Buffer.h"
#include <set>
Receptor::Receptor(const ChannelSocket& chan):
								channel(chan),
								recibiendo(true),
								recepcion_sana(true){
}
void Receptor::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(callbacks.count(tipo_mensaje)==0)
		throw CustomException("No hay un callback para el tipo de mensaje "+tipo_mensaje);
	callbacks[tipo_mensaje]->recepcion(tipo_mensaje,resto_mensaje);
}
void Receptor::run(){
	while(seguirRecibiendo() && getRecepcionSana()){
		std::cout<<"Corriendo receptor!"<<std::endl;
		
		//try{
			std::string tipo, mensaje;
			recibirTipoMensaje(tipo);
			int largo = recibirLargo();
			if(largo>0){
				recibirString(mensaje,largo);
			}
			ejecutarMensaje(tipo,mensaje);
			std::cout<<"Ejecuté!"<<std::endl;
		/*
		}//catch(RecvException& e){}
		 catch(RecvTimeOutException &e){
			 std::cout<<"Recepción rota!"<<std::endl;
			 setRecepcionRota();
			 throw e;////////////////////POR AHORA NO HAGO NINGUN MANEJO ESPECIAL DE ESTA SITUACION!!
			 /////////////////////////-----------------
		 }
		 */
		std::cout<<"Fin del loop!"<<std::endl;
	}
	std::cout<<"RUN!"<<std::endl;
	std::cout<<seguirRecibiendo()<<std::endl;
	std::cout<<getRecepcionSana()<<std::endl;
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
	std::map<std::string,CallbackReceptor*>::iterator it;
	std::set<CallbackReceptor*> borrados;
	for(it=callbacks.begin(); it !=callbacks.end(); ++it){
		CallbackReceptor* a_borrar = it->second;
		if(borrados.count(a_borrar)==0){
			borrados.insert(a_borrar);
			delete a_borrar;
		}
	}
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

void Receptor::agregarCallback(const std::string& tipo_mensaje,CallbackReceptor* callback){
	Lock l(m_callbacks);
	callbacks[tipo_mensaje]=callback;
}
