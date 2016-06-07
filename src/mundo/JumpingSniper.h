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

	void actualizarMaquinaEstados(real deltaT);
	void actualizar(real deltaT);
	ushort tipoCuerpo() const {return ENEMIGOS;};


	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(JumpingSniper);
	static JumpingSniper* desdeSnapshot(const Snapshot& sn, Mundo& mundo);

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);}

	bool espejado() const{return obtenerOrientacion()==izquierda;};

	const Rectangulo obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOJUMPINGSNIPER/2,
						obtenerPosicion().y-ALTOJUMPINGSNIPER/2,
						ANCHOJUMPINGSNIPER,
						ALTOJUMPINGSNIPER);}
};

#endif
