#include "Dibujador.h"
Dibujador::Dibujador(const Mundo& mun): mundo(mun){}
//Dibujador::Dibujador(){}
void Dibujador::dibujar(const Cairo::RefPtr<Cairo::Context>& cr,
			 const int width, 
			 const int height) const{
	std::list<Dibujable*> dibujables = mundo.obtenerDibujables();
	std::list<Dibujable*>::iterator it;
	for(it = dibujables.begin(); it!= dibujables.end(); ++it){
		(*it)->dibujarEn(cr, 0,0);
	}
}
