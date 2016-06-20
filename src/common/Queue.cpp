/*
#include "Queue.h"
template<class T>
void Queue<T>::push(const T& val) {
	cond.lock();
	if (q.empty()) {
		cond.broadcast();
     }

	q.push(val);
	cond.unlock();
}

template<class T>
T Queue<T>::pop() {
	cond.lock();
	while (q.empty()) {
		cond.wait();
	}
	const T val = q.front();
	q.pop();

	cond.unlock();
	return val;
}
*/
