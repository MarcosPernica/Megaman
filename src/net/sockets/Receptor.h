#ifndef RECEPTOR
#define RECEPTOR
#include "../../common/Thread.h"
#include <string>
#include "ChannelSocket.h"
#include <map>
#include "../../common/Mutex.h"
#include "CallbackReceptor.h"
#include "RecepcionRotaCallback.h"
/**
 * Es un hilo que responde con eventos cuando recibe mensajes.
 * Advertencia 1: los mensajes se llaman en el hilo correspondiente a esta instancia
 * Advertencia 2: el hilo no termina hasta que no se cierre el socket correspondiente.
 * */
class Receptor: public Thread{
	private:
	bool recibiendo;
	Mutex m_recibir;
	std::map<std::string,CallbackReceptor*> callbacks;
	Mutex m_callbacks;
	RecepcionRotaCallback* call_rota;
	
	bool recepcion_sana;
	Mutex m_recepcion_sana;
	
	const ChannelSocket& channel;
	void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
	protected:
	
	Receptor(const ChannelSocket& channel, RecepcionRotaCallback* call_rota = NULL);
	
	
	
	private:
	virtual void run();
	virtual void end();
	void decodificarMensaje(const std::string& mensaje);
	bool seguirRecibiendo();
	bool setRecepcionRota();
	
	/**
	 * Recibe los 3 caracteres que son el tipo de mensaje
	 * */
	void recibirTipoMensaje(std::string& poner_en);
	
	/**
	 * Recibe un número
	 * */
	int recibirLargo();
	
	/**
	 * recibe un string de tamaño variable
	 * */
	void recibirString(std::string& poner_en, int tamanio);
	
	public:
	~Receptor();
	bool getRecepcionSana();
	/**
	 * el Receptor borrará los callbacks al borrarse
	 * */
	void agregarCallback(const std::string& tipo_mensaje,CallbackReceptor* callback);
};
#endif
