#include "ContenedorProxies.h"
#include <iostream>
ContenedorProxies::ContenedorProxies(std::set<ProxyJugador*>& p):proxies(p){}
void ContenedorProxies::distribuir(const FullSnapshot& full_snapshot){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->enviar(full_snapshot);
	}
}

void ContenedorProxies::ejecutarControlesSobreMegaman(){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->ejecutarControlSobreMegaman();
	}
}
