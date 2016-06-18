#ifndef PROXYJUGADOR
#define PROXYJUGADOR
/**
 * Esta clase representa el Cliente visto desde el Servidor. 
 * ProxyCliente hubiera sido otro nombre posible.
 * Va a aptretar botones de Megaman*
**/
#include <string>
#include "../sockets/Receptor.h"
#include <vector>
#include "../../mundo/Megaman.h"
#include "../snapshots/FullSnapshot.h"
#include <queue>
#include "../sockets/Emisor.h"
#include <iostream>
class ProxyJugador: public Receptor{
	private:
	uint posicion;
	long nanos_ultimo_envio;
	
	Mutex m_id;
	Mutex m_conexion_sana;
	Mutex m_quiero_iniciar;
	Mutex m_controles_recibidos;
	
	std::queue<std::string> controles_recibidos;
	
	Megaman* controlado;
	
	std::string id_usuario;
	bool conexion_sana;
	char quiero_iniciar;//es el CARACTER que representa el nivel: no es 1...5 sino '1'...'5', '0' significa no quiere iniciar
	
	ChannelSocket* channel;
	
	bool tengoUsuario();
	void informarEstaRota();
	void setQuiereIniciarPartida(char nivel);
	Emisor emisor;
	public:
	//ProxyJugador(const std::string& id_usuario, ChannelSocket* channel);
	ProxyJugador(ChannelSocket* channel);
	
	void enviarListaJugadores(const std::vector<ProxyJugador*>& lista);
	void notificarLlegada(ProxyJugador* jugador);
	void notificarEstaba(ProxyJugador* jugador);
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	const std::string& getUsuario();
	bool getEstaSana();
	void enviar(const FullSnapshot& full_snapshot);
	
	bool quiereIniciarPartida();
	char nivelQueEligio();
	void notificarInicio();
	void enviarNivel(char nivel);
	
	~ProxyJugador();
	
	/**
	 * Define a qué Megaman enviar los keystrokes recibidos desde el cliente.
	 * Cuando haya que dejar de enviar keystrokes a ese Megaman, se debe pasar NULL
	 * */ 
	void enviarKeystrokesA(Megaman* a);
	
	/**
	 * Envia la posición en que entró al server
	 * */
	void enviarPosicion(uint posicion);
	
	/**
	 * Devuelve la posición en que entró al server
	 * */
	uint obtenerPosicion();
	
	/**
	 * Desacola algún control recibido y apreta los botones del Megaman correspondiente
	 * */
	 void ejecutarControlSobreMegaman();
	 
	 /**
	  * Envía al jugador el mensaje de que se envió el nivel
	  * */
	 void enviarFinNivel();
};

class CallbackProxyJugador : public CallbackReceptor {
	private:
	ProxyJugador& proxy;
	public:
	CallbackProxyJugador(ProxyJugador& p):proxy(p){};
	void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje){
		proxy.recepcion(tipo_mensaje,resto_mensaje);
	};
};
#endif
