#ifndef _COMMON_SOCKET_H_
#define _COMMON_SOCKET_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

typedef struct addrinfo AddressInfo;
typedef struct sockaddr Address;
class ChannelSocket;
/**
 * Socket representa un ente multipropósito utilizado para llevar adelante
 * conexiones entre procesos a través de internet o locales.
 * */
class Socket{
	private:
	int file_descriptor;
	
	public:
	/**
	 * Abre el socket, dejándolo listo para conectarse a un Location
	 */
	Socket();
	/**
	 * En vez de abrir otro socket, asocia un nuevo Socket a 
	 * un socket ya abierto. Para uso desde accept()
	 * */
	explicit Socket(int fd);
	/**
	 * Cierra el socket
	 * */
	virtual ~Socket();
	/**
	 * Inicializa el AddressInfo
	 * asociado a un hostname y a un port.
	 * si hostname es NULL, se connecta a localhost
	 * */
	void getAddrinfo(AddressInfo* &set, const char* hostname, const unsigned port);
	
	protected:
	/**
	* Acepta una conexión entrante. De no haber ninguna, se lanza una
	* excepción.
	* */
	ChannelSocket* acceptCon() const;
	/**
	 * Hace que el socket sea no bloqueante
	 * */
	void setNonBlocking();
	
	/**
	 * Bind
	 * */
	void bindS(const AddressInfo* info);
	/**
	 * Listen
	 * */
	void listenS(const int queue);
	
	/**
	 * connect, devuelve el resultado, es un bind directo
	 * */
	int connectS(Address* address, socklen_t length);
	
	/**
	 * recv, devuelve el resultado, es un bnd directo
	 * */
	int recvS(char* into, unsigned size) const;
	
	/**
	 * send, es un bind directo, devuelve el resultado
	 * */
	int sendS(char* from, unsigned size) const;
};
#endif
