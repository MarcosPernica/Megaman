#include "ReceptorCliente.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../defines_protocolo.h"
#include <glibmm/main.h>
#include <fstream>
#include "Cliente.h"

#define IMPLEMENTAR_CALL(tipo_mensaje) void ReceptorCliente::call ## tipo_mensaje(const std::string resto_mensaje)
#define AGREGAR_CALLBACK(tipo_mensaje) \
std::string mensaje_##tipo_mensaje(MENSAJE_##tipo_mensaje);\
Callback##tipo_mensaje* c_##tipo_mensaje = new Callback##tipo_mensaje(*this);\
agregarCallback(mensaje_##tipo_mensaje, c_##tipo_mensaje)

ReceptorCliente::ReceptorCliente(const ChannelSocket& chan, Cliente& cli):
								Receptor(chan),
								cliente(cli){
	a_inyectar = NULL;
	horario_ultimo_inyectado = clock();		
	//horario_ultima_recepcion = clock();	
	inyectado = true;
	//agrego la señal de timeout, porque idle es poco confiable/inestable
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &ReceptorCliente::onInyectar),100);//los milis son arbitrarios
	//configurar callbacks
	configurarCallbacks();
}
void ReceptorCliente::configurarCallbacks(){
	AGREGAR_CALLBACK(ESTABA);
	AGREGAR_CALLBACK(LLEGA);
	AGREGAR_CALLBACK(POSICION);
	AGREGAR_CALLBACK(INICIAR);
	AGREGAR_CALLBACK(INICIAR_ENVIO_FULLSNAPSHOT);
	AGREGAR_CALLBACK(ENVIO_SNAPSHOT);
	AGREGAR_CALLBACK(TERMINAR_ENVIO_FULLSNAPSHOT);
	AGREGAR_CALLBACK(INICIAR_ENVIO_NIVEL);
	AGREGAR_CALLBACK(ENVIO_NIVEL);
	AGREGAR_CALLBACK(TERMINAR_ENVIO_NIVEL);
	
	AGREGAR_CALLBACK(INICIAR_ENVIO_CONFIG);
	AGREGAR_CALLBACK(ENVIO_CONFIG);
	AGREGAR_CALLBACK(TERMINAR_ENVIO_CONFIG);
}



IMPLEMENTAR_CALL(ESTABA){
	cliente.agregarEstaba(resto_mensaje);
}

IMPLEMENTAR_CALL(LLEGA){
	cliente.agregarLlega(resto_mensaje);
}
IMPLEMENTAR_CALL(POSICION){
	std::istringstream ss(resto_mensaje);
	int posicion;
	ss>>posicion;
	cliente.definirPosicion(posicion);
}
IMPLEMENTAR_CALL(INICIAR){
	cliente.iniciar();
}

/**
 * Dejo los cout comentados ya que esta sección de código es crítica 
 * y pueden ser muy utiles a futuro
 * */
IMPLEMENTAR_CALL(INICIAR_ENVIO_FULLSNAPSHOT){
	//std::cout<<"----------------me llega un fulls de"<<resto_mensaje<<" a las "<<clock()<<std::endl;
	recibidas.clear();
}
IMPLEMENTAR_CALL(ENVIO_SNAPSHOT){
	recibidas.push_back(resto_mensaje);
}
IMPLEMENTAR_CALL(TERMINAR_ENVIO_FULLSNAPSHOT){
	if(a_inyectar!=NULL){
		//inyectar el full snapshot en cuanto pueda!
		Lock l(m_a_punto);
		
		/*
		std::vector<SnapshotSerializada>::iterator it;
		std::cout<<"----------mostrando fs recibida"<<std::endl;
		for(it = recibidas.begin(); it != recibidas.end(); ++it){
			std::cout<<*it<<std::endl;
		}
		std::cout<<"--------------finfs recibida"<<std::endl;
		*/
		//horario_ultima_recepcion=clock();
		a_punto_de_inyectar = FullSnapshot::desdeSerializada(recibidas);
		//a_punto_de_inyectar.mostrar();
	}
}
IMPLEMENTAR_CALL(INICIAR_ENVIO_NIVEL){
	iniciarDescargaNivel();
}
IMPLEMENTAR_CALL(ENVIO_NIVEL){
	recibirDatosNivel(resto_mensaje);
}
IMPLEMENTAR_CALL(TERMINAR_ENVIO_NIVEL){
	terminarDescargaNivel();
}

IMPLEMENTAR_CALL(INICIAR_ENVIO_CONFIG){
	std::string nombre_archivo = cliente.obtenerNombre()+SJuego::archivoConfig;
	stream_config.open(nombre_archivo.c_str(),std::ios_base::out|std::ios_base::trunc);//out:salida trunc:elimina todo lo que había antes
}
IMPLEMENTAR_CALL(ENVIO_CONFIG){
	stream_config<<resto_mensaje<<std::endl;
}
IMPLEMENTAR_CALL(TERMINAR_ENVIO_CONFIG){
	stream_config.close();
	SJuego::attr.cargar(cliente.obtenerNombre()+SJuego::archivoConfig);
}

void ReceptorCliente::inyectarFullSnapshotsA(Mundo* a){
	a_inyectar = a;
}
bool ReceptorCliente::onInyectar(){
	if(a_inyectar!=NULL){
		Lock l(m_a_punto);
		clock_t horario_creacion = a_punto_de_inyectar.obtenerHorarioCreacion();
		if(horario_ultimo_inyectado<horario_creacion || (horario_ultimo_inyectado-horario_creacion)>5000000){
			inyectado = true;
			/*
			FullSnapshot fs = FullSnapshot::desdeSerializada(a_punto_de_inyectar);
			fs.mostrar();
			* */
			//a_punto_de_inyectar.mostrar();
			/*
			timespec antes_de_inyectar;
			clock_gettime(CLOCK_REALTIME,&antes_de_inyectar);
			*/
			a_inyectar->inyectarSnapshot(a_punto_de_inyectar);
			
			timespec luego_de_inyectar;
			clock_gettime(CLOCK_REALTIME,&luego_de_inyectar);
//			std::cout<<"estoy inyectando un fs que recibi a las "<<horario_creacion<<"son las "<<clock()<<"en segundos la antigüedad es: "<<(float)(horario_creacion-clock())/CLOCKS_PER_SEC<<std::endl;
//			std::cout<<"s desde la ultima inyeccion: "<<(float)(clock()-horario_ultima_inyeccion)/CLOCKS_PER_SEC<<std::endl;
//			std::cout<<"Nanos que tardé en inyectar: "<<luego_de_inyectar.tv_nsec-antes_de_inyectar.tv_nsec<<std::endl;
			horario_ultimo_inyectado = horario_creacion;
			horario_ultima_inyeccion=clock();
			
		}
	}
	return true;
}
void ReceptorCliente::iniciarDescargaNivel(){
	std::string nombre_archivo = cliente.obtenerNombre()+"nivel.xml";
	stream_nivel.open(nombre_archivo.c_str(),std::ios_base::out|std::ios_base::trunc);//out:salida trunc:elimina todo lo que había antes
}
void ReceptorCliente::terminarDescargaNivel(){
	stream_nivel.close();
}

void ReceptorCliente::recibirDatosNivel(const std::string& datos){
	stream_nivel<<datos<<std::endl;
}

ReceptorCliente::~ReceptorCliente(){
	std::cout<<"Destructor de ReceptorCliente!"<<std::endl;
}
