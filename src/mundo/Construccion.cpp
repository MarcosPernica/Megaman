#include "Construccion.h"

Construccion::Construccion(uint ID,
						   Mundo &mundo, 
						   const b2Vec2 &posicion, 
						   real ancho, 
						   real alto,
						   bool fantasma) :
						   Cuerpo(ID,
							  mundo,
							  ancho,
							  alto,
							  MASAINFINITA,	
							  CONSTRUCCIONES,
							  (!fantasma) ? (PERSONAJES | POWERUPS | ENEMIGOS | DISPAROS | JUMPBOX | LEFTBOX | RIGHTBOX) : (PERSONAJES),
							  posicion,
							  false,
							  false,
							  b2Vec2_zero,
							  izquierda,
							  fantasma)
{
}

ushort Construccion::tipoCuerpo() const
{
	return CONSTRUCCIONES;
}
