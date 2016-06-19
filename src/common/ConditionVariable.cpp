#include "ConditionVariable.h"
#include "exceptions.h"
ConditionVariable::ConditionVariable():locked(false) {
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&cond, 0);
}

void ConditionVariable::lock() {
	locked = true;
	pthread_mutex_lock(&mutex);
}
void ConditionVariable::unlock() {
	locked = false;
	pthread_mutex_unlock(&mutex);
}
void ConditionVariable::wait() {
	if(!locked)throw CException("El mutex no esta bloqueado por lo tanto la conditionvariable no se puede esperar");
	pthread_cond_wait(&cond, &mutex);
}
void ConditionVariable::signal() {
	pthread_cond_signal(&cond);
}
void ConditionVariable::broadcast() {
	pthread_cond_broadcast(&cond);
}
ConditionVariable::~ConditionVariable() {
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}
