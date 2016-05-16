/*
//------------MAIN PARA SABER SI COMPILA (?)---------


#include <Box2D/Box2D.h>
#include <iostream>
int main(int argc, char* argv[])
{
	std::cout<<"estoy compilado y corriendo! eso es bueno!"<<std::endl;
	return 0;
}
*/
/*
//------------MAIN PARA PROBAR COSITAS DE GTKMM + IGNORES DE VALGRIND?----------
#include <gtkmm.h>
int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  Gtk::Window window;# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket
  window.set_default_size(200, 200);
  Gtk::Button boton;
  window.add(boton);
  boton.show();
  return app->run(window);
}
*/

/*
//-------------MAIN CON CLASE VENTANA (o 2 ventanas)-------------
#include "graficos/VentanaJuego.h"
#include "mundo/Mundo.h"
#include <X11/Xlib.h>
int main(int argc, char *argv[])
{
	//XInitThreads();
	
	Mundo mundo;
	VentanaJuego ventana(mundo,argc,argv,"1");
	
	ventana.start();
	//VentanaJuego ventana2(mundo,argc,argv,"2");
	//ventana2.start();
	
	ventana.join();
	//ventana2.join();
}
*/

//-------------MAIN CON VENTANA Y FISICAS-------------
#include "graficos/VentanaJuego.h"
#include "mundo/Mundo.h"
#include <ctime>
int main(int argc, char *argv[])
{
	Mundo mundo;
	VentanaJuego ventana(mundo,argc,argv,"1");
	ventana.start();
	
	
	
	ventana.join();
}
