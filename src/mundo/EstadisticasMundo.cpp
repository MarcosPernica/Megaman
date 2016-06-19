#include "EstadisticasMundo.h"
#include <iostream>
EstadisticasMundo::EstadisticasMundo(uint cantidad_jugadores){
	for(uint i =0; i <cantidad_jugadores;i++){
		vidas.push_back(3);
	}
}
EstadisticasMundo::EstadisticasMundo(Snapshot& sn, uint cantidad_jugadores){
	std::cout<<"Creando EstadisticasMundo desde snapshot!!!"<<std::endl;
	for(uint i =0; i <cantidad_jugadores;i++){
		vidas.push_back(3);
	}
}
