#include "Entidad.h"
#include "Mundo.h"
Entidad::Entidad(Mundo & mundo, 
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
			     Cuerpo(mundo,
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

void Entidad::recuperarEnergia(uint cantidadEnergia)
{
	if (energia + cantidadEnergia > energiaMaxima)
		energia = energiaMaxima;
	else
		energia += cantidadEnergia;
}

void Entidad::atacado(uint danio)
{
	if (danio < energia)
		energia -= danio;
	else
		/*Eliminar*/;
}
