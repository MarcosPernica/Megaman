#ifndef POWERUP
#define POWERUP 

#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "Actualizable.h"
#include "Callbacks.h"

class PowerUp;

class CallbackAumentador : public Callback
{
private:
	PowerUp *powerUp;
	Megaman *megaman;
public:
	CallbackAumentador(PowerUp *powerUp, Megaman *megaman);
	void ejecutar();
};



class PowerUp : public Cuerpo, public Actualizable
{
private:
	real probabilidadAparicion;
public:
	PowerUp(uint ID, 
			Mundo &mundo,
			real probabilidadAparicion,
			const b2Vec2 &posicion);
	~PowerUp(){};

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();
	ushort tipoCuerpo() const;

	void actualizar(real deltaT){};
	virtual void aumentar(Megaman &megaman) = 0;
};



class NuevaVida : public PowerUp
{
public:
	NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};


class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};

class HabilitadorBomba : public PowerUp
{
public:
	HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
};

#endif
