#include "Magnetman.h"
#include "Mundo.h"
#include "Megaman.h"
#include "PowerUp.h"
#include <iostream>

#include "../net/snapshots/Snapshot.h"

#define QUIETO 0
#define CORRIENDO 1
#define SALTANDO 2
#define REFLEJOS 0.5

#define CANTDISPAROS 3

void Magnetman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),IMAN));
	eliminarse(obtenerMundo());
}

Magnetman::Magnetman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOMAGNETMAN,
				   ALTOMAGNETMAN,
				   &arma,
			      	   ENERGIAMAXIMAMAGNETMAN,
				   ESCUDOMAGNETMAN,
				   MASAMAGNETMAN, 
				   VELOCIDADSALTOMAGNETMAN,
				   VELOCIDADCORRERMAGNETMAN,
				   ENEMIGOS,
				   CONSTRUCCIONES | DISPAROS,
				   posicion, 
				   false,
				   true,
				   velocidad,
				   izquierda,
				   false)
{
	reflejos = 0;
	disparos = 0;
	estadoMagnetman = QUIETO;
	
	deshabilitarFriccion();
}

void Magnetman::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	switch(estadoMagnetman)
	{
		case CORRIENDO:
		{
			if(!puedeCorrer())
			{
				virar();
				estadoMagnetman = QUIETO;		
			}	
			break;
		}
		case SALTANDO:
		{
			if(reflejos >= REFLEJOS && disparos)
			{
				reflejos = 0;

				Megaman *megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());

				b2Vec2 vista = megaman->obtenerPosicion()-obtenerPosicion();

				if(b2Dot(vista,Cuerpo::versorIzquierda) > 0)
					modificarOrientacion(izquierda);
				else 
					modificarOrientacion(derecha);

				disparar(megaman->obtenerPosicion()-obtenerPosicion());
				disparos--;
			}

			if(puedeSaltar())
				estadoMagnetman = QUIETO;
			break;
		}
		case QUIETO:
		{
			
			real aleatorio = numeroAleatorio(0,1);
			
			if(aleatorio > 0.6)
			{
				saltar();
				estadoMagnetman = SALTANDO;
				disparos = CANTDISPAROS;
			}
			else
			{
				correr();
				estadoMagnetman = CORRIENDO;
			}

			reflejos = 0;
			break;
		}
	}
}

void Magnetman::actualizar(real deltaT)
{
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Magnetman::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoMagnetman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Magnetman::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoMagnetman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Magnetman* Magnetman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Magnetman* p =new Magnetman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
