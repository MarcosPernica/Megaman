#include "Snapshot.h"
#include <sstream>
Snapshot::Snapshot(const SnapshotSerializada& serializada){
	deserializar(serializada);
}
Snapshot::Snapshot(ID id){
	agregarPropiedad("ID", id);
}
Snapshot::Snapshot(){}

virtual SnapshotSerializada Snapshot::serializar(){
	std::ostringstream ostream;
	MapaPropiedades::iterable it;
	for(it=propiedades.begin(); it!=propiedades.end(); ++it){
		ostream<< it->first <<" "<<it->second<<std::endl;
	}
	
	return String(ostream.str());///////COPIA/////////////////////////////	
}

void Snapshot::agregarPropiedad(const std::string& nombre, int valor){
	propiedades[nombre]=valor;
}

int Snapshot::obtenerPropiedad(const std::string& nombre){
	if(propiedades.count(nombre)==0){
		throw new CustomException("La propiedad "+nombre+" no existe");
	}
	return propiedades[nombre];
}

int Snapshot::getID(){
	return obtenerPropiedad("ID");
}

void SnapshotSerializada::deserializar(const SnapshotSerializada& serializada){
	std::istringstream istream(serializada);
	while(!istream.eof()){
		std::string nombre;
		int valor;
		istream>>nombre;
		istream>>valor;
		agregarPropiedad(nombre,valor);
	}
}