#ifndef ENTIDAD
#define ENTIDAD

#include "Definiciones.h"
#include "Cuerpo.h"
#include "Actualizable.h"
#include "Mundo.h"
#include <Box2D\Box2D.h>

class Entidad : public Cuerpo, public Actualizable
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
			ushort categoria,
			ushort colisionaCon,
			const b2Vec2 &posicion,
			bool rotable = false,
			bool gravitacional = true,
			const b2Vec2 &velocidad = b2Vec2_zero,
			Orientaciones orientacion = derecha);

	void recuperarEnergia(uint cantidadEnergia);

	virtual void atacado(uint daño);
};

#endif