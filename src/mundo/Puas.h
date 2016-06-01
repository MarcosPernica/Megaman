#ifndef PUAS
#define PUAS

#include "CajaAccion.h"

class Puas : public CajaAccion
{
private:
	
public:
	Puas(Mundo &mundo,
			real ancho,
			real alto,
			const b2Vec2 &posicion);
	~Puas(){};
	void interactuar(Megaman *megaman);
};

#endif
