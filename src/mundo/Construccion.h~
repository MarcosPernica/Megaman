#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>
#include "../graficos/ImagenRectangulo.h"
class Construccion: public Cuerpo
{
private:
	ushort tipo;	
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, ushort tipo = 0, bool fantasma = false);
	char tipoCuerpo() const;
};

#endif
