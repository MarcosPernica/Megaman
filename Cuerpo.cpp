#include "Cuerpo.h"

const Vector2D Cuerpo::gravedad(0,9.8);

Cuerpo::Cuerpo(real masa, const Vector2D & posicion, bool gravitacional, const Vector2D & velocidad, const Vector2D & orientacion) : posicion(posicion), gravitacional(gravitacional), velocidad(velocidad), orientacion(orientacion)
{
	if (masa)
		masaInversa = 1 / masa;
	else
		masaInversa = MASAINVERSAINFINITA;
}

void Cuerpo::gravitar()
{
	gravitacional = true;
}

void Cuerpo::ingravitar()
{
	gravitacional = false;
}

void Cuerpo::agregarFuerza(const Vector2D & fuerza)
{
	fuerzas += fuerza;
}

void Cuerpo::calcularFisicas(real deltaT)
{
	Vector2D aceleracion;

	if (gravitacional)
		fuerzas += gravedad;

	aceleracion = masaInversa*fuerzas;

	velocidad += aceleracion*deltaT;

	posicion += velocidad*deltaT + 0.5*aceleracion*deltaT*deltaT;

	fuerzas = Vector2D();
}

const Vector2D & Cuerpo::obtenerPosicion() const
{
	return posicion;
}

const Vector2D & Cuerpo::obtenerVelocidad() const
{
	return velocidad;
}

const Vector2D & Cuerpo::obtenerOrientacion() const
{
	return orientacion;
}

void Cuerpo::modificarVelocidad(const Vector2D &velocidad)
{
	this->velocidad = velocidad;
}

void Cuerpo::modificarPosicion(const Vector2D & posicion)
{
	this->posicion = posicion;
}

void Cuerpo::modificarOrientacion(const Vector2D & orientacion)
{
	this->orientacion = orientacion;
}

