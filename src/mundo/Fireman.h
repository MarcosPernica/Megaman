#ifndef FIREMAN
#define FIREMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Fireman : public Enemigo
{
private:
	Megaman *megaman;
	char estadoFireman;
	real reflejos;
	Fuego arma;
public:
	Fireman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Fireman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Fireman);
	static Fireman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
