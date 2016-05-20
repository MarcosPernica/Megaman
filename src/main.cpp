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


//-------------MAIN CON CLASE VENTANA (o 2 ventanas)-------------
/*
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
/*
#include "graficos/VentanaJuego.h"
#include "mundo/Mundo.h"
#include "mundo/Simulador.h"
#include "net/Jugador.h"

int main(int argc, char *argv[])
{
	Mundo mundo;
	VentanaJuego ventana(mundo,argc,argv,"1");
	ventana.start();
	Simulador simulador(mundo,33);
	simulador.run();
	*/
	/**
	 * Marcos, qué te parece si hacemos
	 * Megaman* Mundo::agregarMegaman(id_usuario)
	 * y después se llama
	 * mundo.iniciar() o lo que sea
	 * */
	 /*
	Jugador jugador(mundo.getMegaman(), ventana);
	ventana.join();
}
*/
//-------------MAIN CLI/SERV HASTA LA PIJA-------------
/*
#include <string>
#include "net/ChannelSocket.h"
#include "net/AccepterSocket.h"
#include "net/Buffer.h"
#include <iostream>
#include "common/exceptions.h"
#ifndef compiling_server
*/
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
/*
int main(int argc, char *argv[])
{
	ChannelSocket channel;
	channel.connectTo("127.0.0.1", 5002);
	std::cout<<"soy el cliente y estamos hasta la pija"<<std::endl;
	//envias el ID tuyo, talvez en el futuro un username
	std::cout<<"ingrese un ID de usuario"<<std::endl;
	int id_usuario = 0;
	//std::cin>>id_usuario;
	Buffer mensaje = Buffer::createString("usuario\n");
	channel.sendFixed(mensaje);
}
#else
int main(int argc, char *argv[])
{
	AccepterSocket accepter;
	ChannelSocket* channel;
	accepter.open(5002,15);
	bool escuchando = true;
	int ee = 0;
	
	while(escuchando && ee<10000){
		try{
			channel = accepter.acceptConnection();
			escuchando = false;
		}catch(...){}
	}
	
	std::cout<<"aceptado"<<std::endl;
	std::string mensaje;
	while(mensaje.length()==0){
		try{
			mensaje = channel->receiveUntilNl();
			std::cout<<mensaje<<std::endl;
		}catch(RecvException& e){}
	}
	std::cout<<mensaje<<std::endl;
	
	sleep(3);//acá se va el cliente!
	
	mensaje ="";
	while(mensaje.length()==0){
		try{
			mensaje = channel->receiveUntilNl();
			std::cout<<mensaje<<std::endl;
		}catch(RecvException& e){}
	}
	std::cout<<mensaje<<std::endl;
	
	return 0;
}
#endif
*/
//-------------MAIN CLI/SERV con complejidad-------------

#include "net/Servidor.h"
#include "net/Cliente.h"
#ifndef compiling_server

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

int main(int argc, char *argv[])
{
	Cliente cli;
	cli.correr();
}
#else
int main(int argc, char *argv[])
{
	Servidor servidor;
	servidor.correr();
}
#endif

