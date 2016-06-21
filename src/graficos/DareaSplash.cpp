#include "DareaSplash.h"
#include <gdkmm/general.h> // set_source_pixbuf()
#include <iostream>
#include "Dibujable.h"
DareaSplash::DareaSplash(){
	pixbuf = Gdk::Pixbuf::create_from_file("imagenes/principal.png");
	set_size_request(800,600);
}

bool DareaSplash::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Dibujable::dibujarImagen(cr, 
				  b2Vec2(0,0),
				  1, 
				  b2Vec2(0,0),
				  800,
				  600,
				  pixbuf,
				  false);
	return true;
}
