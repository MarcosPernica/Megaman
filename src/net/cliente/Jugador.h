#ifndef PROXYJUGADOR
#define PROXYJUGADOR


class VentanaJuego;
class ServerProxy;
#include "../../mundo/Megaman.h"

class ServerProxy;
#include <gdk/gdk.h>

typedef char CodigoEvento;
#define CODIGO_EVENTO_SALTO 's'

#include "../sockets/Emisor.h"

/**
 * Jugador detecta eventos del teclado, habla con la interfaz del objeto
 * Megaman enviándole los controles, y a la vez los envía al servidor.
 * Se ocupa sólo de la emisión de mensajes, no su recepción. 
 * 
 * */


class Jugador{
	private:
	unsigned int ultimaTecla;
	Megaman* controlado;
	const Emisor& emisor;
	public:
	/**
	 * Usado del lado del cliente
	 * */
	 Jugador(Megaman* controlado, VentanaJuego& ventana,const Emisor& emi);
	/**
	 * Esta se uso del lado de cliente para detectar el teclado
	 * */
	bool detectarPresionTecla(GdkEventKey* evento);
	bool detectarLiberacionTecla(GdkEventKey* evento);
};
#endif
