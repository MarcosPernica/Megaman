#ifndef CALLBACKS
#define CALLBACKS

#include <Box2D/Box2D.h>
#include "Definiciones.h"
#include <list>

class Dibujable;
class Mundo;
class PowerUp;
class Bomba;

class Callback
{	
public:
	virtual void ejecutar() = 0;
	~Callback(){};
};

class CallbackCreadorPowerUp : public Callback
{
private:
	uint ID;
	Mundo &mundo;
	const b2Vec2 &posicion;
public:
	CallbackCreadorPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void ejecutar();
};

class CallbackHabilitadorArma : public Callback
{
private:
	uint ID, arma;
	Mundo &mundo;
	const b2Vec2 &posicion;
public:
	CallbackHabilitadorArma(uint ID, Mundo &mundo, const b2Vec2 &posicion, uint arma);
	void ejecutar();
};

class ElementosEnZona : public b2QueryCallback
{
private:
	std::list<Dibujable*> &elementos;
public:
	ElementosEnZona(std::list<Dibujable*> &elementos);
	bool ReportFixture(b2Fixture *fixture);
};

class DanarRadio : public b2QueryCallback
{
private:
	uint dano;
	Bomba *bomba;
public:
	DanarRadio(uint dano, Bomba *Bomba);
	bool ReportFixture(b2Fixture *fixture);
};

class DetectarSuelo : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};

class DetectarEscalera : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};


class DetectarBalistica : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

class DetectarTocarEnemigos : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

class DetectarTocarPowerUp : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

class DetectarTocarCajaAccion : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

class ListenerColisiones : public b2ContactListener
{
private:
	DetectarTocarPowerUp detectorPowerUp;
	DetectarEscalera detectorEscalera;
	DetectarBalistica detectorBalistica;
	DetectarSuelo detectorSuelo;
	DetectarTocarEnemigos detectorToqueEnemigos;
	DetectarTocarCajaAccion detectorCajaAccion;
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};

#endif
