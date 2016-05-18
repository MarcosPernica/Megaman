#include "Cliente.h"
#include <iostream>
#include "Buffer.h"
#include "ReceptorCliente.h"
#include <cstdlib>
#include "defines_protocolo.h"
//Cliente::Cliente(){}
void Cliente::correr(){
	es_primero=true;
	conectarse();
	enviarID();
	ReceptorCliente receptor(socket,*this);
	receptor.start();
	sleep(5);
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
	es_primero=false;
	std::cout<<"Estaba el usuario "<<usuario<<std::endl;
}
void Cliente::agregarLlega(const std::string& usuario){
	//LOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::cout<<"Llega el usuario "<<usuario<<std::endl;
}
