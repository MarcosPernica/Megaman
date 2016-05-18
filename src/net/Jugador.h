#ifndef PROXYJUGADOR
#define PROXYJUGADOR

//#include "../graficos/VentanaJuego.h"
class VentanaJuego;
class ServerProxy;
#include "../mundo/Megaman.h"
class ServerProxy;
#include <gdk/gdk.h>

typedef char CodigoEvento;
#define CODIGO_EVENTO_SALTO 's'

/**
 * Jugador detecta eventos del teclado, habla con la interfaz del objeto
 * Megaman enviándole los controles, y a la vez los envía al servidor.
 * Se ocupa sólo de la emisión de mensajes, no su recepción. 
 * */
class Jugador{
	private:
	Megaman* controlado;
	//ServerProxy& server_proxy;
	public:
	/**
	 * Usado del lado del cliente
	 * */
	 Jugador(Megaman* controlado, VentanaJuego& ventana);
	//ProxyJugador(Megaman* controlado, VentanaJuego& ventana, ServerProxy& server_proxy);
	/**
	 * Esta se uso del lado de cliente para detectar el teclado
	 * */
	bool detectarPresionTecla(GdkEventKey* evento);
	bool detectarLiberacionTecla(GdkEventKey* evento);
};
#endif
