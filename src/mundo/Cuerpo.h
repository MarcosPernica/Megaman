#ifndef CUERPO
#define CUERPO 97

#include "Definiciones.h"

#include "../common/Rectangulo.h"
#include <Box2D/Box2D.h>
#define MASAINFINITA -1
#include "../graficos/Dibujable.h"
//#include "Mundo.h"
#include "../net/snapshots/Snapshotable.h"
#include "Orientaciones.h"
class Mundo;
class Cuerpo;

struct DatosColisionCuerpo
{
	Cuerpo *cuerpo;
	uint ID;
	Rectangulo caja;

	DatosColisionCuerpo(Cuerpo *cuerpo, uint ID, Rectangulo caja) : cuerpo(cuerpo), ID(ID), caja(caja){};
};

class Cuerpo: public virtual Dibujable, public Snapshotable {
private:
	b2Body *cuerpo;
	Orientaciones orientacion;
	Mundo &mundo;
	real ancho, alto;
	bool detectorSuelo;
	std::vector<DatosColisionCuerpo*> datos;
public:
	Cuerpo(uint ID,
		   Mundo &mundo, 
		   real ancho,
		   real alto,
		   real masa,
	       	   ushort categoria,
		   ushort colisionaCon,
		   const b2Vec2 &posicion, 
		   bool rotable = false,
		   bool gravitacional = true, 
		   const b2Vec2 &velocidad = b2Vec2_zero ,
		   Orientaciones orientacion = derecha,
		   bool fantasma = false);

	virtual ~Cuerpo();

	Mundo &obtenerMundo();
	const b2Vec2& obtenerPosicion() const;
	const b2Vec2& obtenerVelocidad() const;
	Orientaciones obtenerOrientacion() const;

	void finalizarCreacion();
	Rectangulo obtenerCajaMagnificada(uint magnificador) const;
	real obtenerAncho() const;
	real obtenerAlto() const;

	void modificarVelocidad(const b2Vec2 &velocidad);
	void modificarOrientacion(Orientaciones orientacion);
	void modificarPosicion(const b2Vec2 &posicion);
	void aplicarImpulso(const b2Vec2 &impulso);
	void modificarRestitucion(real coeficiente);
	void gravitar();
	void ingravitar();
	
	void materializar();

	
	void agregarCuerpoInmaterial(real ancho, real alto, b2Vec2 posicion, uint identificador, ushort categoria, ushort colisionaCon, bool fantasma = true);

	virtual ushort tipoCuerpo() const = 0;

	static const b2Vec2 versorIzquierda, versorDerecha;
	static const b2Vec2 &orientacionAVector(Orientaciones orientacion);
	
	/*Es responsabilidad de cada cuerpo saber que forma tiene.*/
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion);
	
	//Snapshotable
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_CUERPO;};
	virtual void eliminarse(Mundo& de) = 0;
};

#endif
