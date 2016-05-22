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
	ushort tipoCuerpo() const {return ENEMIGOS;};
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_MET;};
	static Met* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
