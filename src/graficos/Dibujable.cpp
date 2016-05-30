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
/**
 * Dibuja el Pixbuf escalándolo para ponerlo en el lugar que se indica.
 * si invertir == true, la imagen se invierte por el eje vertical que pasa por el borde izquierdo
 * */
void Dibujable::dibujarImagen(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto,
				  Glib::RefPtr<Gdk::Pixbuf> imagen,
				  bool invertir)
{
	real alto_def = alto*factorAmplificacion;
	real ancho_def = ancho*factorAmplificacion;
	b2Vec2 aux = factorAmplificacion*(posicion - origen);
	real escala_x = ancho_def/imagen->get_width();
	real escala_y = alto_def/imagen->get_height();
	cr->save();
	
	cr->translate(aux.x,aux.y);
	if(invertir){
		cr->scale(-escala_x,escala_y);
	}else{
		cr->scale(escala_x,escala_y);
	}
	Gdk::Cairo::set_source_pixbuf(cr, 
						imagen,
						0,0);
	
	cr->rectangle(0, 
		      0, 
		      ancho_def, 
		      alto_def);
	
	cr->clip();
	
	cr->paint();
	cr->restore();
}
