#ifndef ENTIDAD
#define ENTIDAD

#include "Vector2D.h"
#include "Definiciones.h"
#include "Cuerpo.h"
#include "Actualizable.h"
#include "Mundo.h"
#include "CajaColision.h"

class Entidad : public Cuerpo, public Actualizable, public CajaColision
{
private:
	uint energia, energiaMaxima;
	Mundo &mundo;
public:
	Entidad(Mundo &mundo,
			real ancho,
			real alto,
			uint energiaMaxima, 
			real masa,
			const Vector2D &posicion,
			bool gravitacional = true,
			const Vector2D &velocidad = Vector2D(),
			const Vector2D &orientacion = Vector2D(1, 0));

	Mundo &obtenerMundo();
	void recuperarEnergia(int cantidadEnergia);

	virtual void atacado(real daño);
	virtual void eliminar() = 0;
};

#endif