#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "Conexion.h"
#include <memory.h>
#include "Definiciones.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#else

#include <WinSock2.h>
#include <Ws2tcpip.h>

#endif

Conexion::Conexion(int descriptorSocket)
{
	this->descriptorSocket = descriptorSocket;
}

Conexion::~Conexion()
{
#ifndef _WIN32
	close(descriptorSocket);
#else
	closesocket(descriptorSocket);
#endif
	descriptorSocket = 0;
}

void Conexion::asignarDescriptor(int descriptorSocket)
{
#ifndef _WIN32
	close(descriptorSocket);
#else
	closesocket(descriptorSocket);
#endif
	this->descriptorSocket = descriptorSocket;
}

int Conexion::recibir(void * buffer, uint cantidadBytes) const
{
	if (!descriptorSocket)
		throw NoHayConexion();

	unsigned int bytesRecibidos = 0, bytesTotales = 0;

	do
	{
		bytesRecibidos = recv(descriptorSocket,
			(char *)buffer + bytesTotales,
			cantidadBytes - bytesTotales,
			MSG_NOSIGNAL);

		/*No tiene sentido seguir.*/
		if (bytesRecibidos <= 0)
			throw ErrorEnLaConexion();

		bytesTotales += bytesRecibidos;
	} while (bytesTotales != cantidadBytes);
	return OK;
}

bool Conexion::recibirHastaDelim(Cadena &buffer,
							   char delim) const
{
	if (!descriptorSocket)
		throw NoHayConexion();

	bool finBuffer = true;
	unsigned int bytesRecibidos = 0, bytesTotales = 0;
	char bufferAux[MAXIMALONGITUDBUFFER+1];

	do
	{
		bytesRecibidos = recv(descriptorSocket,
			bufferAux + bytesTotales,
			MAXIMALONGITUDBUFFER - bytesTotales +1,
			MSG_NOSIGNAL);

		bytesTotales += bytesRecibidos;
	} while (bytesRecibidos != 0);

	if(bufferAux[bytesTotales-1] != delim)
	{
		if(bytesTotales != MAXIMALONGITUDBUFFER)
			throw ErrorEnLaConexion();
		else
			finBuffer = false;
	}

	bufferAux[bytesTotales] = '\0';
	buffer += bufferAux;
	return finBuffer;
}

int Conexion::enviar(void * buffer, uint cantidadBytes) const
{
	if (!descriptorSocket)
		throw NoHayConexion();

	unsigned int bytesEnviados = 0, bytesTotales = 0;

	do
	{
		bytesEnviados = send(descriptorSocket,
			(char *)buffer + bytesTotales,
			cantidadBytes - bytesEnviados,
			MSG_NOSIGNAL);

		/*No tiene sentido seguir.*/
		if (bytesEnviados <= 0)
			throw ErrorEnLaConexion();

		bytesTotales += bytesEnviados;
	} while (bytesTotales != cantidadBytes);


	return OK;
}

bool Conexion::abierta() const
{
	return descriptorSocket == 0;
}

Conexion *Conexion::crearConexion(const Cadena &host, const Cadena &puerto)
{
	struct addrinfo consulta, *resultados = NULL, *res = NULL;
	int descriptorSocket;

	if ((descriptorSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return NULL;

	memset(&consulta, 0, sizeof(consulta));
	consulta.ai_family = AF_INET;
	consulta.ai_socktype = SOCK_STREAM;

	getaddrinfo(host.c_str(), puerto.c_str(), &consulta, &resultados);


	for (res = resultados; res != NULL; res = res->ai_next)
	{
		if (connect(descriptorSocket,
			res->ai_addr,
			res->ai_addrlen) < 0)
			continue;
		else
			break;
	}

	if (!res)
#ifndef _WIN32
		close(descriptorSocket);
#else
		closesocket(descriptorSocket);
#endif

	freeaddrinfo(resultados);

	if (!res)
		return NULL;
	return new Conexion(descriptorSocket);
}
