#include "Socket.h"
#include <sstream>
#include "../../common/exceptions.h"
#include <string>
#include <string.h>
#include <iostream>
#include "ChannelSocket.h"
#include <fcntl.h>
Socket::Socket(){
	file_descriptor = -1;
	file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
}
Socket::Socket(int fd){
	file_descriptor = fd;
}

Socket::~Socket(){
	if (file_descriptor != -1){
		try{
			closeS();
		}
		catch(...){ }
	}
}
void Socket::closeS(){
	if (file_descriptor != -1){
		shutdown(file_descriptor,SHUT_RDWR);
		close(file_descriptor);
		file_descriptor = -1;
	}
}

void Socket::getAddrinfo(AddressInfo* &set, 
							const char* hostname, 
							const unsigned port){
	AddressInfo hints;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	
	
	std::ostringstream ss;
	ss << port;
	std::string port_s = ss.str();
	
	int i_result = getaddrinfo(hostname, port_s.c_str(), &hints, &set);
	if(i_result != 0) throw GaiException(
						std::string("error en getaddrinfo. parametros: ")+
						std::string("hostname: ") + std::string(hostname) +
						std::string("port: ") + port_s,
						i_result);
}

ChannelSocket* Socket::acceptCon() const{
	ChannelSocket* channel;
	int fd = accept(file_descriptor,NULL, NULL);
	if(fd>=0){
		channel = new ChannelSocket(fd);
	}else{
		throw AcceptException();
	}
	return channel;
}

void Socket::setNonBlocking(){
	if(file_descriptor != -1){
		fcntl(file_descriptor, F_SETFL, O_NONBLOCK);
	}
}
void Socket::bindS(const AddressInfo* info){
	int res_b = bind(file_descriptor, info->ai_addr, info->ai_addrlen);
	if(res_b<0){
		throw CException("problema en bind");
	}
}

void Socket::listenS(const int queue){
	int res_l = listen(file_descriptor,queue);
	if(res_l<0){
		throw CException("problema en listen");
	}
}

int Socket::connectS(Address* address, socklen_t length){
	return connect(file_descriptor, address, length);
}
int Socket::recvS(char* into, unsigned size) const{
	return recv(file_descriptor, into, size, MSG_NOSIGNAL);
}
int Socket::sendS(char* from, unsigned size) const{
	return send(file_descriptor, from, size, MSG_NOSIGNAL);
}
