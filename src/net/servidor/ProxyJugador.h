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

class ProxyJugador: public Receptor{
	private:
	Mutex m_id;
	Mutex m_conexion_sana;
	Mutex m_quiero_iniciar;
	
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
	
	//void recibirMensajeDeCliente(CodigoEvento evento);
};
#endif
