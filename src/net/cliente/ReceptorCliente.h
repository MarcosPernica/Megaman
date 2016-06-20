#ifndef RECEPTOR_CLIENTE
#define RECEPTOR_CLIENTE

#include "../sockets/Receptor.h"
#include <string>
#include <iostream>
#include "../snapshots/FullSnapshot.h"
#include "../../mundo/Mundo.h"
#include "../../common/Lock.h"
#include <ctime>
#include <fstream>

#define DECLARAR_CALL(tipo_mensaje) void call ## tipo_mensaje(const std::string resto_mensaje)

class Cliente;
class ReceptorCliente: public Receptor{
	private:
	clock_t horario_ultimo_inyectado;
	clock_t horario_ultima_inyeccion;
	bool inyectado;
	Cliente& cliente;
	
	std::ofstream stream_nivel;
	std::ofstream stream_config;
	
	
	 /**
	  * iniciar descarga del nivel
	  * */
	void iniciarDescargaNivel();
	 /**
	  * Agregar la línea recibida al nivel
	  * */
	void recibirDatosNivel(const std::string& datos);
	  /**
	   * Terminar la descarga del nivel
	* */
	void terminarDescargaNivel();
	
	
	/**
	 * Recibidas contiene la lista de snapshots recibida hasta ahora
	 * */
	std::vector<SnapshotSerializada> recibidas;
	/**
	 * a_punto_de_inyectar es el fullsnapshot finalizado.
	 * Está protegido porque gtkmm accede a ella a través del callback
	 * */
	Mutex m_a_punto;
	FullSnapshot a_punto_de_inyectar;
	Mundo* a_inyectar;
	void configurarCallbacks();
	public: 
	ReceptorCliente(const ChannelSocket& channel, Cliente& cliente);
	~ReceptorCliente();
	//void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	
	/**
	 * Define al Mundo al que deben inyectársele las FullSnapshot.
	 * Si el argumento es NULL, no se le inyectarán FullSnapshots a ningún Mundo.
	 * */ 
	 void inyectarFullSnapshotsA(Mundo* a);
	 /**
	  * callback de timeout, inyectar el snapshot
	  * */
	 bool onInyectar();
	 
	 //-----------------declaro los calls-------------------
	 DECLARAR_CALL(ESTABA);
	 DECLARAR_CALL(LLEGA);
	 DECLARAR_CALL(POSICION);
	 DECLARAR_CALL(INICIAR);
	 DECLARAR_CALL(INICIAR_ENVIO_FULLSNAPSHOT);
	 DECLARAR_CALL(ENVIO_SNAPSHOT);
	 DECLARAR_CALL(TERMINAR_ENVIO_FULLSNAPSHOT);
	 DECLARAR_CALL(INICIAR_ENVIO_NIVEL);
	 DECLARAR_CALL(ENVIO_NIVEL);
	 DECLARAR_CALL(TERMINAR_ENVIO_NIVEL);
	 
	 DECLARAR_CALL(INICIAR_ENVIO_CONFIG);
	 DECLARAR_CALL(ENVIO_CONFIG);
	 DECLARAR_CALL(TERMINAR_ENVIO_CONFIG);
};

#define DEFINIR_CALLBACK(tipo_mensaje) class Callback ## tipo_mensaje:public CallbackReceptor{\
	private:\
	ReceptorCliente& receptor;\
	public:\
	Callback ## tipo_mensaje(ReceptorCliente& rec):receptor(rec){};\
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){\
		receptor.call ## tipo_mensaje(resto_mensaje);\
	};\
};\

DEFINIR_CALLBACK(ESTABA)
DEFINIR_CALLBACK(LLEGA)
DEFINIR_CALLBACK(POSICION)
DEFINIR_CALLBACK(INICIAR)
DEFINIR_CALLBACK(INICIAR_ENVIO_FULLSNAPSHOT)
DEFINIR_CALLBACK(ENVIO_SNAPSHOT)
DEFINIR_CALLBACK(TERMINAR_ENVIO_FULLSNAPSHOT)
DEFINIR_CALLBACK(INICIAR_ENVIO_NIVEL)
DEFINIR_CALLBACK(ENVIO_NIVEL)
DEFINIR_CALLBACK(TERMINAR_ENVIO_NIVEL)

DEFINIR_CALLBACK(INICIAR_ENVIO_CONFIG)
DEFINIR_CALLBACK(ENVIO_CONFIG)
DEFINIR_CALLBACK(TERMINAR_ENVIO_CONFIG)

#endif
