#ifndef MUNDO	
#define MUNDO

#include <list>
#include <Box2D/Box2D.h>
#include "Definiciones.h"
#include "Callbacks.h"

#include "Megaman.h"
#include "PowerUp.h"
#include "Entidad.h"
#include "Disparo.h"
#include "Construccion.h"
/*
class Disparo;

class Entidad;
class Construccion;
*/
class PowerUp;
class Cuerpo;

/* Volar todas las listas, dejar 
 * 
 * -mapa (ID de usuario, Megaman*)
 * -mapa (ID, snapshotable)
 * -conjunto de Cuerpo* destruciones mantenerla
 * 
 * -conjunto de Dibujables
 * -conjunto de Actualizables.
 * 
 * */

class Mundo
{
private:
	ListenerColisiones listenerColisiones;
	b2World mundo;
	std::list<Megaman*> jugadores;

	std::list<Disparo*> disparos;
	std::list<Entidad*> enemigos;
	std::list<PowerUp*> powerUps;

	std::list<Construccion*> construcciones;
	std::list<Cuerpo*> destrucciones;
	
	std::list<Actualizable*> actualizables;
	
	void crearNivel();
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
	std::list<Dibujable*> obtenerDibujables() const;/////////COPIA//// esa lista podría ser demasiado grande

	void destruirCuerpos();

	static const b2Vec2 gravedad;
	
	void actualizar(real segundosDesdeUltima);
	
	Megaman* getMegaman();
	
};

#endif
