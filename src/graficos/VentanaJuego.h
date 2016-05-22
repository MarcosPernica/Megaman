
#ifndef VENTANAJUEGO
#define VENTANAJUEGO
#include <gtkmm.h>
#include <iostream>
#include "../common/Thread.h"
#include "../mundo/Mundo.h"
#include <string>
#include "Camara.h"

class VentanaJuego : public Thread{
	private:
	Gtk::DrawingArea *darea;
	const Mundo& mundo;
	Glib::RefPtr<Gtk::Application> app;
	Gtk::Window* window;
	Camara &camara;
	public:
	~VentanaJuego();
	VentanaJuego(const Mundo& mundo, Camara &camara, int argc, char *argv[],const std::string& id);
	virtual void run();
	virtual void end();
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_actualizar_dibujo();
	Gtk::Window& getWindow();
};



#endif
