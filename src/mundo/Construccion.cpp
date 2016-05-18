#include "Construccion.h"

Construccion::Construccion(uint ID,
						   Mundo &mundo, 
						   const b2Vec2 &posicion, 
						   real ancho, 
						   real alto) :
						   Cuerpo(ID,
								mundo,
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
