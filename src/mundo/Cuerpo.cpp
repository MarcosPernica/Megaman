#include "Cuerpo.h"
#include "Mundo.h"
#include <Box2D/Box2D.h>
#include "../graficos/Dibujable.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"
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

void Cuerpo::modificarRestitucion(real coeficiente)
{
	cuerpo->GetFixtureList()->SetRestitution(coeficiente);
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
			     ushort colisionaCon,
			     bool fantasma)
{
		b2PolygonShape cajita;
		cajita.SetAsBox(ancho/2, alto/2, posicion, 0);
		b2FixtureDef unionCajita;
		unionCajita.isSensor = fantasma;

		unionCajita.filter.categoryBits = categoria;
		unionCajita.filter.maskBits = colisionaCon;

		/*El rectangulo usa de posicion el topLeft (no el centro de masa).*/
		datos.push_back(new DatosColisionCuerpo(this,identificador,Rectangulo(posicion.x-ancho/2,posicion.y-alto/2,ancho,alto)));

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

void Cuerpo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion)
{
	Rectangulo principal = obtenerCajaMagnificada(1);

	Dibujable::dibujarRectangulo(cr, origen, factorAmplificacion, Dibujable::mundoARender(principal.topLeft()), Dibujable::mundoARender(principal.obtenerAncho()), Dibujable::mundoARender(principal.obtenerAlto()));

	for(uint i=1;i<datos.size();i++)
	{
		b2Vec2 topLeftCuerpo = datos.at(i)->caja.topLeft();
		b2Vec2 topLeftMundo = topLeftCuerpo + obtenerPosicion();
		
		Dibujable::dibujarRectangulo(cr, origen, factorAmplificacion, Dibujable::mundoARender(topLeftMundo), Dibujable::mundoARender(datos.at(i)->caja.obtenerAncho()), Dibujable::mundoARender(datos.at(i)->caja.obtenerAlto()));
	}
}
////---------------------------snapshotable-----------------------------//

/**
 * 1- cada Snapshotable concreto tiene un getTipo() que devuelve un int /macro de 
 * 		las definidas en Snapshotable.h.
 * 	Además, tienen un desdeSnapshot() que llama el new y inyecta el snapshot or primera vez.
 * 	Cuando llega un desconocido y nuevo, Mundo mira su atributo tipo y decide qué objeto crear.
 * 2-llamar a las macros SN_AGREGAR_PROPIEDAD en agregarPropiedadesASnapshot, las variables entran 
 * 	y salen con su nombre: sí ó sí, tenés que recuperar y/o meter una variable que se llame igual
 *  siempre.
 * 	Ojo que lo que metas entre los paréntesis  (me refiero al texto!) NO DEBE TENER ESPACIOS
 * 3-lo mismo en setStateFromSnapshot, con SN_OBTENER_PROPIEDAD. observá que el 
 * nombre de las variables es el mismo!!
 * 
 * La idea es que en situaciones donde directamente se toquen los atributos privados, 
 * esto queda más lindo
 * 
 * PROBLEMA: no se pueden tener variables homónimas en el hijo y el padre, de 
 * todas formas siempre se puede hacer una variable con otro nombre y snapshotear esa.
 * 
 * Para comprimir los strings más adelante, podemos usar una función de hash o de 
 * compresión o algo por el estilo
 * 
 * PRECAUCIÓN: el argumento de ambos métodos SIEMPRE DEBE LLAMARSE sn 
 * porque la macro tiene eso incorporado
 * 
 * SIEMPRE en agregarPropiedadesASnapshot y setStateFromSnapshot, 
 * hay que llamar al mismo método del padre antes!(esta es la única excepción)
 * */

void Cuerpo::agregarPropiedadesASnapshot(Snapshot& sn){
	real pos_x = obtenerPosicion().x;
	real pos_y = obtenerPosicion().y;
	SN_AGREGAR_PROPIEDAD(pos_x);
	SN_AGREGAR_PROPIEDAD(pos_y);
	
	real vel_x = obtenerVelocidad().x;
	real vel_y = obtenerVelocidad().y;
	SN_AGREGAR_PROPIEDAD(vel_x);
	SN_AGREGAR_PROPIEDAD(vel_y);
	
	Orientaciones orientacion = obtenerOrientacion();
	SN_AGREGAR_PROPIEDAD(orientacion);
}
void Cuerpo::setStateFromSnapshot(const Snapshot& sn){
	real pos_x,pos_y;
	SN_OBTENER_PROPIEDAD(pos_x);
	SN_OBTENER_PROPIEDAD(pos_y);
	
	real vel_x,vel_y;
	SN_OBTENER_PROPIEDAD(vel_x);
	SN_OBTENER_PROPIEDAD(vel_y);
	
	Orientaciones orientacion;
	SN_OBTENER_PROPIEDAD(orientacion);
	
	modificarPosicion(b2Vec2(pos_x,pos_y));
	modificarVelocidad(b2Vec2(vel_x,vel_y));
	modificarOrientacion(orientacion);
}
