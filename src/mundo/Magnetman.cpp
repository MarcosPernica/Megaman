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
			CONSTRUCCIONES,
			posicion, 
			false,
			true,
			velocidad,
			izquierda,
			false),
		Animado(&animacion_saltando),
		animacion_saltando(ANIM_MAGNETMAN_SALTANDO,1),
		animacion_corriendo(ANIM_MAGNETMAN_CORRIENDO,0.1),
		estadoMagnetman(QUIETO),
		reflejos(0),			
		arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		disparos(0)
{
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

	/*Es mas preciso cambiarlo de esta forma que una vez por cambio de la maquina de estados.*/

	if(estaEnElAire())
		cambiar(&animacion_saltando);
	else
		cambiar(&animacion_corriendo);
}

void Magnetman::actualizar(real deltaT)
{
	avanzar(deltaT);
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

void Magnetman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr,
			  b2Vec2 origen, 
			  real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Magnetman::espejado() const
{
	return obtenerOrientacion() == izquierda;
};

const Rectangulo Magnetman::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOMAGNETMAN/2,
			  obtenerPosicion().y-ALTOMAGNETMAN/2,
			  ANCHOMAGNETMAN,
			  ALTOMAGNETMAN);
}
