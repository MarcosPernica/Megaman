#ifndef PROXYJUGADOR
#define PROXYJUGADOR
/**
 * Esta clase representa el Cliente visto desde el Servidor. 
 * ProxyCliente hubiera sido otro nombre posible.
 * Va a aptretar botones de Megaman*
**/
#include <string>
#include "Receptor.h"
#include <set>

class ProxyJugador: public Receptor{
	private:
	std::string id_usuario;
	bool coneccion_sana;
	//const std::string id_usuario;
	ChannelSocket* channel;
	bool tengoUsuario();
	void informarEstaRota();
	public:
	//ProxyJugador(const std::string& id_usuario, ChannelSocket* channel);
	ProxyJugador(ChannelSocket* channel);
	
	void enviarListaJugadores(const std::set<ProxyJugador*>& lista);
	void notificarLlegada(ProxyJugador* jugador);
	void notificarEstaba(ProxyJugador* jugador);
	void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	const std::string& getUsuario();
	bool getEstaSana();
	
	~ProxyJugador();
	/**
	 * Esta se usa del lado del servidor para recibir los keystrokes remotos...
	 * */
	
	//void recibirMensajeDeCliente(CodigoEvento evento);
};
#endif
