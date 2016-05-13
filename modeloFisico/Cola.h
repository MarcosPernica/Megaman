#ifndef COLA	
#define COLA

#include <list>
#include "Mutex.h"

template<class T> class Cola : public std::list<T>
{
private:
	Mutex mutexCola;
public:
	T pop()
	{
		mutexCola.bloquear();
		return this->pop_back();
		mutexCola.desbloquear();
	}
	push(typename T elemento)
	{
		mutexCola.bloquear();
		this->push_front(elemento);
		mutexCola.desbloquear();
	}
};

#endif