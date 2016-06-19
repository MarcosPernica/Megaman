#ifndef MUTEX
#define MUTEX

#include <pthread.h>
#include "Lockable.h"
class Mutex: public Lockable
{
private:
	pthread_mutex_t mutex;
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();

	friend class VariableCondicional;
    private:
        Mutex(const Mutex&);
        Mutex& operator=(const Mutex&);
};


#endif
