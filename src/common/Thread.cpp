#include "Thread.h"
#include <exception>
#include <iostream>
#include "exceptions.h"

void Thread::start() {
	
	int c_result = pthread_create(&thread, NULL, Thread::runner, this);
	if(c_result != 0)
		throw CException("Error al abrir el thread");
	running = true;
}

void* Thread::runner(void *data) {
	
	try{
		Thread *self = (Thread*)data;
		
		self->run();
	}catch(const std::exception& e){
		std::cerr<<"Error: "<< e.what()<<std::endl;
	}catch(...){
		std::cerr<<"Error desconocido."<<std::endl;
	}
	return NULL;
}
        
void Thread::join() {
	if(running){
		this->end();
		void* endss;
		int j_result = pthread_join(thread, &endss);
		if(j_result != 0){
			std::cerr<<"Error al joinear el thread."<<std::endl;
			throw CException("Error al joinear el thread");
			
		}
	}
	running = false;
}

Thread::~Thread(){}
Thread::Thread():running(false),thread(0){}
