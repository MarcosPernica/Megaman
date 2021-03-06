#include "Emisor.h"
#include "../sockets/Buffer.h"
#include <iostream>
#include <sstream>
#include "../defines_protocolo.h"
#include "../Debug.h"
#include <fstream>
#include <string>
#include "../../mundo/Definiciones.h"
Emisor::Emisor(const ChannelSocket& s):socket(s){}
void Emisor::enviar(const std::string& tipo_mensaje, int mensaje) const{
	#ifndef DEBUG
	std::ostringstream stream;
	stream<<mensaje;
	enviar(tipo_mensaje,stream.str());
	#endif
}

void Emisor::enviar(const std::string& tipo_mensaje, const std::string& mensaje) const{
	#ifndef DEBUG
	enviarString(tipo_mensaje);
	enviarNumero(mensaje.size());
	enviarString(mensaje);
	#endif
}
void Emisor::enviar(const std::string& tipo_mensaje) const{
	#ifndef DEBUG
	enviarString(tipo_mensaje);
	enviarNumero(0);
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

void Emisor::enviarConfiguracion(){
	std::ifstream archivo_config(SJuego::archivoConfig.c_str());
	enviar(MENSAJE_INICIAR_ENVIO_CONFIG);
	std::string enviando;
	while(!archivo_config.eof()){
		std::getline(archivo_config,enviando);
		enviar(MENSAJE_ENVIO_CONFIG,enviando);
	}
	enviar(MENSAJE_TERMINAR_ENVIO_CONFIG);
}
