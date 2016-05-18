#include "ImagenRectangulo.h"
#include <iostream>
void ImagenRectangulo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const{
	const std::list<Rectangulo> representacion = obtenerRepresentacion();
	std::list<Rectangulo>::const_iterator it;
	for(it = representacion.begin(); it != representacion.end(); ++it){
		b2Vec2 aux = FACTORCONVERSIONMPX*it->topLeft();
		cr->rectangle(aux.x-cam_x, 
					  aux.y-cam_y, 
					  it->obtenerAncho()*FACTORCONVERSIONMPX, 
					  it->obtenerAlto()*FACTORCONVERSIONMPX);
		cr->stroke();
	}
}
