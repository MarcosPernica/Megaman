#ifndef CAJAACCION
#define CAJAACCION

#include "../net/snapshots/Snapshotable.h"
#include "Actualizable.h"
#include "Met.h"
#include "Bumby.h"
#include "Sniper.h"
#include "JumpingSniper.h"
#include "Bombman.h"
#include "Sparkman.h"
#include "Magnetman.h"
#include "Ringman.h"
#include "Fireman.h"
#include "Construccion.h"

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
private:
	bool habilitada;
public:
	CajaAccion(Mundo &mundo,
		   real ancho,
		   real alto,
		   const b2Vec2 &posicion);

	virtual ~CajaAccion(){};
	ushort tipoCuerpo() const;
	void eliminarse(Mundo &de){};
	
	void deshabilitar();
	void habilitarse();
	bool estaHabilitada();

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

class ZonaGuardado : public CajaAccion
{
private:
	bool tomada;
	real ancho, alto;
public:
	ZonaGuardado(Mundo &mundo,
		     real ancho,
		     real alto,
		     const b2Vec2 &posicion);

	~ZonaGuardado(){};
	
	void actualizar(real deltaT);
	void interactuar(Megaman *megaman){};
};

class ZonaCerradura : public CajaAccion
{
private:
	Puerta *puerta;
	real ancho, alto;
public:
	ZonaCerradura(Mundo &mundo,
		      real ancho,
		      real alto,
		      const b2Vec2 &posicion,
		      Puerta *puerta);

	~ZonaCerradura(){};
	
	void actualizar(real deltaT);
	void interactuar(Megaman *megaman){};
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
	/*Recibe un ID del Sniper a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
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
	/*Recibe un ID del JumpingSniper a crear, siempre se crean con el mismo ID (renace el mismo monstruo)*/
	uint ID;
public:
	CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnBombman : public CajaSpawn
{
private:
	Puerta *puerta;
	/*Solo se crea una vez.*/
	bool creado;
	uint ID;
public:
	CajaSpawnBombman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnSparkman : public CajaSpawn
{
private:
	Puerta *puerta;
	/*Solo se crea una vez.*/
	bool creado;
	uint ID;
public:
	CajaSpawnSparkman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnMagnetman : public CajaSpawn
{
private:
	Puerta *puerta;
	/*Solo se crea una vez.*/
	bool creado;
	uint ID;
public:
	CajaSpawnMagnetman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnRingman : public CajaSpawn
{
private:
	Puerta *puerta;
	/*Solo se crea una vez.*/
	bool creado;
	uint ID;
public:
	CajaSpawnRingman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class CajaSpawnFireman : public CajaSpawn
{
private:
	Puerta *puerta;
	/*Solo se crea una vez.*/
	bool creado;
	uint ID;
public:
	CajaSpawnFireman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion);
	void interactuar(Megaman *megaman){};
	void actualizar(real deltaT);
};

class ZonaCamara
{
private:
	b2Vec2 posicion, posicionCentral;

	/*Como se recalcula en cada cuadro se cachean estos valores en lugar de pedirselos a cuerpo 
	ya que no los devuelve como escalares sino como un Rectangulo y habria que calcularlos una y otra vez.*/
	real ancho, alto;
	Mundo& mundo;

public:
	ZonaCamara(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion);
	~ZonaCamara(){};

	void reiniciar();
	real obtenerAlto();
	real obtenerAncho();
	b2Vec2 obtenerPosicion();

	void actualizar(real deltaT);

private:
	void actualizarRecinto(real deltaT);
};

#endif
