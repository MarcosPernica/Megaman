#include "Mundo.h"
#include "Callbacks.h"
#include <algorithm>
#include "PowerUp.h"
#include "Entidad.h"
#include "Megaman.h"
#include "Disparo.h"
#include "Construccion.h"

const b2Vec2 Mundo::gravedad(0, GRAVEDAD);

Mundo::Mundo() : mundo(gravedad)
{
	mundo.SetContactListener(&detectorBalistica);
	mundo.SetContactListener(&detectorSuelo);
	mundo.SetContactListener(&detectorToqueEnemigos);
}

b2World & Mundo::obtenerMundo()
{
	return mundo;
}

void Mundo::danarZona(b2AABB zona, uint dano)
{
	DanarRadio danoRadio(dano);

	mundo.QueryAABB(&danoRadio, zona);
}

void Mundo::eliminar(Entidad * entidad)
{
	std::list<Entidad*>::iterator i = std::find(enemigos.begin(), enemigos.end(), entidad);

	if (i != enemigos.end())
	{
		destrucciones.push_back(*i);
		enemigos.erase(i);
	}
}

void Mundo::eliminar(Disparo * disparo)
{
	std::list<Disparo*>::iterator i = std::find(disparos.begin(), disparos.end(), disparo);

	if (i != disparos.end())
	{
		destrucciones.push_back(*i);
		disparos.erase(i);
	}
}

void Mundo::eliminar(PowerUp * powerUp)
{
	std::list<PowerUp*>::iterator i = std::find(powerUps.begin(), powerUps.end(), powerUp);

	if (i != powerUps.end())
	{
		destrucciones.push_back(*i);
		powerUps.erase(i);
	}
}

void Mundo::agregar(Disparo * disparo)
{
	disparos.push_back(disparo);
}

void Mundo::agregar(PowerUp * powerUp)
{
	powerUps.push_back(powerUp);
}

void Mundo::agregar(Entidad * entidad)
{
	enemigos.push_back(entidad);
}

void Mundo::destruirCuerpos()
{
	std::list<Cuerpo*>::iterator i = destrucciones.begin();

	while (i != destrucciones.end())
		delete *i;
	destrucciones.clear();
}
