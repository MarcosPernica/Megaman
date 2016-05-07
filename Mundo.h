#ifndef MUNDO	
#define MUNDO

#include <list>
#include "CajaColision.h"

class Disparo;
class PowerUp;
class Entidad;

class Mundo
{
private:
public:
	void eliminar(Disparo *disparo);
	void eliminar(PowerUp *powerUp);

	void agregar(Disparo *disparo);

	std::list<Entidad *> obtenerlistaColisiones(CajaColision &radio);
};

#endif