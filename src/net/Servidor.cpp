#include "Servidor.h"
#include <iostream>
#include "../common/exceptions.h"
void Servidor::conectar(){
	accepter.open(5008,4);
}
void Servidor::correr(){
	conectar();
	agregarJugadores();
}
void Servidor::agregarJugadores(){
	aceptarJugadores = true;
	while(aceptarJugadores){
		try{
			ChannelSocket* channel = accepter.acceptConnection();
			ProxyJugador* nuevo = new ProxyJugador(channel);
			nuevo->start();
			std::string id_usuario = nuevo->getUsuario();//bloquea hasta que se recibe el usuario por primera vez
			std::cout<<"Entra: "<<id_usuario<<std::endl;
			nuevo->enviarListaJugadores(proxies);//se le envían los que ya estaban
			notificarLlegada(nuevo);//se notifica a los que ya estaban
			proxies.insert(nuevo);//se agrega el nuevo a la lista
			std::cout<<"Ahora hay "<<proxies.size()<<" tipos conectados"<<std::endl;
			
		}catch(AcceptException& e){}
	}
	std::cout<<"Mira que me estoy yendo normalmente....."<<std::endl;
}
void Servidor::notificarLlegada(ProxyJugador* jugador){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarLlegada(jugador);
	}
}

Servidor::~Servidor(){
	std::set<ProxyJugador*>::iterator it;
	for(it=proxies.begin(); it!=proxies.end(); ++it){
		ProxyJugador* a_borrar=*it;
		delete a_borrar;
	}
}
