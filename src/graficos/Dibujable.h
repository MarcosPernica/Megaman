#ifndef DIBUJABLE
#define DIBUJABLE
#include <cairomm/context.h>
class Dibujable{
	public:
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, const int cam_x, const int cam_y) const = 0;
};

#endif
