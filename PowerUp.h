#ifndef POWERUP
#define POWERUP

#include "Cuerpo.h"
#include "Megaman.h"
#include "Vector2D.h"
#include "Mundo.h"

class PowerUp : public Cuerpo
{
private:
	real probabilidadAparicion;
	Mundo &mundo;
public:
	PowerUp(Mundo &mundo, real probabilidadAparicion, real masa, const Vector2D &posicion, const Vector2D &velocidad = PowerUp::velocidad, bool gravitacional = true);

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();

	virtual void aumentar(Megaman &megaman) = 0;

	static const Vector2D velocidad;
};



class NuevaVida : public PowerUp
{
public:
	NuevaVida(Mundo &mundo, const Vector2D &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(Mundo &mundo, const Vector2D &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(Mundo &mundo, const Vector2D &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(Mundo &mundo, const Vector2D &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(Mundo &mundo, const Vector2D &posicion);
	void aumentar(Megaman &megaman);
};

#endif