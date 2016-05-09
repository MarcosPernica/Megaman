#include "Bumby.h"
#include "Disparo.h"
#include <Box2D\Box2D.h>


void Bumby::actualizar(real deltaT)
{
}

Bumby::Bumby(Mundo & mundo,
			 const b2Vec2 & posicion,
			 const b2Vec2 & velocidad) :
			 Entidad(mundo,
					 ANCHOSPRITEENEMIGO,
					 ALTOSPRITEENEMIGO,
				     ENERGIAMAXIMABUMBY,
				     MASABUMBY,
				     ENEMIGOS, 
				     PERSONAJES | CONSTRUCCIONES,
				     posicion,
				     false)
{
}