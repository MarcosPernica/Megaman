#ifndef EMISOR
#define EMISOR
#include "../sockets/ChannelSocket.h"
class Emisor{
	private:
	const ChannelSocket& socket;
	void enviarString(const std::string& st) const;
	void enviarNumero(int num) const;
	public:
	Emisor(const ChannelSocket& socket);
	/**
	 * Envía un mensaje con tipo y contenido de acuerdo al protocolo
	 * */
	void enviar(const std::string& tipo_mensaje, const std::string& mensaje) const;
	void enviar(const std::string& tipo_mensaje, int mensaje) const;
	/**
	 * Envía un mensjae que no tiene contenido, sólo tipo, de acuerdo al procolo
	 * */
	void enviar(const std::string& tipo_mensaje) const;
	
	void enviarNivel(char nivel) const;
	
	void enviarConfiguracion();
};

#endif
