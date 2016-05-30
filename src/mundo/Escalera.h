#ifndef ESCALERA
#define ESCALERA

#include "Construccion.h"
#include <Box2D/Box2D.h>

#define DETECTORTOPEESCALERA 2
#define DETECTORFONDOESCALERA 1
#define ALTODETECTORESCALERA 0.1


class Escalera: public Construccion
{	
public:
	Escalera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real alto);
	ushort tipoCuerpo() const;
};

#endif
