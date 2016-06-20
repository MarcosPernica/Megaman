#ifndef VENTANAJUEGO
#define VENTANAJUEGO
#include <gtkmm/window.h>
#include <iostream>
#include <gtkmm/drawingarea.h>
#include <string>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/entry.h>
#include <gdk/gdk.h>
#include "../net/cliente/Cliente.h"
#include "Fondo.h"
#include "DareaSplash.h"
class Terminador{
	public:
	virtual void terminar() = 0;
};

class Mundo;
class Jugador;
class Simulador;
class VentanaJuego : public Gtk::Window{
	private:
	bool inicio_ok;
	
	DareaSplash dareaSplash;
	Terminador* terminador;//se destruye afuera
	
	Fondo fondo;
	std::string nombre;
	Gtk::DrawingArea darea;
	Gtk::Label estado;
	Gtk::VBox cajaSplash;
	Gtk::Entry entry;
	
	sigc::connection conexionActualizarDibujo;
	sigc::connection conexionMiOnDraw;
	sigc::connection conexionKeyPress;
	
	Gtk::Label lobby;
	
	Gtk::HBox malos;
	std::vector<Gtk::Button*> botonesMalos;//los destruyo
	
	Cliente cliente;//no sabe bien cómo destruirse
	
	Jugador* jugador;//los destruyo
	Mundo* mundo;//los destruyo
	Simulador* simulador;//los destruyo
	public:
	bool cerrarVentana(GdkEventAny* evento);
	VentanaJuego(Terminador* terminador);
	~VentanaJuego();
	
	uint cantidad_jugadores;
	
	bool on_actualizar_dibujo();
	
	bool mi_on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	/*
	void ejecutar();
	*/
	//void simularMundo(Mundo& mundo){};
	void iniciarNivel();
	
	void on_intro_nombre();
	void setPrimero(bool primero);
	
	void agregarJugador(const std::string& nombre);
	void on_button_clicked(int cual);
	
	void mostrarPantallaSeleccion();
	
	void liberarRecursos();
	
	bool expose_event(GdkEventExpose* evento);
	
	bool detectarPresionTecla(GdkEventKey* evento);
	
};
#endif
