#ifndef POWERUP
#define POWERUP 

#include "Definiciones.h"
#include "Cuerpo.h"
#include "Megaman.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "Actualizable.h"
#include "Callbacks.h"
#include "../net/snapshots/Snapshot.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"
#endif

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
			const b2Vec2 &posicion,
			real ancho = ANCHOSPRITEPOWERUP,
			real alto = ALTOSPRITEPOWERUP);
	~PowerUp(){};

	real obtenerProbabilidadAparicion();
	void eliminarPowerUp();
	ushort tipoCuerpo() const;

	virtual void actualizar(real deltaT){};
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
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
public:
	NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(NuevaVida);
	GENERAR_DESDESNAPSHOT(NuevaVida);

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};



class CapsulaEnergiaChica : public PowerUp
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
public:
	CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaEnergiaChica);
	GENERAR_DESDESNAPSHOT(CapsulaEnergiaChica);

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};


class CapsulaEnergiaGrande : public PowerUp
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
public:
	CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaEnergiaGrande);
	GENERAR_DESDESNAPSHOT(CapsulaEnergiaGrande);

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};



class CapsulaPlasmaChica : public PowerUp
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
public:
	CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);

	void actualizar(real deltaT);

	GENERAR_GET_TIPO(CapsulaPlasmaChica);
	GENERAR_DESDESNAPSHOT(CapsulaPlasmaChica);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};


class CapsulaPlasmaGrande : public PowerUp
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
public:
	CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(CapsulaPlasmaGrande);
	GENERAR_DESDESNAPSHOT(CapsulaPlasmaGrande);

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Habilitador
#ifndef compiling_server
 : public ImagenEscalada
#endif
{
public:
	#ifndef compiling_server
	virtual ArchivoImagen a_dibujar();
	virtual const Rectangulo obtenerRepresentacion() const = 0;
	#endif
};

class HabilitadorBomba : public PowerUp, public Habilitador
{
public:
	HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorBomba);
	GENERAR_DESDESNAPSHOT(HabilitadorBomba);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	const Rectangulo obtenerRepresentacion() const;
	#endif
};


class HabilitadorIman : public PowerUp, public Habilitador
{
public:
	HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorIman);
	GENERAR_DESDESNAPSHOT(HabilitadorIman);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	const Rectangulo obtenerRepresentacion() const;
	#endif
};


class HabilitadorChispa : public PowerUp, public Habilitador
{
public:
	HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorChispa);
	GENERAR_DESDESNAPSHOT(HabilitadorChispa);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class HabilitadorAnillo : public PowerUp, public Habilitador
{
public:
	HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorAnillo);
	GENERAR_DESDESNAPSHOT(HabilitadorAnillo);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class HabilitadorFuego: public PowerUp, public Habilitador
{
public:
	HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion);
	void aumentar(Megaman &megaman);
	GENERAR_GET_TIPO(HabilitadorFuego);
	GENERAR_DESDESNAPSHOT(HabilitadorFuego);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

#endif
