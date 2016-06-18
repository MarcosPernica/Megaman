#include "Ringman.h"
#include "Mundo.h"
#include "Megaman.h"
#include "PowerUp.h"
#include <iostream>

#include "../net/snapshots/Snapshot.h"

#define QUIETO 0
#define CORRIENDO 1
#define SALTANDO 2
#define REFLEJOS 1

#define CANTDISPAROS 3

void Ringman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),ANILLO));
	eliminarse(obtenerMundo());
}

Ringman::Ringman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 Enemigo(ID,
				mundo,
				   ANCHORINGMAN,
				   ALTORINGMAN,
				   &arma,
			      	   ENERGIAMAXIMARINGMAN,
				   ESCUDORINGMAN,
				   MASARINGMAN, 
				   VELOCIDADSALTORINGMAN,
				   VELOCIDADCORRERRINGMAN,
				   ENEMIGOS,
				   CONSTRUCCIONES,
				   posicion, 
				   false,
				   true,
				   velocidad,
				   izquierda,
				   false),
			Animado(&animacion_saltando),
			animacion_saltando(ANIM_RINGMAN_SALTANDO,1),
			animacion_corriendo(ANIM_RINGMAN_CORRIENDO,0.1),
			estadoRingman(QUIETO),
			reflejos(0),
			arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
			disparos(0)
{
	deshabilitarFriccion();
}

void Ringman::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	switch(estadoRingman)
	{
		case CORRIENDO:
		{
			if(reflejos >= REFLEJOS && disparos)
			{
				reflejos = 0;
				disparar();
				disparos--;
			}


			if(!puedeCorrer())
			{
				virar();
				estadoRingman = QUIETO;		
			}	
			break;
		}
		case SALTANDO:
		{
			if(reflejos >= REFLEJOS && disparos)
			{
				reflejos = 0;
				disparos--;
				disparar();
			}

			if(puedeSaltar())
				estadoRingman = QUIETO;
			break;
		}
		case QUIETO:
		{
			
			real aleatorio = numeroAleatorio(0,1);
			
			if(aleatorio > 0.6)
			{
				saltar();
				estadoRingman = SALTANDO;
				disparos = CANTDISPAROS;
			}
			else
			{
				correr();
				estadoRingman = CORRIENDO;
				disparos = CANTDISPAROS;
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

void Ringman::actualizar(real deltaT)
{
	avanzar(deltaT);
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Ringman::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoRingman);
	SN_AGREGAR_PROPIEDAD(reflejos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Ringman::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoRingman);
	SN_OBTENER_PROPIEDAD(reflejos);
	Enemigo::setStateFromSnapshot(sn);
}

Ringman* Ringman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Ringman* p =new Ringman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

void Ringman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool Ringman::espejado() const{return obtenerOrientacion()==izquierda;};

const Rectangulo Ringman::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHORINGMAN/2,
						obtenerPosicion().y-ALTORINGMAN/2,
						ANCHORINGMAN,
						ALTORINGMAN);}
