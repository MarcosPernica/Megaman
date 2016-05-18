#ifndef CLIENTE
#define CLIENTE
#include "ChannelSocket.h"
#include <set>
#include <string>
class Cliente{
	private:
	ChannelSocket socket;
	bool es_primero;
	
	/**
	 * Pide ip y port por cmd, y conecta el Socket
	 * */
	void conectarse();
	/**
	 * Pide ID y lo envía al server
	 * */
	void enviarID();
	
	
	/**
	 * Envia la señal de iniciar la partida
	 * */
	 void iniciarPartida();
	public:
	void correr();
	
	//interfaz para ReceptorCliente
	void agregarEstaba(const std::string& usuario);
	void agregarLlega(const std::string& usuario);
	
	//void enviarMensaje(const std::string& mensaje);
	
};
#endif
