#include "Emisor.h"
#include "../sockets/Buffer.h"
#include <iostream>
#include <sstream>
#include "../defines_protocolo.h"
#include "../Debug.h"
#include <fstream>
#include <string>
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

/**
 * Después con esto enviamos el archivo de configuración!
 * */
void Emisor::enviarNivel(char nivel) const{
	//nombre del nivel
	std::string nombre_nivel("niveles/nivel");
	nombre_nivel+=nivel;
	nombre_nivel+=".xml";//sí
	
	//archivo
	std::ifstream archivo_nivel;
	archivo_nivel.open(nombre_nivel.c_str());
	
	//enviarlo
	enviar(MENSAJE_INICIAR_ENVIO_NIVEL);
	std::string enviando;
	while(!archivo_nivel.eof()){
		std::getline(archivo_nivel,enviando);
		enviar(MENSAJE_ENVIO_NIVEL,enviando);
	}
	enviar(MENSAJE_TERMINAR_ENVIO_NIVEL);
	archivo_nivel.close();
}
