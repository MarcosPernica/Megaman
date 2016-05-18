#ifndef POWERUP
#define POWERUP

#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "Actualizable.h"

class PowerUp : public Cuerpo, public Actualizable
{
private:
	real probabilidadAparicion;
public:
	PowerUp(uint ID, 
			Mundo &mundo,
			real probabilidadAparicion,
			const b2Vec2 &posicion);

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();

	void actualizar(real deltaT){};
	virtual void aumentar(Megaman &megaman) = 0;
};



class NuevaVida : public PowerUp
{
public:
	NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};

#endif
