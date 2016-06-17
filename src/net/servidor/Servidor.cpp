#include "Servidor.h"
#include <iostream>
#include "../../common/exceptions.h"
#include <ctime>
#include "../../mundo/Mundo.h"
#include "../../mundo/SimuladorSinVentana.h"
#include "ContenedorProxies.h"
#include "../../graficos/Dibujable.h" 
#include <fstream>
/*
void Servidor::copiarParaTiny(char nivel){
	std::string nombre_nivel("niveles/nivel");
	nombre_nivel+=nivel;
	nombre_nivel+=".xml";
	
	std::ifstream src(nombre_nivel.c_str(),std::ios::binary);
	std::ofstream dst("nivel_tiny.xml",std::ios::binary);
	dst<<src.rdbuf();
	dst.close();
}
*/
void Servidor::nueva(ChannelSocket* nuevo_channel){
	contenedor.nuevaConexion(nuevo_channel);
}

Servidor::Servidor():
			aceptador(10020,4),
			contenedor(new CallbackIniciarPartida(*this), new CallbackLimite(*this) ),
			nivel(0){
				
				aceptador.agregarCallback(new CallbackAceptador(*this));
				aceptador.start();
				//sleep(10);
}


void Servidor::alcanzadoLimiteJugadores(){
	//aceptador.join();
}
void Servidor::ejecutar(){
	while(true){
		sleep(0.5);
		Lock l(m_nivel);
		if(nivel!=0) break;
	}
	Lock l(m_nivel);
	ejecutarNivel(nivel);
}
void Servidor::ejecutarNivel(char nivel){
	contenedor.enviarNivel(nivel);
	std::cout<<nivel<<std::endl;
	contenedor.notificarInicio();
	
	std::ostringstream nombre_nivel;
	nombre_nivel<<"niveles/nivel";
	nombre_nivel<<(char)nivel;
	nombre_nivel<< ".xml";
	std::cout<<"El nombre del nivel es: "<<nombre_nivel.str()<<std::endl;
	
	std::cout<<"Ahora lanzo el Mundo"<<std::endl;
	Mundo mundo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600),b2Vec2(0,0),nombre_nivel.str().c_str(),contenedor.cantidadJugadores());
	
	
	std::vector<ProxyJugador*> jugadores = contenedor.obtenerJugadores();
	
	std::vector<ProxyJugador*>::iterator it;
	for(it = jugadores.begin(); it!=jugadores.end(); ++it){
		int pos = (*it)->obtenerPosicion();
		(*it)->enviarKeystrokesA(mundo.obtenerMegaman(pos));
	}
	
	/*
	std::set<ProxyJugador*>::iterator it;
	for(it=proxies.begin(); it != proxies.end(); ++it){
		int pos = (*it)->obtenerPosicion();
		(*it)->enviarKeystrokesA(mundo.obtenerMegaman(pos));
	}
	*/
	
	SimuladorSinVentana sim(mundo,20,contenedor);
	sim.start();
	std::cout<<"Ingresa cualquier cosa para matar el server sin avisarle a nadie"<<std::endl;
	std::string listo;
	std::cin>>listo;
	sim.join();
	
	contenedor.matarConexiones();
	std::cout<<"chau servidor!!!"<<std::endl;
}


void Servidor::iniciar(char nivel){
	Lock l(m_nivel);
	alcanzadoLimiteJugadores();//basta de aceptar jugadores
	
	this->nivel = nivel;
}

Servidor::~Servidor(){
	
}
void CallbackIniciarPartida::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	serv.iniciar(resto_mensaje[0]);
};

void CallbackLimite::limiteAlcanzado(){
	serv.alcanzadoLimiteJugadores();
}

void CallbackAceptador::nueva(ChannelSocket* nuevo_channel){
	serv.nueva(nuevo_channel);
}
