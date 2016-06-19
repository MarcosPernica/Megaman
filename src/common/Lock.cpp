#include "Lock.h"
Lock::Lock(Lockable &m) : m(m) {
	m.lock();
}

Lock::~Lock() {
	m.unlock();
}
