#include "ProxyJugador.h"
#include <iostream>
#include "../../graficos/VentanaJuego.h"
#include "Logger.h"
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
void ProxyJugador::enviarListaJugadores(const std::vector<ProxyJugador*>& lista){
	std::vector<ProxyJugador*>::const_iterator it;
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
			}else if(tipo_mensaje == MENSAJE_KEY_X){
				controlado->disparar();
			}else if(tipo_mensaje == MENSAJE_KEY_UP){
				controlado->subirEscalera();
			}else if(tipo_mensaje == MENSAJE_KEY_DN){
				controlado->bajarEscalera();
			}else if(tipo_mensaje == MENSAJE_KEY_RIGHT){
				controlado->mirarDerecha();
				controlado->correr();
			}else if(tipo_mensaje == MENSAJE_KEY_LEFT){
				controlado->mirarIzquierda();
				controlado->correr();
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

void ProxyJugador::recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
	if(tipo_mensaje == MENSAJE_ID){
		{
			Lock l(m_id);
			id_usuario = resto_mensaje;
		}
		try{
			emisor.enviarConfiguracion();
		}catch(CException& e){
			informarEstaRota();
		}
		
		{
			Lock l(cv_tengoUsuario);
			cv_tengoUsuario.broadcast();
		}
	}else if(tipo_mensaje == MENSAJE_INICIAR){//YA NO LLEGA!!!!!
		setQuiereIniciarPartida(resto_mensaje[0]);//no es el número de nivel, sino el caracter que lo representa!
	}else if(controlado != NULL){
		Lock l(m_controles_recibidos);
		controles_recibidos.push(tipo_mensaje);
	}
}

ProxyJugador::ProxyJugador(ChannelSocket* chan)
							:Receptor(*chan),
							 channel(chan),
							 conexion_sana(true),
							 quiero_iniciar('0'),
							 emisor(*chan),
							 controlado(NULL){
	CallbackProxyJugador* callback=new CallbackProxyJugador(*this);
	
	agregarCallback(MENSAJE_ID,callback);
	
	agregarCallback(MENSAJE_KEY_1,callback);
	agregarCallback(MENSAJE_KEY_2,callback);
	agregarCallback(MENSAJE_KEY_3,callback);
	agregarCallback(MENSAJE_KEY_4,callback);
	agregarCallback(MENSAJE_KEY_5,callback);
	agregarCallback(MENSAJE_KEY_UP,callback);
	agregarCallback(MENSAJE_KEY_DN,callback);
	agregarCallback(MENSAJE_KEY_RIGHT,callback);
	agregarCallback(MENSAJE_KEY_LEFT,callback);
	agregarCallback(MENSAJE_KEY_Z,callback);
	agregarCallback(MENSAJE_KEY_X,callback);
	
	agregarCallback(MENSAJE_KEY_UP_LIBERADA,callback);
	agregarCallback(MENSAJE_KEY_DN_LIBERADA,callback);
	agregarCallback(MENSAJE_KEY_RIGHT_LIBERADA,callback);
	agregarCallback(MENSAJE_KEY_LEFT_LIBERADA,callback);
	
	start();
}
							 
bool ProxyJugador::tengoUsuario(){
	Lock l(m_id);
	return (id_usuario.length()>0);
}
const std::string& ProxyJugador::getUsuario(){
	Lock l_cv(cv_tengoUsuario);
	while(!tengoUsuario()){
		cv_tengoUsuario.wait();
		//El programa esta bloqueado mientras espero el nombre de usuario.
	}
	Lock l(m_id);
	return id_usuario;
}

ProxyJugador::~ProxyJugador(){
	channel->closeS();
	delete channel;
	channel = NULL;
}

bool ProxyJugador::getEstaSana(){
	Lock l(m_conexion_sana);
	return conexion_sana && getRecepcionSana();
}

void ProxyJugador::informarEstaRota(){
	Lock l(m_conexion_sana);
	if(conexion_sana){
		std::cout<<"Ciente "<<getUsuario()<<" desconectado"<<std::endl;
		serverLog.log("Cliente "+getUsuario()+" desconectado");
	}
	
	conexion_sana = false;
}
bool ProxyJugador::quiereIniciarPartida(){
	Lock l(m_quiero_iniciar);
	return quiero_iniciar!='0';
}
char ProxyJugador::nivelQueEligio(){
	if(!quiereIniciarPartida()) throw CustomException("Este jugador no quiere iniciar la partida entonces no eligio ningun nivel");
	Lock l(m_quiero_iniciar);
	return quiero_iniciar;
}

void ProxyJugador::setQuiereIniciarPartida(char nivel){
	if(!(nivel>='1' && nivel <='5')) throw CustomException("El nivel recibido no es válido");
	Lock l(m_quiero_iniciar);
	quiero_iniciar = nivel;
}
void ProxyJugador::notificarInicio(){
	try{
			emisor.enviar(MENSAJE_INICIAR);
		}catch(CException& e){
			informarEstaRota();
		}
	
	Lock l(m_quiero_iniciar);
	quiero_iniciar = false;//esto prepara la próxima pantalla de selección de niveles
}

void ProxyJugador::enviarKeystrokesA(Megaman* a){
	controlado = a;
}

void ProxyJugador::enviar(const FullSnapshot& full_snapshot){

	const FSSerializada serializada = full_snapshot.serializar();
	FSSerializada::const_iterator it;
	
	try{
			emisor.enviar(MENSAJE_INICIAR_ENVIO_FULLSNAPSHOT,full_snapshot.obtenerHorarioCreacion());
		}catch(CException& e){
			informarEstaRota();
		}
	
	
	//std::cout<<"-----------ENVIANDO  FULL SNAPSHOT------------"<<std::endl;
	for(it = serializada.begin(); it!=serializada.end(); ++it){
		try{
			emisor.enviar(MENSAJE_ENVIO_SNAPSHOT,*it);
		}catch(CException& e){
			informarEstaRota();
		}
		
		//std::cout<<*it<<std::endl;
	}
	
	timespec ahora;
	clock_gettime(CLOCK_REALTIME, &ahora);
	long nanos_ahora = ahora.tv_nsec;
	//std::cout<<"Enviando un full snapshot de"<<full_snapshot.obtenerHorarioCreacion()<<" a las "<<clock()<<". Desde el ultimo pasaron: "<< ((double)(nanos_ahora - nanos_ultimo_envio))/1000000000000<<std::endl;
	
	
	nanos_ultimo_envio = nanos_ahora;
	
	try{
			emisor.enviar(MENSAJE_TERMINAR_ENVIO_FULLSNAPSHOT);
		}catch(CException& e){
			informarEstaRota();
		}
}

void ProxyJugador::enviarPosicion(uint posicion){
	try{
			emisor.enviar(MENSAJE_POSICION,(int)posicion);
		}catch(CException& e){
			informarEstaRota();
		}
	
	this->posicion = posicion;
}
uint ProxyJugador::obtenerPosicion(){
	return posicion;
}

void ProxyJugador::enviarNivel(char nivel){
	try{
			emisor.enviarNivel(nivel);
		}catch(CException& e){
			informarEstaRota();
		}
	
}

void ProxyJugador::enviarFinNivel(){
	try{
			emisor.enviar(MENSAJE_FIN_NIVEL);
		}catch(CException& e){
			informarEstaRota();
		}
	
}

void ProxyJugador::notificarRecepcionRota(){
	informarEstaRota();
}
