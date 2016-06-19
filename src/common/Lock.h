#ifndef _LOCK_
#define _LOCK_
#include "Mutex.h"
#include "Lockable.h"
/**
 * bloquea y desbloquea un Mutex por RAII
 * */
class Lock {
    private:
        Lockable &m;

    public:
        explicit Lock(Lockable &m);
        ~Lock();
    private:
        Lock(const Lock&);
        Lock& operator=(const Lock&);
};
#endif
