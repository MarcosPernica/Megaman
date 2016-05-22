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

	cr->rectangle(aux.x, 
		      aux.y, 
		      ancho*factorAmplificacion, 
		      alto*factorAmplificacion);

	cr->stroke();
}
