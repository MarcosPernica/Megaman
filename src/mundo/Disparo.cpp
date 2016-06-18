#include "Disparo.h"
#include "Mundo.h"
#include <list>
#include "Entidad.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "../common/Rectangulo.h"
#include "../net/snapshots/Snapshot.h"

void Disparo::actualizar(real DeltaT)
{
}

void Disparo::alColisionar(Cuerpo *cuerpo)
{
	if(cuerpo->tipoCuerpo() == PERSONAJES || cuerpo->tipoCuerpo() == ENEMIGOS)
		((Entidad*)cuerpo)->atacado(dano, this);
	eliminarse(obtenerMundo());
}

void Disparo::eliminarse(Mundo& de)
{
	de.eliminar(this);
}

bool Disparo::lanzable()
{
	return false;
}

ushort Disparo::tipoCuerpo() const
{
	return DISPAROS;
}

ushort Disparo::obtenerCategoriaTarget()
{
	return categoriaTarget;
}

Disparo::Disparo(uint ID, Mundo &mundo,
		 uint dano,
		 real ancho,
		 real alto,
		 real masa,
		 ushort categoriaTarget, 
		 const b2Vec2 &posicion,
		 bool gravitacional,
		 const b2Vec2 &velocidad) :
	     	 Cuerpo(ID, 
			mundo,
			ancho,
			alto,
			masa,
			DISPAROS,
			CONSTRUCCIONES | categoriaTarget,
			posicion,
			false,
			gravitacional,
			velocidad),
			dano(dano),
		        categoriaTarget(categoriaTarget)
{
}

Bomba::Bomba(uint ID, 
	     Mundo & mundo, 
	     ushort categoriaTarget,
             const b2Vec2 & posicion,
             const b2Vec2 & velocidad) :
	     Disparo(ID, 
		     mundo,
		     DANOBOMBA,
		     ANCHOSPRITEBOMBA,
		     ALTOSPRITEBOMBA,
		     MASABOMBA,
		     categoriaTarget,
		     posicion,
	             true,
		     velocidad),
	    Animado(&animacion),
	    animacion(ANIM_DISPARO_BOMBA,0.5),
	    tiempoTotal(TIEMPOEXPLOSIONBOMBA)
			
{
}

ushort Bomba::tipoDisparo() const
{
	return BOMBA;
}

void Bomba::actualizar(real deltaT)
{
	avanzar(deltaT);

	tiempoTotal -= deltaT;

	if (tiempoTotal <= 0)
		explotar();
}

uint Bomba::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADBOMBA;
}

bool Bomba::lanzable()
{
	return true;
}

Disparo * Bomba::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Bomba(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Bomba::explotar()
{
	b2AABB consulta;
	Rectangulo rect = obtenerCajaMagnificada(RADIOEXPLOSION);

	consulta.upperBound = rect.rightBottom();
	consulta.lowerBound = rect.topLeft();

	obtenerMundo().danarZona(consulta, DANOBOMBA, this);
	obtenerMundo().eliminar(this);
}


void Bomba::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
                      b2Vec2 origen, 
                      real factorAmplificacion)
{
	Imagen::dibujarEn(cr,origen,factorAmplificacion);
}

bool Bomba::espejado() const
{
	return false;
};

const Rectangulo Bomba::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITEBOMBA/2,
			  obtenerPosicion().y-ALTOSPRITEBOMBA/2,
			  ANCHOSPRITEBOMBA,
			  ALTOSPRITEBOMBA);
}

Plasma::Plasma(uint ID, 
	       Mundo & mundo,
	       ushort categoriaTarget,
	       const b2Vec2 & posicion,
	       const b2Vec2 & velocidad) :
	       Disparo(ID,
		       mundo,
		       DANOPLASMA,
		       ANCHOSPRITEPLASMA,
		       ALTOSPRITEPLASMA,
		       MASAPLASMA,
		       categoriaTarget,
		       posicion,
		       false,
		       velocidad),
		Animado(&animacion),		
		animacion(ANIM_DISPARO_PLASMA,0.1)
			
