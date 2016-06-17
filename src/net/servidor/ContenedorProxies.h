#ifndef DISTRIBUIDOR_SNAPSHOTS
#define DISTRIBUIDOR_SNAPSHOTS
#include <vector>
#include "ProxyJugador.h"
#include "../snapshots/FullSnapshot.h"
#include "../../common/Lock.h"
class CallbackLimiteJugadores{
	public:
	virtual void limiteAlcanzado() = 0;
};


class ContenedorProxies{
	private:
	Mutex m_proxies;
	std::vector<ProxyJugador*> proxies;
	CallbackLimiteJugadores* callbackLimite;
	CallbackReceptor* callbackIniciar;
	public:
	ContenedorProxies(CallbackReceptor* callbackIniciar, CallbackLimiteJugadores* callbackLimite);
	/**
	 * Distribuye un fullsnapshot a todos los clientes
	 * */
	void distribuir(const FullSnapshot& full_snapshot);
	/**
	 * hace que todos los eventos de teclado recibidos por los proxies
	 * se transmitan a sus megamanes
	 * */
	void ejecutarControlesSobreMegaman();
	
	/**
	 * Recibe las conexiones nuevas
	 * */
	 void nuevaConexion(ChannelSocket* nueva);
	 
	/**
	 * Le envia el nive (el archivo!) a todos los clientes
	 * */
	 
	 void enviarNivel(char nivel);
	 
	 
	 /**
	  * Avisa del inicio del juego a todos los proxies que hay hasta ahora
	  * */
	 
	 void notificarInicio();
	 
	/**
	 * Borra todas las conexiones. 
	 * */
	
	 void matarConexiones();
	 
	 /**
	 * Avisa de la llegada de ese usuario a todos los proxies que 
	 * hay hasta ahora
	 * */
	 void notificarLlegada(ProxyJugador* jugador);
	 
	 std::vector<ProxyJugador*> obtenerJugadores();
};
#endif
