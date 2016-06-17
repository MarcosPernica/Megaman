#ifndef THREADACEPTADOR
#define THREADACEPTADOR
#include "CallbackNuevaConexion.h"
#include "../../common/Thread.h"
#include <vector>

#include "AccepterSocket.h"
class ThreadAceptador : public Thread{
	private:
	bool continuar;//no lo protejo porque es atómico
	std::vector<CallbackNuevaConexion*> callbacks;
	AccepterSocket accepter;
	virtual void run();//
	virtual void end();//
	public:
	ThreadAceptador(const unsigned port, const unsigned queue);//
	void agregarCallback(CallbackNuevaConexion* callback);//
	~ThreadAceptador();//
	
};
#endif
