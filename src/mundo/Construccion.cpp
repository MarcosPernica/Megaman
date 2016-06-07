#include "Construccion.h"
#include <iostream>
Construccion::Construccion(uint ID,
						   Mundo &mundo, 
						   const b2Vec2 &posicion, 
						   real ancho, 
						   real alto,
						   bool fantasma) :
						   Cuerpo(ID,
							  mundo,
							  ancho,
							  alto,
							  MASAINFINITA,	
							  CONSTRUCCIONES,
							  (!fantasma) ? (PERSONAJES | POWERUPS | ENEMIGOS | DISPAROS | JUMPBOX | LEFTBOX | RIGHTBOX) : (PERSONAJES),
							  posicion,
							  false,
							  false,
							  b2Vec2_zero,
							  izquierda,
							  fantasma)
{
}

ushort Construccion::tipoCuerpo() const
{
	return CONSTRUCCIONES;
}

CuboMadera::CuboMadera(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto)
{
}

CuboMetal::CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto)
{
}

CuboLadrillo::CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto)
{
}

CuboTierra::CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto)
{
}

Puerta::Puerta(uint ID, uint IDInterno, Mundo &mundo, real ancho, real alto, const b2Vec2 &posicion):
			Cuerpo(ID,
							  mundo,
							  ancho,
							  alto,
							  MASAINFINITA,	
							  CONSTRUCCIONES,
							  PERSONAJES | POWERUPS | ENEMIGOS | DISPAROS | JUMPBOX | LEFTBOX | RIGHTBOX,
							  posicion,
							  false,
							  false,
							  b2Vec2_zero,
							  izquierda,
							  true),
							  cerrada(false),
							  IDInterno(IDInterno)
{
}

uint Puerta::obtenerIDInterno()
{
	return IDInterno;
}

void Puerta::cerrar()
{
	std::cout << "Cerrada" << std::endl;
	cerrada = true;
	materializar();	
}

bool Puerta::estaCerrada()
{
	return cerrada;
}
