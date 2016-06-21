#ifndef SPARKMAN
#define SPARKMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "Orientaciones.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#endif

class Megaman;

class Sparkman : public Enemigo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion_saltando;
	Animacion animacion_corriendo;
	#endif

	Megaman *megaman;
	uint IDTarget;
	char estadoSparkman;
	real reflejos;
	Chispa arma;
	Orientaciones orientacion;
public:
	Sparkman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Sparkman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);

	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Sparkman);
	static Sparkman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

#endif
