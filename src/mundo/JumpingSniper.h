#ifndef JUMPINGSNIPER
#define JUMPINGSNIPER

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"

class Megaman;

class JumpingSniper : public Enemigo, public Animado
{
private:
	Animacion animacion_protegido;
	Animacion animacion_disparando;
	Animacion animacion_saltando;

	Megaman *megaman;
	uint IDTarget;
	char estadoSniper;
	real reflejos;
	char cantidadDisparos;
	Plasma arma;
public:
	JumpingSniper(uint ID,
		      Mundo &mundo,
		      const b2Vec2 &posicion,
		      const b2Vec2 &velocidad = b2Vec2_zero);
	~JumpingSniper(){};

	void atacado(int dano, Disparo *disparo);
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);

	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(JumpingSniper);
	static JumpingSniper* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;

	const Rectangulo obtenerRepresentacion() const;
};

#endif
