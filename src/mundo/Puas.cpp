#include "Puas.h"

Puas::Puas(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion)
			    
{
}

void Puas::interactuar(Megaman *megaman)
{
	megaman->atacado(megaman->obtenerEnergiaMaxima(), NULL);
}

void Puas::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
			     b2Vec2 origen, 
			     real factorAmplificacion)
{
	ImagenEscalada::dibujarEn(cr, origen, factorAmplificacion);
		
}
ArchivoImagen Puas::a_dibujar()
{
	return ArchivoImagen(ANIM_PUAS);
}

const Rectangulo Puas::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-obtenerAncho()/2,
			  obtenerPosicion().y-obtenerAlto()/2,
			  obtenerAncho(),
			  obtenerAlto());
}
