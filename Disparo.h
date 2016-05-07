#ifndef DISPARO
#define DISPARO

#include "Cuerpo.h"
#include "CajaColision.h"
#include "Interactuable.h"
#include "Actualizable.h"
#include "Entidad.h"

class Mundo;

class Disparo : public Interactuable, public Actualizable, public Cuerpo, public CajaColision
{
private:
	real daño;
public:
	Disparo(real daño, real masa, const Vector2D &posicion, bool gravitacional, const Vector2D &velocidad);
	virtual bool interactuar(Entidad *entidad);
	virtual void actualizar(real deltaT);

	/*Si puede traspasar las paredes debe devolver false.*/
	virtual bool soloEnemigos();

	/*Un disparo puede lanzarse (Bomba o bumerang) o dispararse (Plasma)*/
	virtual bool lanzable();
	virtual real multiplicadorVelocidad() const = 0;

	virtual Disparo *nuevo(const Vector2D &posicion, const Vector2D &velocidad) = 0;
};

class Plasma : public Disparo
{
private:
	
public:
	Plasma(const Vector2D &posicion = Vector2D::nulo, const Vector2D &velocidad = Vector2D::nulo);
	real multiplicadorVelocidad() const;
	Disparo *nuevo(const Vector2D &posicion, const Vector2D &velocidad);
};

class Bomba : public Disparo
{
private:
	Mundo &mundo;
	real tiempoTotal;
	CajaColision radio;
public:
	Bomba(Mundo &mundo, const Vector2D &posicion = Vector2D::nulo, const Vector2D &velocidad = Vector2D::nulo);
	bool interactuar(Entidad *entidad);
	bool soloEnemigos();
	void actualizar(real deltaT);

	real multiplicadorVelocidad() const;

	bool lanzable();
	Disparo *nuevo(const Vector2D &posicion, const Vector2D &velocidad);
private:
	void explotar();
};


#endif
