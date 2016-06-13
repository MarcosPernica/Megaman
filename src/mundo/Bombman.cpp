#include "Bombman.h"
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

void Bombman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),BOMBA));
	eliminarse(obtenerMundo());
}

Bombman::Bombman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOBOMBMAN,
				   ALTOBOMBMAN,
				   &arma,
			      	   ENERGIAMAXIMABOMBMAN,
				   ESCUDOBOMBMAN,
				   MASABOMBMAN, 
				   VELOCIDADSALTOBOMBMAN,
				   VELOCIDADCORRERBOMBMAN,
				   ENEMIGOS,
				   CONSTRUCCIONES | DISPAROS,
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
	estadoBombman = QUIETO;
}

void Bombman::actualizarMaquinaEstados(real deltaT)
{
	if(!megaman || !obtenerMundo().existeMegaman(IDTarget))
	{
		megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = megaman->obtenerID();
	}

	reflejos += deltaT;

	switch(estadoBombman)
	{
		case DISPARANDO:
		{
			disparar(megaman->obtenerPosicion()-obtenerPosicion());
			estadoBombman = QUIETO;
			
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
				estadoBombman = QUIETO;
			
			break;
		}
		case QUIETO:
		{

			b2Vec2 orientacion = megaman->obtenerPosicion()-obtenerPosicion();
	
			if(orientacion.LengthSquared() >= DISTANCIAVISION*DISTANCIAVISION)
				return;

			if(b2Dot(orientacion,Cuerpo::versorIzquierda) > 0)
				modificarOrientacion(izquierda);
			else 
				modificarOrientacion(derecha);

			real aleatorio = numeroAleatorio(0,1);

			if(aleatorio < 0.4)
			{
				correr();
				saltar();
				estadoBombman = SALTANDO;
			}
			else
			{
				estadoBombman = DISPARANDO;
			}
			reflejos = 0;
			break;
		}
	}
}

void Bombman::actualizar(real deltaT)
{
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Bombman::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoBombman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Bombman::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoBombman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Bombman* Bombman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Bombman* p =new Bombman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
