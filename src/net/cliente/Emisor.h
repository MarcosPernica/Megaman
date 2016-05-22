#ifndef EMISOR
#define EMISOR
#include "../sockets/ChannelSocket.h"
class Emisor{
	const ChannelSocket& socket;
	public:
	Emisor(const ChannelSocket& socket);
	void enviar(const std::string& tipo_mensaje, const std::string& mensaje) const;
	void enviar(const std::string& tipo_mensaje) const;
};

#endif
