#include "SimuladorSinVentana.h"
#include <ctime>
#include "../common/Lock.h"
#include <iostream>
void SimuladorSinVentana::run()
{
	while(getContinuar()){
		time_t t_inicial=clock();
		time_t t_final=t_inicial;
		while(getContinuar() && ((float)(t_final-t_inicial))/CLOCKS_PER_SEC < segundosPorActualizacion){
			contenedor.ejecutarControlesSobreMegaman();
		}
		mundo.actualizar(segundosPorActualizacion);
	}
	std::cout<<"Chau ventana!!"<<std::endl;
}

SimuladorSinVentana::SimuladorSinVentana(Mundo& mun, uint milis,ContenedorProxies& con):mundo(mun), contenedor(con){
	segundosPorActualizacion = ((float)milis)/1000;
}

bool SimuladorSinVentana::getContinuar(){
	Lock l(m_continuar);
	return continuar;
}
void SimuladorSinVentana::end(){
	std::cout<<"Se refiere a ventana!"<<std::endl;
	Lock l(m_continuar);
	continuar = false;
	std::cout<<"Digamos que anda!"<<std::endl;
}
