#ifndef PUAS
#define PUAS

#include "CajaAccion.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"

class Puas : public CajaAccion, public ImagenEscalada
{
private:
	Glib::RefPtr<Gdk::Pixbuf> textura;
public:
	Puas(Mundo &mundo,
			real ancho,
			real alto,
			const b2Vec2 &posicion);
	~Puas(){};
	void interactuar(Megaman *megaman);

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	Glib::RefPtr<Gdk::Pixbuf> a_dibujar();
	const Rectangulo obtenerRepresentacion() const;
};

#endif
