#include "Imagen.h"
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <iostream>
void Imagen::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
										b2Vec2 origen, 
										real factorAmplificacion){
	
															
	Glib::RefPtr<Gdk::Pixbuf> imagen = a_dibujar();
	if(imagen==NULL) return;//no se dibuja nada
	
	const Rectangulo representacion = obtenerRepresentacion();
	const b2Vec2 top_left_escalada = mundoARender(representacion.topLeft());
	const real altoEscalado = mundoARender(representacion.obtenerAlto());
	const real anchoEscalado = mundoARender(representacion.obtenerAncho());
	
	real ancho_imagen = (real)imagen->get_width()/(real)imagen->get_height()*altoEscalado;
	//no se respeta el ancho de la representación, sino que se mantienen las proporciones de la imagen
	
	b2Vec2 top_center(top_left_escalada.x+anchoEscalado/2,top_left_escalada.y);
	b2Vec2 top_left_def = top_center - b2Vec2(ancho_imagen/2,0);
	
	if(espejado()){
		top_left_def.x += ancho_imagen;
	}
	
	Dibujable::dibujarImagen(	cr, origen, factorAmplificacion, top_left_def,
								ancho_imagen, altoEscalado,imagen,espejado());
	
	/*Dibujable::dibujarRectangulo(	cr, origen, factorAmplificacion, top_left_escalada,
								anchoEscalado, altoEscalado);*/
}
