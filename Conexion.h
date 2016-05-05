#ifndef CONEXION
#define CONEXION

#include <stdio.h>
#include "Definiciones.h"
#include "Cadena.h"

#ifndef _WIN32
#include <sys/socket.h>
#else
#include <WinSock2.h>
#endif

/*Recibe una conexion ya creada y la gestiona liberandola al finalizar.*/
class Conexion
{
private:
	int descriptorSocket;
public:
	explicit Conexion(int descriptorSocket = 0);
	~Conexion();

	void asignarDescriptor(int descriptorSocket);

	int recibir(void * buffer,
		uint cantidadBytes) const;

	bool recibirHastaDelim(Cadena &buffer, char delim) const;

	int enviar(void * buffer,
		uint cantidadBytes) const;

	bool abierta() const;

	static Conexion *crearConexion(const Cadena &host, const Cadena &puerto);

	friend const Conexion &operator <<(const Conexion &conexion, Cadena &datos);
	friend const Conexion &operator >>(const Conexion &conexion, Cadena &datos);
};
#endif
