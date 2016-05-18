#include "Cliente.h"
#include <iostream>
#include "Buffer.h"
//Cliente::Cliente(){}
void Cliente::correr(){
	conectarse();
	enviarID();
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
	Buffer id_buf = Buffer::createString(id + "\n");
	socket.sendFixed(id_buf);
}
