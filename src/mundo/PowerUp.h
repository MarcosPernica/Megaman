#ifndef POWERUP
#define POWERUP

#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>

class PowerUp : public Cuerpo
{
private:
	real probabilidadAparicion;
public:
	PowerUp(Mundo &mundo,
			real probabilidadAparicion,
			const b2Vec2 &posicion);

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();

	virtual void aumentar(Megaman &megaman) = 0;
};



class NuevaVida : public PowerUp
{
public:
	NuevaVida(Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};

#endif
