#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>

class Construccion: public Cuerpo
{
public:
	Construccion(Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	char tipoCuerpo() const;
};

#endif
