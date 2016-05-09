#ifndef MUNDO	
#define MUNDO

#include <list>
#include <Box2D\Box2D.h>
#include "Definiciones.h"
#include "Callbacks.h"

class Disparo;
class PowerUp;
class Entidad;
class Megaman;
class Construccion;
class Cuerpo;

class Mundo
{
private:
	DetectarBalistica detectorBalistica;
	DetectarSuelo detectorSuelo;
	DetectarTocarEnemigos detectorToqueEnemigos;

	b2World mundo;
	std::list<Megaman> jugadores;

	std::list<Disparo*> disparos;
	std::list<Entidad*> enemigos;
	std::list<PowerUp*> powerUps;

	std::list<Construccion> construcciones;
	std::list<Cuerpo*> destrucciones;
public:
	Mundo();
	b2World &obtenerMundo();
	void danarZona(b2AABB zona, uint dano);

	void eliminar(Entidad *entidad);
	void eliminar(Disparo *disparo);
	void eliminar(PowerUp *powerUp);

	void agregar(Disparo *disparo);
	void agregar(PowerUp *powerUp);
	void agregar(Entidad *entidad);

	void destruirCuerpos();

	static const b2Vec2 gravedad;
};

#endif