#ifndef MUNDO	
#define MUNDO
#include "EstadisticasMundo.h"
#include <list>
#include <Box2D/Box2D.h>
#include "Definiciones.h"
#include "Callbacks.h"
#include "Cadena.h"
#include <string>

#include "Megaman.h"
#include "PowerUp.h"
#include "Entidad.h"
#include "Disparo.h"
#include "Construccion.h"
#include "../graficos/Dibujable.h"

#include <tinyxml.h>

class FullSnapshot;
class ZonaCamara;

class PowerUp;
class Cuerpo;
class CajaAccion;
class Interactuable;
class Enemigo;
class Puerta;

enum EstadoMundo
{
	vivo,
	gameover,
	ganado,
	perdido	
};

class Mundo
{
private:

	enum Categoria
	{
		enemigo,
		powerUp,
		disparo
	};

	struct DatosEliminacion
	{
		uint ID;
		Categoria categoria;
		DatosEliminacion(uint ID, Categoria categoria) : ID(ID), categoria(categoria){};
	};

	struct SpawnMegaman
	{
		b2Vec2 inicio;
		real longitud;
	};	

	ListenerColisiones listenerColisiones;
	b2World mundo;

	/*Recta de spawn de los jugadores. Aparecen ahi de forma equidistante.*/
	SpawnMegaman zonaSpawnMegaman;

	/*Todos mapas disjuntos para mejor acceso.*/
	std::map<uint, Megaman*> megamanes;
	std::map<uint, Enemigo*> enemigos;
	std::map<uint, PowerUp*> powerUps;
	std::map<uint, Disparo*> disparos;
	std::map<uint, Puerta*> puertas;

	ZonaCamara *camara;
	
	std::list<CajaAccion*> controladores;
	std::list<Interactuable*> zonas;
	std::list<Construccion*> construcciones;
	std::list<Callback*> tareasDiferidas;
	std::list<DatosEliminacion> destrucciones;

	/*Mundo terminado?.*/
	bool terminado;
	
	void cargarNivel(Cadena nombre);
	std::string nombre_nivel;
	
	uint anterior_ID; 
	
	EstadisticasMundo estadisticas;
	
public:
	/**
	 * Cuando un Megaman muere, debe llamarse este método para que se le descuente una vida
	 * */
	void notificarMuerteMegaman(Megaman* muerto);
	
	uint generarID();
	Mundo(real anchoCamara, 
	      real altoCamara, 
	      b2Vec2 posicionCamara,
	      const std::string& nombre_nivel = "nivel.xml",
	      uint cantidad_jugadores = 1);
	b2World &obtenerMundo();

	b2Vec2 obtenerPosicionCamara();

	Megaman *obtenerMegamanCercano(const b2Vec2 posicion, bool incluirMuertos = false);
	Enemigo *obtenerEnemigoCercano(const b2Vec2 posicion);

	bool existeMegaman(uint ID);
	bool existeEnemigo(uint ID);
	bool existeElemento(uint ID);

	Entidad *obtenerEntidad(uint ID);
	void danarZona(b2AABB zona, uint dano, Bomba *bomba);

	void eliminar(Enemigo * enemigo);
	void eliminar(PowerUp * powerUp);
	void eliminar(Disparo * disparo);

	void agregar(Disparo * disparo);
	void agregar(PowerUp * powerUp);
	void agregar(Enemigo * enemigo);

	std::list<Dibujable*> obtenerDibujables() const;

	void destruirCuerpos();
	void agregarTareaDiferida(Callback *callback);
	void ejecutarTareasDiferidas();
	
	void actualizar(real segundosDesdeUltima);

	std::list<Megaman *> obtenerMegamanes(bool incluirMuertos = false);
	std::list<Dibujable *> elementosEnZona(b2Vec2 posicion, real ancho, real alto);
	void limpiar(b2Vec2 posicion, real ancho, real alto);
	std::list<Dibujable *> obtenerElementosCamara();
	Puerta *obtenerPuerta(uint IDInterno);

	void finalizar();
	EstadoMundo obtenerEstadoMundo();
	void reiniciar();

	
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
	void obtenerSnapshotables(std::map<uint, Snapshotable*> &mapa);
	
	/**
	 * Configura las estadísticas de este Mundo (vidas y armas de cada Megaman)
	 * */
	void setEstadisticas(EstadisticasMundo& estadisticas);
	
	/**
	 * Copia las estadísticas al pasado por referencia
	 * */
	void obtenerEstadisticas(EstadisticasMundo& en);
	
	/**
	 * Agrega un arma para todos los megamanes
	 * */
	void agregarArma(int tipo_arma);

private:
	void agregarCuboMadera(real ancho, real alto, b2Vec2 posicion);
	void agregarCuboMetal(real ancho, real alto, b2Vec2 posicion);
	void agregarCuboLadrillo(real ancho, real alto, b2Vec2 posicion);
	void agregarCuboTierra(real ancho, real alto, b2Vec2 posicion);
	void agregarCuboVacio(real ancho, real alto, b2Vec2 posicion);
	void agregarPuas(real ancho, real alto, b2Vec2 posicion);
	void agregarEscalera(real alto, b2Vec2 posicion);
	void agregarZonaMortal(real ancho, real alto, b2Vec2 posicion);
	void agregarZonaTransporte(real ancho, real alto, b2Vec2 posicion, b2Vec2 posicionDestino);
	void agregarZonaGuardado(real ancho, real alto, b2Vec2 posicion);
	void agregarZonaSpawnMegaman(real longitud, b2Vec2 posicion);
	void agregarZonaCerradura(uint IDPuerta, real ancho, real alto, b2Vec2 posicion);
	void agregarPuerta(uint IDInterno, real ancho, real alto, b2Vec2 posicion);
	void agregarZonaSpawnMet(b2Vec2 posicion);
	void agregarZonaSpawnBumby(b2Vec2 posicion);
	void agregarZonaSpawnSniper(b2Vec2 posicion);
	void agregarZonaSpawnJumpingSniper(b2Vec2 posicion);
	void agregarZonaSpawnBombman(uint IDPuerta, b2Vec2 posicion);
	void agregarZonaSpawnMagnetman(uint IDPuerta, b2Vec2 posicion);
	void agregarZonaSpawnSparkman(uint IDPuerta, b2Vec2 posicion);
	void agregarZonaSpawnRingman(uint IDPuerta, b2Vec2 posicion);
	void agregarZonaSpawnFireman(uint IDPuerta, b2Vec2 posicion);
	Megaman *agregarMegaman();

	void actualizarCuerpos(real deltaT);
	void obtenerAtributosXML(TiXmlAttribute *atributo, std::map<std::string,real>& mapaAtributos);
};

#endif
