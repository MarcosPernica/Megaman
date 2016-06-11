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
				     alto),
			textura(NULL)
{
}

CuboMetal::CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto),
				textura(ANIM_CUBOMETAL,1),
				Animado(textura)
{
}

CuboLadrillo::CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto),
				textura(ANIM_CUBOLADRILLO,1),
				Animado(textura)
{
}

CuboTierra::CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			Construccion(ID,
				     mundo,
				     posicion,
				     ancho,
				     alto),
				textura(ANIM_CUBOTIERRA,1),
				Animado(textura)
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
							  IDInterno(IDInterno),
						textura(ANIM_CUBOMETAL,0.1),
						Animado(textura)
{
}

uint Puerta::obtenerIDInterno()
{
	return IDInterno;
}

void Puerta::cerrar()
{
	cerrada = true;
	materializar();	
}

bool Puerta::estaCerrada()
{
	return cerrada;
}
