/**
 * El juego va a tener las sig. etapas:
 * 
 * Seteo de jugadores e ids, e inicio de partida por parte del primero
 * (si sos el primero, envías y recibís la señal "iniciar", si no sos el primero, sólo recibís la señal iniciar)
 * (mientras, recibiste info de todos los jugadores)
 * 
 * selección de nivel
 * lanzamiento de ventana
 * 
 * selección de nivel
 * lanzamiento de ventana
 * 
 * y así...
 * */

#ifndef compiling_server
#include <gtkmm/application.h>
#include "graficos/VentanaJuego.h"
#include "mundo/Definiciones.h"
#include <string>
#include <sys/time.h>
#include "common/deslocalizacion.h"
#include "graficos/TerminadorAplicacion.h"
int main(int argc, char *argv[])
{
	timeval tv;
	gettimeofday(&tv, 0);
	std::ostringstream oss;
	oss<<"Megaman.Inicia"<<tv.tv_usec;
	std::string nombre = oss.str();

	std::cout << nombre << std::endl;
	
	SJuego::attr.cargar("configuracion.conf");
	Glib::RefPtr<Gtk::Application> app =Gtk::Application::create(argc,argv,nombre);
	TerminadorAplicacion terminador(app);
	VentanaJuego ventana(&terminador);
	return app->run(ventana);
}
#else
#include "net/servidor/Servidor.h"
#include "common/deslocalizacion.h"
int main(int argc, char *argv[])
{
	SJuego::attr.cargar("configuracion.conf");
	Servidor servidor;
	servidor.ejecutar();
}
#endif

