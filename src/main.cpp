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

int main(int argc, char *argv[])
{
	//std::locale::global( std::locale( "" ) );
	std::locale::global(std::locale(std::cout.getloc(), new SJuego::ConComa()));

	timeval tv;
	gettimeofday(&tv, 0);
	std::ostringstream oss;
	oss<<"Megaman.Inicia"<<tv.tv_usec;
	std::string nombre = oss.str();

	std::cout << nombre << std::endl;

	SJuego::attr.cargar("configuracion.conf");
	Glib::RefPtr<Gtk::Application> app =Gtk::Application::create(argc,argv,nombre);
	std::cout << "1" << std::endl;
	VentanaJuego ventana;
	std::cout << "2" << std::endl;
	return app->run(ventana);
	std::cout << "3" << std::endl;
}
#else
#include "net/servidor/Servidor.h"
int main(int argc, char *argv[])
{
	//std::locale::global( std::locale( "" ) );
	std::locale::global(std::locale(std::cout.getloc(), new SJuego::ConComa()));
	SJuego::attr.cargar("configuracion.conf");
	Servidor servidor;
	servidor.correr();
}
#endif

