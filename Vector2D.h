#ifndef VECTOR2D
#define VECTOR2D

#include "Definiciones.h"

#define X 0
#define Y 1

class Vector2D
{
private:
	real x, y;
public:
	Vector2D(real x = 0, real y = 0);

	real norma() const;
	Vector2D normalizado() const;
	Vector2D operator+(const Vector2D &operando) const;
	Vector2D &operator+=(const Vector2D &operando);
	Vector2D operator-(const Vector2D &operando) const;
	Vector2D operator-() const;
	Vector2D &operator-=(const Vector2D &operando);
	real operator*(const Vector2D &operando) const;	
	real &operator[](unsigned int coordenada);
	real operator[](unsigned int coordenada) const;

	friend Vector2D operator*(real escalar, const Vector2D &vector);
	friend Vector2D operator*(const Vector2D &vector, real escalar);

	static const Vector2D nulo;
};

#endif
