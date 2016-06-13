#include "Sparkman.h"
#include "Mundo.h"
#include "Megaman.h"
#include "PowerUp.h"
#include <iostream>

#include "../net/snapshots/Snapshot.h"

#define QUIETO 0
#define CORRIENDO 1
#define SALTANDO 2
#define DISPARANDO 4

#define REFLEJOS 0.5
#define TIEMPOCORRIENDO 3

void Sparkman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),CHISPA));
	eliminarse(obtenerMundo());
}

Sparkman::Sparkman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOSPARKMAN,
				   ALTOSPARKMAN,
				   &arma,
			      	   ENERGIAMAXIMASPARKMAN,
				   ESCUDOSPARKMAN,
				   MASASPARKMAN, 
				   VELOCIDADSALTOSPARKMAN,
				   VELOCIDADCORRERSPARKMAN,
				   ENEMIGOS,
				   CONSTRUCCIONES,
				   posicion, 
				   false,
				   true,
				   velocidad,
				   izquierda,
				   false),
    			  	   megaman(NULL),
				   IDTarget(0)
{
	reflejos = 0;
	estadoSparkman = QUIETO;
	
	deshabilitarFriccion();

	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Sparkman::actualizarMaquinaEstados(real deltaT)
{
	if(!megaman || !obtenerMundo().existeMegaman(IDTarget))
	{
		megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = megaman->obtenerID();
	}

	reflejos += deltaT;

	switch(estadoSparkman)
	{
		case DISPARANDO:
		{
			orientacion = obtenerOrientacion();
	
			b2Vec2 vista = megaman->obtenerPosicion()-obtenerPosicion();

			if(b2Dot(vista,Cuerpo::versorIzquierda) > 0)
				modificarOrientacion(izquierda);
			else 
				modificarOrientacion(derecha);

			disparar(megaman->obtenerPosicion()-obtenerPosicion());

			estadoSparkman = QUIETO;
			
			break;
		}
		case SALTANDO:
		{
			if(reflejos >= TIEMPOCORRIENDO)
			{
				reflejos = 0;
				dejarCorrer();
			}

			if(puedeSaltar())
				estadoSparkman = QUIETO;
			break;
		}
		case QUIETO:
		{
			
			real aleatorio = numeroAleatorio(0,1);

			modificarOrientacion(orientacion);
			
			if(puedeCorrer())
			{

				if(aleatorio < 0.5)
				{
					correr();
					saltar();
					estadoSparkman = SALTANDO;
				}
				else
				{
					estadoSparkman = DISPARANDO;
				}
			}
			else
			{
				virar();
				orientacion = obtenerOrientacion();
			}

			reflejos = 0;
			break;
		}
	}
}

void Sparkman::actualizar(real deltaT)
{
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Sparkman::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoSparkman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Sparkman::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoSparkman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Sparkman* Sparkman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Sparkman* p =new Sparkman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
