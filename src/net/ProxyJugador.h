#ifndef PROXYJUGADOR
#define PROXYJUGADOR
/**
Esta clase reresenta el proxy de cada jugador.
Los playerProxy escuchan del teclado o de un Socket, 
y actualizan al Megaman* que se les asigne. 
De escuchar del teclado, envían una señal al servidor.
En e3l futuro se separarán ambas funciones en 2 clases.
**/

//#include "../graficos/VentanaJuego.h"
class VentanaJuego;
class ServerProxy;
#include "../mundo/Megaman.h"
class ServerProxy;
#include <gdk/gdk.h>

typedef char CodigoEvento;
#define CODIGO_EVENTO_SALTO 's'

class ProxyJugador{
	private:
	Megaman* controlado;
	ServerProxy& server_proxy;
	public:
	/**
	 * Usado del lado del cliente
	 * */
	ProxyJugador(Megaman* controlado, VentanaJuego& ventana, ServerProxy& server_proxy);
	/**
	 * Usado por el server
	 * */
	ProxyJugador(Megaman* controlado);
	/**
	 * Esta se uso del lado de cliente para detectar el teclado
	 * */
	bool detectarPresionTecla(GdkEventKey* evento);
	/**
	 * Esta se usa del lado del servidor para recibir los keystrokes remotos...
	 * */
	void recibirMensajeDeCliente(CodigoEvento evento);
};
#endif
