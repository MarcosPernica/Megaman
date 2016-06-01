#ifndef DISPARO
#define DISPARO

#include "Cuerpo.h"
#include "Actualizable.h"
#include <Box2D/Box2D.h>

class Entidad;

class Mundo;

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

	virtual bool danar(Entidad *entidad);
	virtual void actualizar(real deltaT);
	virtual void alColisionar(Cuerpo *cuerpo);
	~Disparo(){};

	/*Un disparo puede lanzarse (Bomba o bumerang) o dispararse (Plasma)*/
	virtual bool lanzable();
	virtual uint obtenerMultiplicadorVelocidad() const = 0;
	ushort tipoCuerpo() const;
	ushort obtenerCategoriaTarget();
	void eliminarse(Mundo& de);

	virtual Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad) = 0;
};

class Plasma : public Disparo
{
private:
	
public:
	Plasma(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Plasma(){};

	uint obtenerMultiplicadorVelocidad() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int  getTipo() const {return TIPO_DISPARO_PLASMA;};
	static Plasma* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
};

class Chispa : public Disparo
{
private:
	
public:
	Chispa(uint ID, 
		   Mundo &mundo, 
 		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Chispa(){};

	uint obtenerMultiplicadorVelocidad() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
};

class Anillo : public Disparo
{
private:
	real tiempo;
public:
	Anillo(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Anillo(){};

	uint obtenerMultiplicadorVelocidad() const;
	void actualizar(real deltaT);
	void alColisionar(Cuerpo *cuerpo);

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
};

class Fuego : public Disparo
{
private:
	
public:
	Fuego(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Fuego(){};

	uint obtenerMultiplicadorVelocidad() const;

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
};

class Iman : public Disparo
{
private:
	Entidad *target;
public:
	Iman(uint ID, 
		   Mundo &mundo, 
		   ushort categoriaTarget,
		   const b2Vec2 &posicion = b2Vec2(-1000,-1000),
		   const b2Vec2 &velocidad = b2Vec2_zero);
	~Iman(){};

	uint obtenerMultiplicadorVelocidad() const;
	void actualizar(real deltaT);

	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
};

class Bomba : public Disparo
{
private:
	real tiempoTotal;
public:
	Bomba(uint ID, Mundo &mundo, ushort categoriaTarget, const b2Vec2 &posicion = b2Vec2(-1000,-1000), const b2Vec2 &velocidad = b2Vec2_zero);
	~Bomba(){};
	bool danar(Entidad *entidad);
	void actualizar(real deltaT);
	uint obtenerMultiplicadorVelocidad() const;

	bool lanzable();
	void alColisionar(){};
	Disparo *nuevo(uint ID, const b2Vec2 &posicion, const b2Vec2 &velocidad);
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int  getTipo() const {return TIPO_DISPARO_BOMBA;};
	
	static Bomba* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
	
private:
	void explotar();
};


#endif
