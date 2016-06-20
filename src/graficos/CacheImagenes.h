#ifndef CACHEIMAGENES
#define CACHEIMAGENES
#include <gdkmm/pixbuf.h>
#include <map>
#include "ArchivoImagen.h"
#include <gdkmm/general.h>
class CacheImagenes{
	private:
	CacheImagenes();
	CacheImagenes(const CacheImagenes& otro);//no se puede copiar ni construir
	CacheImagenes& operator=(const CacheImagenes& otro);
	
	static std::map< std::string, Glib::RefPtr < Gdk::Pixbuf > > cache;
	public:
	static Glib::RefPtr<Gdk::Pixbuf> obtenerPixbuf(const ArchivoImagen& archivo);
	static uint ancho(const ArchivoImagen& archivo);
	static uint alto(const ArchivoImagen& archivo);
	static bool existe(const ArchivoImagen& archivo);
};

#endif
