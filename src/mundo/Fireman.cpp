#include "Fireman.h"
#include "Mundo.h"
#include "Megaman.h"
#include "PowerUp.h"
#include <iostream>

#include "../net/snapshots/Snapshot.h"

#define QUIETO 0
#define CORRIENDO 1
#define SALTANDO 2
#define DISPARANDO 4

#define REFLEJOS 1
#define TIEMPOCORRIENDO 3

void Fireman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),FUEGO));
	eliminarse(obtenerMundo());
}

Fireman::Fireman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 Enemigo(ID,
			mundo,
			ANCHOFIREMAN,
			ALTOFIREMAN,
			&arma,
			ENERGIAMAXIMAFIREMAN,
			ESCUDOFIREMAN,
			MASAFIREMAN, 
			VELOCIDADSALTOFIREMAN,
			VELOCIDADCORRERFIREMAN,
			ENEMIGOS,
			CONSTRUCCIONES,
			posicion, 
			false,
			true,
			velocidad,
			izquierda,
			false),
		#ifndef compiling_server
		Animado(&animacion_saltando),
		animacion_saltando(ANIM_FIREMAN_SALTANDO,1),
		animacion_corriendo(ANIM_FIREMAN_CORRIENDO,0.1),
		#endif
		estadoFireman(QUIETO),	
		reflejos(0),
		arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES)
{	
	deshabilitarFriccion();
}

void Fireman::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	if(reflejos >= REFLEJOS)
	{	
		reflejos = 0;
		disparar();
	}

	switch(estadoFireman)
	{
		case SALTANDO:
		{
			if(reflejos >= TIEMPOCORRIENDO)
			{
				reflejos = 0;
				dejarCorrer();
			}

			if(puedeSaltar())
				estadoFireman = QUIETO;

			break;
			
		}
		case CORRIENDO:
		{
			if(!puedeCorrer())
			{
				virar();
				estadoFireman = QUIETO; 	
			}
			break;
		}
		case QUIETO:
		{
			real aleatorio;
			aleatorio = numeroAleatorio(0,1);

			if(aleatorio < 0.2)
			{
				correr();
				saltar();
				estadoFireman = SALTANDO;
			}
			else
			{
				correr();
				estadoFireman = CORRIENDO;
			}
			reflejos = 0;
			break;
		}
	}

	#ifndef compiling_server
	/*Es mas preciso cambiarlo de esta forma que una vez por cambio de la maquina de estados.*/

	if(estaEnElAire())
		cambiar(&animacion_saltando);
	else
		cambiar(&animacion_corriendo);
	#endif
}

void Fireman::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Fireman::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoFireman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Fireman::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoFireman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Fireman* Fireman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Fireman* p =new Fireman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

#ifndef compiling_server
void Fireman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
			b2Vec2 origen, 
			real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Fireman::espejado() const
{
	return obtenerOrientacion() == izquierda;
};

const Rectangulo Fireman::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOFIREMAN/2,
		          obtenerPosicion().y-ALTOFIREMAN/2,
			  ANCHOFIREMAN,
			  ALTOFIREMAN);
}
#endif
