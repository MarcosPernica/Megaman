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

#ifndef compiling_server
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
#endif


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

#ifndef compiling_server
std::string CuboMadera::nombreImagen()
{
	return "imagenes/cuboMadera/1.png";
};
#endif

CuboMetal::CuboMetal(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		     Construccion(ID,
				  mundo,
				  posicion,
				  ancho,
				  alto)
{
}

#ifndef compiling_server
std::string CuboMetal::nombreImagen()
{
	return "imagenes/cuboMetal/1.png";
};
#endif

CuboLadrillo::CuboLadrillo(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
			   Construccion(ID,
				        mundo,
				        posicion,
				        ancho,
				        alto)
{
}

#ifndef compiling_server
std::string CuboLadrillo::nombreImagen()
{
	return "imagenes/cuboLadrillo/1.png";
};
#endif

CuboTierra::CuboTierra(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		       Construccion(ID,
				    mundo,
				    posicion,
				    ancho,
				    alto)
{
}

#ifndef compiling_server
std::string CuboTierra::nombreImagen()
{
	return "imagenes/cuboTierra/1.png";
};
#endif

CuboVacio::CuboVacio(uint ID, Mundo &mundo, const b2Vec2 &posicion, real ancho, real alto):
		     Construccion(ID,
				  mundo,
				  posicion,
				  ancho,
				  alto)
{
}

#ifndef compiling_server
std::string CuboVacio::nombreImagen()
{
	return "imagenes/vacio.png";
};
#endif

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
		#ifndef compiling_server
	       Animado(&animacion),
	       animacion(ANIM_PUERTA,0.1,false, 10),
		#endif
	       cerrada(false),
	       IDInterno(IDInterno),
	       ancho(ancho),
	       alto(alto)
{
}

void Puerta::actualizar(real deltaT)
{
	#ifndef compiling_server
	/*Solo si esta cerrada hace la animacion.*/
	if(cerrada)
		avanzar(deltaT);
	#endif
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

#ifndef compiling_server
std::string Puerta::nombreImagen()
{
	return "imagenes/cuboMetal/1.png";
};
#endif

ushort Puerta::tipoCuerpo() const 
{
	return CONSTRUCCIONES;
};

#ifndef compiling_server
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
#endif
