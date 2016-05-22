#include "Emisor.h"
#include "../sockets/Buffer.h"
Emisor::Emisor(const ChannelSocket& s):socket(s){}

void Emisor::enviar(const std::string& tipo_mensaje, const std::string& mensaje) const{
	Buffer id_buf = Buffer::createString(tipo_mensaje+" " + mensaje + "\n");
	socket.sendFixed(id_buf);
}
void Emisor::enviar(const std::string& tipo_mensaje) const{
	Buffer id_buf = Buffer::createString(tipo_mensaje+ "\n");
	socket.sendFixed(id_buf);
}
