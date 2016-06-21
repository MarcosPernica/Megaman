#include "EstadisticasMundo.h"
#include <iostream>
#include <cmath>
#include <sstream>
EstadisticasMundo::EstadisticasMundo():Snapshotable(60000){
	for(uint i =0; i <4;i++){
		vidas[i]=3;
	}
	
}
EstadisticasMundo::EstadisticasMundo(Snapshot& sn):Snapshotable(60000){
	std::cout<<"Creando EstadisticasMundo desde snapshot!!!"<<std::endl;
	for(uint i =0; i <4;i++){
		vidas[i]=3;
	}
}
void EstadisticasMundo::agregarArma(int disparo){
	armas_disponibles.push_back(disparo);
}
const std::vector<int>& EstadisticasMundo::obtenerArmas(){
	return armas_disponibles;
}

uint EstadisticasMundo::vidasDe(uint posicion_jugador){
	return vidas[posicion_jugador];
}

void EstadisticasMundo::setVidas(uint posicion_jugador, uint vs){
	vidas[posicion_jugador] = vs;
}

void EstadisticasMundo::perderUnaVida(uint posicion_jugador){
	
	if(vidas[posicion_jugador]>=1){
		vidas[posicion_jugador]-=1;
	}
}

#define PROP_TIPO_DEL_ARMA "tipo_del_arma"
#define PROP_VIDA "cantidad_vidas"

void EstadisticasMundo::agregarPropiedadesASnapshot(Snapshot& sn){
	int largo_armas = armas_disponibles.size();
	SN_AGREGAR_PROPIEDAD(largo_armas);
	for(int i = 0; i < armas_disponibles.size(); i++){
		std::ostringstream oss;
		oss<<PROP_TIPO_DEL_ARMA<<i;
		sn.agregarPropiedad(oss.str(),armas_disponibles[i]);
	}
	
	for(int i = 0; i < 4; i++){
		std::ostringstream oss;
		oss<<PROP_VIDA<<i;
		sn.agregarPropiedad(oss.str(),vidas[i]);
	}
}
void EstadisticasMundo::setStateFromSnapshot(const Snapshot& sn){
	int largo_armas;
	SN_OBTENER_PROPIEDAD(largo_armas);
	while(largo_armas>armas_disponibles.size()){
		armas_disponibles.push_back(0);
	}
	
	for(int i = 0; i < largo_armas; i++){
		std::ostringstream oss;
		oss<<PROP_TIPO_DEL_ARMA<<i;
		sn.obtenerPropiedad(oss.str(),armas_disponibles[i]);
	}
	
	for(int i = 0; i < 4; i++){
		std::ostringstream oss;
		oss<<PROP_VIDA<<i;
		sn.obtenerPropiedad(oss.str(),vidas[i]);
	}
}

void EstadisticasMundo::eliminarse(Mundo& de){}
