#include "CajaColision.h"

CajaColision::CajaColision(const Vector2D & centroCajaColision, real altoCajaColision, real anchoCajaColision) : centroCajaColision(centroCajaColision), altoCajaColision(altoCajaColision), anchoCajaColision(anchoCajaColision)
{
}

void CajaColision::modificarCentroCajaColision(const Vector2D & centroCajaColision)
{
	this->centroCajaColision = centroCajaColision;
}

bool CajaColision::verificarColision(const CajaColision & objeto, InformacionColision &info) const
{
	verificarColisionX(objeto, info);
	verificarColisionY(objeto, info);

	if (info.penetracionX[X] == info.penetracionX[Y] || info.penetracionY[X] == info.penetracionY[Y])
		return false;
	return true;
}

const Vector2D & CajaColision::obtenerCentroCajaColision() const
{
	return centroCajaColision;
}

real CajaColision::obtenerAltoCajaColision() const
{
	return altoCajaColision;
}

real CajaColision::obtenerAnchoCajaColision() const
{
	return anchoCajaColision;
}

void CajaColision::verificarColisionX(const CajaColision & objeto, InformacionColision & info) const
{
	real inicioInterseccion, finInterseccion;

	real bordeIzquierdo1 = bordeIzquierdo(), bordeDerecho1 = bordeDerecho();
	real bordeIzquierdo2 = objeto.bordeIzquierdo(), bordeDerecho2 = objeto.bordeDerecho();

	if (bordeIzquierdo1 < bordeIzquierdo2)
		inicioInterseccion = bordeIzquierdo2;
	else
		inicioInterseccion = bordeIzquierdo1;

	if (bordeDerecho1 > bordeDerecho2)
		finInterseccion = bordeDerecho2;
	else
		finInterseccion = bordeDerecho1;

	info.penetracionX[X] = inicioInterseccion;
	info.penetracionX[Y] = finInterseccion;
}

void CajaColision::verificarColisionY(const CajaColision & objeto, InformacionColision & info) const
{
	real inicioInterseccion, finInterseccion;

	real bordeSuperior1 = bordeSuperior(), bordeInferior1 = bordeInferior();
	real bordeSuperior2 = objeto.bordeSuperior(), bordeInferior2 = objeto.bordeInferior();

	if (bordeSuperior1 < bordeSuperior2)
		inicioInterseccion = bordeSuperior2;
	else
		inicioInterseccion = bordeSuperior1;

	if (bordeInferior1 > bordeInferior2)
		finInterseccion = bordeInferior2;
	else
		finInterseccion = bordeInferior1;

	info.penetracionY[X] = inicioInterseccion;
	info.penetracionY[Y] = finInterseccion;
}

real CajaColision::bordeSuperior() const
{
	return (obtenerCentroCajaColision() - Vector2D(0, altoCajaColision/2))[Y];
}

real CajaColision::bordeInferior() const
{
	return (obtenerCentroCajaColision() + Vector2D(0, altoCajaColision / 2))[Y];
}

real CajaColision::bordeIzquierdo() const
{
	return (obtenerCentroCajaColision() - Vector2D(anchoCajaColision / 2,0))[X];
}

real CajaColision::bordeDerecho() const
{
	return (obtenerCentroCajaColision() + Vector2D(anchoCajaColision / 2, 0))[X];
}
