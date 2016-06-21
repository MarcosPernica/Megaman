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
	/*Le dice al mundo que agregue el PowerUp que habilita la bomba.*/
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),
									obtenerMundo(),
									obtenerPosicion(),
									BOMBA));

	eliminarse(obtenerMundo());
}

Bombman::Bombman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
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
			#ifndef compiling_server
			 Animado(&animacion_saltando),
			 animacion_saltando(ANIM_BOMBMAN_SALTANDO,1),
			 animacion_corriendo(ANIM_BOMBMAN_CORRIENDO,0.1),
			#endif
			 megaman(NULL),
			 IDTarget(0),
			 estadoBombman(QUIETO),
			 reflejos(0),
			 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES)
			
{
}

void Bombman::actualizarMaquinaEstados(real deltaT)
{
	/*Toma de punto un jugador.*/
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
	
			/*La distancia al cuadrado es varios ordenes de magnitud mas rapida.*/
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

	/*Es mas preciso cambiarlo de esta forma que una vez por cambio de la maquina de estados.*/

	#ifndef compiling_server
	if(estaEnElAire())
		cambiar(&animacion_saltando);
	else
		cambiar(&animacion_corriendo);
	#endif
}

void Bombman::actualizar(real deltaT)
{
	#ifndef compiling_server
	/*Avanza la animacion.*/
	avanzar(deltaT);
	#endif

	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Bombman::agregarPropiedadesASnapshot(Snapshot& sn)
{
	SN_AGREGAR_PROPIEDAD(estadoBombman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Bombman::setStateFromSnapshot(const Snapshot& sn)
{
	SN_OBTENER_PROPIEDAD(estadoBombman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Bombman* Bombman::desdeSnapshot(const Snapshot& sn, Mundo& mundo)
{
	Bombman* p = new Bombman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

#ifndef compiling_server
void Bombman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion)
{
	Imagen::dibujarEn(cr,origen,factorAmplificacion);
}

bool Bombman::espejado() const
{
	return obtenerOrientacion() == izquierda;
};

const Rectangulo Bombman::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOBOMBMAN/2,
			  obtenerPosicion().y-ALTOBOMBMAN/2,
			  ANCHOBOMBMAN,
			  ALTOBOMBMAN);
}

#endif
