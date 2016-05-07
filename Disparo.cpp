#include "Disparo.h"
#include "Mundo.h"
#include <list>

void Disparo::actualizar(real DeltaT)
{
	calcularFisicas(DeltaT);
}

bool Disparo::soloEnemigos()
{
	return true;
}

bool Disparo::lanzable()
{
	return false;
}

Disparo::Disparo(real daño,
				 real masa, 
	             const Vector2D & posicion, 
	             bool gravitacional, 
	             const Vector2D & velocidad) : 
	             daño(daño), 
				 Cuerpo(masa, posicion, gravitacional, velocidad)
{
}

bool Disparo::interactuar(Entidad *entidad)
{
	entidad->atacado(daño);
	return true;
}

Bomba::Bomba(Mundo & mundo, 
	         const Vector2D & posicion,
	         const Vector2D & velocidad) :
			 mundo(mundo),
		     tiempoTotal(TIEMPOEXPLOSIONBOMBA),
			 Disparo(DANOBOMBA, MASABOMBA, posicion, true, velocidad),
			 radio(obtenerPosicion(), RADIOEXPLOSION, RADIOEXPLOSION)
{
}

bool Bomba::interactuar(Entidad * entidad)
{
	return false;
}

bool Bomba::soloEnemigos()
{
	return false;
}

void Bomba::actualizar(real deltaT)
{
	tiempoTotal -= deltaT;

	if (tiempoTotal <= 0)
	{
		explotar();
		mundo.eliminar(this);
	}
}

real Bomba::multiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADBOMBA;
}

bool Bomba::lanzable()
{
	return true;
}

Disparo * Bomba::nuevo(const Vector2D & posicion, const Vector2D & velocidad)
{
	Bomba *aux = new Bomba(*this);
	aux->modificarPosicion(posicion);
	aux->modificarVelocidad(velocidad);

	return aux;
}

void Bomba::explotar()
{
	/*Posible problema si el objeto i se destruyo porque murio mientras se itera.*/
	std::list<Entidad *> ilusos = mundo.obtenerlistaColisiones(radio);
	std::list<Entidad *>::iterator i = ilusos.begin();

	while (i != ilusos.end())
		interactuar(*i);
}

Plasma::Plasma(const Vector2D &posicion, const Vector2D &velocidad) : 
		Disparo(DANOPLASMA, MASANULA, posicion, false, velocidad)
{
}

real Plasma::multiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADPLASMA;
}

Disparo * Plasma::nuevo(const Vector2D & posicion, const Vector2D & velocidad)
{
	Plasma *aux = new Plasma(*this);
	aux->modificarPosicion(posicion);
	aux->modificarVelocidad(velocidad);

	return aux;
}
