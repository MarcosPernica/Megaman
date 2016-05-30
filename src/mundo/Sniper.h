#ifndef SNIPER
#define SNIPER

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Sniper : public Enemigo
{
private:
	Megaman *megaman;
	char estadoSniper;
	real reflejos;
	char cantidadDisparos;
	Plasma arma;
public:
	Sniper(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Sniper(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_MET;};
	static Sniper* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
