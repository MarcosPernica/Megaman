#ifndef CONSTRUCCION
#define CONSTRUCCION

#include "Cuerpo.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"

class Construccion: public Cuerpo
{	
public:
	Construccion(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto, bool fantasma = false);
	virtual ushort tipoCuerpo() const;
	void eliminarse(Mundo& de){};
};

class CuboMadera : public Construccion, public Animado
{
private:
	Animacion textura;
public:
	CuboMadera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==derecha;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-obtenerAncho()/2,
						obtenerPosicion().y-obtenerAlto()/2,
						obtenerAncho(),
						obtenerAlto());}
};

class CuboMetal : public Construccion, public Animado
{
private:
	Animacion textura;
public:
	CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==derecha;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-obtenerAncho()/2,
						obtenerPosicion().y-obtenerAlto()/2,
						obtenerAncho(),
						obtenerAlto());}
};


class CuboLadrillo : public Construccion, public Animado
{
private:
	Animacion textura;
public:
	CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==derecha;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-obtenerAncho()/2,
						obtenerPosicion().y-obtenerAlto()/2,
						obtenerAncho(),
						obtenerAlto());}
};


class CuboTierra : public Construccion, public Animado
{
private:
	Animacion textura;
public:
	CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==derecha;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-obtenerAncho()/2,
						obtenerPosicion().y-obtenerAlto()/2,
						obtenerAncho(),
						obtenerAlto());}
};


class Puerta : public Cuerpo, public Animado
{
private:
	Animacion textura;
	bool cerrada;
	uint IDInterno;
public:
	Puerta(uint ID, uint IDInterno, Mundo &mundo, real ancho, real alto, const b2Vec2 &posicion);
	void cerrar();
	bool estaCerrada();
	uint obtenerIDInterno();
	
	ushort tipoCuerpo() const {return CONSTRUCCIONES;};
	void eliminarse(Mundo& de){};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==derecha;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-obtenerAncho()/2,
						obtenerPosicion().y-obtenerAlto()/2,
						obtenerAncho(),
						obtenerAlto());}
};


#endif
