#ifndef MAGNETMAN
#define MAGNETMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "Orientaciones.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"


class Megaman;

class Magnetman : public Enemigo, public Animado
{
private:
	Animacion animacion_saltando;
	Animacion animacion_corriendo;

	char estadoMagnetman;
	real reflejos;
	Iman arma;
	Orientaciones orientacion;
	uint disparos;
public:
	Magnetman(uint ID,
		  Mundo &mundo,
		  const b2Vec2 &posicion,
		  const b2Vec2 &velocidad = b2Vec2_zero);
	~Magnetman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Magnetman);
	static Magnetman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
};

#endif
