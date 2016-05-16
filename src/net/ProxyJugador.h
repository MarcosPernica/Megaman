/**
Esta clase reresenta el proxy de cada jugador.
Los playerProxy escuchan del teclado o de un Socket, 
y actualizan al Megaman* que se les asigne. 
De escuchar del teclado, envían una señal al servidor.
En e3l futuro se separarán ambas funciones en 2 clases.
**/
#include <gtkmm.h>
#include "../graficos/VentanaJuego.h"
#include "../mundo/Megaman.h"
class ProxyJugador{
	private:
	Megaman* controlado;
	public:
	ProxyJugador(Megaman* controlado, VentanaJuego& ventana);
	bool detectarPresionTecla(GdkEventKey* evento);
};
