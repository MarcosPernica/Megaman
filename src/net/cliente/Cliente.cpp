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
#include "../../common/exceptions.h"
#include "../Debug.h"

//Cliente::Cliente(){}
void Cliente::correr(){
	posicion=-1;
	flag_iniciado=false;
	
	
	conectarse();
	
	ReceptorCliente receptor(socket,*this);
	Emisor emisor(socket);
	enviarID(emisor);

	#ifndef DEBUG
	while(obtenerPosicion()==-1){
		//detener
	}
	//std::cout<<"La posicion  que vino es: "<<obtenerPosicion()<<std::endl;
	if(obtenerPosicion()>0){
		std::cout<<"No sos el primero"<<std::endl;
	}else{
		
		//comentar esto de abajo hace que se deje de esperar la i
		char respuesta='0';
		while(obtenerPosicion()==0 && !(respuesta>='1' && respuesta<='5')){
			std::cout<<"Usted es el primero. Ingrese un número entre 1 y 5 inclusive para iniciar ese nivel"<<std::endl;
			std::cin>>respuesta;
		}
		//(comentar hasta acá)
		std::string nivel_enviar;
		nivel_enviar+=respuesta;
		emisor.enviar(MENSAJE_INICIAR,nivel_enviar);
	}
	
	while(!iniciado()){//ahora, seas segundo o primero, te bloqueo hasta que recibis el iniciar
		//detener este hilo
	}

	#endif

	std::cout<<"Se lanza la partida y la ventana aca!"<<std::endl;	
	iniciarVentana(emisor, receptor);
	//terminó la ventana...
	socket.closeS();
	
}
void Cliente::conectarse(){
	#ifndef DEBUG
	socket.connectTo("127.0.0.1",10020);
	#endif
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
void Cliente::definirPosicion(int pos){
	if( pos<0 || pos>3){
		throw CustomException("Las posiciones deben estar entre 0 y 3");
	}
	Lock l(m_posicion);
	posicion = pos;
}
int Cliente::obtenerPosicion(){
	#ifndef DEBUG
	Lock l(m_posicion);
	return posicion;
	#else
	return 0;
	#endif
}
void Cliente::iniciar(){
	Lock l(m_iniciado);
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	Lock l(m_iniciado);
	return flag_iniciado;
}
const std::string& Cliente::obtenerNombre(){
	return nombre;
}

void Cliente::iniciarVentana(const Emisor& emisor, ReceptorCliente& receptor){
	char* argv1 = "./holi";
	char** argv = &argv1;
	Mundo mundo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600),b2Vec2(0,0),nombre+"nivel.xml");
	VentanaJuego ventana(1,argv,"1", mundo);
	
	
	Jugador jugador(mundo.obtenerMegaman(obtenerPosicion()), ventana, emisor);
	#ifndef DEBUG
	receptor.inyectarFullSnapshotsA(&mundo);
	#endif
	Simulador simulador(mundo,33);
	ventana.ejecutar();//se lanza la ventana
	receptor.inyectarFullSnapshotsA(NULL);
}

Cliente::Cliente(std::string n){
	nombre = n;
}
