#include "ImagenRectangulo.h"
void ImagenRectangulo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const{
	
	const Rectangulo representacion = obtenerRepresentacion();
	cr->rectangle(representacion.x-cam_x, 
				  representacion.y-cam_y, 
				  representacion.w, 
				  representacion.h);
	cr->stroke();
	
}
