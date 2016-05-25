#include "Cliente.h"
#include <iostream>
#include "../sockets/Buffer.h"
#include "ReceptorCliente.h"
#include <cstdlib>
#include "../defines_protocolo.h"
#include "../../common/Lock.h"
#include "../../graficos/VentanaJuego.h"
#include "../../graficos/Camara.h"
#include "../../mundo/Mundo.h"
#include "../../mundo/Simulador.h"
#include "Jugador.h"

//Cliente::Cliente(){}
void Cliente::correr(){
	posicion=Desconocida;
	flag_iniciado=false;
	
	conectarse();
	
	ReceptorCliente receptor(socket,*this);
	Emisor emisor(socket);
	enviarID(emisor);
	
	while(obtenerPosicion()==Desconocida){
		//bloquear el hilo
	}
	
	if(obtenerPosicion()==NoPrimero){
		std::cout<<"No sos el primero"<<std::endl;
	}else{
		char respuesta='0';
		while(obtenerPosicion()==Primero && respuesta!='i'){
			std::cout<<"Usted es el primero. Ingrese i para iniciar la partida"<<std::endl;
			std::cin>>respuesta;
		}
		emisor.enviar(MENSAJE_INICIAR);//acá hay que meter la información del nivel
	}
	
	while(!iniciado()){//ahora, seas segundo o primero, te bloqueo hasta que recibis el iniciar
		//detener este hilo
	}
	
	
	std::cout<<"Se lanza la partida y la ventana aca!"<<std::endl;	
	iniciarVentana(emisor);
	//------------------ACÁ SE LANZA LA VENTANA Y LOS COHETES----------//
}
void Cliente::conectarse(){
	socket.connectTo("127.0.0.1",5002);
}
void Cliente::enviarID(const Emisor& emisor){
	
	std::string id;
	//std::cout<<"Introduzca su ID unica. Confio en usted"<<std::endl;
	//std::cin>>id;
	id = nombre;
	emisor.enviar(MENSAJE_ID,id);
	/*
	Buffer id_buf = Buffer::createString(std::string(MENSAJE_ID)+" " + id + "\n");
	socket.sendFixed(id_buf);
	* */
}

void Cliente::agregarEstaba(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Estaba el usuario "<<usuario<<std::endl;
}
void Cliente::agregarLlega(const std::string& usuario){
	Lock l(m_pantalla);
	std::cout<<"Llega el usuario "<<usuario<<std::endl;
}
void Cliente::definirSoyPrimero(bool soy_primero){
	Lock l(m_posicion);
	if(soy_primero){
		posicion=Primero;
	}else{
		posicion=NoPrimero;
	}
}

Posicion Cliente::obtenerPosicion(){
	Lock l(m_posicion);
	return posicion;
}
/*
void Cliente::enviarIniciar(const Emisor& emisor){
	Buffer men_buf = Buffer::createString(std::string(MENSAJE_INICIAR) + " \n");
	socket.sendFixed(men_buf);
}
*/
void Cliente::iniciar(){
	Lock l(m_iniciado);
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	Lock l(m_iniciado);
	return flag_iniciado;
}

void Cliente::iniciarVentana(const Emisor& emisor){
	Mundo mundo;
	Camara camara(mundo,b2Vec2(0,0),800,600);
	char* argv1="./holi";
	char** argv =&argv1;
	VentanaJuego ventana(mundo,camara,1,argv,"1");
	
	Simulador simulador(mundo,camara,33);
	Jugador jugador(mundo.getMegaman(), ventana, emisor);
	ventana.ejecutar();
	/*
	ventana.start();//sencillo volar este Thread
	ventana.join();
	* */
}

Cliente::Cliente(std::string n){
	nombre = n;
}
