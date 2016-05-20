#ifndef CLIENTE
#define CLIENTE
#include "ChannelSocket.h"
#include <set>
#include <string>
#include "../common/Mutex.h"
enum Posicion{
	Primero,
	NoPrimero,
	Desconocida
};

/**
 * "Singleton" que representa la aplicación cliente
 * */
class Cliente{
	private:
	Mutex m_pantalla;
	Mutex m_posicion;
	Mutex m_iniciado;
	
	ChannelSocket socket;
	Posicion posicion;
	bool flag_iniciado;
	
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
	void definirSoyPrimero(bool soy_primero);
	Posicion obtenerPosicion();
	void enviarIniciar();
	void iniciar();
	bool iniciado();
	//void enviarMensaje(const std::string& mensaje);
	
};
#endif
