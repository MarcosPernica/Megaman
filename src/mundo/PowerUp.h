#ifndef POWERUP
#define POWERUP 

#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "Actualizable.h"
#include "Callbacks.h"
#include "../net/snapshots/Snapshot.h"

class PowerUp;

class CallbackAumentador : public Callback
{
private:
	PowerUp *powerUp;
	Megaman *megaman;
public:
	CallbackAumentador(PowerUp *powerUp, Megaman *megaman);
	void ejecutar();
};



class PowerUp : public Cuerpo, public Actualizable
{
private:
	real probabilidadAparicion;
public:
	PowerUp(uint ID, 
			Mundo &mundo,
			real probabilidadAparicion,
			const b2Vec2 &posicion);
	~PowerUp(){};

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();
	ushort tipoCuerpo() const;

	void actualizar(real deltaT){};
	virtual void aumentar(Megaman &megaman) = 0;
	
	void eliminarse(Mundo& de);
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
};
//-----------------------------MACRO QUE GENERA LOS desdeSnapshot------------//
/*
 declarado como:
 static NuevaVida* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
 --------------------
 implementación:
 HabilitadorBomba* HabilitadorBomba::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	HabilitadorBomba* p =new HabilitadorBomba(sn.getID(),mundo,b2Vec2(0,0));
	p->setStateFromSnapshot(sn);
	return p;
}
*/
#define GENERAR_DESDESNAPSHOT(clase) \
static clase* desdeSnapshot(const Snapshot& sn, Mundo& mundo){ \
	clase* p =new clase(sn.getID(),mundo,b2Vec2(0,0)); \
	p->setStateFromSnapshot(sn); \
	return p; \
}
//-------------------------------------------------------------------------------//

class NuevaVida : public PowerUp
{
public:
	NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(NuevaVida);
	GENERAR_DESDESNAPSHOT(NuevaVida);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaEnergiaChica);
	GENERAR_DESDESNAPSHOT(CapsulaEnergiaChica);
};


class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaEnergiaGrande);
	GENERAR_DESDESNAPSHOT(CapsulaEnergiaGrande);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaPlasmaChica);
	GENERAR_DESDESNAPSHOT(CapsulaPlasmaChica);
};


class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaPlasmaGrande);
	GENERAR_DESDESNAPSHOT(CapsulaPlasmaGrande);
};

class HabilitadorBomba : public PowerUp
{
public:
	HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorBomba);
	GENERAR_DESDESNAPSHOT(HabilitadorBomba);
};


class HabilitadorIman : public PowerUp
{
public:
	HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorIman);
	GENERAR_DESDESNAPSHOT(HabilitadorIman);
};


class HabilitadorChispa : public PowerUp
{
public:
	HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorChispa);
	GENERAR_DESDESNAPSHOT(HabilitadorChispa);
};

class HabilitadorAnillo : public PowerUp
{
public:
	HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorAnillo);
	GENERAR_DESDESNAPSHOT(HabilitadorAnillo);
};

class HabilitadorFuego: public PowerUp
{
public:
	HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorFuego);
	GENERAR_DESDESNAPSHOT(HabilitadorFuego);
};

#endif
