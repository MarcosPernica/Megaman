#ifndef SERVIDOR
#define SERVIDOR
#include <set>
#include "AccepterSocket.h"
#include "ProxyJugador.h"
class Servidor{
	/**
	 * Un thread paralelo tocará este flag para señalizar que se dejen de esperar conexiones
	 * */
	 bool aceptarJugadores;
	/**
	 * Colección con todos los proxies, que tienen un par de Threads
	 * */
	std::set<ProxyJugador*> proxies;//esto va a estar recontra protegido
	/**
	 * Socket aceptador
	 * */
	AccepterSocket accepter;
	/**
	 * pide port
	 * */
	void conectar();
	/**
	 * Etapa de preparación del juego/esperar jugadores/etc
	 * */
	void agregarJugadores();
	/**
	 * Avisa de la llegada de ese usuario a todos los proxies que 
	 * hay hasta ahora
	 * */
	void notificarLlegada(ProxyJugador* jugador);
	
	public:
	
	/**Ejecuta todo
	 * */
	void correr();
	
	~Servidor();
};
#endif
