#ifndef DIBUJABLE
#define DIBUJABLE
#include <cairomm/context.h>
#include <Box2D/Box2D.h>
#include "../mundo/Definiciones.h"
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>

/*Mira aca abajo, esta como escalo el mundo a pixeles. Se lee como 38px/m y esta basado en el ratio original de megaman*/

#define FACTORAMPLIFICACIONVENTANA 2
#define FACTORCONVERSIONMPX (38.0*FACTORAMPLIFICACIONVENTANA)

class Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion) = 0;
	virtual ~Dibujable(){};

	static void dibujarRectangulo(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, uint factorAmplificacion, b2Vec2 posicion, real ancho, real alto);
	static void dibujarImagen(const Cairo::RefPtr<Cairo::Context>& cr, 
				  b2Vec2 origen,
				  uint factorAmplificacion, 
				  b2Vec2 posicion,
				  real ancho,
				  real alto,
				  Glib::RefPtr<Gdk::Pixbuf> imagen,
				  bool invertir = true);

	static b2Vec2 renderAMundo(b2Vec2 vector);	
	static b2Vec2 mundoARender(b2Vec2 vector);
	static real renderAMundo(real numero);	
	static real mundoARender(real numero);
};

#endif
