#include "Simulador.h"
#include "../graficos/Camara.h"
#include <glibmm/main.h>
#include <iostream>

Simulador::Simulador(Mundo& mun, Camara &camara, uint ms):
					mundo(mun),
					camara(camara),			
					milisPorActualizacion(ms){
Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &Simulador::on_actualizar)
			,milisPorActualizacion);
}

bool Simulador::on_actualizar(){
	mundo.actualizar((real)milisPorActualizacion/1000);
	camara.actualizar((real)milisPorActualizacion/1000);	
	return true;
}
