#ifndef _CHANNEL_SOCKET_
#define _CHANNEL_SOCKET_
#include "Socket.h"
#include <string>
class Buffer;
/**
 * Un channel socket representa un canal de comunicación a través del cual
 * 2 procesos pueden intercambiar información a través de internet.
 * Provee métodos generales, para enviar bloques de bytes, así también como
 * métodos más específicos para enviar y recibir bloques de archivos, números
 * unsigned long, y char.
 * */
class ChannelSocket: public Socket{
	public:
	ChannelSocket();
	/**
	 * Configura éste socket a partir de un file descriptor ya abierto
	 */
	explicit ChannelSocket(int file_descriptor);
	
	/**
	 * método usado como interfaz que agrupa los llamados a las rutinas 
	 * para conectar el socket
	 * */
	void connectTo(const std::string url, const unsigned port);
	
	/**
	 * Recibe tantos bytes como para llenar el Buffer.
	 * into: apuntador al Buffer donde se guardarán los datos
	 * */
	void receiveFixed(Buffer& into) const;
	/**
	 * Envía toda la información de un Buffer a través de un socket conectado
	 * */
	void sendFixed(Buffer& into) const;
	/**
	 * Recibe bytes hasta obtener el caracter \n.
	 * No se admiten mensajes de más de MAX_TAM_MENSAJE caracteres.
	 * */
	std::string receiveUntilNl() const;
	
	private:
	/**
	 * Conecta el Socket a un addressinfo, para que pueda enviar y recibir 
	 * información.
	 */
	void connectAddr(AddressInfo* &info);
};

#define MAX_TAM_MENSAJE 500
#endif
