#include "ArchivoImagen.h"
#include "../common/exceptions.h"
ArchivoImagen::ArchivoImagen(const std::string& n):nombre(n){}
const std::string& ArchivoImagen::obtenerNombre() const{
	return nombre;
}
bool ArchivoImagen::operator<(const ArchivoImagen& otro) const{
	return nombre.size()<otro.nombre.size();
}
/*
ArchivoImagen::ArchivoImagen(){
	nombre ="SIN-NOMBRE";
	throw CustomException("Quien se atreve?");
}
*/
ArchivoImagen::ArchivoImagen(const ArchivoImagen& otro){
	nombre = otro.nombre;
}
