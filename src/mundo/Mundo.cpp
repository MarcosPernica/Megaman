#include "Mundo.h"
#include "Callbacks.h"
#include <algorithm>
#include <iostream>
#include "CajaSpawn.h"

const b2Vec2 Mundo::gravedad(0, GRAVEDAD);

Mundo::Mundo() : mundo(gravedad)
{
	mundo.SetContactListener(&listenerColisiones);
	crearNivel();	
}

void Mundo::crearNivel(){
	Construccion *piso = new Construccion(IDCONSTRUCCIONES,*this,b2Vec2(5,8), 10, 1);
	construcciones.push_back(piso);

	Construccion *paredIzquierda = new Construccion(IDCONSTRUCCIONES,*this,b2Vec2(0,3.5), 1, 10);
	construcciones.push_back(paredIzquierda);

	Construccion *paredDerecha = new Construccion(IDCONSTRUCCIONES,*this,b2Vec2(10,3.5), 1, 10);
	construcciones.push_back(paredDerecha);

	Construccion *escalera = new Construccion(IDCONSTRUCCIONES,*this,b2Vec2(2,5), 1.1, 5, ESCALERA, true);
	construcciones.push_back(escalera);

	Construccion *obstruccion = new Construccion(IDCONSTRUCCIONES,*this,b2Vec2(5,7), 1, 1);
	construcciones.push_back(obstruccion);
	Megaman *megaman = new Megaman(generarID(),*this, b2Vec2(2.5,0));

	uint ID = generarID();
	controladores[ID] = new CajaSpawn(ID,*this,b2Vec2(5,2));
	
	megamanes[megaman->obtenerID()] = megaman;
	dibujables[megaman->obtenerID()] = megaman;
	actualizables[megaman->obtenerID()] = megaman;
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

void Mundo::eliminar(Cuerpo * cuerpo)
{
	if (snapshotables.find(cuerpo->obtenerID()) != snapshotables.end() || megamanes.find(cuerpo->obtenerID()) != megamanes.end())
	{
		std::cout << cuerpo->obtenerID() << std::endl;
		destrucciones.push_back(cuerpo->obtenerID());		
	}
}

void Mundo::agregar(Disparo * disparo)
{
	snapshotables[disparo->obtenerID()] = disparo;
	dibujables[disparo->obtenerID()] = disparo;
	actualizables[disparo->obtenerID()] = disparo;
}

void Mundo::agregar(PowerUp * powerUp)
{
	snapshotables[powerUp->obtenerID()] = powerUp;
	dibujables[powerUp->obtenerID()] = powerUp;
	actualizables[powerUp->obtenerID()] = powerUp;
}

void Mundo::agregar(Entidad * entidad)
{
	snapshotables[entidad->obtenerID()] = entidad;
	dibujables[entidad->obtenerID()] = entidad;
	actualizables[entidad->obtenerID()] = entidad;
}

void Mundo::destruirCuerpos()
{
	bool borrado = false;
	std::list<uint>::iterator i = destrucciones.begin();

	while (i != destrucciones.end())	
	{
		if(actualizables.find(*i) != actualizables.end())
		{
			delete actualizables[*i];
			borrado = true;
			actualizables.erase(*i);
		}

		if(megamanes.find(*i) != megamanes.end())
		{
			if(!borrado)
			{
				delete megamanes[*i];
				borrado = true;			
			}
			megamanes.erase(*i);
		}

		if(snapshotables.find(*i) != snapshotables.end())
		{
			if(!borrado)
			{
				delete snapshotables[*i];
				borrado = true;
			}
			snapshotables.erase(*i);
		}

		if(dibujables.find(*i) != dibujables.end())
		{
			if(!borrado)
			{
				delete dibujables[*i];
				borrado = true;
			}
			dibujables.erase(*i);	
		}
	i++;
	}
	destrucciones.clear();
}

bool Mundo::existeElemento(uint ID)
{
	if(snapshotables.find(ID) != snapshotables.end())
		return true;
	return false;
}

std::list<Dibujable*> Mundo::obtenerDibujables() const{/////////COPIA//// esa lista podría ser demasiado grande
	std::list<Dibujable*> ret;
	
	std::map<uint, Dibujable*>::const_iterator i = dibujables.begin();
	std::list<Construccion*>::const_iterator a = construcciones.begin();

	while(a != construcciones.end())
		ret.push_back(*a++);
	
	
	while(i != dibujables.end())
		ret.push_back(i++->second);
	
	return ret;
}

void Mundo::actualizar(real segundosDesdeUltima){
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mundo.Step(segundosDesdeUltima, velocityIterations, positionIterations);
	destruirCuerpos();

	std::map<uint, Actualizable*>::const_iterator i = actualizables.begin();

	while(i != actualizables.end())
		(i++)->second->actualizar(segundosDesdeUltima);	

	/*Hardcode*/
	controladores.begin()->second->actualizar(segundosDesdeUltima);
}

Megaman* Mundo::getMegaman(){
	return megamanes.begin()->second;
}
