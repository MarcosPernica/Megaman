#include "Escalera.h"
#include "Definiciones.h"

Escalera::Escalera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real alto) :
		   Construccion(ID,mundo,posicion, ANCHOESCALERA,alto,true)
{
}

ushort Escalera::tipoCuerpo() const
{
	return ESCALERAS;
}
