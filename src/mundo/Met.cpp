#include "Met.h"
#include "Mundo.h"
#include "Megaman.h"
#include "../common/exceptions.h"
#include <iostream>

#define CUBIERTO 0
#define DESCUBIERTO 1
#define DISPARANDO1 2
#define DISPARANDO2 3
#define DISPARANDO3 4

#define TIEMPOCUBIERTO 5
#define TIEMPODESCUBIERTO 1
#define TIEMPODISPARANDO 0

Met::Met(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
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
				   CONSTRUCCIONES | PERSONAJES | DISPAROS,
				   posicion, 
				   false,
				   true,
				   velocidad)
{
	tiempo = 0;
	estadoMet = CUBIERTO;
	accionEjecutada = false;
	
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
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
			}
			break;
	}
}

void Met::actualizar(real deltaT)
{
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
#define PROP_TIEMPO "tiempo"
#define PROP_ESTADO_MET "estadoMet"
#define PROP_ACCION_EJECUTADA "accionEjecutada"
void Met::agregarPropiedadesASnapshot(Snapshot& sn){
	Enemigo::agregarPropiedadesASnapshot(sn);
	sn.agregarPropiedad(PROP_TIEMPO,(int)(tiempo*1000));
	sn.agregarPropiedad(PROP_ESTADO_MET,estadoMet);
	sn.agregarPropiedad(PROP_ACCION_EJECUTADA,(int)accionEjecutada);
	
}
void Met::setStateFromSnapshot(const Snapshot& sn){
	Enemigo::setStateFromSnapshot(sn);
	try{
	accionEjecutada = (bool)sn.obtenerPropiedad(PROP_ACCION_EJECUTADA);
	estadoMet = sn.obtenerPropiedad(PROP_ESTADO_MET);
	tiempo = (float)sn.obtenerPropiedad(PROP_TIEMPO)/1000;
	//std::cout<<"normal:" <<tiempo<<" "<<(int)estadoMet<<" "<<accionEjecutada<<std::endl;
	}catch(const CustomException& e){
		/*
		std::cout<<"--------SNAPSHOT ANOMALA DE MET------"<<std::endl;
		std::cout<<sn.serializar()<<std::endl;
		//nos salió feo el MET de ID 14. Ni idea qué tiene.
		std::cout<<tiempo<<" "<<(int)estadoMet<<" "<<accionEjecutada<<std::endl;
		*/
	}
}

Met* Met::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Met* p =new Met(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
