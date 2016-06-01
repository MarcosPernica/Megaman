#include "Disparo.h"
#include "Mundo.h"
#include <list>
#include "Entidad.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "../common/Rectangulo.h"

void Disparo::actualizar(real DeltaT)
{
}

void Disparo::alColisionar(Cuerpo *cuerpo)
{
	if(cuerpo->tipoCuerpo() == PERSONAJES || cuerpo->tipoCuerpo() == ENEMIGOS)
		((Entidad*)cuerpo)->atacado(dano);
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

bool Disparo::danar(Entidad *entidad)
{
	entidad->atacado(dano);
	return true;
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
			tiempoTotal(TIEMPOEXPLOSIONBOMBA)
{
}

bool Bomba::danar(Entidad * entidad)
{
	return false;
}

void Bomba::actualizar(real deltaT)
{
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

	obtenerMundo().danarZona(consulta, DANOBOMBA);
	obtenerMundo().eliminar(this);
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
		               velocidad)
{
}

uint Plasma::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADPLASMA;
}

Disparo * Plasma::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Plasma(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
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
		               velocidad)
{
}

uint Chispa::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADCHISPA;
}

Disparo * Chispa::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Chispa(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
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
			       tiempo(TIEMPOANILLO)
{
	modificarRestitucion(1);
}

void Anillo::alColisionar(Cuerpo *cuerpo)
{
	if(cuerpo->tipoCuerpo() == PERSONAJES || cuerpo->tipoCuerpo() == ENEMIGOS)
		danar((Entidad*)cuerpo);
}

void Anillo::actualizar(real deltaT)
{
	tiempo -= deltaT;
	aplicarImpulso(b2Vec2(0,-0.2));

	if(deltaT <= 0)
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
		               velocidad)
{
}

uint Fuego::obtenerMultiplicadorVelocidad() const
{
	return MULTIPLICADORVELOCIDADFUEGO;
}

Disparo * Fuego::nuevo(uint ID, const b2Vec2 & posicion, const b2Vec2 & velocidad)
{
	return new Fuego(ID, obtenerMundo(), obtenerCategoriaTarget(), posicion, velocidad);
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
				target(NULL)
{
}

void Iman::actualizar(real deltaT)
{
	if(!target || target->estaMuerta())
	{
		if(obtenerCategoriaTarget() == ENEMIGOS)
			target = (Entidad*)obtenerMundo().obtenerEnemigoCercano(obtenerPosicion());
		else
			target = (Entidad*)obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
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

//////////---------------------snapshotable de plasma---------------------//
void Plasma::agregarPropiedadesASnapshot(Snapshot& sn){
	//yo
	Disparo::agregarPropiedadesASnapshot(sn);
}
void Plasma::setStateFromSnapshot(const Snapshot& sn){
	//yo
	Disparo::setStateFromSnapshot(sn);
}
Plasma* Plasma::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Plasma* p = new Plasma(sn.getID(), mundo, PERSONAJES /*Puse PERSONAJES pero esta mal, hay que snapshotear esto tambien y ponerlo bien.*/);
	p->setStateFromSnapshot(sn);
	return p;
}

//////////-----------------------snapshotable de bomba--------------------//
#define PROP_TIEMPOTOTAL	"tiempo_total"
void Bomba::agregarPropiedadesASnapshot(Snapshot& sn){
	sn.agregarPropiedad(PROP_TIEMPOTOTAL, (int)(tiempoTotal*1000));
	Disparo::agregarPropiedadesASnapshot(sn);
}
void Bomba::setStateFromSnapshot(const Snapshot& sn){
	tiempoTotal = (real)sn.obtenerPropiedad(PROP_TIEMPOTOTAL)/1000;
	Disparo::setStateFromSnapshot(sn);
}
Bomba* Bomba::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Bomba* p = new Bomba(sn.getID(), mundo, PERSONAJES /*Puse PERSONAJES pero esta mal, hay que snapshotear esto tambien y ponerlo bien.*/);
	p->setStateFromSnapshot(sn);
	return p;
}
