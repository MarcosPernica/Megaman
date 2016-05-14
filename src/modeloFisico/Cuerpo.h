#ifndef CUERPO	
#define CUERPO

#include "Definiciones.h"
#include <Box2D/Box2D.h>
#include "Mundo.h"

#define MASAINFINITA -1

enum Orientaciones
{
	izquierda,
	derecha
};

struct Datos
{
	Cuerpo *cuerpo;
	const bool esDetectorSuelo;
};

class Cuerpo
{
private:
	b2Body *cuerpo;
	Orientaciones orientacion;
	Mundo &mundo;
	real ancho, alto;
	bool detectorSuelo;
	std::vector<Datos> datos;
public:
	Cuerpo(Mundo &mundo, 
		   real ancho,
		   real alto,
		   real masa,
	       ushort categoria,
		   ushort colisionaCon,
		   const b2Vec2 &posicion, 
		   bool rotable = false,
		   bool gravitacional = true, 
		   const b2Vec2 &velocidad = b2Vec2_zero ,
		   Orientaciones orientacion = derecha);

	virtual ~Cuerpo();

	Mundo &obtenerMundo();
	const b2Vec2& obtenerPosicion() const;
	const b2Vec2& obtenerVelocidad() const;
	Orientaciones obtenerOrientacion() const;


	b2Vec2 obtenerLeftTopCajaMagnificada(uint magnificador) const;
	b2Vec2 obtenerRightBottomCajaMagnificada(uint magnificador) const;

	void modificarVelocidad(const b2Vec2 &velocidad);
	void modificarOrientacion(Orientaciones orientacion);
	void aplicarImpulso(const b2Vec2 &impulso);
	void agregarDetectorSuelo();

	virtual char tipoCuerpo() const = 0;

	static const b2Vec2 versorIzquierda, versorDerecha;
	static const b2Vec2 &orientacionAVector(Orientaciones orientacion);
};
#endif