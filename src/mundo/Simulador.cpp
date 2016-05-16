#include "Simulador.h"
#include <glibmm/main.h>
Simulador::Simulador(Mundo& mun, uint ms):
					mundo(mun),
					milisPorActualizacion(ms){
	Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &Simulador::on_actualizar)
			,milisPorActualizacion);
}

bool Simulador::on_actualizar(){
	mundo.actualizar(milisPorActualizacion/1000);
}
