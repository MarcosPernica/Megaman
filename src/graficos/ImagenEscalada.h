#ifndef IMAGENESCALADA
#define IMAGENESCALADA
#include "Dibujable.h"
#include "../common/Rectangulo.h"
class ImagenEscalada : public virtual Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	
	/**
	 * En unidades del mundo
	 * */
	virtual const Rectangulo obtenerRepresentacion() const = 0;
	
	virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar() = 0;
	
};
#endif
