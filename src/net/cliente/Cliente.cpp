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

//Cliente::Cliente(){}
void Cliente::correr(){
	posicion=-1;
	flag_iniciado=false;
	
	conectarse();
	
	ReceptorCliente receptor(socket,*this);
	Emisor emisor(socket);
	enviarID(emisor);
	
	while(obtenerPosicion()==-1){
		//bloquear el hilo
	}
	std::cout<<"La posicion  que vino es: "<<obtenerPosicion()<<std::endl;
	if(obtenerPosicion()>0){
		std::cout<<"No sos el primero"<<std::endl;
	}else{
		
		//comentar esto de abajo hace que se deje de esperar la i
		char respuesta='0';
		while(obtenerPosicion()==0 && respuesta!='i'){
			std::cout<<"Usted es el primero. Ingrese i para iniciar la partida"<<std::endl;
			std::cin>>respuesta;
		}
		//(comentar hasta acá)
		
		emisor.enviar(MENSAJE_INICIAR);//acá hay que meter la información del nivel
	}
	
	while(!iniciado()){//ahora, seas segundo o primero, te bloqueo hasta que recibis el iniciar
		//detener este hilo
	}
	
	
	std::cout<<"Se lanza la partida y la ventana aca!"<<std::endl;	
	iniciarVentana(emisor, receptor);
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
void Cliente::definirPosicion(int pos){
	if( pos<0 || pos>3){
		throw CustomException("Las posiciones deben estar entre 0 y 3");
	}
	Lock l(m_posicion);
	posicion = pos;
}
int Cliente::obtenerPosicion(){
	Lock l(m_posicion);
	return posicion;
}
void Cliente::iniciar(){
	Lock l(m_iniciado);
	flag_iniciado=true;
}

bool Cliente::iniciado(){
	Lock l(m_iniciado);
	return flag_iniciado;
}

void Cliente::iniciarVentana(const Emisor& emisor, ReceptorCliente& receptor){
	Mundo mundo;
	Camara camara(mundo,b2Vec2(0,0),800,600);
	char* argv1 = "./holi";
	char** argv = &argv1;
	VentanaJuego ventana(mundo,camara,1,argv,"1");
	
	
	Jugador jugador(mundo.obtenerMegaman(posicion), ventana, emisor);
	receptor.inyectarFullSnapshotsA(&mundo);
	Simulador simulador(mundo,camara,33);
	ventana.ejecutar();
	receptor.inyectarFullSnapshotsA(NULL);////////esta!!!!!!!!!!!!
	/*
	ventana.start();//sencillo volar este Thread
	ventana.join();
	* */
}

Cliente::Cliente(std::string n){
	nombre = n;
}
