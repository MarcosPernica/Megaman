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

bool Disparo::lanzable()
{
	return false;
}

ushort Disparo::tipoCuerpo() const
{
	return DISPAROS;
}

bool Disparo::megamanLoDisparo() const
{
	return disparoMegaman;
}

Disparo::Disparo(uint ID, Mundo &mundo,
				 uint dano,
				 real ancho,
				 real alto,
				 real masa,
				 const b2Vec2 &posicion,
				 bool gravitacional,
				 const b2Vec2 &velocidad,
				 bool disparoMegaman) :
			     	 Cuerpo(ID, 
						mundo,
						ancho,
						alto,
						masa,
						DISPAROS,
						CONSTRUCCIONES | PERSONAJES | ENEMIGOS,
						posicion,
						false,
						gravitacional,
						velocidad),
				dano(dano),
				 disparoMegaman(disparoMegaman)
{
}

bool Disparo::perecedero()
{
	return true;
}

bool Disparo::danar(Entidad *entidad)
{
	entidad->atacado(dano);
	return true;
}

Bomba::Bomba(uint ID, 
		 Mundo & mundo, 
	         const b2Vec2 & posicion,
	         const b2Vec2 & velocidad) :
			 Disparo(ID, 
				 mundo,
				 DANOBOMBA,
				ANCHOSPRITEBOMBA,
				 ALTOSPRITEBOMBA,
				    MASABOMBA,
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

bool Bomba::perecedero()
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
	return new Bomba(ID, obtenerMundo(), posicion, velocidad);
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
			   const b2Vec2 & posicion,
			   const b2Vec2 & velocidad) :
			   Disparo(ID,
					   mundo,
					   DANOPLASMA,
					   ANCHOSPRITEPLASMA,
					   ALTOSPRITEPLASMA,
					   MASAPLASMA,
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
	return new Plasma(ID, obtenerMundo(), posicion, velocidad);
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
	Plasma* p = new Plasma(sn.getID(), mundo);
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
	Bomba* p = new Bomba(sn.getID(), mundo);
	p->setStateFromSnapshot(sn);
	return p;
}
