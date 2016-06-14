#ifndef DISPARO
#define DISPARO

#include "Cuerpo.h"
#include "Actualizable.h"
#include <Box2D/Box2D.h>
#include "../net/snapshots/Snapshot.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"

class Entidad;

class Mundo;

//--------------------macro que genera desdeSnapshot-----------------------//
#define GENERAR_DESDE_SNAPSHOT(clase) \
static clase* desdeSnapshot(const Snapshot& sn, Mundo& mundo){ \
	clase* p = new clase(sn.getID(), mundo, 0); \
	p->setStateFromSnapshot(sn); \
	return p; \
}//categoriaTarget se snapshotea!

class Disparo : public Actualizable, public Cuerpo
{
private:
	uint dano;
	ushort categoriaTarget;
public:
	Disparo(uint ID,
			Mundo &mundo,
			uint danio, 
			real ancho, 
			real alto,
			real masa,
			ushort categoriaTarget,
			const b2Vec2 &posicion,
			bool gravitacional, 
			const b2Vec2 &velocidad);

	virtual void actualizar(real deltaT);
	virtual void alColisionar(Cuerpo *cuerpo);
	~Disparo(){};

	/*Un disparo puede lanzarse (Bomba o bumerang) o dispararse (Plasma)*/
	virtual bool lanzable();
	virtual uint obtenerMultiplicadorVelocidad() const = 0;
	ushort tipoCuerpo() const;
	virtual ushort tipoDisparo() const = 0;
	ushort obtenerCategoriaTarget();
	void eliminarse(Mundo& de);

	virtual Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad) = 0;
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
};

class Plasma : public Disparo, public Animado
{
private:
	Animacion animacion;
public:
	Plasma(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Plasma(){};

	uint obtenerMultiplicadorVelocidad() const;
	ushort tipoDisparo() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	
	GENERAR_GET_TIPO(Plasma);
	GENERAR_DESDE_SNAPSHOT(Plasma);

	void actualizar(real deltaT){avanzar(deltaT);};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerVelocidad().x < 0;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPLASMA/2,
						obtenerPosicion().y-ALTOSPRITEPLASMA/2,
						ANCHOSPRITEPLASMA,
						ALTOSPRITEPLASMA);}
};

class Chispa : public Disparo, public Animado
{
private:
	Animacion animacion;	
public:
	Chispa(uint ID, 
		   Mundo &mundo, 
 		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Chispa(){};

	uint obtenerMultiplicadorVelocidad() const;
	ushort tipoDisparo() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	GENERAR_GET_TIPO(Chispa);
	GENERAR_DESDE_SNAPSHOT(Chispa);

	void actualizar(real deltaT){avanzar(deltaT);};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return false;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITECHISPA/2,
						obtenerPosicion().y-ALTOSPRITECHISPA/2,
						ANCHOSPRITECHISPA,
						ALTOSPRITECHISPA);}
};

class Anillo : public Disparo, public Animado
{
private:
	Animacion animacion;
	real tiempo;
public:
	GENERAR_GET_TIPO(Anillo);
	Anillo(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Anillo(){};

	ushort tipoDisparo() const;
	uint obtenerMultiplicadorVelocidad() const;
	void actualizar(real deltaT);
	void alColisionar(Cuerpo *cuerpo);

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_DESDE_SNAPSHOT(Anillo);

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return false;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEANILLO/2,
						obtenerPosicion().y-ALTOSPRITEANILLO/2,
						ANCHOSPRITEANILLO,
						ALTOSPRITEANILLO);}
};

class Fuego : public Disparo, public Animado
{
private:
	Animacion animacion;	
public:
	GENERAR_GET_TIPO(Fuego);
	Fuego(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Fuego(){};

	ushort tipoDisparo() const;

	uint obtenerMultiplicadorVelocidad() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	GENERAR_DESDE_SNAPSHOT(Fuego);

	void actualizar(real deltaT){avanzar(deltaT);};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerVelocidad().x < 0;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEFUEGO/2,
						obtenerPosicion().y-ALTOSPRITEFUEGO/2,
						ANCHOSPRITEFUEGO,
						ALTOSPRITEFUEGO);}
};

class Iman : public Disparo, public Animado
{
private:
	Animacion animacion;
	Entidad *target;
	uint IDTarget;
public:
	GENERAR_GET_TIPO(Iman);
	Iman(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Iman(){};

	ushort tipoDisparo() const;
	uint obtenerMultiplicadorVelocidad() const;
	void actualizar(real deltaT);

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	GENERAR_DESDE_SNAPSHOT(Iman);

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return false;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEIMAN/2,
						obtenerPosicion().y-ALTOSPRITEIMAN/2,
						ANCHOSPRITEIMAN,
						ALTOSPRITEIMAN);}
};

class Bomba : public Disparo, public Animado
{
private:
	Animacion animacion;
	real tiempoTotal;
public:
	GENERAR_GET_TIPO(Bomba);
	Bomba(uint ID, Mundo &mundo, ushort categoriaTarget, const b2Vec2 &posicion = b2Vec2(-1000,-1000), const b2Vec2 &velocidad = b2Vec2_zero);
	~Bomba(){};

	ushort tipoDisparo() const;

	void actualizar(real deltaT);
	uint obtenerMultiplicadorVelocidad() const;

	bool lanzable();
	void alColisionar(Cuerpo *cuerpo){};
	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	
	GENERAR_DESDE_SNAPSHOT(Bomba);

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return false;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEBOMBA/2,
						obtenerPosicion().y-ALTOSPRITEBOMBA/2,
						ANCHOSPRITEBOMBA,
						ALTOSPRITEBOMBA);}
	
private:
	void explotar();
};


#endif
