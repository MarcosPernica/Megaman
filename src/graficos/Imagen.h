#ifndef IMAGEN
#define IMAGEN
#include "Dibujable.h"
#include "../common/Rectangulo.h"
class Imagen : public virtual Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion) const;
	
	/**
	 * En unidades del mundo
	 * */
	virtual const Rectangulo obtenerRepresentacion() const = 0;
};
#endif