{
}

ushort Plasma::tipoDisparo() const
{
	return PLASMA;
}

uint Plasma::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADPLASMA;
}

Disparo * Plasma::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Plasma(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Plasma::actualizar(real deltaT)
{
	avanzar(deltaT);
};

void Plasma::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
                       b2Vec2 origen, 
                       real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Plasma::espejado() const
{
	return obtenerVelocidad().x < 0;
}

const Rectangulo Plasma::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITEPLASMA/2,
			  obtenerPosicion().y-ALTOSPRITEPLASMA/2,
			  ANCHOSPRITEPLASMA,
			  ALTOSPRITEPLASMA);
}


Chispa::Chispa(uint ID, 
	       Mundo & mundo,
	       ushort categoriaTarget,
	       const b2Vec2 & posicion,
	       const b2Vec2 & velocidad) :
	       Disparo(ID,
		       mundo,
		       DANOCHISPA,
		       ANCHOSPRITECHISPA,
		       ALTOSPRITECHISPA,
		       MASACHISPA,
		       categoriaTarget,
		       posicion,
		       false,
		       velocidad),
	       Animado(&animacion),
	       animacion(ANIM_DISPARO_CHISPA,0.5)
{
}

ushort Chispa::tipoDisparo() const
{
	return CHISPA;
}

uint Chispa::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADCHISPA;
}

Disparo * Chispa::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Chispa(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Chispa::actualizar(real deltaT)
{
	avanzar(deltaT);
};

void Chispa::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr,
		       b2Vec2 origen, 
		       real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Chispa::espejado() const
{
	return false;
};

const Rectangulo Chispa::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITECHISPA/2,
			  obtenerPosicion().y-ALTOSPRITECHISPA/2,
			  ANCHOSPRITECHISPA,
			  ALTOSPRITECHISPA);
}


Anillo::Anillo(uint ID, 
	       Mundo & mundo,
	       ushort categoriaTarget,
	       const b2Vec2 & posicion,
	       const b2Vec2 & velocidad) :
	       Disparo(ID,
		       mundo,
		       DANOANILLO,
		       ANCHOSPRITEANILLO,
		       ALTOSPRITEANILLO,
		       MASAANILLO,
		       categoriaTarget,
		       posicion,
		       false,
	               velocidad),
		Animado(&animacion),
		animacion(ANIM_DISPARO_ANILLO,1),
		tiempo(TIEMPOANILLO)
{
	modificarRestitucion(1);
}

ushort Anillo::tipoDisparo() const
{
	return ANILLO;
}

void Anillo::alColisionar(Cuerpo *cuerpo)
{
	if(cuerpo->tipoCuerpo() == PERSONAJES || cuerpo->tipoCuerpo() == ENEMIGOS)
		((Entidad*)cuerpo)->atacado(DANOANILLO, this);
}

void Anillo::actualizar(real deltaT)
{
	avanzar(deltaT);
	tiempo -= deltaT;	

	if(tiempo <= 0)
		eliminarse(obtenerMundo());
}

uint Anillo::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADANILLO;
}

Disparo * Anillo::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Anillo(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Anillo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
		       b2Vec2 origen, 
		       real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Anillo::espejado() const
{
	return false;
};

const Rectangulo Anillo::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITEANILLO/2,
			  obtenerPosicion().y-ALTOSPRITEANILLO/2,
			  ANCHOSPRITEANILLO,
			  ALTOSPRITEANILLO);
}

