#include "Servidor.h"
#include <iostream>
#include "../../common/exceptions.h"
#include <ctime>
#include "../../mundo/Mundo.h"
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
			nivel(0),
			simulador(NULL),
			nivelContinua(true){
				
				aceptador.agregarCallback(new CallbackAceptador(*this));
				aceptador.start();
				//sleep(10);
}


void Servidor::alcanzadoLimiteJugadores(){
	//aceptador.join();
}
void Servidor::ejecutar(){
	
	//espero a que me digan qué nivel correr
	while(true){
		sleep(0.5);
		Lock l(m_nivel);
		if(nivel!=0) break;
	}
	
	//arranco el nivel
	Lock l(m_nivel);
	ejecutarNivel(nivel);
	
	//espero a que termine el nivel
	while(true){
		sleep(0.5);
		Lock l(m_nivelContinua);
		if(!nivelContinua) break;
	}
	
	//termino la simulacion
	desconectarProxiesDeMegamanes();
	
	simulador->join();
	delete simulador;
	simulador = NULL;
	
	delete mundo;
	mundo = NULL;
	
	//termino los proxies porque se termina el programa
	contenedor.matarConexiones();
}
void Servidor::conectarProxiesConMegamanes(){
	std::vector<ProxyJugador*> jugadores = contenedor.obtenerJugadores();
	std::vector<ProxyJugador*>::iterator it;
	for(it = jugadores.begin(); it!=jugadores.end(); ++it){
		int pos = (*it)->obtenerPosicion();
		(*it)->enviarKeystrokesA(mundo->obtenerMegaman(pos));
	}
}
void Servidor::desconectarProxiesDeMegamanes(){
	std::vector<ProxyJugador*> jugadores = contenedor.obtenerJugadores();
	std::vector<ProxyJugador*>::iterator it;
	for(it = jugadores.begin(); it!=jugadores.end(); ++it){
		int pos = (*it)->obtenerPosicion();
		(*it)->enviarKeystrokesA(NULL);
	}
}
void Servidor::ejecutarNivel(char nivel){
	nivelContinua = true;
	
	contenedor.enviarNivel(nivel);
	std::cout<<nivel<<std::endl;
	contenedor.notificarInicio();
	
	std::ostringstream nombre_nivel;
	nombre_nivel<<"niveles/nivel";
	nombre_nivel<<(char)nivel;
	nombre_nivel<< ".xml";
	std::cout<<"El nombre del nivel es: "<<nombre_nivel.str()<<std::endl;
	
	std::cout<<"Ahora lanzo el Mundo"<<std::endl;
	mundo = new Mundo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600),b2Vec2(0,0),nombre_nivel.str().c_str(),contenedor.cantidadJugadores());
	
	
	conectarProxiesConMegamanes();
	
	simulador = new SimuladorSinVentana(*mundo,20,contenedor,new CallbackFin(*this));
	simulador->start();
}


void Servidor::iniciar(char nivel){
	Lock l(m_nivel);
	alcanzadoLimiteJugadores();//basta de aceptar jugadores
	
	this->nivel = nivel;
}

Servidor::~Servidor(){
	delete simulador;
	delete mundo;
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

void Servidor::finNivel(){
	Lock l(m_nivelContinua);
	nivelContinua = false;
}
