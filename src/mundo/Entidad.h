#ifndef ENTIDAD
#define ENTIDAD

#include "Definiciones.h"
#include "Cuerpo.h"
#include "Actualizable.h"
#include "Enemigo.h"
#include "../net/snapshots/Snapshotable.h"
#include <Box2D/Box2D.h>
class Mundo;
class Entidad : public Cuerpo, public Actualizable, public Enemigo
{
private:
	uint energia, energiaMaxima;
	Mundo &mundo;
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

	void recuperarEnergia(uint cantidadEnergia);
	uint obtenerEnergiaMaxima();
	uint obtenerEnergiaActual();
	virtual void atacado(uint danio);


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
};

#endif
