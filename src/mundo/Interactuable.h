#ifndef INTERACTUABLE
#define INTERACTUABLE

#include "Entidad.h"

class Interactuable
{
public:
	/*Devuelve true si debe eliminarse el objeto tras la interaccion.*/
	virtual bool interactuar(Entidad *entidad) = 0;
};

#endif
