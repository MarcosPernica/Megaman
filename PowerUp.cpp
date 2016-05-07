#include "PowerUp.h"

const Vector2D PowerUp::velocidad VELOCIDADPOWERUP;

NuevaVida::NuevaVida(Mundo &mundo, const Vector2D &posicion) : PowerUp(mundo, PROBANUEVAVIDA, MASAPOWERUP, posicion)
{
}

void NuevaVida::aumentar(Megaman & megaman)
{
	megaman.aumentarVida();
	eliminarPowerUp();
}

CapsulaEnergiaChica::CapsulaEnergiaChica(Mundo &mundo, const Vector2D &posicion) : PowerUp(mundo, PROBAENERGIACHICA, MASAPOWERUP, posicion)
{
}

void CapsulaEnergiaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(2);
	eliminarPowerUp();
}

CapsulaEnergiaGrande::CapsulaEnergiaGrande(Mundo &mundo, const Vector2D &posicion) : PowerUp(mundo, PROBAENERGIAGRANDE, MASAPOWERUP, posicion)
{
}

void CapsulaEnergiaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(6);
	eliminarPowerUp();
}

CapsulaPlasmaChica::CapsulaPlasmaChica(Mundo &mundo, const Vector2D &posicion) : PowerUp(mundo, PROBAPLASMACHICA, MASAPOWERUP, posicion)
{
}

void CapsulaPlasmaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(2);
	eliminarPowerUp();
}

CapsulaPlasmaGrande::CapsulaPlasmaGrande(Mundo &mundo, const Vector2D &posicion) : PowerUp(mundo, PROBAPLASMAGRANDE, MASAPOWERUP, posicion)
{
}

void CapsulaPlasmaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(6);
	eliminarPowerUp();
}

PowerUp::PowerUp(Mundo &mundo, 
	             real probabilidadAparicion,
			     real masa, 
			     const Vector2D &posicion, 
				 const Vector2D &velocidad,
			     bool gravitacional) :
				 mundo(mundo),
				 Cuerpo(masa, posicion, gravitacional, velocidad)
{
	if (probabilidadAparicion < 0 || probabilidadAparicion > 1)
		return;

	this->probabilidadAparicion = probabilidadAparicion;
}

real PowerUp::obtenerProbabilidadAparicion()
{
	return probabilidadAparicion;
}

void PowerUp::eliminarPowerUp()
{
	mundo.eliminar(this);
}