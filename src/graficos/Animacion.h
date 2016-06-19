#ifndef ANIMACION
#define ANIMACION
#include <list>
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <map>
#include <string>

#define CANTIDADMAXIMACUADROS 100

class Animacion{
public:
	std::string nombre;
	bool loop;
private:
	int cuadro_actual;
	int cantidad_cuadros;
	float segundos_por_cuadro;
	float segundos_desde_cambio;
	std::map<int, Glib::RefPtr<Gdk::Pixbuf> > cargadas;
	public:
	void avanzar(float segundos);
	virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar();
	Animacion(const std::string& nombre,float segundos_por_cuadro, bool loop = true, unsigned int cantidadCuadros = CANTIDADMAXIMACUADROS);
	void reiniciar();
	bool operator==(const Animacion& animacion);
};
#define ANIM_MEGAM_CORRE 		"imagenes/megaman/megaman corriendo/"
#define ANIM_MEGAM_CORRE_DISP 	"imagenes/megaman/megaman corriendo disparando/"
#define ANIM_MEGAM_QUIETO  		"imagenes/megaman/megaman quieto/"
#define ANIM_MEGAM_QUIETO_DISP 	"imagenes/megaman/megaman quieto disparando/"
#define ANIM_MEGAM_SALTA 		"imagenes/megaman/megaman saltando/"
#define ANIM_MEGAM_SALTA_DISP 	"imagenes/megaman/megaman saltando disparando/"
#define ANIM_MEGAM_SUBIENDO 	"imagenes/megaman/megaman subiendo escalera/"
#define ANIM_MEGAM_SUBIENDO_DISP 	"imagenes/megaman/megaman subiendo escalera disparando/"

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
#define ANIM_FONDO "imagenes/fondo/1.png"

#define ANIM_FIREMAN_SALTANDO	"imagenes/megamanrojo/saltando/"
#define ANIM_FIREMAN_CORRIENDO	"imagenes/megamanrojo/corriendo/"

#define ANIM_BOMBMAN_SALTANDO	"imagenes/megamannegro/saltando/"
#define ANIM_BOMBMAN_CORRIENDO	"imagenes/megamannegro/corriendo/"

#define ANIM_SPARKMAN_SALTANDO	"imagenes/megamanamarillo/saltando/"
#define ANIM_SPARKMAN_CORRIENDO	"imagenes/megamanamarillo/corriendo/"

#define ANIM_MAGNETMAN_SALTANDO	"imagenes/megamanblanco/saltando/"
#define ANIM_MAGNETMAN_CORRIENDO "imagenes/megamanblanco/corriendo/"

#define ANIM_RINGMAN_SALTANDO	"imagenes/megamanverde/saltando/"
#define ANIM_RINGMAN_CORRIENDO	"imagenes/megamanverde/corriendo/"

#define ANIM_VIDA "imagenes/vida/"
#define ANIM_PLASMA "imagenes/plasma/"
#define ANIM_ENERGIA "imagenes/energia/"
#define ANIM_DISPARO_PLASMA "imagenes/disparoPlasma/"
#define ANIM_DISPARO_FUEGO "imagenes/disparoFuego/"
#define ANIM_DISPARO_ANILLO "imagenes/disparoAnillo/"
#define ANIM_DISPARO_BOMBA "imagenes/disparoBomba/"
#define ANIM_DISPARO_IMAN "imagenes/disparoIman/"
#define ANIM_DISPARO_CHISPA "imagenes/disparoChispa/"

#define ANIM_PUERTA "imagenes/puerta/"
#define ANIM_PODER "imagenes/poder/1.png"

#define ANIM_PUAS "imagenes/pinches/1.png"

#endif
