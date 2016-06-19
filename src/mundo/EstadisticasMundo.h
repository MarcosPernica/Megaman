#ifndef ESTADISTICASMUNDO
#define ESTADISTICASMUNDO
#include "Disparo.h"
#include "Definiciones.h"
#include "../net/snapshots/Snapshotable.h"
class EstadisticasMundo: public Snapshotable{
	private:
	/**
	 * El orden en que se obtuvieron las armas
	 * */
	std::vector<int> armas_disponibles;
	/**
	 * Las vidas de cada Megaman, en orden de llegada
	 * */
	std::vector<uint> vidas;
	public:
	EstadisticasMundo(uint cantidad_jugadores);
	EstadisticasMundo(Snapshot& sn, uint cantidad_jugadores);
	void agregarArma(int tipo_disparo);
	const std::vector<int>& obtenerArmas();
	uint vidasDe(uint posicion_jugador);
	void setVidas(uint posicion_jugador, uint vidas);
	void perderUnaVida(uint posicion_jugador);
	
	GENERAR_GET_TIPO(EstadisticasMundo);
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	
	virtual void eliminarse(Mundo& de);
	
};
#endif
