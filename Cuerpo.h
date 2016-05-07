#ifndef CUERPO	
#define CUERPO

#include "Vector2D.h"
#include "Definiciones.h"

#define MASAINVERSAINFINITA -1

class Cuerpo
{
private:
	real masaInversa;
	Vector2D posicion, velocidad, orientacion;
	Vector2D fuerzas, peso;
	bool gravitacional;
public:
	Cuerpo(real masa, const Vector2D &posicion, bool gravitacional = true, const Vector2D &velocidad = Vector2D(), const Vector2D &orientacion = Vector2D(1,0));
	void gravitar();
	void ingravitar();
	void agregarFuerza(const Vector2D &fuerza);
	void calcularFisicas(real deltaT);

	const Vector2D &obtenerPosicion() const;
	const Vector2D &obtenerVelocidad() const;
	const Vector2D &obtenerOrientacion() const; 
	const Vector2D &obtenerPeso() const;

	void modificarVelocidad(const Vector2D &velocidad);
	void modificarPosicion(const Vector2D &posicion);
	void modificarOrientacion(const Vector2D &orientacion);

	static const Vector2D gravedad;
};
#endif