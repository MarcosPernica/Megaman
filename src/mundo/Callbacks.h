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
	virtual ~Callback(){};
};

/*Decide que PowerUp lanza el enemigo (si acaso lanza).*/

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


/*Pone en el mundo el habilitador de arma especial.*/
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

/*Obtiene todos los elementos en una zona y los coloca en elementos.*/
class ElementosEnZona : public b2QueryCallback
{
private:
	std::list<Dibujable*> &elementos;
public:
	ElementosEnZona(std::list<Dibujable*> &elementos);
	bool ReportFixture(b2Fixture *fixture);
};

/*Ataca todas las entidades en un radio.*/
class DanarRadio : public b2QueryCallback
{
private:
	uint dano;
	Bomba *bomba;
public:
	DanarRadio(uint dano, Bomba *Bomba);
	bool ReportFixture(b2Fixture *fixture);
};

/*Detecta cuando una de las Boxes toca una pared.*/
class DetectarSuelo : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};

/*Avisa si puede megaman escalar.*/
class DetectarEscalera : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};

/*Avisa si hubo algun impacto de bala.*/
class DetectarBalistica : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

/*Megaman pierde vida si toca un enemigo.*/
class DetectarTocarEnemigos : public b2ContactListener
{
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto){};
};

/*Para que megaman pueda agarrar los powerUps.*/
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

/*Nuclea todos en un solo ContactListener ya que Box2D no soporta varios.*/

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
