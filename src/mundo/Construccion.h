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
	virtual std::string nombreImagen() = 0;
};

class CuboMadera : public Construccion
{
public:
	CuboMadera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual std::string nombreImagen(){return "imagenes/cuboMadera/1.png";};
};

class CuboMetal : public Construccion
{
public:
	CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual std::string nombreImagen(){return "imagenes/cuboMetal/1.png";};
};


class CuboLadrillo : public Construccion
{
public:
	CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual std::string nombreImagen(){return "imagenes/cuboLadrillo/1.png";};
};


class CuboTierra : public Construccion
{
public:
	CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual std::string nombreImagen(){return "imagenes/cuboTierra/1.png";};
};


class CuboVacio : public Construccion
{
public:
	CuboVacio(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual std::string nombreImagen(){return "imagenes/vacio.png";};
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
	virtual std::string nombreImagen(){return "imagenes/cuboMetal/1.png";};
	void cerrar();
	bool estaCerrada();
	uint obtenerIDInterno();
	void actualizar(real deltaT);
	
	ushort tipoCuerpo() const {return CONSTRUCCIONES;};
	void eliminarse(Mundo& de){};

		virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return false;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ancho/2,
						obtenerPosicion().y-alto/2,
						ancho,
						alto);}

};
#endif
