#ifndef BUMBY
#define BUMBY

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Bumby : public Enemigo
{
private:
	Megaman *megaman;
	real tiempo, reflejos;//snapshotados
	bool quieto;//snapshotado
	Plasma arma;
public:
	Bumby(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Bumby(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_BUMBY;};
	static Bumby* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
