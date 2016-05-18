#ifndef CLIENTE
#define CLIENTE
#include "ChannelSocket.h"
#include <set>
class Cliente{
	private:
	ChannelSocket socket;
	
	/**
	 * Pide ip y port por cmd, y conecta el Socket
	 * */
	void conectarse();
	/**
	 * Pide ID y lo envía al server
	 * */
	void enviarID();
	/**
	 * Recibe la lista de jugadores que entraron hasta el momento, 
	 * puede estar vacía
	 * */
	std::set<int> recibirListaJugadores();
	
	
	/**
	 * Envia la señal de iniciar la partida
	 * */
	 void iniciarPartida();
	public:
	void correr();
	//Cliente();
	
	//void enviarMensaje(const std::string& mensaje);
	
};
#endif
