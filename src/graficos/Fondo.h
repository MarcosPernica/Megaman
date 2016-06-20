#ifndef FONDO
#define FONDO

#include "../graficos/ImagenEscalada.h"

class Fondo: public ImagenEscalada
{
private:
	double ancho, alto;
public:
	Fondo(double ancho, double alto);
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	virtual ArchivoImagen a_dibujar();
	const Rectangulo obtenerRepresentacion() const;
};
#endif
