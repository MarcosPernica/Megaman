#include "Server.h"
#include "ProxyJugador.h"
Server::Server():jugador(mundo.getMegaman()){}
void Server::inicializar(){
	Simulador(mundo,100);
}

ProxyJugador& ProxyJugador::getJugador(){
	return jugador;
}
