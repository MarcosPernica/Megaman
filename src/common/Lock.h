#ifndef _LOCK_
#define _LOCK_
#include "Mutex.h"
/**
 * bloquea y desbloquea un Mutex por RAII
 * */
class Lock {
    private:
        Mutex &m;

    public:
        explicit Lock(Mutex &m);
        ~Lock();
    private:
        Lock(const Lock&);
        Lock& operator=(const Lock&);
};
#endif
