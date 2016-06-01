#include "Camara.h"
#include <iostream>

Camara::Camara(Mundo &mundo, b2Vec2 posicion, real ancho, real alto) : mundo(mundo), posicion(posicion), ancho(ancho), alto(alto), ejeXBloqueado(false), ejeYBloqueado(true)
{
	megamanes = mundo.obtenerMegamanes();
}

void Camara::bloquearEjeX()
{
	ejeXBloqueado = true;
}

void Camara::desbloquearEjeX()
{
	ejeXBloqueado = false;
}

void Camara::bloquearEjeY()
{
	ejeYBloqueado = true;
}

void Camara::desbloquearEjeY()
{
	ejeYBloqueado = false;
}

void Camara::modificarDimensiones(real ancho, real alto)
{
	ancho = ancho;
	alto = alto;
}

void Camara::actualizar(real deltaT)
{
	b2Vec2 posicionPromedio = b2Vec2_zero;

	std::list<Megaman*>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		posicionPromedio += (*i++)->obtenerPosicion();

	posicionPromedio = (1/(real)megamanes.size()) * posicionPromedio;

	posicionPromedio = Dibujable::mundoARender(posicionPromedio);

	posicionPromedio -= b2Vec2(ancho/2,alto/2);

	if(!ejeXBloqueado)
		posicion.x = posicionPromedio.x;

	if(!ejeYBloqueado)
		posicion.y = posicionPromedio.y;
}

void Camara::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr)
{
	std::list<Dibujable*> dibujables = mundo.elementosEnZona(Dibujable::renderAMundo(posicion), Dibujable::renderAMundo(ancho), Dibujable::renderAMundo(alto));

	std::list<Dibujable*>::iterator i = dibujables.begin();

	while(i != dibujables.end())
		(*i++)->dibujarEn(cr, posicion, 1);
		
	Dibujable::dibujarRectangulo(cr,
						Dibujable::mundoARender(posicion),
						1,
						Dibujable::mundoARender(b2Vec2(6.5,0)),
						1,
						600
						);
}
