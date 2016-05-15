#ifndef CUERPO	
#define CUERPO

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

class Datos;

class Cuerpo: public ImagenRectangulo
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
	
	private:
	//Dibujable (de esta forma nos aseguramos que todos los cuerpos estén en pantalla)
	virtual const Rectangulo obtenerRepresentacion() const;
};

/**
 * Marcos leelo y borralo: la hice clase porque C++ se puso jodón con
 * el operador = y el const de esDetectorSuelo y la copia y no sé qué, 
 * parece que algún std::vector usa el = adentro (capaz los de Entidades?)
 * */
class Datos
{
	private:
	bool esDetectorSuelo;
	
	public:
	Cuerpo *cuerpo;
	bool getEsDetectorSuelo(){
		return esDetectorSuelo;
	}
	Datos(Cuerpo* duenio,bool esDetSuelo){
		this->cuerpo=duenio;
		this->esDetectorSuelo=esDetSuelo;
	}
};
#endif
