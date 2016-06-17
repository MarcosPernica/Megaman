#include "ContenedorProxies.h"
#include <iostream>
#include "../defines_protocolo.h"
ContenedorProxies::ContenedorProxies(CallbackReceptor* iniciar, CallbackLimiteJugadores* limite):
					callbackIniciar(iniciar),
					callbackLimite(limite){}

/**
 * Ideas para agregar robustez:
 * -Si un jugador se va?
 * -Si el primero se va?
 * */
void ContenedorProxies::nuevaConexion(ChannelSocket* channel){
	Lock l(m_proxies);
	
	ProxyJugador* nuevo = new ProxyJugador(channel);
	std::string id_usuario = nuevo->getUsuario();//bloquea hasta que se recibe el usuario por primera vez
	std::cout<<"Entra: "<<id_usuario<<std::endl;
	nuevo->enviarPosicion(proxies.size());
	
	nuevo->enviarListaJugadores(proxies);//se le envían los que ya estaban//
	notificarLlegada(nuevo);//se notifica a los que ya estaban//
	proxies.push_back(nuevo);//se agrega el nuevo a la lista//
	
	if(proxies.size()==4){
		if(callbackLimite!=NULL)callbackLimite->limiteAlcanzado();
		std::cout<<"Se llegó al límite de jugadores"<<std::endl;
	}
	
	/**
	 * listener aparte!!!!!!!!!!!!!
	 * */
	 if(proxies.size()==1){
		 proxies[0]->agregarCallback(MENSAJE_INICIAR,callbackIniciar);
	 }
	/*
	if(primero!=NULL && primero->quiereIniciarPartida()){
		aceptarJugadores = false;
		std::cout<<"El primer jugador decidio iniciar"<<std::endl;
	}
	* */
}

void ContenedorProxies::distribuir(const FullSnapshot& full_snapshot){
	std::vector<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->enviar(full_snapshot);
	}
}

void ContenedorProxies::ejecutarControlesSobreMegaman(){
	std::vector<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->ejecutarControlSobreMegaman();
	}
}

void ContenedorProxies::enviarNivel(char nivel){
	/*
	std::cout<<"----------------------ENVIO EL  NIVEL"<<nivel<<"A TODOS----------"<<std::endl;
	* */
	std::vector<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->enviarNivel(nivel);
	}
}

void ContenedorProxies::notificarInicio(){
	std::vector<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarInicio();
	}
}

void ContenedorProxies::matarConexiones(){
	std::vector<ProxyJugador*>::iterator it;
	for(it=proxies.begin(); it!=proxies.end(); ++it){
		ProxyJugador* a_borrar=*it;
		delete a_borrar;
	}
}

void ContenedorProxies::notificarLlegada(ProxyJugador* jugador){
	std::vector<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarLlegada(jugador);
	}
}

std::vector<ProxyJugador*> ContenedorProxies::obtenerJugadores(){
	return proxies;
}
