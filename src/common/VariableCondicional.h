#ifndef VARIABLECONDICIONAL
#define VARIABLECONDICIONAL

#include <pthread.h>
#include "Mutex.h"

class VariableCondicional
{
private:
	pthread_cond_t condicion;
	Mutex &mutexCondicion;
public:
	explicit VariableCondicional(Mutex &mut);
	~VariableCondicional();

	void esperarCondicion();
	void despertarHilo();
};

#endif

