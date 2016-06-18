#ifndef BUMBY
#define BUMBY

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"

class Megaman;

class Bumby : public Enemigo, public Animado
{
private:
	Animacion animacion_volando;

	Megaman *megaman;
	uint IDTarget;
	real tiempo, reflejos;//snapshotados
	bool quieto;//snapshotado
	Plasma arma;
public:
	Bumby(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);

	~Bumby(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);

	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Bumby);
	static Bumby* desdeSnapshot(const Snapshot& sn, Mundo& mundo);


	/*Como se dibuja.*/
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr,
		       b2Vec2 origen, 
		       real factorAmplificacion);

	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
};

#endif
