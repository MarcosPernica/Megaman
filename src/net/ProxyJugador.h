#ifndef PROXYJUGADOR
#define PROXYJUGADOR
/**
 * Esta clase representa el Cliente visto desde el Servidor. 
 * ProxyCliente hubiera sido otro nombre posible.
 * Va a aptretar botones de Megaman*
**/
#include <string>
#include "ChannelSocket.h"
#include <set>

class ProxyJugador{
	private:
	const std::string id_usuario;
	ChannelSocket* channel;
	public:
	ProxyJugador(const std::string& id_usuario, ChannelSocket* channel);
	void enviarListaJugadores(const std::set<ProxyJugador*>& lista);
	void notificarLlegada(ProxyJugador* jugador);
	void notificarEstaba(ProxyJugador* jugador);
	const std::string& getUsuario();
	/**
	 * Esta se usa del lado del servidor para recibir los keystrokes remotos...
	 * */
	
	//void recibirMensajeDeCliente(CodigoEvento evento);
};
#endif
