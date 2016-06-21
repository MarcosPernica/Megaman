#ifndef FIREMAN
#define FIREMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#endif

class Megaman;

class Fireman : public Enemigo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion_saltando;
	Animacion animacion_corriendo;
	#endif

	char estadoFireman;
	real reflejos;
	Fuego arma;
public:
	Fireman(uint ID,
		Mundo &mundo,
		const b2Vec2 &posicion,
		const b2Vec2 &velocidad = b2Vec2_zero);
	~Fireman(){};

	void alMorir();
	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);


	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Fireman);
	static Fireman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

#endif
