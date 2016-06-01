#include "Puas.h"

Puas::Puas(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion)
			    
{
}

void Puas::interactuar(Megaman *megaman)
{
	megaman->atacado(megaman->obtenerEnergiaMaxima());
}
