#ifndef MUTEX
#define MUTEX

#include <pthread.h>

class Mutex
{
private:
	pthread_mutex_t mutex;
public:
	Mutex();
	~Mutex();
	void bloquear();
	void desbloquear();

	friend class VariableCondicional;
};


#endif