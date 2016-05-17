#ifndef IMAGENRECTANGULO
#define IMAGENRECTANGULO
#include "Dibujable.h"
#include "../common/Rectangulo.h"
/**
 * Este dibujable es un Rectangulo
 * */
class ImagenRectangulo: public Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const;
	protected:
	/**
	 * Pregunta qué rectángulo dibujar, las coordenadas son absolutas
	 * */
	virtual const std::list<Rectangulo> obtenerRepresentacion() const = 0;
};

#endif
