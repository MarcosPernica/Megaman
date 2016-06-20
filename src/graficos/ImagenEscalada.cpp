#include "ImagenEscalada.h"
#include <iostream>
void ImagenEscalada::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
										b2Vec2 origen, 
										real factorAmplificacion){
	
															
	ArchivoImagen imagen = a_dibujar();
	//if(imagen==NULL) return;//no se dibuja nada
	
	const Rectangulo representacion = obtenerRepresentacion();
	const b2Vec2 top_left_escalada = mundoARender(representacion.topLeft());
	const real altoEscalado = mundoARender(representacion.obtenerAlto());
	const real anchoEscalado = mundoARender(representacion.obtenerAncho());
	
	/*
	Dibujable::dibujarImagen(	cr, origen, factorAmplificacion, top_left_escalada,
								38, 100,imagen,false);
	*/
	
	Dibujable::dibujarImagen(	cr, origen, factorAmplificacion, top_left_escalada,
								anchoEscalado, altoEscalado,imagen,false);
	
	/*Dibujable::dibujarRectangulo(	cr, origen, factorAmplificacion, top_left_escalada,
								anchoEscalado, altoEscalado);*/
}
