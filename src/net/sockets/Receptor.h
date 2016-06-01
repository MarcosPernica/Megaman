#ifndef RECEPTOR
#define RECEPTOR
#include "../../common/Thread.h"
#include <string>
#include "ChannelSocket.h"
#include <map>
#include "../../common/Mutex.h"
class EventoReceptor{
	public:
	virtual void operator()(const std::string& mensaje){};
};

/**
 * Es un hilo que responde con eventos cuando recibe mensajes.
 * Advertencia 1: los mensajes se llaman en el hilo correspondiente a esta instancia
 * Advertencia 2: el hilo no termina hasta que no se cierre el socket correspondiente.
 * */
class Receptor: private Thread{
	private:
	bool recibiendo;
	Mutex m_recibir;
	
	bool recepcion_sana;
	Mutex m_recepcion_sana;
	
	const ChannelSocket& channel;
	
	protected:
	
	Receptor(const ChannelSocket& channel);
	virtual void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje) = 0;
	
	
	private:
	virtual void run();
	virtual void end();
	void decodificarMensaje(const std::string& mensaje);
	bool seguirRecibiendo();
	bool setRecepcionRota();
	public:
	~Receptor();
	bool getRecepcionSana();
};
#endif
