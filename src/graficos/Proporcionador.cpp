#include "Proporcionador.h"
b2Vec2 Proporcionador::renderAMundo(b2Vec2 vector)
{
	return (1/FACTORCONVERSIONMPX)*vector;
}	

b2Vec2 Proporcionador::mundoARender(b2Vec2 vector)
{
	return FACTORCONVERSIONMPX*vector;
}

real Proporcionador::renderAMundo(real numero)
{
	return numero/FACTORCONVERSIONMPX;
}

real Proporcionador::mundoARender(real numero)
{
	return numero*FACTORCONVERSIONMPX;
}
