#include "Bumby.h"
#include "Disparo.h"
#include <Box2D/Box2D.h>



void Bumby::actualizar(real deltaT)
{
}

void Bumby::agregarPropiedadesASnapshot(Snapshot& sn){
	//mis propiedades
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void Bumby::setStateFromSnapshot(const Snapshot& snapshot){
	//mis propiedades
	Cuerpo::setStateFromSnapshot(snapshot);
}

Bumby* Bumby::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Bumby* b =new Bumby(sn.getID(),mundo,b2Vec2_zero,b2Vec2_zero);
	b->setStateFromSnapshot(sn);
	return b;
}

Bumby::Bumby(uint ID,
			 Mundo & mundo,
			 const b2Vec2 & posicion,
			 const b2Vec2 & velocidad) :
			 Entidad(ID,
				     mundo,
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
