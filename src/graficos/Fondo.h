#ifndef FONDO
#define FONDO

#include "../graficos/ImagenEscalada.h"

class Fondo: public ImagenEscalada
{
private:
	double ancho, alto;
	Glib::RefPtr<Gdk::Pixbuf> textura;
public:
	Fondo(double ancho, double alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar();
	const Rectangulo obtenerRepresentacion() const;
};
#endif
