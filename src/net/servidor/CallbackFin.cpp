#include "CallbackFin.h"
#include "Servidor.h"
void CallbackFin::fin(){
	servidor.finNivel();
}

CallbackFin::CallbackFin(Servidor& serv):
			servidor(serv){}
