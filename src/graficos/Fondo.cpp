#include "Fondo.h"
#include "Animacion.h"

Fondo::Fondo(double ancho, double alto) : ancho(ancho), alto(alto)
{
};


void Fondo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
		
}
Glib::RefPtr<Gdk::Pixbuf> Fondo::a_dibujar(){
	if(textura == NULL){
		textura = Gdk::Pixbuf::create_from_file(ANIM_FONDO);
	}
	return textura;
}
const Rectangulo Fondo::obtenerRepresentacion() const{
	return Rectangulo(	0,
						0,
						ancho,
						alto
					);
}

