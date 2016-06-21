#include "Escalera.h"
#include "Definiciones.h"

Escalera::Escalera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real alto) :
		   Construccion(ID, mundo, posicion, ANCHOESCALERA, alto, true)
{
	/*Tope de la escalera.*/
	agregarCuerpoInmaterial(ANCHOESCALERA, 
				ALTODETECTORESCALERA, 
				b2Vec2(0,-alto/2-ALTODETECTORESCALERA/2), 
				DETECTORTOPEESCALERA,
				CONSTRUCCIONES, 
				PERSONAJES | POWERUPS | ENEMIGOS | JUMPBOX,
				false);
}

ushort Escalera::tipoCuerpo() const
{
	return ESCALERAS;
}

#ifndef compiling_server
std::string Escalera::nombreImagen()
{
	return "imagenes/escalera/1.png";
};
#endif
