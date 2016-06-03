#include "ReceptorCliente.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../defines_protocolo.h"
#include <glibmm/main.h>

ReceptorCliente::ReceptorCliente(const ChannelSocket& chan, Cliente& cli):
								Receptor(chan),
								cliente(cli){
	a_inyectar = NULL;
	horario_ultimo_inyectado = clock();		
	//horario_ultima_recepcion = clock();	
	inyectado = true;
}


void ReceptorCliente::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	//std::cout<<"estoy recibiendo un mensaje "<<tipo_mensaje<<std::endl;
	if(tipo_mensaje==MENSAJE_ESTABA){
		cliente.agregarEstaba(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_LLEGA){
		cliente.agregarLlega(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_POSICION){
		std::istringstream ss(resto_mensaje);
		int posicion;
		ss>>posicion;
		cliente.definirPosicion(posicion);
	}else if(tipo_mensaje==MENSAJE_INICIAR){
		cliente.iniciar();
	}else if(tipo_mensaje==MENSAJE_INICIAR_ENVIO_FULLSNAPSHOT){
		//std::cout<<"----------------me llega un fulls"<<std::endl;
		//std::cout<<"----------------me llega un fulls de"<<resto_mensaje<<" a las "<<clock()<<std::endl;
		recibidas.clear();
	}else if(tipo_mensaje==MENSAJE_ENVIO_SNAPSHOT){
		//std::cout<<resto_mensaje<<std::endl;
		
		recibidas.push_back(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_TERMINAR_ENVIO_FULLSNAPSHOT){
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
			
			if(inyectado){
				Glib::signal_idle().connect(sigc::mem_fun(*this, &ReceptorCliente::onInyectar));
				inyectado = false;
			}
			
			//a_punto_de_inyectar.mostrar();
		}
	}
}

void ReceptorCliente::inyectarFullSnapshotsA(Mundo* a){
	a_inyectar = a;
}
bool ReceptorCliente::onInyectar(){
	if(a_inyectar!=NULL){
		Lock l(m_a_punto);
		clock_t horario_creacion = a_punto_de_inyectar.obtenerHorarioCreacion();
		if(horario_ultimo_inyectado<horario_creacion){
			inyectado = true;
			/*
			FullSnapshot fs = FullSnapshot::desdeSerializada(a_punto_de_inyectar);
			fs.mostrar();
			* */
			//a_punto_de_inyectar.mostrar();
			a_inyectar->inyectarSnapshot(a_punto_de_inyectar);
			//std::cout<<"estoy inyectando un fs que recibi a las "<<horario_creacion<<"son las "<<clock()<<"en segundos la antigüedad es: "<<(float)(horario_creacion-clock())/CLOCKS_PER_SEC<<std::endl;
			//std::cout<<"s desde la ultima inyeccion: "<<(float)(clock()-horario_ultima_inyeccion)/CLOCKS_PER_SEC<<std::endl;
			horario_ultimo_inyectado = horario_creacion;
			horario_ultima_inyeccion=clock();
		}
	}
	return true;
}
