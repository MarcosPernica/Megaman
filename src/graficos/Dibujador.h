#ifndef DIBUJADOR
#define DIBUJADOR
#include <cairo.h>
#include <cairomm/context.h>
#include "../mundo/Mundo.h"
class Dibujador{
	private:
	const Mundo& mundo;
	
	public:
	Dibujador(const Mundo& mun);
	//Dibujador();
	void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height) const;
};
#endif
