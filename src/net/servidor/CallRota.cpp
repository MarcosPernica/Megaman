#include "CallRota.h"
void CallRota::notificar(){
	proxy.notificarRecepcionRota();
}
CallRota::CallRota(ProxyJugador& p):proxy(p){}
