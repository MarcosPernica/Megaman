#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>
#include <iostream>

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"
#endif

#include "Actualizable.h"

class Construccion: public Cuerpo
#ifndef compiling_server
, public ImagenEscalada
#endif
{
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, bool fantasma = false);
	virtual ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};

	#ifndef compiling_server
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	virtual ArchivoImagen a_dibujar();
	const Rectangulo obtenerRepresentacion() const;

	/*Que archivo usan para dibujarse?.*/
	virtual std::string nombreImagen() = 0;
	#endif
};

class CuboMadera : public Construccion
{
public:
	CuboMadera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	std::string nombreImagen();
};

class CuboMetal : public Construccion
{
public:
	CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	#ifndef compiling_server
	std::string nombreImagen();
	#endif
};


class CuboLadrillo : public Construccion
{
public:
	CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	#ifndef compiling_server
	std::string nombreImagen();
	#endif
};


class CuboTierra : public Construccion
{
public:
	CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	#ifndef compiling_server
	std::string nombreImagen();
	#endif
};


class CuboVacio : public Construccion
{
public:
	CuboVacio(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	#ifndef compiling_server
	std::string nombreImagen();
	#endif
};


class Puerta : public Cuerpo
#ifndef compiling_server
, public Animado
#endif
, public Actualizable
{
private:
	#ifndef compiling_server
	Animacion animacion;
	#endif
	bool cerrada;
	uint IDInterno;
	real ancho, alto;
public:
	Puerta(uint ID, uint IDInterno, Mundo &mundo, real ancho, real alto, const b2Vec2 &posicion);
	#ifndef compiling_server
	std::string nombreImagen();
	#endif
	void cerrar();
	bool estaCerrada();
	uint obtenerIDInterno();
	void actualizar(real deltaT);
	
	ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif

};
#endif
