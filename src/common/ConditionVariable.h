#ifndef CONDITION_VARIABLE
#define CONDITION_VARIABLE
#include <pthread.h>
#include "Lockable.h"
class ConditionVariable : public Lockable{
    private:
        pthread_mutex_t mutex;
        pthread_cond_t cond;

        ConditionVariable& operator=(const ConditionVariable&);
        ConditionVariable(const ConditionVariable&);
        bool locked;
    public:
        ConditionVariable();

        void lock();

        void unlock();

        /*
         * Duerme al hilo actual a la espera de recibir una señal.
         * De forma automatica libera el mutex; cuando se despierte el hilo
         * se captura nuevamente (lock).
         *
         * Este metodo debe llamarse solo si el mutex ya fue adquirido
         * (se debe llamar al metodo lock() antes).
         * */
        void wait();

        /*
         * Envia una señal y despierta a un unico hilo que este durmiendo
         * en un wait.
         * 
         * Si no hay ningun hilo durmiendo, la señal se descarta.
         * */
        void signal();

        /*
         * Envia una señal y despierta a todos los hilos que esten durmiendo
         * en un wait. Cabe aclarar que esos hilos intentaran adquirir el
         * mutex (lock) pero solo uno de ellos lo lograra; el resto quedara
         * despierto y bloqueado en la toma del mutex.
         *
         * Si no hay ningun hilo durmiendo, la señal se descarta.
         * */
        void broadcast();

        ~ConditionVariable();
};

#endif
