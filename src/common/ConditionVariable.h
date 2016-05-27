#ifndef CONDITION_VARIABLE
#define CONDITION_VARIABLE
#include <pthread.h>
class ConditionVariable {
    private:
        pthread_mutex_t mutex;
        pthread_cond_t cond;

        ConditionVariable& operator=(const ConditionVariable&);
        ConditionVariable(const ConditionVariable&);
    public:
        ConditionVariable() {
            pthread_mutex_init(&mutex, 0);
            pthread_cond_init(&cond, 0);
        }

        void lock() {
            pthread_mutex_lock(&mutex);
        }

        void unlock() {
            pthread_mutex_unlock(&mutex);
        }

        /*
         * Duerme al hilo actual a la espera de recibir una señal.
         * De forma automatica libera el mutex; cuando se despierte el hilo
         * se captura nuevamente (lock).
         *
         * Este metodo debe llamarse solo si el mutex ya fue adquirido
         * (se debe llamar al metodo lock() antes).
         * */
        void wait() {
            pthread_cond_wait(&cond, &mutex);
        }

        /*
         * Envia una señal y despierta a un unico hilo que este durmiendo
         * en un wait.
         * 
         * Si no hay ningun hilo durmiendo, la señal se descarta.
         * */
        void signal() {
            pthread_cond_signal(&cond);
        }

        /*
         * Envia una señal y despierta a todos los hilos que esten durmiendo
         * en un wait. Cabe aclarar que esos hilos intentaran adquirir el
         * mutex (lock) pero solo uno de ellos lo lograra; el resto quedara
         * despierto y bloqueado en la toma del mutex.
         *
         * Si no hay ningun hilo durmiendo, la señal se descarta.
         * */
        void broadcast() {
            pthread_cond_broadcast(&cond);
        }

        ~ConditionVariable() {
            pthread_cond_destroy(&cond);
            pthread_mutex_destroy(&mutex);
        }
};

#endif
