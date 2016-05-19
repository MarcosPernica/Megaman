#ifndef MET
#define MET

#include "Protegido.h"
#include <Box2D/Box2D.h>

class Met : public Protegido
{
private:

public:
	Met(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Met(){};

	void actualizar(real deltaT){};
	char tipoCuerpo() const {return ENEMIGOS;};
};

#endif
