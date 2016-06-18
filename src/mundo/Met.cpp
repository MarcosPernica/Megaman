#include "Met.h"
#include "Mundo.h"
#include "Megaman.h"
#include "../common/exceptions.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"

#define CUBIERTO 0
#define DESCUBIERTO 1
#define DISPARANDO1 2
#define DISPARANDO2 3
#define DISPARANDO3 4

#define TIEMPOCUBIERTO 5
#define TIEMPODESCUBIERTO 1
#define TIEMPODISPARANDO 0.5

Met::Met(uint ID,
	 Mundo & mundo, 
	 const b2Vec2 & posicion,
	 const b2Vec2 & velocidad) : 
	 Enemigo(ID,
		mundo,
		ANCHOMET,
		ALTOMET,
		&arma,
		ENERGIAMAXIMAMET,
		ESCUDOMET,
		MASAMET, 
		VELOCIDADSALTOMET,
		VELOCIDADCORRERMET,
		ENEMIGOS,
		CONSTRUCCIONES,
		posicion, 
		false,
		true,
		velocidad),
	Animado(&animacion_protegido),
	animacion_protegido(ANIM_MET_PROTEGIDO,1),
	animacion_disparando(ANIM_MET_DISPARANDO,1),
	megaman(NULL),
	IDTarget(0),
	tiempo(0),
	estadoMet(CUBIERTO),
	arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES)
{
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Met::atacado(int dano, Disparo *disparo)
{
	if(estadoMet == CUBIERTO)
	{
		if(disparo->tipoDisparo() == BOMBA || disparo->tipoDisparo() == CHISPA)
			Enemigo::atacado(ENERGIAMAXIMAMET/2+ESCUDOMET, disparo);
		else if(disparo->tipoDisparo() != PLASMA)
			Enemigo::atacado(ENERGIAMAXIMAMET+ESCUDOMET, disparo);		
	}
	else
		Enemigo::atacado(dano, disparo);
}

void Met::actualizarMaquinaEstados(real deltaT)
{
	tiempo += deltaT;
	
	switch(estadoMet)
	{
		case CUBIERTO:
			if(tiempo >= TIEMPOCUBIERTO)
			{
				tiempo = 0;
				estadoMet = DESCUBIERTO;
				exponerse();
				cambiar(&animacion_disparando);
			}
			break;
		case DESCUBIERTO:
			if(tiempo >= TIEMPODESCUBIERTO)
			{
				tiempo = 0;
				estadoMet = DISPARANDO1;
				disparar();
			}
			break;
		case DISPARANDO1:
			if(tiempo >= TIEMPODISPARANDO)
			{
				tiempo = 0;
				estadoMet = DISPARANDO2;
				disparar(Cuerpo::orientacionAVector(obtenerOrientacion())+b2Vec2(0,-1/2.0));
			}
			break;
		case DISPARANDO2:
			if(tiempo >= TIEMPODISPARANDO)
			{
				tiempo = 0;
				estadoMet = DISPARANDO3;
				disparar(Cuerpo::orientacionAVector(obtenerOrientacion())+b2Vec2(0,-1));
			}
			break;
		case DISPARANDO3:
			if(tiempo >= TIEMPODISPARANDO)
			{
				tiempo = 0;
				estadoMet = CUBIERTO;
				cubrirse();
				cambiar(&animacion_protegido);
			}
			break;
	}
}

void Met::actualizar(real deltaT)
{
	avanzar(deltaT);

	if(!megaman || !obtenerMundo().existeMegaman(IDTarget))
	{
		megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = megaman->obtenerID();
	}

	b2Vec2 orientacion = megaman->obtenerPosicion()-obtenerPosicion();
	
	if(orientacion.LengthSquared() >= DISTANCIAVISION*DISTANCIAVISION)
		return;

	if(b2Dot(orientacion,Cuerpo::versorIzquierda) > 0)
		modificarOrientacion(izquierda);
	else 
		modificarOrientacion(derecha);

	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}


void Met::agregarPropiedadesASnapshot(Snapshot& sn){
	Enemigo::agregarPropiedadesASnapshot(sn);
	SN_AGREGAR_PROPIEDAD(tiempo);
	SN_AGREGAR_PROPIEDAD(estadoMet);
	
}
void Met::setStateFromSnapshot(const Snapshot& sn){
	Enemigo::setStateFromSnapshot(sn);
	SN_OBTENER_PROPIEDAD(tiempo);
	SN_OBTENER_PROPIEDAD(estadoMet);
}

Met* Met::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Met* p =new Met(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}

void Met::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
		    b2Vec2 origen, 
	            real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}


bool Met::espejado() const
{
	return obtenerOrientacion() == derecha;
};

const Rectangulo Met::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOMET/2,
			  obtenerPosicion().y-ALTOMET/2,
			  ANCHOMET,
			  ALTOMET);
}
