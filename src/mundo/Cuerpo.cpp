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
	
	cajaColision.SetAsBox(ancho / 2, alto / 2);
	
	if(masa != MASAINFINITA)
		unionCuerpo.density = masa / (ancho*alto);

	unionCuerpo.shape = &cajaColision;
	unionCuerpo.filter.categoryBits = categoria;
	unionCuerpo.filter.maskBits = colisionaCon;

	datos.push_back(Datos(this,false));

	unionCuerpo.userData = &datos.at(0);
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
	return cuerpo->GetPosition();
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

void Cuerpo::agregarDetectorSuelo()
{
	if (!detectorSuelo)
	{
		detectorSuelo = true;
		b2PolygonShape cajita;
		cajita.SetAsBox(0.3, 0.3, b2Vec2(0, -alto/2), 0);
		b2FixtureDef unionCajita;
		unionCajita.isSensor = true;

		datos.push_back(Datos(this,true));

		unionCajita.userData = &datos.at(1);
		unionCajita.shape = &cajita;

		cuerpo->CreateFixture(&unionCajita);

		detectorSuelo = true;
	}
}

const b2Vec2 & Cuerpo::orientacionAVector(Orientaciones orientacion)
{
	if (orientacion == derecha)
		return versorDerecha;
	else
		return versorIzquierda;
}
