#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"
#include "Actualizable.h"

class Construccion: public Cuerpo, public ImagenEscalada
{
private:
	Glib::RefPtr<Gdk::Pixbuf> textura;
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, bool fantasma = false);
	virtual ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar();
	const Rectangulo obtenerRepresentacion() const;

	/*Que archivo usan para dibujarse?.*/
	virtual std::string nombreImagen() = 0;
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
	std::string nombreImagen();
};


class CuboLadrillo : public Construccion
{
public:
	CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	std::string nombreImagen();
};


class CuboTierra : public Construccion
{
public:
	CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	std::string nombreImagen();
};


class CuboVacio : public Construccion
{
public:
	CuboVacio(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	std::string nombreImagen();
};


class Puerta : public Cuerpo, public Animado, public Actualizable
{
private:
	Animacion animacion;
	bool cerrada;
	uint IDInterno;
	real ancho, alto;
public:
	Puerta(uint ID, uint IDInterno, Mundo &mundo, real ancho, real alto, const b2Vec2 &posicion);
	std::string nombreImagen();
	void cerrar();
	bool estaCerrada();
	uint obtenerIDInterno();
	void actualizar(real deltaT);
	
	ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;

};
#endif
