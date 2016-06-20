#ifndef DAREASPLASH
#define DAREASPLASH
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <cairo.h>
class DareaSplash : public Gtk::DrawingArea{
	private:
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;// = Gdk::Pixbuf::create_from_file("imagenes/principal.png");
	public:
	DareaSplash();
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};
#endif
