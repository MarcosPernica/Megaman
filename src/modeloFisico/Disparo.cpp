#include "Disparo.h"
#include "Mundo.h"
#include <list>
#include "Entidad.h"
#include <Box2D/Box2D.h>

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

Disparo::Disparo(Mundo &mundo,
				 uint daño,
				 real ancho,
				 real alto,
				 real masa,
				 const b2Vec2 &posicion,
				 bool gravitacional,
				 const b2Vec2 &velocidad,
				 bool disparoMegaman) :
				 dano(dano),
				 disparoMegaman(disparoMegaman),
			     Cuerpo(mundo,
						ancho,
						alto,
						masa,
						DISPAROS,
						CONSTRUCCIONES | PERSONAJES | ENEMIGOS,
						posicion,
						false,
						true,
						velocidad)
{
}

bool Disparo::interactuar(Entidad *entidad)
{
	entidad->atacado(dano);
	return true;
}

Bomba::Bomba(Mundo & mundo, 
	         const b2Vec2 & posicion,
	         const b2Vec2 & velocidad) :
		     tiempoTotal(TIEMPOEXPLOSIONBOMBA),
			 Disparo(mundo,
					 DANOBOMBA,
					 ANCHOSPRITEBOMBA,
					 ALTOSPRITEBOMBA,
				     MASABOMBA,
				     posicion,
					 true,
				     velocidad)
{
}

bool Bomba::interactuar(Entidad * entidad)
{
	return false;
}

void Bomba::actualizar(real deltaT)
{
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

Disparo * Bomba::nuevo(const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Bomba(obtenerMundo(), posicion, velocidad);
}

void Bomba::explotar()
{
	b2AABB consulta;
	consulta.upperBound = obtenerLeftTopCajaMagnificada(RADIOEXPLOSION);
	consulta.lowerBound = obtenerRightBottomCajaMagnificada(RADIOEXPLOSION);

	obtenerMundo().danarZona(consulta, DANOBOMBA);
	obtenerMundo().eliminar(this);
}

Plasma::Plasma(Mundo & mundo,
			   const b2Vec2 & posicion,
			   const b2Vec2 & velocidad) :
			   Disparo(mundo,
					   DANOPLASMA,
					   ANCHOSPRITEPLASMA,
					   ALTOSPRITEPLASMA,
					   MASAPLASMA,
					   posicion,
				       true,
		               velocidad)
{
}

uint Plasma::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADPLASMA;
}

Disparo * Plasma::nuevo(const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Plasma(obtenerMundo(), posicion, velocidad);
}
