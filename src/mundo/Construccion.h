#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>

class Construccion: public Cuerpo
{	
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, bool fantasma = false);
	virtual ushort tipoCuerpo() const;
};

#endif
