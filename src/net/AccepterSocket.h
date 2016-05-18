#ifndef _ACCEPTER_SOCKET_
#define _ACCEPTER_SOCKET_
#include "Socket.h"
#include "ChannelSocket.h"
/**
 * Representa un socket que espera y acepta conexiones.
 * Las conexiones entrantes se obtienen como ChannelSocket a través de 
 * la función accept.
 * 
 * Nótese que el socket es no-bloqueante, acceptConnection() lanzará una 
 * CException de no haber alguna conexión en la cola.
 * */
class AccepterSocket: public Socket{
	public:
	/**
	* abre el socket para que reciba conexiones
	* */
	void open(const unsigned port, const unsigned queue);
	
	ChannelSocket* acceptConnection() const;
	AccepterSocket();
};
#endif
