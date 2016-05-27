#ifndef DISTRIBUIDOR_SNAPSHOTS
#define DISTRIBUIDOR_SNAPSHOTS
#include <set>
#include "ProxyJugador.h"
#include "../snapshots/FullSnapshot.h"
class ContenedorProxies{
	private:
	std::set<ProxyJugador*>& proxies;
	public:
	ContenedorProxies(std::set<ProxyJugador*>& proxies);
	void distribuir(const FullSnapshot& full_snapshot);
	void ejecutarControlesSobreMegaman();
};
#endif
