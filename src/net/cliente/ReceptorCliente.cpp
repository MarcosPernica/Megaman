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
}


void ReceptorCliente::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(tipo_mensaje==MENSAJE_ESTABA){
		cliente.agregarEstaba(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_LLEGA){
		cliente.agregarLlega(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_SOS_PRIMERO){
		cliente.definirSoyPrimero(true);
	}else if(tipo_mensaje==MENSAJE_NO_SOS_PRIMERO){
		cliente.definirSoyPrimero(false);
	}else if(tipo_mensaje==MENSAJE_INICIAR){
		cliente.iniciar();
	}else if(tipo_mensaje==MENSAJE_INICIAR_ENVIO_FULLSNAPSHOT){
		//std::cout<<"----------------me llega un fulls"<<std::endl;
		recibidas.clear();
	}else if(tipo_mensaje==MENSAJE_ENVIO_SNAPSHOT){
		//std::cout<<resto_mensaje<<std::endl;
		recibidas.push_back(resto_mensaje);
	}else if(tipo_mensaje==MENSAJE_TERMINAR_ENVIO_FULLSNAPSHOT){
		//std::cout<<"----------------esta terminando el fulls"<<std::endl;
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
			* */
			a_punto_de_inyectar = FullSnapshot::desdeSerializada(recibidas);
			Glib::signal_idle().connect(sigc::mem_fun(*this, &ReceptorCliente::onInyectar));
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
		/*
		FullSnapshot fs = FullSnapshot::desdeSerializada(a_punto_de_inyectar);
		fs.mostrar();
		* */
		//a_punto_de_inyectar.mostrar();
		a_inyectar->inyectarSnapshot(a_punto_de_inyectar);
	}
	return true;
}
