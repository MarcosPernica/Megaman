#include "Imagen.h"
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <iostream>
void Imagen::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
										b2Vec2 origen, 
										real factorAmplificacion) const{
											
	Cairo::RefPtr<Cairo::ImageSurface> image = Cairo::ImageSurface::create_from_png("imagenes/spritesheet.png");
	//Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("imagenes/spritesheet.png");
	//std::cout<<image<<std::endl;
	//Gdk::Cairo::set_source_pixbuf(cr,image,100,100);
	
	//cr->rectangle(0.1,0.1,0.1,0.1);
	//cr->fill();		
	//cr->stroke();		
	const Rectangulo representacion = obtenerRepresentacion();
	const b2Vec2 top_left_escalada = mundoARender(representacion.topLeft());
	const real altoEscalado = mundoARender(representacion.obtenerAlto());
	const real anchoEscalado = mundoARender(representacion.obtenerAncho());
	
	Dibujable::dibujarImagen(	cr, origen, factorAmplificacion, top_left_escalada,
								anchoEscalado, altoEscalado, image);		
}
