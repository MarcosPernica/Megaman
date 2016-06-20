#ifndef PROPORCIONADOR
#define PROPORCIONADOR
/*Mira aca abajo, esta como escalo el mundo a pixeles. Se lee como 38px/m y esta basado en el ratio original de megaman*/
#include <Box2D/Box2D.h>
#include "../mundo/Definiciones.h"
#define FACTORCONVERSIONMPX (38.0*FACTORAMPLIFICACIONVENTANA)
#define FACTORAMPLIFICACIONVENTANA 1
class Proporcionador{
	public:
	static b2Vec2 renderAMundo(b2Vec2 vector);	
	static b2Vec2 mundoARender(b2Vec2 vector);
	static real renderAMundo(real numero);	
	static real mundoARender(real numero);
	private:
	Proporcionador();
};

#endif
