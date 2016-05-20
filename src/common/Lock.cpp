#include "Lock.h"
Lock::Lock(Mutex &m) : m(m) {
	m.bloquear();
}

Lock::~Lock() {
	m.desbloquear();
}
