#include "Bumby.h"
#include "Mundo.h"
#include "Megaman.h"
#include <math.h>
#include <iostream>

#define DISTANCIADISPARO 2
#define TIEMPODISPARO 1
#define TIEMPOREFLEJO 1

Bumby::Bumby(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOBUMBY,
				   ALTOBUMBY,
				   &arma,
				   0,
			      	   ENERGIAMAXIMABUMBY,
				   MASABUMBY,
				   VELOCIDADSALTOBUMBY,
				   VELOCIDADCORRERBUMBY, 
				   ENEMIGOS,
				   CONSTRUCCIONES | DISPAROS,
				   posicion, 
				   false,
				   false,
				   velocidad)
{
	tiempo = 0;	
	reflejos = 0;
	quieto = true;
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Bumby::actualizarMaquinaEstados(real deltaT)
{	
	real direccion = megaman->obtenerPosicion().x-obtenerPosicion().x;

	if(abs(direccion) >= DISTANCIAVISION*0.5)
	{
		dejarCorrer();
		return;
	}

	reflejos += deltaT;

	if(abs(direccion) > DISTANCIADISPARO)
		tiempo = 0;
	else
	{
		tiempo += deltaT;
		if(tiempo >= TIEMPODISPARO)
		{
			tiempo = 0;
			disparar(b2Vec2(0,1));
		}
	}

	if(reflejos >= TIEMPOREFLEJO)
	{
		/*Reacciona al estimulo*/

		if(quieto && abs(direccion) > 0.25)
		{
			if(direccion >= 0)
				modificarOrientacion(derecha);
			else 	
				modificarOrientacion(izquierda);

			correr();
			quieto = false;
		}
		else if(!quieto && abs(direccion) <= 0.25)
		{
			dejarCorrer();
			quieto = true;
		}
		
		reflejos = 0;
	}
}

void Bumby::actualizar(real deltaT)
{
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}
#define PROP_TIEMPO "tiempo"
#define PROP_REFLEJOS "reflejos"
#define PROP_QUIETO "quieto"
/*
real tiempo, reflejos;//snapshotados
bool quieto;//snapshotado
*/
void Bumby::agregarPropiedadesASnapshot(Snapshot& sn){
	sn.agregarPropiedad(PROP_TIEMPO,(int)(tiempo*1000));
	sn.agregarPropiedad(PROP_REFLEJOS,(int)(reflejos*1000));
	sn.agregarPropiedad(PROP_QUIETO,(int)quieto);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Bumby::setStateFromSnapshot(const Snapshot& sn){
	tiempo = (float)sn.obtenerPropiedad(PROP_TIEMPO)/1000;
	reflejos = (float)sn.obtenerPropiedad(PROP_REFLEJOS)/1000;
	quieto = (bool)sn.obtenerPropiedad(PROP_QUIETO);
	Enemigo::setStateFromSnapshot(sn);
}

Bumby* Bumby::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Bumby* p = new Bumby(sn.getID(),mundo,b2Vec2_zero,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
