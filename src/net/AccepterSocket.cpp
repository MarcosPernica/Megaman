#include "AccepterSocket.h"
#include "Socket.h"
#include <unistd.h>

#include "../common/exceptions.h"
#include <iostream>
void AccepterSocket::open(const unsigned port, const unsigned queue){
	AddressInfo *info;
	const char* local = NULL;//"localhost\0";
	getAddrinfo(info,local,port);
	bindS(info);
	freeaddrinfo(info);
	listenS(queue);
}


ChannelSocket* AccepterSocket::acceptConnection() const{
	return Socket::acceptCon();
}

AccepterSocket::AccepterSocket(){
	setNonBlocking();
}
