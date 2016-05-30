#include "Sniper.h"
#include "Mundo.h"
#include "Megaman.h"
#include <iostream>

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
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
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
				   CONSTRUCCIONES | PERSONAJES | DISPAROS,
				   posicion, 
				   false,
				   true,
				   velocidad)
{
	reflejos = 0;
	cantidadDisparos = 0;
	estadoSniper = DESCUBRIENDOSE;
	
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Sniper::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

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
	}
}

void Sniper::actualizar(real deltaT)
{
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
	//yo aquí
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Sniper::setStateFromSnapshot(const Snapshot& sn){
	//yo aquí
	Enemigo::setStateFromSnapshot(sn);
}

Sniper* Sniper::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Sniper* p =new Sniper(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
