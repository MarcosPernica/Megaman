#ifndef ACTUALIZABLE
#define ACTUALIZABLE

/*Interface que deben heredar todos los cuerpos que deban evolucionar en el tiempo*/

class Actualizable
{
public:
	virtual void actualizar(real deltaT) = 0;
	virtual ~Actualizable(){};
};

#endif
