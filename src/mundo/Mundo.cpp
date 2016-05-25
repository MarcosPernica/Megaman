#include "Mundo.h"
#include "Callbacks.h"
#include <algorithm>
#include <iostream>
#include "CajaAccion.h"
#include "Cuerpo.h"
#include "Escalera.h"
#include "../net/snapshots/FullSnapshot.h"
#include "Bumby.h"
#include "Met.h"
const b2Vec2 Mundo::gravedad(0, GRAVEDAD);

Mundo::Mundo() : mundo(gravedad)
{
	mundo.SetContactListener(&listenerColisiones);
	crearNivel();	
}

void Mundo::crearNivel(){
	agregarConstruccion(18,1,b2Vec2(9,6.5));
	agregarConstruccion(1,6,b2Vec2(0.5,3));
	agregarConstruccion(22,1,b2Vec2(11,0.5));
	agregarConstruccion(1,11,b2Vec2(22.5,5.5));
	agregarConstruccion(8,1,b2Vec2(19,11.5));
	agregarConstruccion(1,3,b2Vec2(14.5,10.5));
	agregarConstruccion(2,1,b2Vec2(13,9.5));
	agregarConstruccion(1,2,b2Vec2(12.5,11));
	agregarConstruccion(3,1,b2Vec2(10.5,11.5));
	agregarConstruccion(1,2,b2Vec2(9.5,10));
	agregarConstruccion(1,5,b2Vec2(7.5,9.5));

	agregarConstruccion(6,1,b2Vec2(8,5.5));
	agregarConstruccion(5,1,b2Vec2(8.5,4.5));
	agregarConstruccion(4,1,b2Vec2(9,3.5));

	agregarConstruccion(6,1,b2Vec2(18,3.5));

	agregarEscalera(4,b2Vec2(14.5,4));
	agregarEscalera(3,b2Vec2(15.5,9.5));

	agregarMegaman(b2Vec2(3,2));

	agregarZonaTransporte(1,1,b2Vec2(8.5,12.5), b2Vec2(3,2));
	agregarZonaMortal(2,1,b2Vec2(11,11.5));

	agregar(new HabilitadorBomba(generarID(),*this,b2Vec2(17.5,5.5)));
	
	controladores.push_back(new CajaSpawnMet(generarID(),*this, b2Vec2(16,5)));
	
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
		destrucciones.push_back(cuerpo->obtenerID());		
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

void Mundo::agregarConstruccion(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new Construccion(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarEscalera(real alto, b2Vec2 posicion)
{
	construcciones.push_back(new Escalera(IDCONSTRUCCIONES,*this,posicion, alto));
}

Megaman *Mundo::agregarMegaman(b2Vec2 posicion)
{
	Megaman *megaman = new Megaman(generarID(),*this, posicion);
	
	megamanes[megaman->obtenerID()] = megaman;
	dibujables[megaman->obtenerID()] = megaman;
	actualizables[megaman->obtenerID()] = megaman;
	snapshotables[megaman->obtenerID()] = megaman;

	return megaman;
}

void Mundo::agregarZonaMortal(real ancho, real alto, b2Vec2 posicion)
{
	controladores.push_back(new ZonaMortal(*this, ancho, alto, posicion));
}

void Mundo::agregarZonaTransporte(real ancho, real alto, b2Vec2 posicion, b2Vec2 posicionDestino)
{
	controladores.push_back(new ZonaTransporte(*this, ancho, alto, posicion, posicionDestino));
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

void Mundo::agregarTareaDiferida(Callback *callback)
{
	tareasDiferidas.push_back(callback);
}

void Mundo::ejecutarTareasDiferidas()
{
	std::list<Callback*>::iterator a = tareasDiferidas.begin();

	while(a != tareasDiferidas.end())
	{
		(*a)->ejecutar();
		delete *a;
		a++;
	}

	tareasDiferidas.clear();
}

bool Mundo::existeElemento(uint ID)
{
	if(snapshotables.find(ID) != snapshotables.end())
		return true;
	return false;
}

void Mundo::actualizar(real segundosDesdeUltima){
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mundo.Step(segundosDesdeUltima, velocityIterations, positionIterations);
	ejecutarTareasDiferidas();
	destruirCuerpos();

	std::map<uint, Actualizable*>::const_iterator i = actualizables.begin();

	while(i != actualizables.end())
		(i++)->second->actualizar(segundosDesdeUltima);	

	std::list<CajaAccion*>::const_iterator a = controladores.begin();

	while(a != controladores.end())
		(*a++)->actualizar(segundosDesdeUltima);
}

std::list<Megaman *> Mundo::obtenerMegamanes()
{
	std::list<Megaman *> megas;

	std::map<uint, Megaman*>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		megas.push_back((i++)->second);

	return megas;
}

std::list<Dibujable *> Mundo::elementosEnZona(b2Vec2 posicion, real ancho, real alto)
{
	b2AABB consulta;
	
	std::list<Dibujable *> aux;
	ElementosEnZona zona(aux);

	consulta.upperBound = b2Vec2(posicion.x+ancho, posicion.y+alto);
	consulta.lowerBound = posicion;

	mundo.QueryAABB(&zona, consulta);

	return aux;
}

Megaman* Mundo::getMegaman(){
	return megamanes.begin()->second;
}

void Mundo::obtenerSnapshot(FullSnapshot& en){
	FullSnapshot nueva;
	std::map<uint, Snapshotable*>::iterator it;
	for(it=snapshotables.begin(); it!=snapshotables.end(); ++it){
		nueva.add((it->second)->getSnapshot());
	}
	en=nueva;
}

/**
 * Inyecta un FullSnapshot.
 * -Los objetos en mundo pero no en el fs, son destruídos
 * -A los objetos en el mundo y en el fs se les inyecta una Snapshot
 * -Los objetos que están sólo en el fs se crean en cualquier estado
 * y se les inyecta una snapshot
 * 
 * Dos Snapshotables representan al mismo objeto sii su ID y su tipo son iguales.
 * */
void Mundo::inyectarSnapshot(FullSnapshot& fs){
	fs.reiniciarRevisadas();
	
	//-----iterar sobre los Snapshotables, encontrar cuales remover y actualizar los que sea necesario
	std::map<uint, Snapshotable*>::iterator it;
	std::set<Snapshotable*> a_eliminar;
	for(it=snapshotables.begin(); it != snapshotables.end(); ++it){
		Snapshotable* snapshotable =it->second;
		if(fs.existe(*snapshotable)){
			snapshotable->setStateFromSnapshot(fs.get(*snapshotable));
			fs.marcarRevisada(*snapshotable);
		}else{
			a_eliminar.insert(snapshotable);
		}
	}
	
	//-----remover los Snapshotable que estén en mundo y no en fs
	std::set<Snapshotable*>::iterator ite;
	for(ite=a_eliminar.begin(); ite!=a_eliminar.end(); ++ite){
		(*ite)->eliminarse(*this);
	}
	
	//-----crear los snapshotables que no fueron revisados al princípio porque no estaban
	const std::set<const Snapshot*> no_revisadas = fs.noRevisadas();
	std::set<const Snapshot*>::const_iterator itr;
	for(itr = no_revisadas.begin(); itr!=no_revisadas.end(); ++itr){
		agregarDesdeSnapshot(*(*itr));
	}
}
/**
#define TIPO_CUERPO 	1//"tipo_cuerpo"
#define TIPO_ENTIDAD 	2//"tipo_entidad"
#define TIPO_DISPARO 	3//"tipo_disparo"
#define TIPO_BUMBY 		4//"tipo_bumby"
#define TIPO_MEGAMAN 	5//"tipo_megaman"
#define TIPO_POWERUP 	6//"tipo_powerup"
#define TIPO_MET 		7//"tipo_met"
#define TIPO_PROTEGIDO 	8//"tipo_protegido"
* */
void Mundo::agregarDesdeSnapshot(const Snapshot& sn){
	switch(sn.getTipo()){
		/*
		case TIPO_CUERPO : 
			agregar(new Cuerpo(
		*/
		//case TIPO_ENTIDAD:
		case TIPO_DISPARO_PLASMA:
			agregar(Plasma::desdeSnapshot(sn,*this));
			break;
		case TIPO_DISPARO_BOMBA:
			agregar(Bomba::desdeSnapshot(sn,*this));
			break;
		case TIPO_BUMBY:
			agregar(Bumby::desdeSnapshot(sn,*this));
			break;
		//case TIPO_MEGAMAN :
		//	agregar(new Megaman(sn));
		//	break;
		/*
		case TIPO_POWERUP:
			agregar(PowerUp::desdeSnapshot(sn,*this));
			break;
		*/
		case TIPO_MET:
			agregar(Met::desdeSnapshot(sn,*this));
			break;
		//case TIPO_PROTEGIDO:
		//	agregar(new Protegido(sn));
		//	break;
	}
}
