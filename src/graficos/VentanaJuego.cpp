#include "VentanaJuego.h"
#include <cairo.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
void VentanaJuego::run(){
	
	std::cout<<"VentanaJuego esta corriendo"<<std::endl;
	
	
	
	window->set_default_size(800, 600);
	
	Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &VentanaJuego::on_actualizar_dibujo)
			,33);
	/*
	Gtk::Button boton;
	window.add(boton);
	boton.show();
	* */
	
	window->add(*darea);
	
	darea->signal_draw().connect(sigc::mem_fun(*this, &VentanaJuego::on_draw));
	darea->show();
	
	app->run(*window);
	
}
void VentanaJuego::end(){}

VentanaJuego::VentanaJuego(const Mundo& mun, Camara &camara, int argc, char * argv[], const std::string& id):mundo(mun), camara(camara){
	app = Gtk::Application::create(argc, argv, "Megamarta.is.angry" + id);
	darea=new Gtk::DrawingArea;//tengo que hacer estos new después de crear la application porque sino gtkmm chilla
	window= new Gtk::Window;
}

bool VentanaJuego::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	/*
	cr->set_line_width(10.0);
	cr->set_source_rgb(1,1,0);
	cr->move_to(0,0.2);
	cr->move_to(0.1,3);
	cr->stroke();
	* */

	Gtk::Allocation allocation = darea->get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	camara.dibujarEn(cr);
	return true;
}
bool VentanaJuego::on_actualizar_dibujo(){
	//std::cout<<"actualizando dibujjo"<<std::endl;
	darea->queue_draw();
	return true;
}

VentanaJuego::~VentanaJuego(){
	delete darea;
}

Gtk::Window& VentanaJuego::getWindow(){
	return *window;
}
