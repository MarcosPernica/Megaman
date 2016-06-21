#include "Snapshot.h"
#include <sstream>
#include "../../common/exceptions.h"
#include <iostream>
#include "../../mundo/Cuerpo.h"
#include "../../mundo/Disparo.h"
#include "../../common/deslocalizacion.h"

Snapshot::Snapshot() : id(0){}
Snapshot::Snapshot(const SnapshotSerializada& serializada){
	deserializar(serializada);
}
Snapshot::Snapshot(uint id){
	agregarPropiedad("ID", id);
}


SnapshotSerializada Snapshot::serializar() const{
	std::ostringstream ostream;
	MapaPropiedades::const_iterator it;
	ostream.imbue(std::locale(ostream.getloc(), new ConComa()));
	ostream.imbue(std::locale(ostream.getloc(), new PonerNada()));
	
	for(it=propiedades.begin(); it!=propiedades.end(); ++it){
		ostream<< it->first <<" "<<it->second<<" ";
	}
	
	return ostream.str();///////COPIA/////////////////////////////	
}

int Snapshot::getID() const{
	return obtenerPropiedad("ID");
}

void Snapshot::deserializar(const SnapshotSerializada& serializada){
	std::istringstream istream(serializada);
	istream.imbue(std::locale(istream.getloc(), new ConComa()));
	istream.imbue(std::locale(istream.getloc(), new PonerNada()));
	while(!istream.eof()){
		std::string nombre;
		int valor;
		istream>>nombre;
		istream>>valor;
		if(nombre.size()>=1){
			agregarPropiedad(nombre,valor);
		}
	}
}

int Snapshot::getTipo() const{
	return obtenerPropiedad(PROP_TIPO);
}

//-------------------------int-------------------------------------//

void Snapshot::agregarPropiedad(const std::string& nombre, int valor){
	propiedades[nombre]=valor;
}
void Snapshot::obtenerPropiedad(const std::string& nombre, int& ponerEn) const{
	ponerEn = obtenerPropiedad(nombre);
}

int Snapshot::obtenerPropiedad(const std::string& nombre) const{
	if(propiedades.count(nombre)==0){
		throw CustomException("La propiedad "+nombre+" no existe");
	}
	return (propiedades.find(nombre)->second);
}

//-------------------uint----------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, uint valor){
	agregarPropiedad(nombre,(int)valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, uint& ponerEn) const{
	ponerEn = (uint) obtenerPropiedad(nombre);
}

//-------------------bool--------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, bool valor){
	agregarPropiedad(nombre,(int) valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, bool& ponerEn) const{
	ponerEn = (bool) obtenerPropiedad(nombre);
}

//-------------------real--------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, real valor){
	int post = (int) (valor*1000);
	agregarPropiedad(nombre,post);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, real& ponerEn) const{
	int prop = obtenerPropiedad(nombre);
	ponerEn = ((float)prop)/1000;
}
//-------------------char--------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, char valor){
	agregarPropiedad(nombre,(int) valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, char& ponerEn) const{
	ponerEn = (char) obtenerPropiedad(nombre);
}

//--------------------Orientacion-------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, Orientaciones valor){
	agregarPropiedad(nombre,(int) valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, Orientaciones& ponerEn) const{
	ponerEn = (Orientaciones) obtenerPropiedad(nombre);
}

//-------------------ushort----------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, ushort valor){
	agregarPropiedad(nombre,(int) valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, ushort& ponerEn) const{
	ponerEn = (ushort) obtenerPropiedad(nombre);
}
