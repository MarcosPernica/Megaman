#ifndef FIREMAN
#define FIREMAN

#include "Enemigo.h"
#include <Box2D/Box2D.h>
#include "Disparo.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"

class Megaman;

class Fireman : public Enemigo, public Animado
{
private:
	Animacion animacion_saltando;
	Animacion animacion_corriendo;

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
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Fireman);
	static Fireman* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==izquierda;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOFIREMAN/2,
						obtenerPosicion().y-ALTOFIREMAN/2,
						ANCHOFIREMAN,
						ALTOFIREMAN);}
};

#endif
