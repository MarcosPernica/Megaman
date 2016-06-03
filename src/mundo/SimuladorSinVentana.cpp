#include "SimuladorSinVentana.h"
#include <ctime>
#include "../common/Lock.h"
#include <iostream>
#include <unistd.h>
#include <cmath>

#define _POSIX_C_SOURCE 200809L

void SimuladorSinVentana::run()
{
	FullSnapshot a_distribuir;
	//-------------while con el server no jodiendo----------------
	/*
	while(getContinuar()){
		sleep(1);
	}
	*/
	
	/*
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
		
	}
	*/
	//--------------CON CLOCK()-----------------------------------//
	/*
	int loops_desde_ultimo_envio = 0;
	float segs_dormi_extra = 0;
	while(getContinuar()){
		loops_desde_ultimo_envio += 1;
		
		time_t t_inicial = clock();
		
		contenedor.ejecutarControlesSobreMegaman();
		mundo.actualizar(segundosPorActualizacion);
		if(loops_desde_ultimo_envio>10){
			mundo.obtenerSnapshot(a_distribuir);
			contenedor.distribuir(a_distribuir);
			loops_desde_ultimo_envio = 0;
		}
		
		time_t t_despues_de_computos = clock();
		float segs_computando = ((float)(t_despues_de_computos-t_inicial))/CLOCKS_PER_SEC;
		float segs_a_dormir = segundosPorActualizacion - segs_computando - segs_dormi_extra;
		
		usleep((useconds_t)(segs_a_dormir * 1000000));
		
		time_t t_despues_de_dormir = clock();
		
		float segs_que_dormi = ((float)(t_despues_de_dormir-t_despues_de_computos))/CLOCKS_PER_SEC;
		segs_dormi_extra = segs_que_dormi-segs_a_dormir;
	}
	*/
	//--------------------------CON CLOKC_GETTIME()--------------------//
	//primero, determino un factor de escalamiento entre el tiempo real y el 
	//tiempo que me dicen que es el real. De esta manera, no me boludea linux.
	
	//primer paso: avanzo hasta el principio del próximo segundo
	time_t t_inicial;
	time(&t_inicial);
	time_t t_final=t_inicial;
	while(t_final-t_inicial<1){
		time(&t_final);
	}
	//segundo paso: cuántos nanosegundos hay en un segundo?
	timespec preciso_inicial,preciso_final;
	clock_gettime(CLOCK_REALTIME,&preciso_inicial);
	time_t t_inicial2;
	time(&t_inicial2);
	time_t t_final2=t_inicial2;
	/*
	while(t_final2-t_inicial2<1){
		time(&t_final2);
	}*/
	usleep(1000000);
	clock_gettime(CLOCK_REALTIME,&preciso_final);
	//tercer paso: escalamiento
	long nanos_por_segundo = abs(preciso_final.tv_nsec-preciso_inicial.tv_nsec);
	std::cout<<"Nanos por segundo: "<<nanos_por_segundo<<std::endl;
	nanos_por_segundo=1000000000;
	//ahora sí, el ciclo
	int loops_desde_ultimo_envio = 0;
	double segs_dormi_extra = 0;
	while(getContinuar()){
		
		
		timespec t_inicial;
		clock_gettime(CLOCK_REALTIME,&t_inicial);
		
		contenedor.ejecutarControlesSobreMegaman();
		mundo.actualizar(segundosPorActualizacion);
		
		loops_desde_ultimo_envio += 1;
		if(loops_desde_ultimo_envio>10){
			mundo.obtenerSnapshot(a_distribuir);
			contenedor.distribuir(a_distribuir);
			loops_desde_ultimo_envio = 0;
		}
		
		timespec t_despues_de_computos;
		clock_gettime(CLOCK_REALTIME,&t_despues_de_computos);
		
		double segs_computando = ((double)(t_despues_de_computos.tv_nsec-t_inicial.tv_nsec))/nanos_por_segundo;//aunque deberían ser 9 ceros (se supone que son 9!)
		double segs_a_dormir = segundosPorActualizacion - segs_computando - segs_dormi_extra;
		if(segs_a_dormir>0){
//			std::cout<<"voy a dormir en us"<<(useconds_t)(segs_a_dormir * 1000000)<<" en s: "<<segs_a_dormir<<std::endl;
//			std::cout<<"segs p/a "<<segundosPorActualizacion<<" segs computando "<<segs_computando<<" segs extra "<<segs_dormi_extra<<std::endl;
			usleep((useconds_t)(segs_a_dormir * 1000000));// 6 ceros
			
			timespec t_despues_de_dormir;
			clock_gettime(CLOCK_REALTIME,&t_despues_de_dormir);
			
			double segs_que_dormi = ((double)(t_despues_de_dormir.tv_nsec-t_despues_de_computos.tv_nsec))/nanos_por_segundo;//aunque deberían ser 9 ceros (se supone que son 9!)
			segs_dormi_extra = segs_que_dormi-segs_a_dormir;
			if(segs_dormi_extra<0){
				segs_dormi_extra = 0;
			}
		}else{
			//segundosPorActualizacion += -segs_a_dormir;
		}
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
