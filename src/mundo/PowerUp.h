#ifndef POWERUP
#define POWERUP 

#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "Actualizable.h"
#include "Callbacks.h"

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
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
};



class NuevaVida : public PowerUp
{
public:
	NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_NUEVA_VIDA;};
	static NuevaVida* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};



class CapsulaEnergiaChica : public PowerUp
{
public:
	CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_ENRG_CHICA;};
	static CapsulaEnergiaChica* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};


class CapsulaEnergiaGrande : public PowerUp
{
public:
	CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_ENRG_GDE;};
	static CapsulaEnergiaGrande* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};



class CapsulaPlasmaChica : public PowerUp
{
public:
	CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_PLASM_CHICA;};
	static CapsulaPlasmaChica* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};


class CapsulaPlasmaGrande : public PowerUp
{
public:
	CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_PLASM_GDE;};
	static CapsulaPlasmaGrande* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

class HabilitadorBomba : public PowerUp
{
public:
	HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_HABILITA_BOMBA;};
	static HabilitadorBomba* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};


class HabilitadorIman : public PowerUp
{
public:
	HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_HABILITA_BOMBA;};
};


class HabilitadorChispa : public PowerUp
{
public:
	HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_HABILITA_BOMBA;};
};

class HabilitadorAnillo : public PowerUp
{
public:
	HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_HABILITA_BOMBA;};
};

class HabilitadorFuego: public PowerUp
{
public:
	HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	virtual int getTipo() const {return TIPO_PWRUP_HABILITA_BOMBA;};
};

#endif
