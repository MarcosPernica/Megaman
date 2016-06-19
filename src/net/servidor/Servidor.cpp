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
bool Servidor::algunNivelSeleccionado(){
	Lock l(m_nivel);
	return nivel!=0;
}

void Servidor::esperarSeleccionNivel(){
	Lock l(cv_nivelElegido);
	while(!algunNivelSeleccionado()){
		cv_nivelElegido.wait();
	}
}

void Servidor::esperarFinNivel(){
	Lock l(cv_nivelContinua);
	while(nivelContinua){
		cv_nivelContinua.wait();
	}
}

void Servidor::alcanzadoLimiteJugadores(){
	//aceptador.join();
}
void Servidor::ejecutar(){
	while(true){
		//espero a que me digan qué nivel correr
		esperarSeleccionNivel();
		
		//arranco el nivel
		if(true){
			Lock l(m_nivel);
			ejecutarNivel(nivel);
		}
		
		//espero a que termine el nivel
		/*
		while(true){
			sleep(0.5);
			if(!nivelContinua) break;//bool es atomico
		}
		**/
		esperarFinNivel();
		
		//guardo las estadisticas
		EstadisticasMundo& correctas = mundo->obtenerEstadisticas();
		//estadisticas.copiarDe(correctas);
		estadisticas = correctas;
		std::cout<<"Vidas(estadisticas):"<<estadisticas.vidasDe(0)<<std::endl;
		std::cout<<"Vidas(correctas):"<<correctas.vidasDe(0)<<std::endl;
		
		//termino la simulacion
		desconectarProxiesDeMegamanes();
		
		simulador->join();
		delete simulador;
		simulador = NULL;
		
		delete mundo;
		mundo = NULL;
		
		if(true){
			Lock l(m_nivel);
			nivel = 0;
		}
		
		std::cout<<"A dormir!"<<std::endl;
		sleep(1);
	}
	
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
	mundo->setEstadisticas(estadisticas);
	
	
	conectarProxiesConMegamanes();
	
	simulador = new SimuladorSinVentana(*mundo,20,contenedor,new CallbackFin(*this));
	simulador->start();
}


void Servidor::iniciar(char nivel){
	Lock l_cv(cv_nivelElegido);
	if(!algunNivelSeleccionado()){//no estoy seguro de que haga falta este if
		cv_nivelElegido.broadcast();
	}
	alcanzadoLimiteJugadores();//basta de aceptar jugadores
	Lock l(m_nivel);
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
	nivelContinua = false;//no hace falta proteger bools
	std::cout<<"----------------fin nivel--------------"<<std::endl;
	contenedor.distribuirFinNivel();
	Lock l(cv_nivelContinua);
	cv_nivelContinua.broadcast();
}
