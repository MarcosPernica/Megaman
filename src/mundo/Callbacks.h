#ifndef CALLBACKS
#define CALLBACKS

#include <Box2D/Box2D.h>
#include "Definiciones.h"

class DanarRadio : public b2QueryCallback
{
private:
	uint dano;
public:
	DanarRadio(uint dano);
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

class ListenerColisiones : public b2ContactListener
{
private:
	DetectarEscalera detectorEscalera;
	DetectarBalistica detectorBalistica;
	DetectarSuelo detectorSuelo;
	DetectarTocarEnemigos detectorToqueEnemigos;
public:
	void BeginContact(b2Contact *contacto);
	void EndContact(b2Contact *contacto);
};

#endif
