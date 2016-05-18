#ifndef RECEPTOR_CLIENTE
#define RECEPTOR_CLIENTE

#include "Receptor.h"
#include <string>
#include "Cliente.h"
#include <iostream>
class ReceptorCliente: public Receptor{
	private:
	Cliente& cliente;
	public: 
	ReceptorCliente(const ChannelSocket& channel, Cliente& cliente);
	void ejecutarMensaje(const std::string& tipo_mensaje,const std::string& resto_mensaje);
};
#endif
