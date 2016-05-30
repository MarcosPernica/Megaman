
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
	Glib::RefPtr<Gtk::Application> app;
	Gtk::Window* window;
	Camara* camara;
	virtual void run();
	virtual void end();
	
	public:
	~VentanaJuego();
	VentanaJuego(int argc, char *argv[],const std::string& id);
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_actualizar_dibujo();
	Gtk::Window& getWindow();
	void ejecutar();
	void setCamara(Camara* camara);
};



#endif
