#include "Bumby.h"
#include "Mundo.h"
#include "Megaman.h"
#include <math.h>
#include <iostream>
#include "../net/snapshots/Snapshot.h"

#define DISTANCIADISPARO 2
#define TIEMPODISPARO 1
#define TIEMPOREFLEJO 1

Bumby::Bumby(uint ID,
	     Mundo & mundo, 
	     const b2Vec2 & posicion,
	     const b2Vec2 & velocidad) : 
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
		     CONSTRUCCIONES,
		     posicion, 
		     false,
		     false,
		     velocidad),
	     Animado(&animacion_volando),
	     animacion_volando(ANIM_BUMBY_VOLANDO,0.1),
	     megaman(NULL),
	     IDTarget(0),
	     tiempo(0),
	     reflejos(0),
	     quieto(true),
	     arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES)
				 
{
}

void Bumby::actualizarMaquinaEstados(real deltaT)
{	
	/*Sigue a un determinado jugador (El mas cercano).*/

	if(!megaman || !obtenerMundo().existeMegaman(IDTarget))
	{
		megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = megaman->obtenerID();
	}

	real direccion = megaman->obtenerPosicion().x-obtenerPosicion().x;

	/*Avanza la animacion.*/
	avanzar(deltaT);

	if(abs(direccion) >= DISTANCIAVISION*0.5)
	{
		dejarCorrer();
		return;
	}

	reflejos += deltaT;

	/*Dispara solo si esta cerca.*/

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

void Bumby::agregarPropiedadesASnapshot(Snapshot& sn)
{
	SN_AGREGAR_PROPIEDAD(tiempo);
	SN_AGREGAR_PROPIEDAD(reflejos);
	SN_AGREGAR_PROPIEDAD(quieto);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Bumby::setStateFromSnapshot(const Snapshot& sn)
{
	SN_OBTENER_PROPIEDAD(tiempo);
	SN_OBTENER_PROPIEDAD(reflejos);
	SN_OBTENER_PROPIEDAD(quieto);
	Enemigo::setStateFromSnapshot(sn);
}

Bumby* Bumby::desdeSnapshot(const Snapshot& sn, Mundo& mundo)
{
	Bumby* p = new Bumby(sn.getID(), mundo, b2Vec2_zero, b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

void Bumby::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
		      b2Vec2 origen, 	 
		      real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Bumby::espejado() const
{
	return obtenerOrientacion() == derecha;
};

const Rectangulo Bumby::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOBUMBY/2,
			  obtenerPosicion().y-ALTOBUMBY/2,
			  ANCHOBUMBY,
			  ALTOBUMBY);
}
