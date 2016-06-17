#include "ThreadAceptador.h"
#include "../../common/exceptions.h"
#include <iostream>
ThreadAceptador::ThreadAceptador(const unsigned port, const unsigned queue):
														continuar(true){
	accepter.open(port,queue);
}
void ThreadAceptador::agregarCallback(CallbackNuevaConexion* callback){
	callbacks.push_back(callback);
}
ThreadAceptador::~ThreadAceptador(){
	std::vector<CallbackNuevaConexion*>::iterator it;
	for(it = callbacks.begin(); it!=callbacks.end(); ++it){
		delete *it;
	}
}

void ThreadAceptador::run(){
	
	while(continuar){
		try{
			ChannelSocket* aceptado = accepter.acceptConnection();
			
			std::vector<CallbackNuevaConexion*>::iterator it;
			for(it = callbacks.begin(); it!=callbacks.end(); ++it){
				(*it)->nueva(aceptado);
			}
		}catch(const CException& e){
			std::cout<<"Hubo un error al aceptar!! creo que porque se cerró el accepter socket"<<std::endl;
		}
	}
	
}

void ThreadAceptador::end(){
	continuar = false;
	accepter.closeS();
}
