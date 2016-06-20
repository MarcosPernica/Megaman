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

void Construccion::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
			     b2Vec2 origen, 
			     real factorAmplificacion)
{
	ImagenEscalada::dibujarEn(cr, origen, factorAmplificacion);
		
}
ArchivoImagen Construccion::a_dibujar()
{
	return ArchivoImagen(nombreImagen());
}

const Rectangulo Construccion::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-obtenerAncho()/2,
			  obtenerPosicion().y-obtenerAlto()/2,
			  obtenerAncho(),
			  obtenerAlto());
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

std::string CuboMadera::nombreImagen()
{
	return "imagenes/cuboMadera/1.png";
};

CuboMetal::CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		     Construccion(ID,
				  mundo,
				  posicion,
				  ancho,
				  alto)
{
}

std::string CuboMetal::nombreImagen()
{
	return "imagenes/cuboMetal/1.png";
};

CuboLadrillo::CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			   Construccion(ID,
				        mundo,
				        posicion,
				        ancho,
				        alto)
{
}

std::string CuboLadrillo::nombreImagen()
{
	return "imagenes/cuboLadrillo/1.png";
};

CuboTierra::CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		       Construccion(ID,
				    mundo,
				    posicion,
				    ancho,
				    alto)
{
}

std::string CuboTierra::nombreImagen()
{
	return "imagenes/cuboTierra/1.png";
};

CuboVacio::CuboVacio(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		     Construccion(ID,
				  mundo,
				  posicion,
				  ancho,
				  alto)
{
}

std::string CuboVacio::nombreImagen()
{
	return "imagenes/vacio.png";
};

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
	       Animado(&animacion),
	       animacion(ANIM_PUERTA,0.1,false, 10),
	       cerrada(false),
	       IDInterno(IDInterno),
	       ancho(ancho),
	       alto(alto)
{
}

void Puerta::actualizar(real deltaT)
{
	/*Solo si esta cerrada hace la animacion.*/
	if(cerrada)
		avanzar(deltaT);
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

std::string Puerta::nombreImagen()
{
	return "imagenes/cuboMetal/1.png";
};

ushort Puerta::tipoCuerpo() const 
{
	return CONSTRUCCIONES;
};

void Puerta::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
		       b2Vec2 origen, 
		       real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Puerta::espejado() const
{
	return false;
};

const Rectangulo Puerta::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ancho/2,
			  obtenerPosicion().y-alto/2,
			  ancho,
			  alto);
}
