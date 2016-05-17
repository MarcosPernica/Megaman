#include "Cuerpo.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
const b2Vec2 Cuerpo::versorIzquierda(-1, 0);
const b2Vec2 Cuerpo::versorDerecha(1, 0);

Cuerpo::Cuerpo(Mundo &mundo,
			   real ancho, 
			   real alto,
			   real masa,
			   ushort categoria,
			   ushort colisionaCon, 
			   const b2Vec2 & posicion,
		       bool rotable,
			   bool gravitacional,
		       const b2Vec2 & velocidad,
			   Orientaciones orientacion) :
			   orientacion(orientacion),
			   mundo(mundo),
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
	
	cajaColision.SetAsBox(ancho*FACTORCONVERSION / 2, alto*FACTORCONVERSION / 2);
	
	if(masa != MASAINFINITA)
		unionCuerpo.density = masa / (ancho*FACTORCONVERSION*alto*FACTORCONVERSION);

	unionCuerpo.shape = &cajaColision;
	unionCuerpo.filter.categoryBits = categoria;
	unionCuerpo.filter.maskBits = colisionaCon;

	datos.push_back(DatosColisionCuerpo(this,CUERPO));

	unionCuerpo.userData = new DatosColisionCuerpo(this,CUERPO);
	cuerpo->CreateFixture(&unionCuerpo);
}

Cuerpo::~Cuerpo()
{
	mundo.obtenerMundo().DestroyBody(cuerpo);
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

b2Vec2 Cuerpo::obtenerLeftTopCajaMagnificada(uint magnificador) const
{
	const b2Vec2 centro = obtenerPosicion();

	return b2Vec2(centro.x - ancho / 2 * magnificador, centro.y - alto / 2 * magnificador);
}

b2Vec2 Cuerpo::obtenerRightBottomCajaMagnificada(uint magnificador) const
{
	const b2Vec2 centro = obtenerPosicion();

	return b2Vec2(centro.x + ancho / 2 * magnificador, centro.y + alto / 2 * magnificador);
}

void Cuerpo::modificarVelocidad(const b2Vec2 & velocidad)
{
	cuerpo->SetLinearVelocity(velocidad);
}

void Cuerpo::modificarOrientacion(Orientaciones orientacion)
{
	this->orientacion = orientacion;
}

void Cuerpo::aplicarImpulso(const b2Vec2 & impulso)
{
	cuerpo->ApplyLinearImpulse(impulso, cuerpo->GetPosition(), true);
}

void Cuerpo::agregarCuerpoInmaterial(real ancho, 
			     real alto,
			     b2Vec2 posicion, 
			     uint identificador)
{
		b2PolygonShape cajita;
		cajita.SetAsBox(ancho, alto, posicion, 0);
		b2FixtureDef unionCajita;
		unionCajita.isSensor = true;

		datos.push_back(DatosColisionCuerpo(this,identificador));

		unionCajita.userData = new DatosColisionCuerpo(this,identificador);
		unionCajita.shape = &cajita;

		cuerpo->CreateFixture(&unionCajita);

		detectorSuelo = true;
	
}

const b2Vec2 & Cuerpo::orientacionAVector(Orientaciones orientacion)
{
	if (orientacion == derecha)
		return versorDerecha;
	else
		return versorIzquierda;
}

const Rectangulo Cuerpo::obtenerRepresentacion() const{
	Rectangulo r;
	b2Vec2 top_left=obtenerLeftTopCajaMagnificada(1);
	b2Vec2 bot_right=obtenerRightBottomCajaMagnificada(1);
	r.x=top_left.x;
	r.y=top_left.y;
	r.w=bot_right.x-top_left.x;
	r.h=bot_right.y-top_left.y;
	return r;
}
