#ifndef DIBUJABLE
#define DIBUJABLE
#include <cairomm/context.h>
#include <Box2D/Box2D.h>
#include "../mundo/Definiciones.h"
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include "Proporcionador.h"
#include "ArchivoImagen.h"
#include "CacheImagenes.h"
class Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion) = 0;
	virtual ~Dibujable(){};

	static void dibujarRectangulo(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, uint factorAmplificacion, b2Vec2 posicion, real ancho, real alto);
	static void dibujarRectanguloLleno(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, uint factorAmplificacion, b2Vec2 posicion, real ancho, real alto, uint color=0);
	
	static void dibujarImagen(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto,
				  Glib::RefPtr<Gdk::Pixbuf> imagen,
				  bool invertir = true);
	static void dibujarImagen(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto,
				  ArchivoImagen imagen,
				  bool invertir = true);

	static b2Vec2 renderAMundo(b2Vec2 vector);	
	static b2Vec2 mundoARender(b2Vec2 vector);
	static real renderAMundo(real numero);	
	static real mundoARender(real numero);
	static void dibujarCirculoLleno(const Cairo::RefPtr<Cairo::Context>& cr, 
									b2Vec2 origen, 
									uint factorAmplificacion, 
									b2Vec2 posicion, 
									real radio, 
									uint color);
};

#endif
