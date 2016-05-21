#include "Enemigo.h"
#include <time.h>
#include "PowerUp.h"
#include <stdlib.h>
#include "Mundo.h"
#include <iostream>

CallbackCreadorPowerUp::CallbackCreadorPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion) : ID(ID), mundo(mundo), posicion(posicion){};

void CallbackCreadorPowerUp::ejecutar()
{
	/*Equiprobabilidad de eventos.*/

	srand(time(NULL));
	
	real aleatorio = (real)rand()/RAND_MAX, piso = 0;

	if(aleatorio >= piso && aleatorio < (piso += PROBANUEVAVIDA))
		mundo.agregar(new NuevaVida(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAENERGIACHICA))
		mundo.agregar(new CapsulaEnergiaChica(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAENERGIAGRANDE))
		mundo.agregar(new CapsulaEnergiaGrande(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAPLASMACHICA))
		mundo.agregar(new CapsulaPlasmaChica(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAPLASMAGRANDE))
		mundo.agregar(new CapsulaPlasmaChica(ID,mundo,posicion));
}

Enemigo::Enemigo()
{
}

void Enemigo::ruletaPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion)
{
	mundo.agregarTareaDiferida(new CallbackCreadorPowerUp(ID,mundo,posicion));
}
