#ifndef RINGMAN
#define RINGMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "Orientaciones.h"

class Megaman;

class Ringman : public Enemigo
{
private:
	char estadoRingman;
	real reflejos;
	Anillo arma;
	Orientaciones orientacion;
	uint disparos;
public:
	Ringman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Ringman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Ringman);
	static Ringman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
