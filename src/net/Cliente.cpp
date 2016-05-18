#include "Cliente.h"
#include <iostream>
#include "Buffer.h"
#include "ReceptorCliente.h"
#include <cstdlib>
#include "defines_protocolo.h"
//Cliente::Cliente(){}
void Cliente::correr(){
	posicion=Desconocida;
	flag_iniciado=false;
	
	conectarse();
	enviarID();
	ReceptorCliente receptor(socket,*this);
	receptor.start();
	std::cout<<"antes de entrar a lo desconocido"<<std::endl;
	while(obtenerPosicion()==Desconocida){
		//bloquear el hilo
	}
	std::cout<<"Ya sali de lo desconocido"<<std::endl;
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
	std::cout<<"Ahora voy a esperar a que me inicie el servidor, pero ese mensaje todavia no se envia así que mete ctrl-c. Estamos hasta la pija!"<<std::endl;
	while(!iniciado()){//ahora, seas segundo o primero, te bloqueo hasta que recibis el iniciar
		//detener este hilo
	}
	
	std::cout<<"Se lanza la partida y la ventana aca!"<<std::endl;	
	//------------------ACÁ SE LANZA LA VENTANA Y LOS COHETES----------//
	
	receptor.join();
	std::cout<<"chau!"<<std::endl;
	/*
	std::set<int> jugadores = recibirListaJugadores();
	std::set<int>::iterator it;
	for(it = jugadores.begin(); it!=jugadores.end(); ++it){
		std::cout<<"Existe un jugador con id "<<*it<<std::endl;
	}
	*/
	/**
	 * Ciclo que recibe más jugadores y los muestra por pantalla. 
	 * Es un hilo aparte, que termina cuando se recibe el iniciar.
	 * */
	 /*
	ReceptorNotificaciones receptor;
	receptor.start();
	if(size(jugadores)==0){
		iniciarPartda();
	}
	esperador.join();
	*/
}
void Cliente::conectarse(){
	socket.connectTo("127.0.0.1",5008);
}
void Cliente::enviarID(){
	std::string id;
	std::cout<<"Introduzca su ID unica. Confio en usted"<<std::endl;
	std::cin>>id;
	Buffer id_buf = Buffer::createString(std::string(MENSAJE_ID)+" " + id + "\n");
	socket.sendFixed(id_buf);
}

void Cliente::agregarEstaba(const std::string& usuario){
	//LOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::cout<<"Estaba el usuario "<<usuario<<std::endl;
}
void Cliente::agregarLlega(const std::string& usuario){
	//LOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::cout<<"Llega el usuario "<<usuario<<std::endl;
}
void Cliente::definirSoyPrimero(bool soy_primero){
	//LOCK DE POSICION!!!!!!!!!!!!!!!!!!!!!!
	if(soy_primero){
		std::cout<<"soy primero"<<std::endl;
		posicion=Primero;
	}else{
		posicion=NoPrimero;
		std::cout<<"soy no-primero"<<std::endl;
	}
}

Posicion Cliente::obtenerPosicion(){
	//LOCK DE POSICION!!!!!!!!!!!!!!!!!!!!!!
	return posicion;
}

void Cliente::enviarIniciar(){
	Buffer id_buf = Buffer::createString(std::string(MENSAJE_INICIAR) + "\n");
	socket.sendFixed(id_buf);
}

void Cliente::iniciar(){
	//LOCK DE INICIADO!!!!!!!!!!
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	//LOCK DE INICIADO!!!!!!!!!!
	return flag_iniciado;
}
