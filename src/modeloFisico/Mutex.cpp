#include "Mutex.h"
#include <pthread.h>

Mutex::Mutex()
{
	pthread_mutex_init(&mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mutex);
}

void Mutex::bloquear()
{
	pthread_mutex_lock(&mutex);
}

void Mutex::desbloquear()
{
	pthread_mutex_unlock(&mutex);
}

