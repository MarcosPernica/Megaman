#ifndef PUERTA
#define PUERTA

#include "Cuerpo.h"

class Puerta: public Cuerpo
{	
public:
	Puerta(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};
	
};


#endif
