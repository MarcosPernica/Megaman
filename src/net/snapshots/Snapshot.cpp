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
	//std::cout<<"deserializando----------------------"<<std::endl;
	while(!istream.eof()){
		std::string nombre;
		int valor;
		istream>>nombre;
		istream>>valor;
		if(nombre.size()>=1){
			agregarPropiedad(nombre,valor);
			//std::cout<<"agregando propiedad: "<<nombre<<", "<<valor<<std::endl;
		}
	}
	//std::cout<<"Yo cuando estaba serializado: "<<serializada<<std::endl;
	//std::cout<<"Yo antes de serializar: "<<serializar()<<std::endl;
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
	//if(valor!=0)
	//std::cout<<"AGREGAR: Entra: "<<valor<<" sale: "<<post<<std::endl;
	agregarPropiedad(nombre,post);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, real& ponerEn) const{
	int prop = obtenerPropiedad(nombre);
	ponerEn = ((float)prop)/1000;
	//if(prop!=0)
	//std::cout<<"OBTENER: Entra: "<<prop<<" sale: "<<ponerEn<<std::endl;
}
//-------------------char--------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, char valor){
	agregarPropiedad(nombre,(int) valor);
}
void Snapshot::obtenerPropiedad(const std::string& nombre, char& ponerEn) const{
	ponerEn = (char) obtenerPropiedad(nombre);
}
//-------------------Arma*--------------------------------//
void Snapshot::agregarPropiedad(const std::string& nombre, Disparo* valor){
	agregarPropiedad(nombre,valor->getTipo());
}

void Snapshot::obtenerPropiedad(const std::string& nombre, Disparo*& ponerEn) const{
	//delete ponerEn;
	int obtenido = obtenerPropiedad(nombre);
	switch(obtenido){
		default:
		;
			//ponerEn = new Plasma();
		/*
		 * acá iría case TIPO_DISP_PLASMA :
		 * case TIPO_DISP_BOMBA :
		 * y así...
		 * */
	}
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
