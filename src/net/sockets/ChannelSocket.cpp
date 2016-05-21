#include "ChannelSocket.h"
#include <sstream>
#include <string>
#include "Buffer.h"
#include "../../common/exceptions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <ctime>
/*
 * MARTIN: DEBERÍA USAR POLL() O PUEDO MEDIR EL TIEMPO A MANO COMO HICE?
 * */
 
/**
 * El llamado a Socket(file_descriptor) soluciona el leak de la primera entrega
 * Lo que pasaba era que se llamaba a Socket() (que SIEMPRE abre un nuevo 
 * socket) desde este constructor. El file descriptor luego se pisaba y se 
 * perdía.
 * */
ChannelSocket::ChannelSocket(int file_descriptor):Socket(file_descriptor){setNonBlocking();}

ChannelSocket::ChannelSocket(){
}

void ChannelSocket::connectAddr(AddressInfo* &info){
	int result = -1;
	AddressInfo* current = info;
	while(result < 0 && current != NULL){
		Address* address = current -> ai_addr;
		socklen_t length = current -> ai_addrlen;
		
		result = connectS(address,length);
		if(result < 0){
			current = current -> ai_next;
		}
	}
	if(current == NULL && result < 0){
		throw CException("Error al conectar el ChannelSocket");
	}
}

void ChannelSocket::connectTo(const std::string url, const unsigned port){
	AddressInfo *address;
	
	getAddrinfo(address, url.c_str(),port);
	connectAddr(address);
	freeaddrinfo(address);
	setNonBlocking();
}

void ChannelSocket::receiveFixed(Buffer& into) const{
	int received = 0;
	unsigned left = into.getSize();
	while(left > 0 && received >= 0){
		received = recvS(into.getData(), into.getSize());
		left -= received;
	}
	if(received<0){
		throw CException("hubo un error al recibir datos (receive Fifex)");
	}
}


std::string ChannelSocket::receiveUntilNl(float seconds) const{
	if(seconds>10){
		throw CustomException("No se permiten timeout de más de 10 segundos");
	}
	
	
	std::string result;
	char received_datum = 0;
	int total_received = 0;
	int received = 0;
	
	time_t start_time=0, now_time=0;
	start_time = clock();
	now_time = start_time;
	
	while(received >= 0 
		&& received_datum != '\n'
		&& total_received < MAX_TAM_MENSAJE
		&& (now_time-start_time)<seconds*CLOCKS_PER_SEC){
			
		received = recvS(&received_datum, 1);
		
		total_received += received;
		result += received_datum;
		
		now_time = clock();
	}
	/*
	if(received<0){
		throw CException("hubo un error al recibir datos (receive until Nl)");
	}
	*/
	
	if((now_time-start_time)>=seconds*CLOCKS_PER_SEC){
		throw RecvTimeOutException();
	}
	
	if(received<=0){
		throw RecvException();//CException("no hay datos que recibir (receive until Nl)");
	}
	
	
	return result;
}

void ChannelSocket::sendFixed(Buffer& from) const{
	int sent = 0;
	unsigned left = from.getSize();
	while(left > 0 && sent >= 0){
		sent = sendS(from.getData(), from.getSize());
		left -= sent;
	}
	if(sent < 0){
		throw CException("error al enviar datos");
	}
}
