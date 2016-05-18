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
#include "../graficos/Dibujable.h"


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
/**
	 * Marcos, qué te parece si hacemos
	 * Megaman* Mundo::agregarMegaman(id_usuario)
	 * y después se llama
	 * mundo.iniciar() o algo así
	 * */
class Mundo
{
private:
	ListenerColisiones listenerColisiones;
	b2World mundo;

	/*Distintas representaciones del mismo objeto en memoria (optimiza y ademas el polimorfismo no aplica aca).*/
	std::map<uint, Megaman*> megamanes;
	std::map<uint, Snapshotable*> snapshotables;
	std::map<uint, Dibujable*> dibujables;
	std::map<uint, Actualizable*> actualizables;

	std::list<Construccion*> construcciones;
	std::list<uint> destrucciones;
	
	void crearNivel();
public:
	/*Paleativo del server*/
	uint generarID(){static uint ID = 0; return ++ID;};

	Mundo();
	b2World &obtenerMundo();
	void danarZona(b2AABB zona, uint dano);

	void eliminar(Cuerpo *cuerpo);

	void agregar(Disparo * disparo);
	void agregar(PowerUp * powerUp);
	void agregar(Entidad * entidad);

	std::list<Dibujable*> obtenerDibujables() const;/////////COPIA//// esa lista podría ser demasiado grande

	void destruirCuerpos();

	static const b2Vec2 gravedad;
	
	void actualizar(real segundosDesdeUltima);
	
	Megaman* getMegaman();
	
};

#endif
