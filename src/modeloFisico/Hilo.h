#ifndef HILO
#define HILO

#include <pthread.h>
#include <map>
#include "Cadena.h"
#include "VariableCondicional.h"

class Hilo
{
private:
	VariableCondicional *flagListo;
	pthread_t *thread;
	bool flagEstado;
	bool flagConcurrir;
	unsigned int id;
public:
	explicit Hilo(VariableCondicional *flagListo = NULL);
	virtual ~Hilo();

	bool lanzar();
	void *concurrir();

	/*Devuelve true si finalizo el hilo.*/
	bool finalizado();
	/*Devuelve true si se esta concurriendo el hilo*/
	bool concurriendo();

	void *procesar();
	virtual void *funcion() = 0;
	virtual void rutinaTerminacion();

	int obtenerID();

private:
	static void *funcion(void *dato);
	static unsigned int contadorID;

protected:
	/*Le informa al creador del hilo que ya esta operativo*/
	void informarListo();
};

#endif
