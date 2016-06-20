#ifndef PUAS
#define PUAS

#include "CajaAccion.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"

class Puas : public CajaAccion, public ImagenEscalada
{
public:
	Puas(Mundo &mundo,
			real ancho,
			real alto,
			const b2Vec2 &posicion);
	~Puas(){};
	void interactuar(Megaman *megaman);

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	ArchivoImagen a_dibujar();
	const Rectangulo obtenerRepresentacion() const;
};

#endif
