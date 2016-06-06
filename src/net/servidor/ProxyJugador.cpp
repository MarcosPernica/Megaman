#include "ProxyJugador.h"
#include <iostream>
#include "../../graficos/VentanaJuego.h"

#include "../sockets/Buffer.h"
#include "../defines_protocolo.h"
#include "../../common/exceptions.h"
#include "../../common/Lock.h"
#include <ctime>
/*
ProxyJugador::ProxyJugador(const std::string& id, ChannelSocket* chan)
							:channel(chan),
							id_usuario(id){}
*/
void ProxyJugador::enviarListaJugadores(const std::set<ProxyJugador*>& lista){
	std::set<ProxyJugador*>::iterator it;
	for( it=lista.begin(); it != lista.end(); ++it){
		notificarEstaba(*it);
	}
}

void ProxyJugador::notificarLlegada(ProxyJugador* jugador){
	try{
		emisor.enviar(MENSAJE_LLEGA,jugador->getUsuario());
	}catch(CException& e){
		informarEstaRota();
	}
}
void ProxyJugador::notificarEstaba(ProxyJugador* jugador){
	try{
		emisor.enviar(MENSAJE_ESTABA,jugador->getUsuario());
	}catch(CException& e){
		informarEstaRota();
	}
}

void ProxyJugador::ejecutarControlSobreMegaman(){
	Lock l(m_controles_recibidos);
	while(controles_recibidos.size()!=0){
		std::string tipo_mensaje = controles_recibidos.front();
		controles_recibidos.pop();
		
		if(controlado != NULL){
			if(tipo_mensaje == MENSAJE_KEY_1){
				controlado->seleccionarArma(1);
			}else if(tipo_mensaje == MENSAJE_KEY_2){
				controlado->seleccionarArma(2);
			}else if(tipo_mensaje == MENSAJE_KEY_3){
				controlado->seleccionarArma(3);
			}else if(tipo_mensaje == MENSAJE_KEY_4){
				controlado->seleccionarArma(4);
			}else if(tipo_mensaje == MENSAJE_KEY_5){
				controlado->seleccionarArma(5);
			}else if(tipo_mensaje == MENSAJE_KEY_Z){
				controlado->saltar();
				std::cout<<"Z!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_X){
				controlado->disparar();
				//std::cout<<"X!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_UP){
				controlado->subirEscalera();
				//std::cout<<"UP!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_DN){
				controlado->bajarEscalera();
				//std::cout<<"DN!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_RIGHT){
				controlado->mirarDerecha();
				controlado->correr();
				std::cout<<"right!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_LEFT){
				controlado->mirarIzquierda();
				controlado->correr();
				std::cout<<"left!"<<std::endl;
			}else if(tipo_mensaje == MENSAJE_KEY_UP_LIBERADA){
				controlado->pararMovimientoEscalera();
			}else if(tipo_mensaje == MENSAJE_KEY_DN_LIBERADA){
				controlado->pararMovimientoEscalera();
			}else if(tipo_mensaje == MENSAJE_KEY_RIGHT_LIBERADA){
				controlado->dejarCorrer();
			}else if(tipo_mensaje == MENSAJE_KEY_LEFT_LIBERADA){
				controlado->dejarCorrer();
			}
		}
	}
}

void ProxyJugador::ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	//std::cout<<"el mensaje que llega es: "<<tipo_mensaje<<std::endl;
	
	if(tipo_mensaje == MENSAJE_ID){
		Lock l(m_id);
		id_usuario = resto_mensaje;
	}else if(tipo_mensaje == MENSAJE_INICIAR){
		setQuiereIniciarPartida();
	}else if(controlado != NULL){
		if(tipo_mensaje == MENSAJE_KEY_Z){
			timespec ahora;
			clock_gettime(CLOCK_REALTIME,&ahora);
			std::cout<<"Llega la Z a las "<<ahora.tv_nsec<<std::endl;
		}
		Lock l(m_controles_recibidos);
		controles_recibidos.push(tipo_mensaje);
		//std::cout<<"Llegó un mensaje: "<<tipo_mensaje<<std::endl;
	}
}

ProxyJugador::ProxyJugador(ChannelSocket* chan)
							:Receptor(*chan),
							 channel(chan),
							 conexion_sana(true),
							 quiero_iniciar(false),
							 emisor(*chan){
	controlado = NULL;
}
							 
bool ProxyJugador::tengoUsuario(){
	Lock l(m_id);
	return (id_usuario.length()>0);
}
const std::string& ProxyJugador::getUsuario(){
	while(!tengoUsuario()){
		//std::cout<<"El programa esta bloqueado mientras espero el nombre de usuario. Que lastima!"<<std::endl;
		//bloqueo el programa!	
		//...y entonces el hilo mágico nos saca de este loop
	}
	Lock l(m_id);
	return id_usuario;
}

ProxyJugador::~ProxyJugador(){
	delete channel;
}
bool ProxyJugador::getEstaSana(){
	Lock l(m_conexion_sana);
	return conexion_sana && getRecepcionSana();
}

void ProxyJugador::informarEstaRota(){
	Lock l(m_conexion_sana);
	conexion_sana = false;
}
bool ProxyJugador::quiereIniciarPartida(){
	Lock l(m_quiero_iniciar);
	return quiero_iniciar;
}
void ProxyJugador::setQuiereIniciarPartida(){
	Lock l(m_quiero_iniciar);
	quiero_iniciar = true;
}
void ProxyJugador::notificarInicio(){
	emisor.enviar(MENSAJE_INICIAR);
	Lock l(m_quiero_iniciar);
	quiero_iniciar = false;//esto prepara la próxima pantalla de selección de niveles
}

void ProxyJugador::enviarKeystrokesA(Megaman* a){
	controlado = a;
}

void ProxyJugador::enviar(const FullSnapshot& full_snapshot){

	const FSSerializada serializada = full_snapshot.serializar();
	FSSerializada::const_iterator it;
	
	emisor.enviar(MENSAJE_INICIAR_ENVIO_FULLSNAPSHOT,full_snapshot.obtenerHorarioCreacion());
	
	//std::cout<<"-----------ENVIANDO  FULL SNAPSHOT------------"<<std::endl;
	for(it = serializada.begin(); it!=serializada.end(); ++it){
		emisor.enviar(MENSAJE_ENVIO_SNAPSHOT,*it);
		//std::cout<<*it<<std::endl;
	}
	
	timespec ahora;
	clock_gettime(CLOCK_REALTIME, &ahora);
	long nanos_ahora = ahora.tv_nsec;
	std::cout<<"Enviando un full snapshot de"<<full_snapshot.obtenerHorarioCreacion()<<" a las "<<clock()<<". Desde el ultimo pasaron: "<< ((double)(nanos_ahora - nanos_ultimo_envio))/1000000000000<<std::endl;
	
	nanos_ultimo_envio = nanos_ahora;
	emisor.enviar(MENSAJE_TERMINAR_ENVIO_FULLSNAPSHOT);
}

void ProxyJugador::enviarPosicion(uint posicion){
	emisor.enviar(MENSAJE_POSICION,(int)posicion);
	this->posicion = posicion;
}
uint ProxyJugador::obtenerPosicion(){
	return posicion;
}
