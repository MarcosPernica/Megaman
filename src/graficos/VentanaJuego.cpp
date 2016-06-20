#include "VentanaJuego.h"
#include <cairo.h>
#include <gdk/gdk.h>

//-------------
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>
//#include <Box2D/Box2D.h>//include demasiado grande??
#include "../mundo/Mundo.h"
//--------------------
#include "../net/cliente/CallbackPosicion.h"
#include "CallbackEstabaLlega.h"
#include "CallbackIniciar.h"
#include "CallbackFinVen.h"
#include "../net/defines_protocolo.h"
#include "../mundo/Simulador.h"
#include "../net/cliente/Jugador.h"
#include <glibmm/main.h>
#include "../net/Debug.h"
#include <cstdio>

VentanaJuego::VentanaJuego(Terminador* termina):cajaSplash(false,10),
				cliente(*this),
				malos(true,10),
				jugador(NULL),
				mundo(NULL),
				simulador(NULL), 
				fondo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600)),
				cantidad_jugadores(0),
				terminador(termina){
					
	set_default_size(800, 600);
	
	signal_delete_event().connect(sigc::mem_fun(*this,&VentanaJuego::cerrarVentana));
	
	#ifndef DEBUG
	estado.set_text("Introduzca nombre de usuario");
	lobby.set_text("JUGADORES:\n");
	
	add(cajaSplash);
	cajaSplash.add(estado);
	cajaSplash.add(entry);
	estado.show();
	entry.show();
	
	for(int i = 0;i<5;i++){
		std::ostringstream oss;
		oss<<"nivel: ";
		oss<<i+1;
		Gtk::Button* b = new Gtk::Button(oss.str());
		b->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&VentanaJuego::on_button_clicked),i+1));
		botonesMalos.push_back(b);
		malos.add(*b);
		b->show();
	}
	cajaSplash.add(malos);
	malos.show();
	malos.set_sensitive(false);
	cajaSplash.add(lobby);
	lobby.show();
	
	entry.signal_activate().connect(
			sigc::mem_fun(*this, &VentanaJuego::on_intro_nombre));
	cajaSplash.show();
	
	/*
	
	*/
	
	//
	//darea.show();
	cliente.agregarCallback(MENSAJE_POSICION,new CallbackPosicion(*this,cliente));
	cliente.agregarCallback(MENSAJE_ESTABA,new CallbackEstabaLlega(*this,cliente));
	cliente.agregarCallback(MENSAJE_LLEGA,new CallbackEstabaLlega(*this,cliente));
	cliente.agregarCallback(MENSAJE_INICIAR,new CallbackIniciar(*this,cliente));
	cliente.agregarCallback(MENSAJE_FIN_NIVEL,new CallbackFinVen(*this,cliente));

	#else
		iniciarNivel();
	#endif
}

bool VentanaJuego::mi_on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

	Gtk::Allocation allocation = darea.get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	fondo.dibujarEn(cr, b2Vec2(0,0), 1);

	b2Vec2 posicion = Dibujable::mundoARender(mundo->obtenerPosicionCamara());
	std::list<Dibujable*> dibujables = mundo->obtenerElementosCamara();

	std::list<Dibujable*>::iterator i = dibujables.begin();

	while(i != dibujables.end())
		(*i++)->dibujarEn(cr, posicion, 1);
	
	return true;
}

bool VentanaJuego::on_actualizar_dibujo(){
	darea.queue_draw();
	return true;
}

void VentanaJuego::on_intro_nombre(){
	Glib::RefPtr<Gtk::EntryBuffer> buffer = entry.get_buffer();
	nombre = buffer->get_text();
	std::cout<<"El usuario es "<<nombre<<std::endl;
	entry.set_text("ya enviaste tu nombre de usuario");
	estado.set_text("Conectando...");
	entry.set_sensitive(false);
	cliente.conectarse(nombre);
	agregarJugador(nombre);
}
void VentanaJuego::setPrimero(bool primero){
	if(primero){
		malos.set_sensitive(true);
		estado.set_text("Sos el primero, elegí un nivel para iniciar la partida.");
	}else{
		estado.set_text("No sos el primero, esperando a que el primero elija un nivel.");
	}
}

void VentanaJuego::agregarJugador(const std::string& nombre){
	std::cout<<"Se agrega al lobby: "<<nombre<<std::endl;
	Glib::ustring texto_lobby = lobby.get_text();
	texto_lobby+=nombre+"\n";
	lobby.set_text(texto_lobby);
	cantidad_jugadores+=1;
}

void VentanaJuego::on_button_clicked(int cual){
	cliente.enviarIniciar(cual);
}


void VentanaJuego::iniciarNivel(){
	remove();
	add(darea);
	darea.show();
	
	#ifndef DEBUG
	mundo = new Mundo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600),b2Vec2(0,0),nombre+"nivel.xml",cantidad_jugadores);
	#else 
	mundo = new Mundo(Dibujable::renderAMundo(800),Dibujable::renderAMundo(600),b2Vec2(0,0),nombre+"nivel.xml",1);
	#endif
	jugador = cliente.configurarNivel(*this,*mundo);
	///int caca = sigc::mem_fun(*this, &VentanaJuego::on_actualizar_dibujo);
	simulador = new Simulador(*mundo,33);
	
	conexionActualizarDibujo = Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &VentanaJuego::on_actualizar_dibujo)
			,33);
	
	conexionMiOnDraw = darea.signal_draw().connect(sigc::mem_fun(*this, &VentanaJuego::mi_on_draw));
}

void VentanaJuego::mostrarPantallaSeleccion(){
	std::cout<<"mostrarPantallaSeleccion"<<std::endl;
	
	liberarRecursos();
	remove();
	add(cajaSplash);
	
}

bool VentanaJuego::cerrarVentana(GdkEventAny* evento){
	std::remove((cliente.obtenerNombre()+"nivel.xml").c_str());
	std::remove((cliente.obtenerNombre()+SJuego::archivoConfig).c_str());
	liberarRecursos();
	std::cout<<"Cerrando ventana!"<<std::endl;
	terminador->terminar();
}

void VentanaJuego::liberarRecursos(){
	if(conexionActualizarDibujo.connected()){
		conexionActualizarDibujo.disconnect();
	}
	
	if(conexionMiOnDraw.connected()){
		conexionMiOnDraw.disconnect();
	}
	
	if(jugador!=NULL){
		jugador->desconectar();
		delete jugador;
		jugador = NULL;
	}
	
	if(simulador != NULL){
		simulador->desconectar();
		delete simulador;
		simulador = NULL;
	}
	
	cliente.terminarMundo();
	
	delete mundo;
	mundo = NULL;
}

VentanaJuego::~VentanaJuego(){
	liberarRecursos();
	std::vector<Gtk::Button*>::iterator it;
	for(it = botonesMalos.begin(); it !=botonesMalos.end(); ++it){
		delete *it;
	}
}

