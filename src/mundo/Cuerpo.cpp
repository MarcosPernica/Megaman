#include "Cuerpo.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include <iostream>
const b2Vec2 Cuerpo::versorIzquierda(-1, 0);
const b2Vec2 Cuerpo::versorDerecha(1, 0);

Cuerpo::Cuerpo(uint ID,
			   Mundo &mundo,
			   real ancho, 
			   real alto,
			   real masa,
			   ushort categoria,
			   ushort colisionaCon, 
			   const b2Vec2 & posicion,
		       bool rotable,
			   bool gravitacional,
		       const b2Vec2 & velocidad,
			   Orientaciones orientacion,
			   bool fantasma) :
			   orientacion(orientacion),
			   mundo(mundo),
			   Snapshotable(ID),
			   ancho(ancho),
			   alto(alto),
			   detectorSuelo(false)
{
	b2BodyDef defCuerpo;
	b2PolygonShape cajaColision;
	b2FixtureDef unionCuerpo;

	/*Si la masa es infinita se crea de manera que no se calculen las fisicas.*/
	if (masa != MASAINFINITA)
		defCuerpo.type = b2_dynamicBody;
	else
		defCuerpo.type = b2_staticBody;

	defCuerpo.fixedRotation = !rotable;
	defCuerpo.position = posicion;
	defCuerpo.linearVelocity = velocidad;

	if (!gravitacional)
		defCuerpo.gravityScale = 0;

	cuerpo = mundo.obtenerMundo().CreateBody(&defCuerpo);

	cajaColision.SetAsBox(ancho / 2, alto / 2);
	
	if(masa != MASAINFINITA)
		unionCuerpo.density = masa / (ancho*alto);

	unionCuerpo.shape = &cajaColision;
	unionCuerpo.filter.categoryBits = categoria;
	unionCuerpo.filter.maskBits = colisionaCon;
	unionCuerpo.isSensor = fantasma;

	datos.push_back(new DatosColisionCuerpo(this,CUERPOPRINCIPAL,Rectangulo(posicion.x,posicion.y,ancho,alto)));

	unionCuerpo.userData = datos.at(0);

	cuerpo->CreateFixture(&unionCuerpo);
}

Cuerpo::~Cuerpo()
{
	for (b2Fixture* f = cuerpo->GetFixtureList(); f; f = f->GetNext()) 
	{
		delete f->GetUserData();	
		f->SetUserData(NULL);
	}

	mundo.obtenerMundo().DestroyBody(cuerpo);

	datos.clear();
}

Mundo &Cuerpo::obtenerMundo()
{
	return mundo;
}

const b2Vec2 & Cuerpo::obtenerPosicion() const
{
	return cuerpo->GetWorldCenter();
}

const b2Vec2 & Cuerpo::obtenerVelocidad() const
{
	return cuerpo->GetLinearVelocity();
}

Orientaciones Cuerpo::obtenerOrientacion() const
{
	return orientacion;
}

Rectangulo Cuerpo::obtenerCajaMagnificada(uint magnificador) const
{
	const b2Vec2 centro = obtenerPosicion();

	return Rectangulo(centro.x - ((ancho/2)*magnificador),
		    centro.y - ((alto/2)*magnificador),
 		    ancho*magnificador,
		    alto*magnificador);
}

void Cuerpo::modificarVelocidad(const b2Vec2 & velocidad)
{
	cuerpo->SetLinearVelocity(velocidad);
}

void Cuerpo::modificarPosicion(const b2Vec2 & posicion)
{
	cuerpo->SetTransform(posicion,0);
}

void Cuerpo::modificarOrientacion(Orientaciones orientacion)
{
	this->orientacion = orientacion;
}

void Cuerpo::aplicarImpulso(const b2Vec2 & impulso)
{
	cuerpo->ApplyLinearImpulse(impulso,cuerpo->GetWorldCenter(),false);
}

void Cuerpo::gravitar()
{
	cuerpo->SetGravityScale(1);
}

void Cuerpo::ingravitar()
{
	cuerpo->SetGravityScale(0);
}

void Cuerpo::agregarCuerpoInmaterial(real ancho, 
			     real alto,
			     b2Vec2 posicion, 
			     uint identificador,
			     ushort categoria,
			     ushort colisionaCon)
{
		b2PolygonShape cajita;
		cajita.SetAsBox(ancho/2, alto/2, posicion, 0);
		b2FixtureDef unionCajita;
		unionCajita.isSensor = true;

		unionCajita.filter.categoryBits = categoria;
		unionCajita.filter.maskBits = colisionaCon;

		datos.push_back(new DatosColisionCuerpo(this,identificador,Rectangulo(posicion.x,posicion.y,ancho,alto)));

		unionCajita.userData = datos.at(datos.size()-1);
		unionCajita.shape = &cajita;

		cuerpo->CreateFixture(&unionCajita);	
}

const b2Vec2 & Cuerpo::orientacionAVector(Orientaciones orientacion)
{
	if (orientacion == derecha)
		return versorDerecha;
	else
		return versorIzquierda;
}

const std::list<Rectangulo> Cuerpo::obtenerRepresentacion() const{
	std::list<Rectangulo> rectangulos;

	rectangulos.push_back(obtenerCajaMagnificada(1));

	for(uint i=1;i<datos.size();i++)
	{
		b2Vec2 topLeftCuerpo = datos.at(i)->caja.topLeft();
		b2Vec2 topLeftMundo = topLeftCuerpo + obtenerPosicion();
		
		rectangulos.push_back(Rectangulo(topLeftMundo.x,topLeftMundo.y,datos.at(i)->caja.obtenerAncho(),datos.at(i)->caja.obtenerAlto()));		
	}


	return rectangulos;
}

#define PROP_POS_X "posX"
#define PROP_POS_Y "posY"
#define PROP_VEL_X "velX"
#define PROP_VEL_Y "velY"
#define PROP_ORIENTACION "orientacion"

Snapshot Cuerpo::getSnapshot(){
	Snapshot sn(obtenerID());
	sn.agregarPropiedad(PROP_POS_X, obtenerPosicion().x*1000);
	sn.agregarPropiedad(PROP_POS_Y, obtenerPosicion().y*1000);
	sn.agregarPropiedad(PROP_VEL_X, obtenerVelocidad().x*1000);
	sn.agregarPropiedad(PROP_VEL_Y, obtenerVelocidad().y*1000);
	sn.agregarPropiedad(PROP_ORIENTACION, (int)obtenerOrientacion());
	return sn;
}
void Cuerpo::setStateFromSnapshot(const Snapshot& sn){
	real px = (real)sn.obtenerPropiedad(PROP_POS_X)/1000;
	real py = (real)sn.obtenerPropiedad(PROP_POS_Y)/1000;
	
	real vx = (real)sn.obtenerPropiedad(PROP_VEL_X)/1000;
	real vy = (real)sn.obtenerPropiedad(PROP_VEL_Y)/1000;
	
	Orientaciones o = (Orientaciones) sn.obtenerPropiedad(PROP_ORIENTACION);
	
	modificarPosicion(b2Vec2(px,py));
	modificarVelocidad(b2Vec2(vx,vy));
	modificarOrientacion(o);
}
