#ifndef BOMBMAN
#define BOMBMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Bombman : public Enemigo
{
private:
	Megaman *megaman;
	uint IDTarget;
	char estadoBombman;
	real reflejos;
	Bomba arma;
public:
	Bombman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Bombman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Bombman);
	static Bombman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
