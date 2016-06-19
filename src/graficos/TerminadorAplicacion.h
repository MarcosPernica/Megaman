#ifndef TERMINADORAPLICACION
#define TERMINADORAPLICACION
#include "VentanaJuego.h"
#include <gtkmm/application.h>
class TerminadorAplicacion: public Terminador{
	private:
	Glib::RefPtr<Gtk::Application> aplicacion;
	public:
	virtual void terminar();
	TerminadorAplicacion(Glib::RefPtr<Gtk::Application> aplicacion);
};
#endif
