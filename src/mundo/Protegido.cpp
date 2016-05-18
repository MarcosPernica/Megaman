#include "Protegido.h"

Protegido::Protegido(uint ID,
			         Mundo & mundo,
					 real ancho,
					 real alto,
			         uint energiaMaxima,
	                 uint escudo, 
					 real masa,
					 ushort categoria,
				     ushort colisionaCon,
					 const b2Vec2 & posicion,
					 bool rotable,
				     bool gravitacional,
					 const b2Vec2 & velocidad,
					 Orientaciones orientacion) :
					 Entidad(ID,
							mundo,
							 ancho,
							 alto,
							 energiaMaxima,
							 masa,
							 categoria,
							 colisionaCon,
							 posicion,
							 rotable,
							 gravitacional,
							 velocidad,
							 orientacion)
{
}

void Protegido::atacado(uint danio)
{
	if (!cubierto || escudo < danio)
		Entidad::atacado(danio - escudo*cubierto);
}

void Protegido::cubrirse()
{
	cubierto = true;
}

void Protegido::exponerse()
{
	cubierto = false;
}

bool Protegido::estaCubierto()
{
	return cubierto;
}
