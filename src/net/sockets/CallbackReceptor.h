#ifndef CALLBACKRECEPTOR
#define CALLBACKRECEPTOR
#include <string>
#include <iostream>
class CallbackReceptor{
	public:
	virtual void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje)=0;
};
#endif
