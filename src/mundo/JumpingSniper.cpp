#include "JumpingSniper.h"
#include "Mundo.h"
#include "Megaman.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"

#define CUBIERTO 1
#define CUBRIENDOSE 2
#define DESCUBRIENDOSE 4
#define DESCUBIERTO 8
#define SALTANDO 16
#define DISPARANDO 32

#define REFLEJOS 0.5
#define TIEMPOCUBIERTO 3


JumpingSniper::JumpingSniper(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOJUMPINGSNIPER,
				   ALTOJUMPINGSNIPER,
				   &arma,
			      	   ENERGIAMAXIMAJUMPINGSNIPER,
				   ESCUDOJUMPINGSNIPER,
				   MASAJUMPINGSNIPER, 
				   VELOCIDADSALTOJUMPINGSNIPER,
				   VELOCIDADCORRERJUMPINGSNIPER,
				   ENEMIGOS,
				   CONSTRUCCIONES,
				   posicion, 
				   false,
				   true,
				   velocidad), 
				   megaman(NULL),
				   IDTarget(0),
				animacion_protegido(ANIM_JSNIPER_PROTEGIDO,0.1),
				animacion_disparando(ANIM_JSNIPER_DISPARANDO,0.1),
				animacion_saltando(ANIM_JSNIPER_SALTANDO,0.1),
				Animado(&animacion_disparando)
{
	reflejos = 0;
	cantidadDisparos = 0;
	estadoSniper = DESCUBRIENDOSE;
	
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void JumpingSniper::atacado(uint dano, Disparo *disparo)
{
	if(estadoSniper == CUBIERTO)
	{
		if(disparo->tipoDisparo() == FUEGO || disparo->tipoDisparo() == ANILLO)
			Enemigo::atacado(ENERGIAMAXIMAJUMPINGSNIPER/2+ESCUDOJUMPINGSNIPER, disparo);
	}
	else
		Enemigo::atacado(dano, disparo);
}

void JumpingSniper::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	avanzar(deltaT);

	if(estadoSniper == CUBIERTO && reflejos >= TIEMPOCUBIERTO)
	{
		reflejos = 0;
		exponerse();
		estadoSniper = DESCUBRIENDOSE;
	}
	
	if(estadoSniper == DESCUBRIENDOSE)
	{
		estadoSniper = DESCUBIERTO;
		srand(time(NULL));
		real aleatorio = (real)rand()/RAND_MAX;

		if(aleatorio < 0.5)
			cantidadDisparos = 1;
		else
			cantidadDisparos = 3;

		/*Salta tambien?*/
		srand(time(NULL)*aleatorio);
		aleatorio = (real)rand()/RAND_MAX;

		if(aleatorio < 0.5)
			estadoSniper |= SALTANDO;
	
		reflejos = 0;		
	}	
	
	if(estadoSniper & SALTANDO)
	{
		saltar();
		estadoSniper &= ~DISPARANDO;
		cambiar(&animacion_saltando);
	}

	if(cantidadDisparos)
	{
		if(reflejos >= REFLEJOS)
		{
			reflejos = 0;
			cantidadDisparos--;
			disparar();
		}
	}
	else
	{
		estadoSniper = CUBIERTO;
		cubrirse();
		cambiar(&animacion_protegido);
	}
}

void JumpingSniper::actualizar(real deltaT)
{
	if(!megaman || !obtenerMundo().existeMegaman(IDTarget))
	{
		megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = megaman->obtenerID();
	}

	b2Vec2 orientacion = megaman->obtenerPosicion()-obtenerPosicion();

	if(orientacion.LengthSquared() >= DISTANCIAVISION)
		return;

	if(b2Dot(orientacion,Cuerpo::versorIzquierda) > 0)
		modificarOrientacion(izquierda);
	else 
		modificarOrientacion(derecha);

	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void JumpingSniper::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoSniper);
	SN_AGREGAR_PROPIEDAD(reflejos);
	SN_AGREGAR_PROPIEDAD(cantidadDisparos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void JumpingSniper::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoSniper);
	SN_OBTENER_PROPIEDAD(reflejos);
	SN_OBTENER_PROPIEDAD(cantidadDisparos);
	Enemigo::setStateFromSnapshot(sn);
}

JumpingSniper* JumpingSniper::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	JumpingSniper* p =new JumpingSniper(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}


