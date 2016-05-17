#ifndef SERVERPROXY
#define SERVERPROXY
/**
Ésta clase representa el server desde el cliente.
Tiene referencias a todos los ProxyJugador y al mundo.
-Envía al Server los mensajes del ProxyJugador del jugador de carne y hueso usuario
-Recibe FullSnapshots y las inyecta en Mundo
*/
#include "../mundo/Mundo.h"
#include "ProxyJugador.h"
#include "Server.h"

class ServerProxy{
	private:
	Mundo& mundo;
	Server& server;//no va a estar!
	public:
	//la idea es que no exista esa referencia al server
	ServerProxy(Mundo& mundo, Server& server);
	void enviarEvento(CodigoEvento evento);
	void inyectarSnapshot();
	
};
#endif
