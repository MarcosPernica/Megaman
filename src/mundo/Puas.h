#ifndef PUAS
#define PUAS

#include "CajaAccion.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include "../graficos/ImagenEscalada.h"
#endif

class Puas : public CajaAccion
#ifndef compiling_server
, public ImagenEscalada
#endif
{
public:
	Puas(Mundo &mundo,
			real ancho,
			real alto,
			const b2Vec2 &posicion);
	~Puas(){};
	void interactuar(Megaman *megaman);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	ArchivoImagen a_dibujar();
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

#endif
