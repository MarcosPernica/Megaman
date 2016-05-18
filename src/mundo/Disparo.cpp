#include "Disparo.h"
#include "Mundo.h"
#include <list>
#include "Entidad.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "../common/Rectangulo.h"

void Disparo::actualizar(real DeltaT)
{

}

bool Disparo::lanzable()
{
	return false;
}

char Disparo::tipoCuerpo() const
{
	return DISPAROS;
}

bool Disparo::megamanLoDisparo() const
{
	return disparoMegaman;
}

Disparo::Disparo(uint ID, Mundo &mundo,
				 uint dano,
				 real ancho,
				 real alto,
				 real masa,
				 const b2Vec2 &posicion,
				 bool gravitacional,
				 const b2Vec2 &velocidad,
				 bool disparoMegaman) :
			     	 Cuerpo(ID, 
						mundo,
						ancho,
						alto,
						masa,
						DISPAROS,
						CONSTRUCCIONES | PERSONAJES | ENEMIGOS,
						posicion,
						false,
						gravitacional,
						velocidad),
				dano(dano),
				 disparoMegaman(disparoMegaman)
{
}

bool Disparo::perecedero()
{
	return true;
}

bool Disparo::interactuar(Entidad *entidad)
{
	entidad->atacado(dano);
	return true;
}

Bomba::Bomba(uint ID, 
		 Mundo & mundo, 
	         const b2Vec2 & posicion,
	         const b2Vec2 & velocidad) :
			 Disparo(ID, 
				 mundo,
				 DANOBOMBA,
				ANCHOSPRITEBOMBA,
				 ALTOSPRITEBOMBA,
				    MASABOMBA,
				     posicion,
					 true,
				     velocidad),
			tiempoTotal(TIEMPOEXPLOSIONBOMBA)
{
}

bool Bomba::interactuar(Entidad * entidad)
{
	return false;
}

bool Bomba::perecedero()
{
	return false;
}

void Bomba::actualizar(real deltaT)
{
	std::cout << "Actualizando" << std::endl;
	tiempoTotal -= deltaT;

	if (tiempoTotal <= 0)
	{
		explotar();
		obtenerMundo().eliminar(this);
	}
}

uint Bomba::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADBOMBA;
}

bool Bomba::lanzable()
{
	return true;
}

Disparo * Bomba::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Bomba(ID, obtenerMundo(), posicion, velocidad);
}

void Bomba::explotar()
{
	b2AABB consulta;
	Rectangulo rect = obtenerCajaMagnificada(RADIOEXPLOSION);

	consulta.upperBound = rect.topLeft();
	consulta.lowerBound = rect.rightBottom();

	obtenerMundo().danarZona(consulta, DANOBOMBA);
	obtenerMundo().eliminar(this);
}

Plasma::Plasma(uint ID, 
			   Mundo & mundo,
			   const b2Vec2 & posicion,
			   const b2Vec2 & velocidad) :
			   Disparo(ID,
					   mundo,
					   DANOPLASMA,
					   ANCHOSPRITEPLASMA,
					   ALTOSPRITEPLASMA,
					   MASAPLASMA,
					   posicion,
				       false,
		               velocidad)
{
}

uint Plasma::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADPLASMA;
}

Disparo * Plasma::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Plasma(ID, obtenerMundo(), posicion, velocidad);
}
