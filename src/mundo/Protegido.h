#ifndef PROTEGIDO
#define PROTEGIDO

#include "Entidad.h"
#include "Definiciones.h"
#include <Box2D/Box2D.h>

class Protegido : public Entidad
{
private:
	uint escudo;
	bool cubierto;
public:
	Protegido(uint ID,
			  Mundo &mundo,
			  real ancho,
			  real alto,
			  uint energiaMaxima,
			  uint escudo,
			  real masa,
			  ushort categoria,
			  ushort colisionaCon,
			  const b2Vec2 &posicion,
			  bool rotable = false,
			  bool gravitacional = true,
			  const b2Vec2 &velocidad = b2Vec2_zero,
			  Orientaciones orientacion = izquierda);

	void atacado(uint danio);

	void cubrirse();
	void exponerse();
	bool estaCubierto();
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo(){return TIPO_PROTEGIDO;};
};

#endif
