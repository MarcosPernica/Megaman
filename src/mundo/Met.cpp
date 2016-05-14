#include "Met.h"

Met::Met(Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 Protegido(mundo,
				   ANCHOSPRITEENEMIGO,
				   ALTOSPRITEENEMIGO,
			       ENERGIAMAXIMAMET,
				   ESCUDOMET,
				   MASAMET, 
				   ENEMIGOS,
				   CONSTRUCCIONES | PERSONAJES,
				   posicion, 
				   false,
				   true,
				   velocidad)
{
}

