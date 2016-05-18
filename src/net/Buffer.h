#ifndef _BUFFER_
#define _BUFFER_
#include <stdlib.h>
#include <string>
/**
 * Representa un Buffer que se genera y libera por RAII
 * Funciona junto con ChannelSocket para enviar números o strings de 
 * tamaño conocido con facilidad
 * */
typedef int CommonNumber;
class Buffer{
	private:
	unsigned len;
	char* data;
	
	public:
	explicit Buffer(unsigned size);
	Buffer();
	~Buffer();
	/**
	 * devuelve el tamaño del buffer
	 * */
	unsigned getSize() const;
	/**
	 * devuelve la posición del buffer
	 * */
	char* getData();
	/**
	 * Permite escribir al buffer directamente
	 * */
	void write(const char* data, const unsigned len);
	/**
	 * Crea un nuevo buffer que contiene un CommonNumber
	 * */
	static Buffer createNumber(CommonNumber n);
	CommonNumber asNumber() const;
	/**
	 * Crea un nuevo buffer que contiene un string
	 * */
	static Buffer createString(const std::string& s);
	std::string asString() const;
};

#endif
