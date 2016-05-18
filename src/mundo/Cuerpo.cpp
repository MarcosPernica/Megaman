#include "Cuerpo.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include <iostream>
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

	datos.push_back(new DatosColisionCuerpo(this,CUERPO,Rectangulo(posicion.x,posicion.y,ancho,alto)));

	unionCuerpo.userData = datos.at(0);
	cuerpo->CreateFixture(&unionCuerpo);
}

Cuerpo::~Cuerpo()
{
	mundo.obtenerMundo().DestroyBody(cuerpo);

	std::vector<DatosColisionCuerpo*>::iterator i = datos.begin();

	while(i != datos.end())
		delete *i++;
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

void Cuerpo::modificarOrientacion(Orientaciones orientacion)
{
	this->orientacion = orientacion;
}

void Cuerpo::aplicarImpulso(const b2Vec2 & impulso)
{
	cuerpo->ApplyLinearImpulse(impulso,cuerpo->GetWorldCenter(),false);
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

		detectorSuelo = true;
	
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
