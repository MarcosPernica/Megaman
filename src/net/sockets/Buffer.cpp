#include "Buffer.h"
#include <cstdlib>
#include <string>
#include <string.h>
#include <arpa/inet.h>
Buffer::Buffer(unsigned size){
	len = size;
	data = (char*) malloc(size*sizeof(char));
	memset(data,0,size);
}
Buffer::Buffer(){
	len = 0;
	data = NULL;
}
Buffer::~Buffer(){
	free(data);
}
unsigned Buffer::getSize() const{
	return len;
}
char* Buffer::getData(){
	return this->data;
}

void Buffer::write(const char* data, const unsigned len){
	memcpy(this->data, data,len);
}

Buffer Buffer::createNumber(CommonNumber n){
	Buffer ret(sizeof(n));
	CommonNumber env = htonl(n);
	ret.write((char*) &env, sizeof(n));
	//devuelve una copia, esto hace más sencillo el código
	//además, Buffer es un objeto pequeño
	return ret;
}
Buffer Buffer::createString(const std::string& s){
	Buffer ret(s.size());
	ret.write(s.c_str(), s.size());
	//char* end_pos = ret.getData() + s.size();
	//(*end_pos)='\0';
	//de nuevo, copia
	return ret;
}

CommonNumber Buffer::asNumber() const{
	CommonNumber env = * ((CommonNumber*) data);
	return ntohl(env);
}

std::string Buffer::asString() const{
	/*
	std::string ret = std::string(data);
	if(ret.size() > len){
		ret.erase(len,std::string::npos);
	}
	* */
	/*
	std::string ret;
	for(unsigned int i = 0; i<len; i++){
		ret+=data[i];
	}
	*/
	return std::string(data,len);
}
