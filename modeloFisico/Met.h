#ifndef MET
#define MET

#include "Protegido.h"
#include <Box2D\Box2D.h>

class Met : public Protegido
{
private:

public:
	Met(Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
};

#endif
