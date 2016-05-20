#ifndef RECEPTOR
#define RECEPTOR
#include "../common/Thread.h"
#include <string>
#include "ChannelSocket.h"
#include <map>
#include "../common/Mutex.h"
class EventoReceptor{
	public:
	virtual void operator()(const std::string& mensaje){};
};

/**
 * Es un hilo que responde con eventos cuando recibe mensajes.
 * Utilizando EventoSocket, se hace la correspondencia entre el tipo de mensaje
 * entrante y la función a ser llamada.
 * Advertencia: los mensajes se llaman en el hilo correspondiente a esta instancia
 * */
class Receptor: private Thread{
	private:
	bool recibiendo;
	Mutex m_recibir;
	
	const ChannelSocket& channel;
	
	protected:
	
	Receptor(const ChannelSocket& channel);
	virtual void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje) = 0;
	
	
	private:
	virtual void run();
	virtual void end();
	void decodificarMensaje(const std::string& mensaje);
	bool seguirRecibiendo();
	public:
	~Receptor();
};
#endif
