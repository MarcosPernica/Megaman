#include "CacheImagenes.h"
#include <gdkmm/general.h>
#include "../common/exceptions.h"
std::map<std::string,Glib::RefPtr<Gdk::Pixbuf> > CacheImagenes::cache;
Glib::RefPtr<Gdk::Pixbuf> CacheImagenes::obtenerPixbuf(const ArchivoImagen& archivo){
	if(cache.count(archivo.obtenerNombre())==0){
		try{
			cache[archivo.obtenerNombre()]= Gdk::Pixbuf::create_from_file(archivo.obtenerNombre());
		}catch(const Glib::Error& ex){
			throw CustomException("El archivo "+archivo.obtenerNombre()+" no existe");
		}
	}
	
	if(cache[archivo.obtenerNombre()]==NULL){
		cache.erase(archivo.obtenerNombre());
		throw CustomException("El archivo "+archivo.obtenerNombre()+" no existe");
	}
	
	return cache[archivo.obtenerNombre()];
}
uint CacheImagenes::ancho(const ArchivoImagen& archivo){
	return CacheImagenes::obtenerPixbuf(archivo.obtenerNombre())->get_width();
}
uint CacheImagenes::alto(const ArchivoImagen& archivo){
	return CacheImagenes::obtenerPixbuf(archivo.obtenerNombre())->get_height();
}
bool CacheImagenes::existe(const ArchivoImagen& archivo){
	bool existe = true;
	Glib::RefPtr<Gdk::Pixbuf> ref;
	try{
		ref = CacheImagenes::obtenerPixbuf(archivo.obtenerNombre());
	}catch (const CustomException& e){
		existe = false;
	}
	return existe && ref != NULL;
}
