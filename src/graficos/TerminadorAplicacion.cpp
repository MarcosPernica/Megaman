#include "TerminadorAplicacion.h"
void TerminadorAplicacion::terminar(){
	aplicacion->quit();
}
TerminadorAplicacion::TerminadorAplicacion(Glib::RefPtr<Gtk::Application> app):aplicacion(app){}