Fuego::Fuego(uint ID, 
	     Mundo & mundo,
	     ushort categoriaTarget,
	     const b2Vec2 & posicion,
	     const b2Vec2 & velocidad) :
	     Disparo(ID,
		     mundo,
		     DANOFUEGO,
		     ANCHOSPRITEFUEGO,
		     ALTOSPRITEFUEGO,
		     MASAFUEGO,
		     categoriaTarget,
		     posicion,
		     false,
		     velocidad),
	     Animado(&animacion),
	     animacion(ANIM_DISPARO_FUEGO,0.25)
				
{
}

ushort Fuego::tipoDisparo() const
{
	return FUEGO;
}

uint Fuego::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADFUEGO;
}

Disparo * Fuego::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Fuego(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Fuego::actualizar(real deltaT)
{
	avanzar(deltaT);
};

void Fuego::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr,
		      b2Vec2 origen, 
		      real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Fuego::espejado() const
{
	return obtenerVelocidad().x < 0;
};

const Rectangulo Fuego::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITEFUEGO/2,
			  obtenerPosicion().y-ALTOSPRITEFUEGO/2,
			  ANCHOSPRITEFUEGO,
			  ALTOSPRITEFUEGO);
}


Iman::Iman(uint ID, 
	   Mundo & mundo,
	   ushort categoriaTarget,
	   const b2Vec2 & posicion,
	   const b2Vec2 & velocidad) :
	   Disparo(ID,
		   mundo,
		   DANOIMAN,
		   ANCHOSPRITEIMAN,
		   ALTOSPRITEIMAN,
		   MASAIMAN,
		   categoriaTarget,
		   posicion,
		   false,
                   velocidad),
	   Animado(&animacion),
	   animacion(ANIM_DISPARO_IMAN,0.5),
	   target(NULL)
{
}

ushort Iman::tipoDisparo() const
{
	return IMAN;
}

void Iman::actualizar(real deltaT)
{
	/*Avanza la animacion*/
	avanzar(deltaT);

	/*Selecciona una target si no tiene y lo sigue.*/
	if(!target || !obtenerMundo().existeEnemigo(IDTarget) || !obtenerMundo().existeMegaman(IDTarget))
	{
		if(obtenerCategoriaTarget() == AURAENEMIGOS)
			target = (Entidad*)obtenerMundo().obtenerEnemigoCercano(obtenerPosicion());
		else
			target = (Entidad*)obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
		IDTarget = target->obtenerID();
	}
	
	b2Vec2 direccion = target->obtenerPosicion() - obtenerPosicion();
	direccion.Normalize();

	aplicarImpulso(IMPULSOIMAN*direccion);		
}

uint Iman::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADIMAN;
}

Disparo * Iman::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Iman(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
}

void Iman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, 
		     b2Vec2 origen, 
		     real factorAmplificacion)
{
	Imagen::dibujarEn(cr, origen, factorAmplificacion);
}

bool Iman::espejado() const
{
	return false;
};

const Rectangulo Iman::obtenerRepresentacion() const
{
	return Rectangulo(obtenerPosicion().x-ANCHOSPRITEIMAN/2,
			  obtenerPosicion().y-ALTOSPRITEIMAN/2,
			  ANCHOSPRITEIMAN,
			  ALTOSPRITEIMAN);
}

//------------------------------snapshotable de Disparo------------------//
void Disparo::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(dano);
	SN_AGREGAR_PROPIEDAD(categoriaTarget);
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void Disparo::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(dano);
	SN_OBTENER_PROPIEDAD(categoriaTarget);
	Cuerpo::setStateFromSnapshot(sn);
}

//////////-----------------------snapshotable de bomba--------------------//
void Bomba::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(tiempoTotal);
	Disparo::agregarPropiedadesASnapshot(sn);
}
void Bomba::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(tiempoTotal);
	Disparo::setStateFromSnapshot(sn);
}
//---------------------------snapshotable de anillo--------------------
void Anillo::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(tiempo);
	Disparo::agregarPropiedadesASnapshot(sn);
}
void Anillo::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(tiempo);
	Disparo::setStateFromSnapshot(sn);
}
