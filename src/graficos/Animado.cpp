#include "Animado.h"
Glib::RefPtr<Gdk::Pixbuf> Animado::a_dibujar(){
	return actual.a_dibujar();
}
Animado::Animado(Animacion& inicial):actual(inicial){}

void Animado::cambiar(Animacion& otra){
	/*Cambia solo si son diferentes*/
	if(!(actual == otra))
	{
		actual = otra;
		actual.reiniciar();
	}
}
void Animado::avanzar(float segundos){
	actual.avanzar(segundos);
}
