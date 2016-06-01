#ifndef MET
#define MET

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

class Megaman;

class Met : public Enemigo
{
private:
	Megaman *megaman;
	real tiempo;//snapshoteado
	char estadoMet;//snapshoteado
	bool accionEjecutada;//snapshoteado
	Plasma arma;//no lo puedo snapshotear
public:
	Met(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Met(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_MET;};
	static Met* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

#endif
