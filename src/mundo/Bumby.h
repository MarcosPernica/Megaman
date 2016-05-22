#ifndef BUMBY
#define BUMBY

#include "Entidad.h"
#include "Definiciones.h"
#include <Box2D/Box2D.h>
#include <string>
class Bumby : public Entidad
{
private:
	
public:
	Bumby(uint ID,
		  Mundo &mundo,
		  const b2Vec2 &posicion,
		  const b2Vec2 &velocidad = b2Vec2_zero);

	void actualizar(real deltaT);
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_BUMBY;};
	
	static Bumby* desdeSnapshot(const Snapshot& sn, Mundo& mundo);
	
	virtual ushort tipoCuerpo() const{return ENEMIGOS;};
};

#endif
