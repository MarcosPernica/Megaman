#include "Cliente.h"
#include <iostream>
#include "Buffer.h"
#include "ReceptorCliente.h"
#include <cstdlib>
#include "defines_protocolo.h"
#include "../common/Lock.h"
//Cliente::Cliente(){}
void Cliente::correr(){
	posicion=Desconocida;
	flag_iniciado=false;
	
	conectarse();
	enviarID();
	ReceptorCliente receptor(socket,*this);
	
	while(obtenerPosicion()==Desconocida){
		//bloquear el hilo
	}
	
	if(obtenerPosicion()==NoPrimero){
		std::cout<<"No sos el primero, estas hasta la pija"<<std::endl;
	}else{
		char respuesta='0';
		while(obtenerPosicion()==Primero && respuesta!='i'){
			std::cout<<"Usted es el primero. Ingrese i para iniciar la partida"<<std::endl;
			std::cin>>respuesta;
		}
		enviarIniciar();//acá hay que meter la información del nivel
	}
	
	while(!iniciado()){//ahora, seas segundo o primero, te bloqueo hasta que recibis el iniciar
		//detener este hilo
	}
	
	std::cout<<"Se lanza la partida y la ventana aca!"<<std::endl;	
	//------------------ACÁ SE LANZA LA VENTANA Y LOS COHETES----------//
}
void Cliente::conectarse(){
	socket.connectTo("127.0.0.1",5002);
}
void Cliente::enviarID(){
	std::string id;
	std::cout<<"Introduzca su ID unica. Confio en usted"<<std::endl;
	std::cin>>id;
	Buffer id_buf = Buffer::createString(std::string(MENSAJE_ID)+" " + id + "\n");
	socket.sendFixed(id_buf);
}

void Cliente::agregarEstaba(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Estaba el usuario "<<usuario<<std::endl;
}
void Cliente::agregarLlega(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Llega el usuario "<<usuario<<std::endl;
}
void Cliente::definirSoyPrimero(bool soy_primero){
	Lock l(m_posicion);
	if(soy_primero){
		posicion=Primero;
	}else{
		posicion=NoPrimero;
	}
}

Posicion Cliente::obtenerPosicion(){
	Lock l(m_posicion);
	return posicion;
}

void Cliente::enviarIniciar(){
	Buffer men_buf = Buffer::createString(std::string(MENSAJE_INICIAR) + " \n");
	socket.sendFixed(men_buf);
}

void Cliente::iniciar(){
	Lock l(m_iniciado);
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	Lock l(m_iniciado);
	return flag_iniciado;
}
