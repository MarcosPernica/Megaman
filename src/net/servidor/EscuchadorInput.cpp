#include "EscuchadorInput.h"
#include <iostream>
EscuchadorInput::EscuchadorInput(Servidor& serv):servidor(serv){}
void EscuchadorInput::run(){
	char entrada ='a';
	while(entrada != 'q' && entrada !='Q'){
		std::cout<<"Ingrese Q para terminar el servidor"<<std::endl;
		std::cin>>entrada;
	}
	servidor.cerrar();
}
void EscuchadorInput::end(){}
