#include "Hilo.h"
#include "Definiciones.h"
#include <iostream>

unsigned int Hilo::contadorID = 0;

Hilo::Hilo(VariableCondicional *flagListo) : flagListo(flagListo)
{
	id = contadorID++;
	flagEstado = false;
	flagConcurrir = false;
	thread = NULL;
}

Hilo::~Hilo()
{
	if(thread)
		pthread_join(*thread, NULL);
}

bool Hilo::lanzar()
{
	thread = new pthread_t;
	if (pthread_create(thread, NULL, Hilo::funcion, this))
	{
		delete thread;
		thread = NULL;
		return false;
	}
	return true;
}

int Hilo::obtenerID()
{
	return id;
}

void * Hilo::concurrir()
{
	void *resultado;
	flagConcurrir = true;
	rutinaTerminacion();

	pthread_join(*thread, &resultado);
	delete thread;
	thread = NULL;

	return resultado;
}

bool Hilo::finalizado()
{
	return flagEstado;
}

bool Hilo::concurriendo()
{
	return flagConcurrir;
}

void * Hilo::procesar()
{
	void *ret = funcion();
	flagEstado = true;
	return ret;
}

void Hilo::rutinaTerminacion()
{
}

void * Hilo::funcion(void * dato)
{
	Hilo *hilo = reinterpret_cast<Hilo *>(dato);

	return hilo->procesar();
}

void Hilo::informarListo()
{
	if(flagListo)
		flagListo->despertarHilo();
}

