#include "SimuladorSinVentana.h"
#include <ctime>
#include "../common/Lock.h"
#include <iostream>
void SimuladorSinVentana::run()
{
	FullSnapshot a_distribuir;
	//-------------while con el server no jodiendo----------------
	/*
	while(getContinuar()){
		sleep(1);
	}
	*/
	
	
	while(getContinuar()){
		time_t t_inicial=clock();
		time_t t_final=t_inicial;
		while(getContinuar() && ((float)(t_final-t_inicial))/CLOCKS_PER_SEC < segundosPorActualizacion){
			t_final = clock();
			contenedor.ejecutarControlesSobreMegaman();
		}
		mundo.actualizar(segundosPorActualizacion);
		mundo.obtenerSnapshot(a_distribuir);
		contenedor.distribuir(a_distribuir);
		std::cout<<"Distribuí el snapshot"<<std::endl;
		
	}
	
	std::cout<<"Chau Simulador sin ventana"<<std::endl;
	//lo que dijo MARTIN/////////////////////////IMPLEMENTAR URGENTE
	/*
	//----------------pseudowhile de Martín-----------------------
	FullSnapshot a_distribuir;
	t_time t_sleep_extra = 0;
	while(getContinuar()){
		
		time_t t_inicial=time();
		time_t t_final=t_inicial;
		
		
		contenedor.ejecutarControlesSobreMegaman(); //procesarn TODOS los eventos
		mundo.actualizar(segundosPorActualizacion);
		mundo.obtenerSnapshot(a_distribuir);
		contenedor.distribuir(a_distribuir);
		std::cout<<"Distribuí el snapshot"<<std::endl;
		time_t t_final=clock();
		time_t t_process_time = t_final - t_inicial;
		usleep(DORMIR - ((t_process_time)*1000000)/CLOCKS_PER_SEC) - t_sleep_extra);//dormir CASI igual a segundosPorActualizacion (pero en micros)
		t_sleep_extra = clock() - (DORMIR - ((t_process_time)*1000000)/CLOCKS_PER_SEC) - t_sleep_extra)
	}
	std::cout<<"Chau Simulador sin ventana"<<std::endl;
	*/
}

SimuladorSinVentana::SimuladorSinVentana(Mundo& mun, uint milis,ContenedorProxies& con):mundo(mun), contenedor(con),continuar(true){
	segundosPorActualizacion = ((float)milis)/1000;
}

bool SimuladorSinVentana::getContinuar(){
	Lock l(m_continuar);
	return continuar;
}
void SimuladorSinVentana::end(){
	//std::cout<<"Se refiere a ventana!"<<std::endl;
	Lock l(m_continuar);
	continuar = false;
	//std::cout<<"Digamos que anda!"<<std::endl;
}
