#include "ImagenRectangulo.h"
#include <iostream>

void ImagenRectangulo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion) const{
	const std::list<Rectangulo> representacion = obtenerRepresentacion();
	std::list<Rectangulo>::const_iterator it;
	for(it = representacion.begin(); it != representacion.end(); ++it){
		
	}
}
