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
	try{
		timeval tv;
		gettimeofday(&tv, 0);
		std::ostringstream oss;
		oss<<"Megaman.Inicia"<<tv.tv_usec;
		std::string nombre = oss.str();
	
		std::cout << nombre << std::endl;
		
		//los atributos se cargan al recibir la configuracion
		Glib::RefPtr<Gtk::Application> app =Gtk::Application::create(argc,argv,nombre);
		TerminadorAplicacion terminador(app);
		VentanaJuego ventana(&terminador);
		return app->run(ventana);
	}catch(const std::exception& e){
		std::cerr<<"Error: "<< e.what()<<std::endl;
	}catch(...){
		std::cerr<<"Error desconocido."<<std::endl;
	}
	return 0;
}
#else
#include "net/servidor/Servidor.h"
#include "common/deslocalizacion.h"
#include "net/servidor/EscuchadorInput.h"
int main(int argc, char *argv[])
{
	try{
		SJuego::attr.cargar("configuracion.conf");
		Servidor servidor;
		EscuchadorInput escuchador(servidor);
		escuchador.start();
		servidor.ejecutar();
		escuchador.join();
	}catch(const std::exception& e){
		std::cerr<<"Error: "<< e.what()<<std::endl;
	}catch(...){
		std::cerr<<"Error desconocido."<<std::endl;
	}
	return 0;
}
#endif

