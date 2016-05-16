#include "Mundo.h"
#include "Callbacks.h"
#include <algorithm>
#include <iostream>

const b2Vec2 Mundo::gravedad(0, GRAVEDAD);

Mundo::Mundo() : mundo(gravedad)
{
	mundo.SetContactListener(&detectorBalistica);
	mundo.SetContactListener(&detectorSuelo);
	mundo.SetContactListener(&detectorToqueEnemigos);
	crearNivel();
}

void Mundo::crearNivel(){
	Construccion *piso = new Construccion(*this,b2Vec2(300,500), 800, 30);
	construcciones.push_back(piso);
	Construccion *obstruccion = new Construccion(*this,b2Vec2(300,500), 80, 80);
	construcciones.push_back(obstruccion);
	Megaman *megaman = new Megaman(*this, b2Vec2(250,0));
	jugadores.push_back(megaman);
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

std::list<Dibujable*> Mundo::obtenerDibujables() const{/////////COPIA//// esa lista podría ser demasiado grande
	std::list<Dibujable*> ret;
	
	//construcciones
	std::list<Construccion*>::const_iterator it;
	for(it=construcciones.begin(); it!=construcciones.end(); ++it){
		ret.push_back(*it);
	}
	
	//megamans
	std::list<Megaman*>::const_iterator jit;
	for(jit=jugadores.begin(); jit!=jugadores.end(); ++jit){
		ret.push_back(*jit);
	}
	
	//disparos
	std::list<Disparo*>::const_iterator dit;
	for(dit= disparos.begin(); dit!=disparos.end(); ++dit){
		ret.push_back(*dit);
	}
	
	//enemigos
	std::list<Entidad*>::const_iterator eit;
	for(eit = enemigos.begin(); eit!=enemigos.end(); ++eit){
		ret.push_back(*eit);
	}
	
	//powerups
	std::list<PowerUp*>::const_iterator pit;
	for(pit = powerUps.begin(); pit!=powerUps.end(); ++pit){
		ret.push_back(*pit);
	}
	
	return ret;
}

void Mundo::actualizar(real segundosDesdeUltima){
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mundo.Step(segundosDesdeUltima, velocityIterations, positionIterations);

	//megamans
	std::list<Megaman*>::iterator jit;
	for(jit=jugadores.begin(); jit!=jugadores.end(); ++jit){
		(*jit)->actualizar(segundosDesdeUltima);
	}
}
Megaman* Mundo::getMegaman(){
	return *jugadores.begin();
}
