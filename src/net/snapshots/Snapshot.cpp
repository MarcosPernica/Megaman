#include "Snapshot.h"
#include <sstream>
#include "../../common/exceptions.h"
Snapshot::Snapshot(){}
Snapshot::Snapshot(const SnapshotSerializada& serializada){
	deserializar(serializada);
}
Snapshot::Snapshot(ID id){
	agregarPropiedad("ID", id);
}


SnapshotSerializada Snapshot::serializar(){
	std::ostringstream ostream;
	MapaPropiedades::iterator it;
	for(it=propiedades.begin(); it!=propiedades.end(); ++it){
		ostream<< it->first <<" "<<it->second<<std::endl;
	}
	
	return ostream.str();///////COPIA/////////////////////////////	
}

void Snapshot::agregarPropiedad(const std::string& nombre, int valor){
	propiedades[nombre]=valor;
}

int Snapshot::obtenerPropiedad(const std::string& nombre) const{
	if(propiedades.count(nombre)==0){
		throw CustomException("La propiedad "+nombre+" no existe");
	}
	return (propiedades.find(nombre)->second);
}

int Snapshot::getID() const{
	return obtenerPropiedad("ID");
}

void Snapshot::deserializar(const SnapshotSerializada& serializada){
	std::istringstream istream(serializada);
	while(!istream.eof()){
		std::string nombre;
		int valor;
		istream>>nombre;
		istream>>valor;
		agregarPropiedad(nombre,valor);
	}
}
