#include "PowerUp.h"

NuevaVida::NuevaVida(Mundo &mundo, const b2Vec2 &posicion) : PowerUp(mundo, PROBANUEVAVIDA, posicion)
{
}

void NuevaVida::aumentar(Megaman & megaman)
{
	megaman.aumentarVida();
	eliminarPowerUp();
}

CapsulaEnergiaChica::CapsulaEnergiaChica(Mundo &mundo, const b2Vec2 &posicion) : PowerUp(mundo, PROBAENERGIACHICA, posicion)
{
}

void CapsulaEnergiaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(2);
	eliminarPowerUp();
}

CapsulaEnergiaGrande::CapsulaEnergiaGrande(Mundo &mundo, const b2Vec2 &posicion) : PowerUp(mundo, PROBAENERGIAGRANDE, posicion)
{
}

void CapsulaEnergiaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(6);
	eliminarPowerUp();
}

CapsulaPlasmaChica::CapsulaPlasmaChica(Mundo &mundo, const b2Vec2 &posicion) : PowerUp(mundo, PROBAPLASMACHICA, posicion)
{
}

void CapsulaPlasmaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(2);
	eliminarPowerUp();
}

CapsulaPlasmaGrande::CapsulaPlasmaGrande(Mundo &mundo, const b2Vec2 &posicion) : PowerUp(mundo, PROBAPLASMAGRANDE, posicion)
{
}

void CapsulaPlasmaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(6);
	eliminarPowerUp();
}

PowerUp::PowerUp(Mundo &mundo,
				 real probabilidadAparicion,
				 const b2Vec2 &posicion) :
				 probabilidadAparicion(probabilidadAparicion),
				 Cuerpo(mundo,
						ANCHOSPRITEPOWERUP,
						ALTOSPRITEPOWERUP,
						MASAPOWERUP,
						POWERUPS,
						CONSTRUCCIONES | PERSONAJES,
						posicion,	
						false,
						true,	
						b2Vec2 VELOCIDADPOWERUP)
			     
{
	if (probabilidadAparicion < 0 || probabilidadAparicion > 1)
		probabilidadAparicion = 0;

	this->probabilidadAparicion = probabilidadAparicion;
}

real PowerUp::obtenerProbabilidadAparicion()
{
	return probabilidadAparicion;
}

void PowerUp::eliminarPowerUp()
{
	
}