#ifndef CAMARA
#define CAMARA

#include "../mundo/Mundo.h"
#include "../mundo/Megaman.h"
#include "../mundo/Actualizable.h"
#include <Box2D/Box2D.h>
#include "Dibujable.h"


class Camara : public Actualizable
{
private:
	bool ejeXBloqueado;
	bool ejeYBloqueado;

	b2Vec2 posicion;

	/*En pixeles.*/
	real ancho, alto;
	std::list<Megaman *> megamanes;
	Mundo &mundo;
public:
	Camara(Mundo &mundo, b2Vec2 posicion, real ancho, real alto);

	void bloquearEjeX();
	void desbloquearEjeX();
	void bloquearEjeY();	
	void desbloquearEjeY();

	void modificarDimensiones(real ancho, real alto);
	void actualizar(real deltaT);

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr);
};

#endif
