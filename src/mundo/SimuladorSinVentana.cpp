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
	long nanos_por_segundo=1000000000;
	int loops_desde_ultimo_envio = 0;
	double segs_dormi_extra = 0;
	while(getContinuar()){
		
		
		timespec t_inicial;
		clock_gettime(CLOCK_REALTIME,&t_inicial);
		
		contenedor.ejecutarControlesSobreMegaman();
		mundo.actualizar(segundosPorActualizacion);
		
		loops_desde_ultimo_envio += 1;
		if(loops_desde_ultimo_envio>2){
			mundo.obtenerSnapshot(a_distribuir);
			contenedor.distribuir(a_distribuir);
			loops_desde_ultimo_envio = 0;
		}
		
		timespec t_despues_de_computos;
		clock_gettime(CLOCK_REALTIME,&t_despues_de_computos);
		
		double segs_computando = ((double)(t_despues_de_computos.tv_nsec-t_inicial.tv_nsec))/nanos_por_segundo;//aunque deberían ser 9 ceros (se supone que son 9!)
		double segs_a_dormir = segundosPorActualizacion - segs_computando - segs_dormi_extra;
		if(segs_a_dormir>0){
			usleep((useconds_t)(segs_a_dormir * 1000000));// 6 ceros
			
			timespec t_despues_de_dormir;
			clock_gettime(CLOCK_REALTIME,&t_despues_de_dormir);
			
			double segs_que_dormi = ((double)(t_despues_de_dormir.tv_nsec-t_despues_de_computos.tv_nsec))/nanos_por_segundo;//aunque deberían ser 9 ceros (se supone que son 9!)
			segs_dormi_extra = segs_que_dormi-segs_a_dormir;
			if(segs_dormi_extra<0){
				segs_dormi_extra = 0;
			}
		}
		
		if(mundo.obtenerEstadoMundo() == perdido){
			mundo.reiniciar();
		}
		
		if(mundo.obtenerEstadoMundo() == gameover || mundo.obtenerEstadoMundo() == ganado){
			callbackFinMundo->fin(mundo.obtenerEstadoMundo());
			Lock l(m_continuar);
			continuar = false;
		}
	}
}

SimuladorSinVentana::SimuladorSinVentana(
				Mundo& mun, 
				uint milis, 
				ContenedorProxies& con, 
				CallbackFinMundo* call):
						contenedor(con), 
						continuar(true), 
						mundo(mun),
						callbackFinMundo(call){
	segundosPorActualizacion = ((float)milis)/1000;
}

bool SimuladorSinVentana::getContinuar(){
	Lock l(m_continuar);
	return continuar;
}
void SimuladorSinVentana::end(){
	Lock l(m_continuar);
	continuar = false;
}

SimuladorSinVentana::~SimuladorSinVentana(){
	delete callbackFinMundo;
}
