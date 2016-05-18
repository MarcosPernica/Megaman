#ifndef DIBUJABLE
#define DIBUJABLE
#include <cairomm/context.h>

/*Mira aca abajo, esta como escalo el mundo a pixeles. Se lee como 38px/m y estaba basado en el ratio original de megaman*/

#define FACTORAMPLIFICACIONVENTANA 2
#define FACTORCONVERSIONMPX 38*FACTORAMPLIFICACIONVENTANA

class Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const = 0;
};

#endif
