#ifndef JUMPINGSNIPER
#define JUMPINGSNIPER

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class JumpingSniper : public Enemigo
{
private:
	Megaman *megaman;
	char estadoSniper;
	real reflejos;
	char cantidadDisparos;
	Plasma arma;
public:
	JumpingSniper(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~JumpingSniper(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_MET;};
	static JumpingSniper* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
