
#ifndef VENTANAJUEGO
#define VENTANAJUEGO
#include <gtkmm.h>
#include <iostream>
#include "../common/Thread.h"
#include "../mundo/Mundo.h"
#include <string>
#include "Camara.h"

/**
 * No se removió la herencia de Thread por las dudas
 * */
class VentanaJuego : private Thread{
	private:
	Gtk::DrawingArea *darea;
	const Mundo& mundo;
	Glib::RefPtr<Gtk::Application> app;
	Gtk::Window* window;
	Camara &camara;
	virtual void run();
	virtual void end();
	public:
	~VentanaJuego();
	VentanaJuego(const Mundo& mundo, Camara &camara, int argc, char *argv[],const std::string& id);
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_actualizar_dibujo();
	Gtk::Window& getWindow();
	void ejecutar();
};



#endif
