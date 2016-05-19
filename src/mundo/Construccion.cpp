#include "Construccion.h"

Construccion::Construccion(uint ID,
						   Mundo &mundo, 
						   const b2Vec2 &posicion, 
						   real ancho, 
						   real alto,
						   ushort tipo,
						   bool fantasma) :
						   Cuerpo(ID,
								mundo,
								  ancho,
								  alto,
								  MASAINFINITA,	
								  CONSTRUCCIONES,
								  (!fantasma) ? (PERSONAJES | POWERUPS | ENEMIGOS | DISPAROS) : (PERSONAJES),
							      posicion,
								  false,
							      false,
							      b2Vec2_zero,
							      izquierda,
							      fantasma),
					           tipo(tipo)
{
}

char Construccion::tipoCuerpo() const
{
	return CONSTRUCCIONES | tipo;
}
