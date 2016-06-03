#include "Emisor.h"
#include "../sockets/Buffer.h"
#include <iostream>
#include <sstream>
#include "../defines_protocolo.h"
Emisor::Emisor(const ChannelSocket& s):socket(s){}
/*
void Emisor::enviar(const std::string& tipo_mensaje, const std::string& mensaje) const{
	#ifndef DEBUG
	Buffer id_buf = Buffer::createString(tipo_mensaje+" " + mensaje + "\n");
	socket.sendFixed(id_buf);
	#endif
}
*/
void Emisor::enviar(const std::string& tipo_mensaje, int mensaje) const{
	#ifndef DEBUG
	std::ostringstream stream;
	stream<<mensaje;
	enviar(tipo_mensaje,stream.str());
	#endif
}
/*
void Emisor::enviar(const std::string& tipo_mensaje) const{
	#ifndef DEBUG
	Buffer id_buf = Buffer::createString(tipo_mensaje+ "\n");
	socket.sendFixed(id_buf);
	//std::cout<<"estoy enviando el mensaje: "<<tipo_mensaje<<std::endl;
	#endif
}
*/

void Emisor::enviar(const std::string& tipo_mensaje, const std::string& mensaje) const{
	#ifndef DEBUG
	enviarString(tipo_mensaje);
	enviarNumero(mensaje.size());
	enviarString(mensaje);
	if(tipo_mensaje==MENSAJE_KEY_Z){
		timespec ahora;
		clock_gettime(CLOCK_REALTIME,&ahora);
		std::cout<<"Envié el Z a las: "<<ahora.tv_nsec<<std::endl;
	}
	#endif
}
void Emisor::enviar(const std::string& tipo_mensaje) const{
	#ifndef DEBUG
	enviarString(tipo_mensaje);
	enviarNumero(0);
	//std::cout<<"estoy enviando el mensaje: "<<tipo_mensaje<<std::endl;
	#endif
}

void Emisor::enviarString(const std::string& st) const{
	Buffer buf = Buffer::createString(st);
	socket.sendFixed(buf);
}
void Emisor::enviarNumero(int num) const{
	Buffer buf = Buffer::createNumber(num);
	socket.sendFixed(buf);
}
