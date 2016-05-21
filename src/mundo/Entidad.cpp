#include "Entidad.h"
#include "PowerUp.h"
#include "Mundo.h"
#include <iostream>
Entidad::Entidad(uint ID, 
		     Mundo & mundo, 
	             real ancho,
			     real alto,
	             uint energiaMaxima,
	             real masa, 
			     ushort categoria,
				 ushort colisionaCon,
	             const b2Vec2 & posicion,
				 bool rotable,
	             bool gravitacional,
	             const b2Vec2 & velocidad,
	             Orientaciones orientacion) :
				 energia(energiaMaxima),
				 energiaMaxima(energiaMaxima),
				 mundo(mundo),
			     Cuerpo(ID,
						mundo,
						ancho,
						alto,
						masa,
						categoria,
						colisionaCon,
						posicion,
						rotable,
						gravitacional,
						velocidad,
						orientacion)
{
}

uint Entidad::obtenerEnergiaMaxima()
{
	return energiaMaxima;
}

uint Entidad::obtenerEnergiaActual()
{
	return energia;
}

void Entidad::recuperarEnergia(uint cantidadEnergia)
{
	if (energia + cantidadEnergia > energiaMaxima)
		energia = energiaMaxima;
	else
		energia += cantidadEnergia;
}

void Entidad::atacado(uint danio)
{
	PowerUp *powerUp;

	if (danio < energia)
		energia -= danio;
	else
	{
		ruletaPowerUp(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion());
		obtenerMundo().eliminar(this);
	}
		
}
