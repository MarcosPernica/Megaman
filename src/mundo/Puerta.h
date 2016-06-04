#ifndef PUERTA
#define PUERTA

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Puerta : public Enemigo
{
private:
public:
	Puerta(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Puerta(){};

	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Met);
	static Met* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
