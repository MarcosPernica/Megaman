#include "Entidad.h"

Entidad::Entidad(Mundo &mundo,
				 real ancho,
				 real alto,
				 uint energiaMaxima,
				 real masa,
				 const Vector2D &posicion,
				 bool gravitacional = true,
				 const Vector2D &velocidad = Vector2D(),
				 const Vector2D &orientacion = Vector2D(1, 0)) :
				 energiaMaxima(energiaMaxima),
			     energia(energiaMaxima),
				 mundo(mundo),
				 Cuerpo(masa, posicion, gravitacional, velocidad, orientacion),
				 CajaColision(posicion, alto, ancho)
{
}

Mundo & Entidad::obtenerMundo()
{
	return mundo;
}

void Entidad::recuperarEnergia(int cantidadEnergia)
{
	if (energia + cantidadEnergia > energiaMaxima)
		energia = energiaMaxima;
	else
		energia += cantidadEnergia;
}

void Entidad::atacado(real daño)
{
	if (daño < energia)
		energia -= daño;
	else
		eliminar();
}
