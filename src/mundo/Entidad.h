#ifndef ENTIDAD
#define ENTIDAD

#include "Definiciones.h"

#include "Actualizable.h"
#include "../net/snapshots/Snapshotable.h"
#include <Box2D/Box2D.h>
#include "Cuerpo.h"

class Disparo;

class Entidad : public Cuerpo, public Actualizable
{
private:
	int energia, energiaMaxima;//snapshoteados
	Mundo &mundo;
	bool muerta;//snapshoteado
public:
	Entidad(uint ID, 
		Mundo &mundo,
		real ancho,
		real alto,
		uint energiaMaxima, 
		real masa,
		ushort categoria,
		ushort colisionaCon,
		const b2Vec2 &posicion,
		bool rotable = false,
		bool gravitacional = true,
		const b2Vec2 &velocidad = b2Vec2_zero,
		Orientaciones orientacion = derecha);
	~Entidad(){};

	void recuperarEnergia(int cantidadEnergia);
	uint obtenerEnergiaMaxima();
	uint obtenerEnergiaActual();
	bool estaMuerta();
	void revivir();
	virtual void atacado(int danio, Disparo *disparo);
	virtual void alMorir();


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo(){return TIPO_ENTIDAD;};
};

#endif
