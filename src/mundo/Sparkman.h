#ifndef SPARKMAN
#define SPARKMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "Orientaciones.h"

class Megaman;

class Sparkman : public Enemigo
{
private:
	Megaman *megaman;
	char estadoSparkman;
	real reflejos;
	Chispa arma;
	Orientaciones orientacion;
public:
	Sparkman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Sparkman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Sparkman);
	static Sparkman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
