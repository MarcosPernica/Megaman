#include "Dibujable.h"

b2Vec2 Dibujable::renderAMundo(b2Vec2 vector)
{
	return (1/FACTORCONVERSIONMPX)*vector;
}	

b2Vec2 Dibujable::mundoARender(b2Vec2 vector)
{
	return FACTORCONVERSIONMPX*vector;
}

real Dibujable::renderAMundo(real numero)
{
	return numero/FACTORCONVERSIONMPX;
}

real Dibujable::mundoARender(real numero)
{
	return numero*FACTORCONVERSIONMPX;
}

void Dibujable::dibujarRectangulo(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto)
{
	b2Vec2 aux = factorAmplificacion*(posicion - origen);
	cr->save();
	cr->set_source_rgb(0,0,0);
	cr->set_line_width(3.0);
	cr->rectangle(aux.x, 
		      aux.y, 
		      ancho*factorAmplificacion, 
		      alto*factorAmplificacion);

	cr->stroke();
	cr->restore();
}

void Dibujable::dibujarImagen(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto,
				  Cairo::RefPtr<Cairo::ImageSurface> imagen)
{
	//Gdk::Cairo::set_source_pixbuf(cr,imagen,imagen->get_width(),imagen->get_height());
	cr->save();
	b2Vec2 aux = factorAmplificacion*(posicion - origen);
	cr->set_source(imagen,aux.x,aux.y);
	
	real cambio_x = ancho/imagen->get_width();
	real cambio_y = alto/imagen->get_height();
	
	//cairo_scale(cr, cambio_x, cambio_y);
	cr->rectangle(aux.x/cambio_x, 
		      aux.y/cambio_y, 
		      imagen->get_width() *factorAmplificacion*cambio_x, 
		      imagen->get_height()*factorAmplificacion*cambio_y);

	cr->clip();
	cr->paint();
	cr->restore();
}
