#include "Vector2D.h"
#include <math.h>

const Vector2D Vector2D::nulo = Vector2D(0, 0);

Vector2D::Vector2D(real x, real y)
{
	this->x = x;
	this->y = y;
}

real Vector2D::norma() const
{
	return sqrt(*this**this);
}

Vector2D Vector2D::normalizado() const
{
	return (1 / norma())**this;
}

Vector2D Vector2D::operator+(const Vector2D & operando) const
{
	return Vector2D(x+operando.x, y+operando.y);
}

Vector2D & Vector2D::operator+=(const Vector2D & operando)
{
	*this = *this + operando;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D & operando) const
{
	return Vector2D(operando.x-x, operando.y-y);
}

Vector2D & Vector2D::operator-=(const Vector2D & operando)
{
	*this = *this - operando;
	return *this;
}

real Vector2D::operator*(const Vector2D & operando) const
{
	return x*operando.x + y*operando.y;
}

real & Vector2D::operator[](unsigned int coordenada)
{
	return (coordenada) ? (x) : (y);
}

real Vector2D::operator[](unsigned int coordenada) const
{
	return (coordenada) ? (x) : (y);
}

Vector2D operator*(real escalar, const Vector2D & vector)
{
	return Vector2D(escalar*vector.x, escalar*vector.y);
}

Vector2D operator*(const Vector2D & vector, real escalar)
{
	return Vector2D(escalar*vector.x, escalar*vector.y);
}
