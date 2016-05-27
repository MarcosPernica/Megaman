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
class FullSnapshot;


class PowerUp;
class Cuerpo;
class CajaAccion;
class Interactuable;

	/*
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
	std::list<CajaAccion*> controladores;

	std::list<Interactuable*> zonas;
	std::list<Construccion*> construcciones;
	std::list<Callback*> tareasDiferidas;
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

	void agregarConstruccion(real ancho, real alto, b2Vec2 posicion);
	void agregarEscalera(real alto, b2Vec2 posicion);
	Megaman *agregarMegaman(b2Vec2 posicion);
	void agregarZonaMortal(real ancho, real alto, b2Vec2 posicion);
	void agregarZonaTransporte(real ancho, real alto, b2Vec2 posicion, b2Vec2 posicionDestino);

	bool existeElemento(uint ID);

	std::list<Dibujable*> obtenerDibujables() const;/////////COPIA//// esa lista podría ser demasiado grande

	void destruirCuerpos();
	void agregarTareaDiferida(Callback *callback);
	void ejecutarTareasDiferidas();

	static const b2Vec2 gravedad;
	
	void actualizar(real segundosDesdeUltima);

	std::list<Megaman *> obtenerMegamanes();
	std::list<Dibujable *> elementosEnZona(b2Vec2 posicion, real ancho, real alto);
	
	Megaman* getMegaman();
	
	/**
	 * Genera un FullSnapshot, lo asigna a la variable en, con lo que se
	 * evita copiar y crear FullSnapshots más veces de las necesarias.
	 * */
	void obtenerSnapshot(FullSnapshot& en);//const;
	
	/**
	 * Inyecta un FullSnapshot.
	 * -Los objetos en mundo pero no en el fs, son destruídos
	 * -A los objetos en el mundo y en el fs se les inyecta una Snapshot
	 * -Los objetos que están sólo en el fs se crean en cualquier estado
	 * y se les inyecta una snapshot
	 * 
	 * Dos Snapshotables representan al mismo objeto sii su ID y su tipo son iguales.
	 * */
	 void inyectarSnapshot(FullSnapshot& fs);
	 
	/**
	 * Agrega lo que el Snapshot represente al mundo
	 * */
	void agregarDesdeSnapshot(const Snapshot& sn);
	
	/**
	 * devuelve el megaman 0, 1, 2, 3; 
	 * cada cliente sabe cuál megaman es el suyo porque
	 * este numero se distribuye
	 * */
	Megaman* obtenerMegaman(uint posicion);
};

#endif
