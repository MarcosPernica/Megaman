
#ifndef VENTANAJUEGO
#define VENTANAJUEGO
#include <gtkmm/window.h>
#include <iostream>
#include <string>
#include <gtkmm/drawingarea.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/entry.h>
#include <gdk/gdk.h>
#include "../net/cliente/Cliente.h"
class Mundo;
class Jugador;
class Simulador;
/**
 * No se removió la herencia de Thread por las dudas
 * */
class VentanaJuego : public Gtk::Window{
	private:
	std::string nombre;
	Gtk::DrawingArea darea;
	Gtk::Label estado;
	Gtk::VBox cajaSplash;
	Gtk::Entry entry;
	
	Gtk::Label lobby;
	
	Gtk::HBox malos;
	std::vector<Gtk::Button*> botonesMalos;
	
	Cliente cliente;
	
	Jugador* jugador;
	Mundo* mundo;
	Simulador* simulador;
	public:
	VentanaJuego();
	~VentanaJuego();
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
};
#endif
