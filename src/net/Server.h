#ifndef SERVER
#define SERVER
/**
Esta clase representa el server.
El inicializar() de esta clase, equivale al main() de la aplicación servidor
*/
#include "../mundo/Mundo.h"
#include <list>
#include "ProxyJugador.h"
class Server{
	
	Mundo mundo;
	private:
	ProxyJugador jugador;//por ahora un único "cliente"
	public:
	Server();
	void inicializar();
	ProxyJugador& getJugador();
	
	
};
#endif
