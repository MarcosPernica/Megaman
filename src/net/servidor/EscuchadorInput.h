#ifndef ESCUCHADORINPUT
#define ESCUCHADORINPUT
#include "../../common/Thread.h"
#include "Servidor.h"
class EscuchadorInput: public Thread{
	private:
	Servidor& servidor;
	public:
	EscuchadorInput(Servidor& servidor);
	virtual void run();
	virtual void end();
};
#endif
