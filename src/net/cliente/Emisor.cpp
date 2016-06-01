#include "Emisor.h"
#include "../sockets/Buffer.h"
#include <iostream>
#include "Debug.h"
Emisor::Emisor(const ChannelSocket& s):socket(s){}

void Emisor::enviar(const std::string& tipo_mensaje, const std::string& mensaje) const{
	#ifndef DEBUG
	Buffer id_buf = Buffer::createString(tipo_mensaje+" " + mensaje + "\n");
	socket.sendFixed(id_buf);
	#endif
}
void Emisor::enviar(const std::string& tipo_mensaje) const{
	#ifndef DEBUG
	Buffer id_buf = Buffer::createString(tipo_mensaje+ "\n");
	socket.sendFixed(id_buf);
	#endif
}
