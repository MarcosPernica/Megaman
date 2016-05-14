#include "VariableCondicional.h"

VariableCondicional::VariableCondicional(Mutex & mutex) : mutexCondicion(mutex)
{
	pthread_cond_init(&condicion, NULL);
}

VariableCondicional::~VariableCondicional()
{
	mutexCondicion.desbloquear();
}

void VariableCondicional::esperarCondicion()
{
	pthread_cond_wait(&condicion, &mutexCondicion.mutex);
}

void VariableCondicional::despertarHilo()
{
	mutexCondicion.bloquear();
	pthread_cond_signal(&condicion);
	mutexCondicion.desbloquear();
}
