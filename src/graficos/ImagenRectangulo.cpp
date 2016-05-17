#include "ImagenRectangulo.h"
void ImagenRectangulo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const{
	const std::list<Rectangulo> representacion = obtenerRepresentacion();
	std::list<Rectangulo>::const_iterator it;
	for(it = representacion.begin(); it != representacion.end(); ++it){
		cr->rectangle(it->x-cam_x, 
					  it->y-cam_y, 
					  it->w, 
					  it->h);
		cr->stroke();
	}
}
