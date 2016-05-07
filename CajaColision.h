#ifndef COLISIONABLE
#define COLISIONABLE

#include "Cuerpo.h"
#include "Definiciones.h"

struct InformacionColision
{
	Vector2D penetracionX, penetracionY;
};

class CajaColision
{
private:
	double altoCajaColision, anchoCajaColision;
	Vector2D centroCajaColision;
public:
	CajaColision(const Vector2D &centroCajaColision, real altoCajaColision, real anchoCajaColision);

	void modificarCentroCajaColision(const Vector2D &centroCajaColision);

	/*Chequea si hay colision y devuelve informacion para poder solucionarla.*/
	bool verificarColision(const CajaColision &objeto, InformacionColision &info) const;

	/*Si existen objetos en movimiento se redefine para optimizar el rendimiento en lugar de setear a cada movimiento el centro de la caja.*/
	virtual const Vector2D &obtenerCentroCajaColision() const;
	real obtenerAltoCajaColision() const;
	real obtenerAnchoCajaColision() const;


private:
	void verificarColisionX(const CajaColision &objeto, InformacionColision &info) const;
	void verificarColisionY(const CajaColision &objeto, InformacionColision &info) const;
	
	real bordeSuperior() const;
	real bordeInferior() const;
	real bordeIzquierdo() const;
	real bordeDerecho() const;
};

#endif
