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

