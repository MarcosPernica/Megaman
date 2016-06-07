#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>

class Construccion: public Cuerpo
{	
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, bool fantasma = false);
	virtual ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};
};

class CuboMadera : public Construccion
{
public:
	CuboMadera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
};

class CuboMetal : public Construccion
{
public:
	CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
};

class CuboLadrillo : public Construccion
{
public:
	CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
};

class CuboTierra : public Construccion
{
public:
	CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
};

class Puerta : public Cuerpo
{
private:
	bool cerrada;
	uint IDInterno;
public:
	Puerta(uint ID, uint IDInterno, Mundo &mundo, real ancho, real alto, const b2Vec2 &posicion);
	void cerrar();
	bool estaCerrada();
	uint obtenerIDInterno();
	
	ushort tipoCuerpo() const {return CONSTRUCCIONES;};
	void eliminarse(Mundo& de){};
};

#endif
