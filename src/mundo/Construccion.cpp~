#include "Construccion.h"

Construccion::Construccion(Mundo &mundo, 
						   const b2Vec2 &posicion, 
						   real ancho, 
						   real alto) :
						   Cuerpo(mundo,
								  ancho,
								  alto,
								  MASAINFINITA,	
								  CONSTRUCCIONES,
								  PERSONAJES | POWERUPS | ENEMIGOS | DISPAROS,
							      posicion,
								  false,
							      false)
{
}

char Construccion::tipoCuerpo() const
{
	return CONSTRUCCIONES;
}
