#ifndef RECEPTOR_CLIENTE
#define RECEPTOR_CLIENTE

#include "../sockets/Receptor.h"
#include <string>
#include "Cliente.h"
#include <iostream>
#include "../snapshots/FullSnapshot.h"
#include "../../mundo/Mundo.h"
#include "../../common/Lock.h"
#include <ctime>
class ReceptorCliente: public Receptor{
	private:
	clock_t horario_ultimo_inyectado;
	clock_t horario_ultima_inyeccion;
	bool inyectado;
	Cliente& cliente;
	/**
	 * Recibidas contiene la lista de snapshots recibida hasta ahora
	 * */
	std::vector<SnapshotSerializada> recibidas;
	/**
	 * a_punto_de_inyectar es el fullsnapshot finalizado.
	 * Está protegido porque gtkmm accede a ella a través del callback
	 * */
	Mutex m_a_punto;
	FullSnapshot a_punto_de_inyectar;
	Mundo* a_inyectar;
	public: 
	ReceptorCliente(const ChannelSocket& channel, Cliente& cliente);
	void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	/**
	 * Define al Mundo al que deben inyectársele las FullSnapshot.
	 * Si el argumento es NULL, no se le inyectarán FullSnapshots a ningún Mundo.
	 * */ 
	 void inyectarFullSnapshotsA(Mundo* a);
	 /**
	  * callback de idle, inyectar el snapshot
	  * */
	 bool onInyectar();
};
#endif
