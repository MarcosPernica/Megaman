#include "Servidor.h"
#include <iostream>
#include "../../common/exceptions.h"
#include <ctime>
#include "../../mundo/Mundo.h"
#include "../../mundo/SimuladorSinVentana.h"
#include "ContenedorProxies.h"

void Servidor::conectar(){
	accepter.open(10020,4);
}
void Servidor::correr(){
	conectar();
	ProxyJugador* primero = agregarJugadores();
	esperarAlPrimero(primero);
	notificarInicio();
	std::cout<<"Ahora lanzo el Mundo"<<std::endl;
	
	ContenedorProxies distribuidor(proxies);
	Mundo mundo;
	//(*proxies.begin())->enviarKeystrokesA(mundo.getMegaman());
	std::set<ProxyJugador*>::iterator it;
	for(it=proxies.begin(); it != proxies.end(); ++it){
		int pos = (*it)->obtenerPosicion();
		(*it)->enviarKeystrokesA(mundo.obtenerMegaman(pos));
	}
	
	SimuladorSinVentana sim(mundo,30,distribuidor);
	sim.start();
	std::cout<<"Ingresa cualquier cosa para matar el server sin avisarle a nadie"<<std::endl;
	std::string listo;
	std::cin>>listo;
	sim.join();
	
	matarConexiones();
	std::cout<<"chau servidor!!!"<<std::endl;
}
/**
 * Ideas para agregar robustez:
 * -Si un jugador se va?
 * -Si el primero se va?
 * */
ProxyJugador* Servidor::agregarJugadores(){
	aceptarJugadores = true;
	ProxyJugador* primero = NULL;;
	while(aceptarJugadores){
		try{
			ChannelSocket* channel = accepter.acceptConnection();
			ProxyJugador* nuevo = new ProxyJugador(channel);
			
			std::string id_usuario = nuevo->getUsuario();//bloquea hasta que se recibe el usuario por primera vez
			std::cout<<"Entra: "<<id_usuario<<std::endl;
			
			if(primero==NULL){
				primero=nuevo;
				//primero->enviarSosPrimero();
			}else{
				//nuevo->enviarNoSosPrimero();
			}
			nuevo->enviarPosicion(proxies.size());
			sleep(1);
			nuevo->enviarPosicion(proxies.size());//dos veces para asegurarme de que llegue
			
			nuevo->enviarListaJugadores(proxies);//se le envían los que ya estaban
			notificarLlegada(nuevo);//se notifica a los que ya estaban
			proxies.insert(nuevo);//se agrega el nuevo a la lista
			
			if(proxies.size()==4){
				aceptarJugadores=false;
				std::cout<<"Se alcanzo el limite de jugadores posibles"<<std::endl;
			}
			
		}catch(AcceptException& e){}
		
		if(primero!=NULL && primero->quiereIniciarPartida()){
			aceptarJugadores = false;
			std::cout<<"El primer jugador decidio iniciar"<<std::endl;
		}
	}
	std::cout<<"---agregarJugadores termina----"<<std::endl;
	return primero;
}
void Servidor::notificarLlegada(ProxyJugador* jugador){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarLlegada(jugador);
	}
}

Servidor::~Servidor(){
	
}
void Servidor::matarConexiones(){
	std::set<ProxyJugador*>::iterator it;
	for(it=proxies.begin(); it!=proxies.end(); ++it){
		ProxyJugador* a_borrar=*it;
		delete a_borrar;
	}
}

void Servidor::esperarAlPrimero(ProxyJugador* primero){
	while(!primero->quiereIniciarPartida()){
		//bloqueo el programa hasta que el primero envíe iniciar
	}
	std::cout<<"El primer jugador decidio iniciar"<<std::endl;
}
void Servidor::notificarInicio(){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->notificarInicio();
	}
}
