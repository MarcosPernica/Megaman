#ifndef DISPARO
#define DISPARO

#include "Cuerpo.h"
#include "Actualizable.h"
#include <Box2D/Box2D.h>
#include "../net/snapshots/Snapshot.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#endif

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

	/*Define que pasa al colisionar. Asi se tiene mejor control y mas versatilidad.*/
	virtual void alColisionar(Cuerpo *cuerpo);
	virtual ~Disparo(){};

	/*Un disparo puede lanzarse (Bomba o bumerang) o dispararse (Plasma)*/
	virtual bool lanzable();

	/*Modifica la velocidad base.*/
	virtual uint obtenerMultiplicadorVelocidad() const = 0;
	ushort tipoCuerpo() const;
	virtual ushort tipoDisparo() const = 0;

	/*Que entidades impacta?.*/
	ushort obtenerCategoriaTarget();
	void eliminarse(Mundo& de);

	/*Permite clonar el disparo.*/
	virtual Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad) = 0;
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	
	static Disparo* crearDesdeTipo(int tipo,uint ID, Mundo &mundo, ushort categoriaTarget);
};

class Plasma : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
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

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Chispa : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif	
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

	void actualizar(real deltaT);

	#ifndef compiling_server

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Anillo : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
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
	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_DESDE_SNAPSHOT(Anillo);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Fuego : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;	
	#endif
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

	void actualizar(real deltaT);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Iman : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
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

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

class Bomba : public Disparo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
	real tiempoTotal;
public:
	GENERAR_GET_TIPO(Bomba);
	Bomba(uint ID, 
	      Mundo &mundo, 
              ushort categoriaTarget, 
              const b2Vec2 &posicion = b2Vec2(-1000,-1000), 
              const b2Vec2 &velocidad = b2Vec2_zero);
	~Bomba(){};

	ushort tipoDisparo() const;

	void actualizar(real deltaT);
	uint obtenerMultiplicadorVelocidad() const;

	bool lanzable();
	void alColisionar(Cuerpo *cuerpo){};
	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	
	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	
	GENERAR_DESDE_SNAPSHOT(Bomba);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;

	const Rectangulo obtenerRepresentacion() const;
	#endif
	
private:
	void explotar();
};


#endif
