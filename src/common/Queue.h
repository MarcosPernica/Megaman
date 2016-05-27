#ifndef QUEUE
#define QUEUE
#include "ConditionVariable.h"
/*
 * Implementacion de una cola protegida (thread safe).
 * No solo los metodos push y pop usan un mutex para evitar
 * race conditions sino que ademas hacen uso de una condition variable
 * para permitir que el metodo pop se bloquee cuando la cola este vacia
 * y se despierte cuando haya algo que sacar (cola no vacia).
 *
 * Se deja al lector las siguientes posibles mejoras:
 *  - implementar una version RAII del objeto ConditionVariable para ser
 *    usado en los metodos push y pop que automaticamente liberen el mutex.
 *  - implementar una especializacion total Queue<void*> y luego
 *    una especializacion parcial Queue<T*> con el fin de evitar el code
 *    bloat por parte del compilador.
 **/
template<class T>
class Queue {
    private:
        std::queue<T> q;

        const Queue& operator=(const Queue&);
        Queue(const Queue&);

        ConditionVariable cond;
    public:
        Queue() { }

        void push(const T& val) {
            cond.lock();
            if (q.empty()) {
                /* 
                 * La cola esta vacia por lo que este push hara que la cola
                 * tenga un elemento y por lo tanto deje de estar vacia.
                 *
                 * Como puede haber hilos esperando a que la cola no este
                 * vacia, despertamos a todos ellos enviandoles una señal
                 * con el metodo broadcast().
                 *
                 * Como este hilo aun tiene adquirido el mutex (lock), los
                 * otros hilos que se despierten no ejecutaran nada hasta 
                 * que liberemos el mutex lo que nos garantiza que no
                 * habra race conditions.
                 * */
                cond.broadcast();
            }

            q.push(val);
            cond.unlock();
        }

        T pop() {
            cond.lock();
            while (q.empty()) {
                /* Si la cola esta vacia, no podemos hacer un pop.
                 * En vez de retornar con un codigo de error esperamos
                 * a que la cola deje de estar vacia con el metodo wait().
                 * 
                 * Literalmente este hilo deja de ejecutarse a la espera de
                 * recibir una señal.
                 * Señal que deberia llegarnos cuando la cola no este vacia
                 * (alguien hizo un push). Sin embargo como pueden haber 
                 * otros hilos tambien haciendo pop, es posible que para
                 * que este hilo en particular se despierte la cola vuelva
                 * a estar vacia: por eso tenemos un loop y mientras este
                 * vacia seguiremos haciendo waits.
                 *
                 * Por supuesto, el metodo wait() automaticamente libera
                 * el mutex asociado. Cuando este hilo se despierte y se
                 * retorne de wait(), el mutex es automaticamente obtenido
                 * (lock) de forma transparente al desarrollador.
                 * */
                cond.wait();
            }

            const T val = q.front();
            q.pop();

            cond.unlock();
            return val;
        }
};
#endif
