#include "Servidor.h"
#include <iostream>
#include "../../common/exceptions.h"
#include <ctime>
#include "../../mundo/Mundo.h"
#include "ContenedorProxies.h"
#include "../../graficos/Proporcionador.h" 
#include <fstream>
#include <sstream>
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
			aceptador(SJuego::preconf.port,4),
			contenedor(new CallbackIniciarPartida(*this), new CallbackLimite(*this) ),
			//contenedor(NULL, NULL),
			nivel(0),
			simulador(NULL),
			nivelContinua(true),
			continuarEjecucion(true),
			mundo(NULL){
				
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
void Servidor::liberarRecursos(){
	//termino la simulacion
	desconectarProxiesDeMegamanes();
	if(simulador!=NULL){
		simulador->join();
		delete simulador;
		simulador = NULL;
	}
	if(mundo == NULL){
		delete mundo;
		mundo = NULL;
	}
}
void Servidor::finalizarNivel(){
	//guardo las estadisticas
	EstadisticasMundo& correctas = mundo->obtenerEstadisticas();
	//estadisticas.copiarDe(correctas);
	estadisticas = correctas;
	
	//termino la simulacion
	liberarRecursos();
	
	//desconectarProxiesDeMegamanes();
	/*
	simulador->join();
	delete simulador;
	simulador = NULL;
	*/
	/*
	delete mundo;
	mundo = NULL;
	*/
	if(true){
		Lock l(m_nivel);
		nivel = 0;
	}
}
void Servidor::ejecutar(){
	while(continuarEjecucion){
		switch(cola.pop()){
			case INICIO_NIVEL :
				if(true){
					Lock l(m_nivel);
					ejecutarNivel(nivel);
				}
				break;
			case FIN_NIVEL :
				finalizarNivel();
				break;
			case SALIDA_FORZADA :
				liberarRecursos();
				continuarEjecucion = false;
				break;
			
		}
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
	contenedor.notificarInicio();
	
	std::ostringstream nombre_nivel;
	nombre_nivel<<"niveles/nivel";
	nombre_nivel<<(char)nivel;
	nombre_nivel<< ".xml";
	
	mundo = new Mundo(Proporcionador::renderAMundo(800),Proporcionador::renderAMundo(600),b2Vec2(0,0),nombre_nivel.str().c_str(),contenedor.cantidadJugadores());
	mundo->setEstadisticas(estadisticas);
	
	
	conectarProxiesConMegamanes();
	
	simulador = new SimuladorSinVentana(*mundo,20,contenedor,new CallbackFin(*this));
	simulador->start();
}


void Servidor::iniciar(char nivel){
	alcanzadoLimiteJugadores();//basta de aceptar jugadores
	{
		Lock l(m_nivel);
		this->nivel = nivel;
	}
	cola.push(INICIO_NIVEL);
}

Servidor::~Servidor(){
	liberarRecursos();
	aceptador.join();
	/*
	delete simulador;
	delete mundo;
	* */
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
	contenedor.distribuirFinNivel();
	cola.push(FIN_NIVEL);
}

void Servidor::cerrar(){
	cola.push(SALIDA_FORZADA);
}
