#ifndef DISTRIBUIDOR_SNAPSHOTS
#define DISTRIBUIDOR_SNAPSHOTS
#include <set>
#include "ProxyJugador.h"
#include "../snapshots/FullSnapshot.h"
class DistribuidorSnapshots{
	private:
	std::set<ProxyJugador*>& proxies;
	public:
	DistribuidorSnapshots(std::set<ProxyJugador*>& proxies);
	void distribuir(const FullSnapshot& full_snapshot);
};
#endif
