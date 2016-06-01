#ifndef CAJAACCION
#define CAJAACCION

#include "../net/snapshots/Snapshotable.h"
#include "Actualizable.h"
#include "Met.h"
#include "Bumby.h"
#include "Sniper.h"
#include "JumpingSniper.h"
#include "Bombman.h"

#include <Box2D/Box2D.h>
#include "Definiciones.h"
#include "Interactuable.h"
#include "Mundo.h"
#include "Callbacks.h"

class Megaman;
class CajaAccion;

class CallbackInteraccionCajaAccion : public Callback
{
private:
	Megaman *megaman;
	CajaAccion *cajaAccion;
public:
	CallbackInteraccionCajaAccion(Megaman *megaman, CajaAccion *cajaAccion);
	void ejecutar();
};



class CajaAccion : public Cuerpo, public Actualizable, public Interactuable
{
public:
	CajaAccion(Mundo &mundo,
		   real ancho,
		   real alto,
		   const b2Vec2 &posicion);

	virtual ~CajaAccion(){};
	ushort tipoCuerpo() const;
	void eliminarse(Mundo &de){};

	virtual void actualizar(real deltaT){};
};

class ZonaMortal : public CajaAccion
{
private:
	
public:
	ZonaMortal(Mundo &mundo,
			real ancho,
			real alto,
			const b2Vec2 &posicion);
	~ZonaMortal(){};
	void interactuar(Megaman *megaman);
};

class ZonaTransporte : public CajaAccion
{
private:
	b2Vec2 posicionDestino;
public:
	ZonaTransporte(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion,
		       const b2Vec2 &posicionDestino);

	~ZonaTransporte(){};

	void interactuar(Megaman *megaman);
};


class CajaSpawn : public CajaAccion
{
private:
	Mundo &mundo;
	b2Vec2 posicion;
public:
	CajaSpawn(Mundo &mundo, b2Vec2 posicion);
	virtual void actualizar(real deltaT) = 0;
};

class CajaSpawnMet : public CajaSpawn
{
private:
	real cuentaRegresiva;
	/*Recibe un ID del met a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnMet(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnBumby : public CajaSpawn
{
private:
	real cuentaRegresiva;
	/*Recibe un ID del Bumby a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnBumby(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnSniper : public CajaSpawn
{
private:
	real cuentaRegresiva;
	/*Recibe un ID del Bumby a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnSniper(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnJumpingSniper : public CajaSpawn
{
private:
	real cuentaRegresiva;
	/*Recibe un ID del Bumby a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnBombman : public CajaSpawn
{
private:
	bool creado;
	/*Recibe un ID del Bumby a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnBombman(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

#endif
