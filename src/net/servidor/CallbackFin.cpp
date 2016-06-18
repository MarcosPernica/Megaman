#include "CallbackFin.h"
#include "Servidor.h"
void CallbackFin::fin(EstadoMundo estado){
	servidor.finNivel();
}

CallbackFin::CallbackFin(Servidor& serv):
			servidor(serv){}
