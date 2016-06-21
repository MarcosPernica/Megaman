#ifndef MET
#define MET

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"

#ifndef compiling_server
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#endif

class Megaman;

class Met : public Enemigo
#ifndef compiling_server
, public Animado
#endif
{
private:
	#ifndef compiling_server
	Animacion animacion_protegido;
	Animacion animacion_disparando;
	#endif

	Megaman *megaman;
	uint IDTarget;
	real tiempo;//snapshoteado
	char estadoMet;//snapshoteado
	Plasma arma;//no lo puedo snapshotear
public:
	Met(uint ID,
	    Mundo &mundo,
	    const b2Vec2 &posicion,
	    const b2Vec2 &velocidad = b2Vec2_zero);
	~Met(){};

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	void atacado(int dano, Disparo *disparo);


	void agregarPropiedadesASnapshot(Snapshot& snapshot);
	void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Met);
	static Met* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	#ifndef compiling_server
	void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);	
	bool espejado() const;
	const Rectangulo obtenerRepresentacion() const;
	#endif
};

#endif
