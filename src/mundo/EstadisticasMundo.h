#ifndef ESTADISTICASMUNDO
#define ESTADISTICASMUNDO
#include "Disparo.h"
#include "Definiciones.h"
#include "../net/snapshots/Snapshotable.h"
class EstadisticasMundo{
	private:
	/**
	 * El orden en que se obtuvieron las armas
	 * */
	std::vector<Disparo*> armas_disponibles;
	/**
	 * Las vidas de cada Megaman, en orden de llegada
	 * */
	std::vector<uint> vidas;
	public:
	EstadisticasMundo(uint cantidad_jugadores);
	EstadisticasMundo(Snapshot& sn, uint cantidad_jugadores);
	void agregarArma(Disparo* disparo);
	const std::vector<Disparo*>& obtenerArmas();
	
};
#endif
