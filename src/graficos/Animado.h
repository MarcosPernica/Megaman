#ifndef ANIMADO
#define ANIMADO
#include "Animacion.h"
#include "Imagen.h"
#include <map>
class Animado: public Imagen{
	private:
	Animacion* actual;
	
	public:
	virtual ArchivoImagen a_dibujar();
	Animado(Animacion* inicial);
	void cambiar(Animacion* otra);
	void avanzar(float segundos);
};

#endif
