#include "Fondo.h"
#include "Animacion.h"

Fondo::Fondo(double ancho, double alto) : ancho(ancho), alto(alto)
{
};


void Fondo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
		
}
ArchivoImagen Fondo::a_dibujar(){
	return ArchivoImagen(ANIM_FONDO);
}
const Rectangulo Fondo::obtenerRepresentacion() const{
	return Rectangulo(	0,
						0,
						ancho,
						alto
					);
}

