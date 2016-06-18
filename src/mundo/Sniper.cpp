#include "Sniper.h"
#include "Mundo.h"
#include "Megaman.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"

#define CUBIERTO 1
#define CUBRIENDOSE 2
#define DESCUBRIENDOSE 4
#define DESCUBIERTO 8
#define DISPARANDO 16

#define REFLEJOS 0.5
#define TIEMPOCUBIERTO 3


Sniper::Sniper(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 Enemigo(ID,
				mundo,
				   ANCHOSNIPER,
				   ALTOSNIPER,
				   &arma,
			      	   ENERGIAMAXIMASNIPER,
				   ESCUDOSNIPER,
				   MASASNIPER, 
				   VELOCIDADSALTOSNIPER,
				   VELOCIDADCORRERSNIPER,
				   ENEMIGOS,
				   CONSTRUCCIONES,
				   posicion, 
				   false,
				   true,
				   velocidad),
				Animado(&animacion_disparando),
				animacion_protegido(ANIM_SNIPER_PROTEGIDO,0.1),
				animacion_disparando(ANIM_SNIPER_DISPARANDO,0.1),
				  megaman(NULL),
				   IDTarget(0),
				estadoSniper(DESCUBRIENDOSE),
				reflejos(0),
				cantidadDisparos(0),				
				 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES)
			
{	
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Sniper::atacado(int dano, Disparo *disparo)
{
	if(estadoSniper == CUBIERTO)
	{
		if(disparo->tipoDisparo() == FUEGO || disparo->tipoDisparo() == ANILLO)
			Enemigo::atacado(ENERGIAMAXIMASNIPER/2+ESCUDOSNIPER, disparo);
	}
	else
		Enemigo::atacado(dano, disparo);
}

void Sniper::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	avanzar(deltaT);
	
	if(estadoSniper == CUBIERTO && reflejos >= TIEMPOCUBIERTO)
	{
		reflejos = 0;
		exponerse();
		estadoSniper = DESCUBRIENDOSE;
		cambiar(&animacion_disparando);
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

		reflejos = 0;		
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

void Sniper::actualizar(real deltaT)
{
	avanzar(deltaT);

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

void Sniper::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(estadoSniper);
	SN_AGREGAR_PROPIEDAD(reflejos);
	SN_AGREGAR_PROPIEDAD(cantidadDisparos);
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Sniper::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(estadoSniper);
	SN_OBTENER_PROPIEDAD(reflejos);
	SN_OBTENER_PROPIEDAD(cantidadDisparos);
	Enemigo::setStateFromSnapshot(sn);
}

Sniper* Sniper::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Sniper* p =new Sniper(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

void Sniper::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool Sniper::espejado() const{return obtenerOrientacion()==izquierda;};

const Rectangulo Sniper::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSNIPER/2,
					obtenerPosicion().y-ALTOSNIPER/2,
					ANCHOSNIPER,
					ALTOSNIPER);}
