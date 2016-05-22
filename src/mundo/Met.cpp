#include "Met.h"

Met::Met(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 Protegido(ID,
				mundo,
				   ANCHOSPRITEENEMIGO,
				   ALTOSPRITEENEMIGO,
			       ENERGIAMAXIMAMET,
				   ESCUDOMET,
				   MASAMET, 
				   ENEMIGOS,
				   CONSTRUCCIONES | PERSONAJES | DISPAROS,
				   posicion, 
				   false,
				   true,
				   velocidad)
{
}
void Met::agregarPropiedadesASnapshot(Snapshot& sn){
	//yo aquí
	Protegido::agregarPropiedadesASnapshot(sn);
}
void Met::setStateFromSnapshot(const Snapshot& sn){
	//yo aquí
	Protegido::setStateFromSnapshot(sn);
}

Met* Met::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Met* p =new Met(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
