#ifndef DISPARO
#define DISPARO

#include "Cuerpo.h"
#include "Interactuable.h"
#include "Actualizable.h"
#include "Entidad.h"
#include <Box2D/Box2D.h>

class Mundo;

class Disparo : public Interactuable, public Actualizable, public Cuerpo
{
private:
	uint dano;
	bool disparoMegaman;
public:
	Disparo(Mundo &mundo,
			uint danio, 
			real ancho, 
			real alto,
			real masa, 
			const b2Vec2 &posicion,
			bool gravitacional, 
			const b2Vec2 &velocidad,
			bool disparoMegaman = true);

	virtual bool interactuar(Entidad *entidad);
	virtual void actualizar(real deltaT);

	/*Un disparo puede lanzarse (Bomba o bumerang) o dispararse (Plasma)*/
	virtual bool lanzable();
	virtual uint obtenerMultiplicadorVelocidad() const = 0;
	char tipoCuerpo() const;
	bool megamanLoDisparo() const;

	virtual Disparo *nuevo(const b2Vec2 &posicion, const b2Vec2 &velocidad) = 0;
};

class Plasma : public Disparo
{
private:
	
public:
	Plasma(Mundo &mundo, 
		   const b2Vec2 &posicion = b2Vec2_zero,
		   const b2Vec2 &velocidad = b2Vec2_zero);

	uint obtenerMultiplicadorVelocidad() const;

	Disparo *nuevo(const b2Vec2 &posicion, const b2Vec2 &velocidad);
};

class Bomba : public Disparo
{
private:
	real tiempoTotal;
public:
	Bomba(Mundo &mundo, const b2Vec2 &posicion = b2Vec2_zero, const b2Vec2 &velocidad = b2Vec2_zero);
	bool interactuar(Entidad *entidad);
	void actualizar(real deltaT);
	uint obtenerMultiplicadorVelocidad() const;

	bool lanzable();
	Disparo *nuevo(const b2Vec2 &posicion, const b2Vec2 &velocidad);
private:
	void explotar();
};


#endif