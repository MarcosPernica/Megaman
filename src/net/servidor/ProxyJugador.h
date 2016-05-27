#ifndef PROXYJUGADOR
#define PROXYJUGADOR
/**
 * Esta clase representa el Cliente visto desde el Servidor. 
 * ProxyCliente hubiera sido otro nombre posible.
 * Va a aptretar botones de Megaman*
**/
#include <string>
#include "../sockets/Receptor.h"
#include <set>
#include "../../mundo/Megaman.h"
#include "../snapshots/FullSnapshot.h"
#include <queue>
class ProxyJugador: public Receptor{
	private:
	uint posicion;
	
	Mutex m_id;
	Mutex m_conexion_sana;
	Mutex m_quiero_iniciar;
	Mutex m_controles_recibidos;
	
	std::queue<std::string> controles_recibidos;
	
	Megaman* controlado;
	
	std::string id_usuario;
	bool conexion_sana;
	bool quiero_iniciar;
	
	ChannelSocket* channel;
	
	bool tengoUsuario();
	void informarEstaRota();
	void setQuiereIniciarPartida();
	public:
	//ProxyJugador(const std::string& id_usuario, ChannelSocket* channel);
	ProxyJugador(ChannelSocket* channel);
	
	void enviarListaJugadores(const std::set<ProxyJugador*>& lista);
	void notificarLlegada(ProxyJugador* jugador);
	void notificarEstaba(ProxyJugador* jugador);
	void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	const std::string& getUsuario();
	bool getEstaSana();
	void enviarSosPrimero();
	void enviarNoSosPrimero();
	void enviar(const FullSnapshot& full_snapshot);
	
	bool quiereIniciarPartida();
	void notificarInicio();
	
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
};
#endif
