#ifndef CUERPO
#define CUERPO 97

#include "Definiciones.h"
#include <Box2D/Box2D.h>
class Mundo;

#define MASAINFINITA -1
#include "../graficos/ImagenRectangulo.h"

enum Orientaciones
{
	izquierda,
	derecha
};

class Cuerpo;

struct DatosColisionCuerpo
{
	Cuerpo *cuerpo;
	uint ID;
	Rectangulo caja;

	DatosColisionCuerpo(Cuerpo *cuerpo, uint ID, Rectangulo caja) : cuerpo(cuerpo), ID(ID), caja(caja){};
};

class Cuerpo: public ImagenRectangulo
{
private:
	b2Body *cuerpo;
	Orientaciones orientacion;
	Mundo &mundo;
	real ancho, alto;
	bool detectorSuelo;
	std::vector<DatosColisionCuerpo*> datos;
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


	Rectangulo obtenerCajaMagnificada(uint magnificador) const;

	void modificarVelocidad(const b2Vec2 &velocidad);
	void modificarOrientacion(Orientaciones orientacion);
	void aplicarImpulso(const b2Vec2 &impulso);

	
	void agregarCuerpoInmaterial(real ancho, real alto, b2Vec2 posicion, uint identificador, ushort categoria, ushort colisionaCon);

	virtual char tipoCuerpo() const = 0;

	static const b2Vec2 versorIzquierda, versorDerecha;
	static const b2Vec2 &orientacionAVector(Orientaciones orientacion);
	
	private:
	//Dibujable (de esta forma nos aseguramos que todos los cuerpos estén en pantalla)
	virtual const std::list<Rectangulo> obtenerRepresentacion() const;
};

#endif
