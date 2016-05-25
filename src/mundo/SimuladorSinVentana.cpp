#include "SimuladorSinVentana.h"
#include <ctime>
#include "../common/Lock.h"
#include <iostream>
void SimuladorSinVentana::run()
{
	std::cout<<"---------------------------Hola sim sin ventana!!-----------"<<std::endl;
	while(getContinuar()){
		time_t t_inicial=clock();
		time_t t_final=t_inicial;
		while(getContinuar() && ((float)(t_final-t_inicial))/CLOCKS_PER_SEC < segundosPorActualizacion){
			t_final = clock();
			//std::cout<<((float)(t_final-t_inicial))/CLOCKS_PER_SEC<<std::endl;
			//bloquear
		}
		mundo.actualizar(segundosPorActualizacion);
		FullSnapshot a_enviar;
		mundo.obtenerSnapshot(a_enviar);
		distribuidor.distribuir(a_enviar);
	}
	std::cout<<"Chau sim sin ventana!!"<<std::endl;
}

SimuladorSinVentana::SimuladorSinVentana(Mundo& mun, uint milis, DistribuidorSnapshots& d):
				mundo(mun),distribuidor(d){
	segundosPorActualizacion = ((float)milis)/1000;
}

bool SimuladorSinVentana::getContinuar(){
	Lock l(m_continuar);
	return continuar;
}
void SimuladorSinVentana::end(){
	std::cout<<"ahora quiero terminar sim sin ventana-------------------!"<<std::endl;
	Lock l(m_continuar);
	continuar = false;
	std::cout<<"Digamos que anda!"<<std::endl;
}
