#include "DistribuidorSnapshots.h"
#include <iostream>
DistribuidorSnapshots::DistribuidorSnapshots(std::set<ProxyJugador*>& p):proxies(p){}
void DistribuidorSnapshots::distribuir(const FullSnapshot& full_snapshot){
	std::set<ProxyJugador*>::iterator it;
	for(it = proxies.begin(); it!=proxies.end(); ++it){
		(*it)->enviar(full_snapshot);
		///std::cout<<"enviados!"<<std::endl;
	}
}
