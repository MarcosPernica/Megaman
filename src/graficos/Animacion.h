#ifndef ANIMACION
#define ANIMACION
#include <list>
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <map>
#include <string>

class Animacion{
	private:
	std::string nombre;
	int cuadro_actual;
	int cantidad_cuadros;
	float segundos_por_cuadro;
	float segundos_desde_cambio;
	std::map<int, Glib::RefPtr<Gdk::Pixbuf> > cargadas;
	public:
	void avanzar(float segundos);
	virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar();
	Animacion(const std::string& nombre,float segundos_por_cuadro);
	void reiniciar();
	bool operator==(const Animacion& animacion);
};
#define ANIM_MEGAM_CORRE 		"imagenes/megaman/megaman corriendo/"
#define ANIM_MEGAM_CORRE_DISP 	"imagenes/megaman/megaman corriendo disparando/"
#define ANIM_MEGAM_QUIETO  		"imagenes/megaman/megaman quieto/"
#define ANIM_MEGAM_QUIETO_DISP 	"imagenes/megaman/megaman quieto disparando/"
#define ANIM_MEGAM_SALTA 		"imagenes/megaman/megaman saltando/"
#define ANIM_MEGAM_SALTA_DISP 	"imagenes/megaman/megaman saltando disparando/"

#define ANIM_MET_PROTEGIDO	"imagenes/met/protegido/"
#define ANIM_MET_DISPARANDO	"imagenes/met/atacando/"

#define ANIM_BUMBY_VOLANDO	"imagenes/bumby/volando/"

#define ANIM_SNIPER_PROTEGIDO	"imagenes/sniper/cubierto/"
#define ANIM_SNIPER_DISPARANDO	"imagenes/sniper/descubierto/"

#define ANIM_JSNIPER_PROTEGIDO	"imagenes/jumpingsniper/cubierto/"
#define ANIM_JSNIPER_DISPARANDO	"imagenes/jumpingsniper/descubierto/"
#define ANIM_JSNIPER_SALTANDO	"imagenes/jumpingsniper/saltando/"

#define ANIM_CUBOMADERA	"imagenes/cuboMadera/"
#define ANIM_CUBOTIERRA "imagenes/cuboTierra/"
#define ANIM_CUBOMETAL "imagenes/cuboMetal/"
#define ANIM_CUBOLADRILLO "imagenes/cuboLadrillo/"

#endif