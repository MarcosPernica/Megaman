#ifndef CAJASPAWN
#define CAJASPAWN

#include "../net/Snapshotable.h"
#include "Actualizable.h"
#include "Met.h"

#include <Box2D/Box2D.h>
#include "Definiciones.h"
#include "Mundo.h"

class CajaSpawn : public Snapshotable, public Actualizable
{
private:
	Mundo &mundo;
	b2Vec2 posicion;
	real cuentaRegresiva;
public:
	CajaSpawn(uint ID, Mundo &mundo, b2Vec2 posicion) : Snapshotable(ID), mundo(mundo), posicion(posicion), cuentaRegresiva(0) {};

	virtual void actualizar(real deltaT)
	{
		if(!mundo.existeElemento(obtenerID()))
		{
			cuentaRegresiva -= deltaT;

			if(cuentaRegresiva <= 0)
			{
				cuentaRegresiva = 5;
				mundo.agregar(new Met(obtenerID(),mundo,posicion,b2Vec2_zero));
			}
		}			
	}
};

#endif
