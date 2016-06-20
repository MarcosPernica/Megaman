#ifndef ARCHIVOIMAGEN
#define ARCHIVOIMAGEN
#include <string>
#include <map>
#include "../mundo/Definiciones.h"
class ArchivoImagen{
	private:
	std::string nombre;
	public:
	//ArchivoImagen();
	ArchivoImagen(const ArchivoImagen& otro);
	ArchivoImagen(const std::string& nombre);
	const std::string& obtenerNombre() const;
	//friend bool operator<(const ArchivoImagen& a1, const ArchivoImagen& a2);
	bool operator<(const ArchivoImagen& otro) const;
	
};
/*
bool operator< (const ArchivoImagen& a1, const ArchivoImagen& a2){
	return a1.nombre<a2.nombre;
}
**/
#endif
