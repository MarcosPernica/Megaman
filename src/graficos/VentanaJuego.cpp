#include "VentanaJuego.h"
#include <cairo.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

//-------------
#include <cairomm/context.h>
//#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>
//--------------------
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

VentanaJuego::VentanaJuego(int argc, char * argv[], const std::string& id){
	app = Gtk::Application::create(argc, argv, "Megamarta.is.angry" + id);
	darea=new Gtk::DrawingArea;//tengo que hacer estos new después de crear la application porque sino gtkmm chilla
	window= new Gtk::Window;
	camara = NULL;//esto es por lo mismo aunque parezca loco!
}

bool VentanaJuego::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

	Gtk::Allocation allocation = darea->get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	/*
	//Cairo::RefPtr<Cairo::Context> cr2 = new Cairo::Context(cairo_create(cr->cobj()));
	//------------------cr2--------------
	cr->save();
	cr->scale(3,3);
	//std::cout<<"El ancho de la ventana es "<<width<<std::endl;
	//std::cout<<"El alto de la ventana es "<<height<<std::endl;
	Glib::RefPtr<Gdk::Pixbuf> imagen_prueba = 
						Gdk::Pixbuf::create_from_file("imagenes/spritesheet.png");
						
	Gdk::Cairo::set_source_pixbuf(cr, 
						imagen_prueba,
						0 , 
						0);
	
	cr->paint();
	cr->restore();
	//-----------fin de cr2---------------
	*/
	if(camara!=NULL){
		camara->dibujarEn(cr);
	}
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

void VentanaJuego::ejecutar(){
	start();
	join();
}

void VentanaJuego::setCamara(Camara* camara){
	this->camara = camara;
}
