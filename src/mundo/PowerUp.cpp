#include "PowerUp.h"
#include "Disparo.h"
#include "Definiciones.h"
#include "../net/snapshots/Snapshot.h"

CallbackAumentador::CallbackAumentador(PowerUp *powerUp, Megaman *megaman) : powerUp(powerUp), megaman(megaman)
{
}

void CallbackAumentador::ejecutar()
{
	powerUp->aumentar(*megaman);
}

NuevaVida::NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void NuevaVida::aumentar(Megaman & megaman)
{
	megaman.aumentarVida();
	eliminarPowerUp();
}


HabilitadorBomba::HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorBomba::aumentar(Megaman & megaman)
{
	megaman.agregarArma(new Bomba(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);
	eliminarPowerUp();
}

HabilitadorIman::HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorIman::aumentar(Megaman & megaman)
{
	megaman.agregarArma(new Iman(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);
	eliminarPowerUp();
}

HabilitadorChispa::HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorChispa::aumentar(Megaman & megaman)
{
	megaman.agregarArma(new Chispa(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);
	eliminarPowerUp();
}

HabilitadorAnillo::HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorAnillo::aumentar(Megaman & megaman)
{
	megaman.agregarArma(new Anillo(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);
	eliminarPowerUp();
}

HabilitadorFuego::HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorFuego::aumentar(Megaman & megaman)
{
	megaman.agregarArma(new Fuego(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);
	eliminarPowerUp();
}

CapsulaEnergiaChica::CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIACHICA, posicion)
{
}

void CapsulaEnergiaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(2);
	eliminarPowerUp();
}

CapsulaEnergiaGrande::CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIAGRANDE, posicion)
{
}

void CapsulaEnergiaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(6);
	eliminarPowerUp();
}

CapsulaPlasmaChica::CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMACHICA, posicion)
{
}

void CapsulaPlasmaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(2);
	eliminarPowerUp();
}

CapsulaPlasmaGrande::CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMAGRANDE, posicion)
{
}

void CapsulaPlasmaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(6);
	eliminarPowerUp();
}

PowerUp::PowerUp(uint ID, Mundo &mundo,
				 real probabilidadAparicion,
				 const b2Vec2 &posicion) :
				 probabilidadAparicion(probabilidadAparicion),
				 Cuerpo(ID, 
						mundo,
						ANCHOSPRITEPOWERUP,
						ALTOSPRITEPOWERUP,
						MASAPOWERUP,
						POWERUPS,
						CONSTRUCCIONES | PERSONAJES,
						posicion,	
						false,
						true,	
						b2Vec2 VELOCIDADPOWERUP)
			     
{
	if (probabilidadAparicion < 0 || probabilidadAparicion > 1)
		probabilidadAparicion = 0;

	this->probabilidadAparicion = probabilidadAparicion;
}

void PowerUp::eliminarse(Mundo& de)
{
	de.eliminar(this);
}

ushort PowerUp::tipoCuerpo() const
{
	return POWERUPS;
}

real PowerUp::obtenerProbabilidadAparicion()
{
	return probabilidadAparicion;
}

void PowerUp::eliminarPowerUp()
{
	obtenerMundo().eliminar(this);
}

void PowerUp::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(probabilidadAparicion);
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void PowerUp::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(probabilidadAparicion);
	Cuerpo::setStateFromSnapshot(sn);
}
/*
 HabilitadorBomba* HabilitadorBomba::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	HabilitadorBomba* p =new HabilitadorBomba(sn.getID(),mundo,b2Vec2(0,0));
	p->setStateFromSnapshot(sn);
	return p;
}
*/
/*
#define GENERAR_IMPLEMENTACION_DESDESNAPSHOT(clase) \
clase* clase::desdeSnapshot(const Snapshot& sn, Mundo& mundo){ \
	clase* p =new clase(sn.getID(),mundo,b2Vec2(0,0)); \
	p->setStateFromSnapshot(sn); \
	return p; \
}

GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorBomba)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorIman)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorChispa)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorAnillo)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorFuego)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaPlasmaGrande)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaPlasmaChica)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaEnergiaGrande)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaEnergiaChica)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(NuevaVida)
*/
