#ifndef RECTANGULO
#define RECTANGULO

#include "../mundo/Definiciones.h"
#include <Box2D/Box2D.h>

class Rectangulo{
public: //Solo para debug
	real x;
	real y;
	real w;
	real h;
public:
	Rectangulo(b2Vec2 topLeft, b2Vec2 botRight) : x(topLeft.x), y(topLeft.y), w(botRight.x-topLeft.x), h(botRight.y-topLeft.y){};
	Rectangulo(real x, real y, real ancho, real alto) : x(x), y(y), w(ancho), h(alto){};

	real obtenerAncho() const
	{
		return w;
	};

	real obtenerAlto() const
	{
		return h;
	};

	b2Vec2 topLeft() const
	{
		return b2Vec2(x, y);
	};

	b2Vec2 topRight() const
	{
		return b2Vec2(x+w,y);	
	};

	b2Vec2 bottomLeft() const
	{
		return b2Vec2(x,y+h);
	};

	b2Vec2 rightBottom() const
	{
		return b2Vec2(x+w, y+h);
	};
};
#endif
