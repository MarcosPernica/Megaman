#include "PowerUp.h"
#include "Disparo.h"
#include "Definiciones.h"
#include "../net/snapshots/Snapshot.h"

CallbackAumentador::CallbackAumentador(PowerUp *powerUp, Megaman *megaman) : powerUp(powerUp), megaman(megaman)
{
}

void CallbackAumentador::ejecutar()
{
	powerUp->aumentar(*megaman);
}

NuevaVida::NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion), 
			Animado(&animacion),
			animacion(ANIM_VIDA,0.5)
{
}

void NuevaVida::aumentar(Megaman & megaman)
{
	megaman.aumentarVida();
	eliminarPowerUp();
}

void NuevaVida::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool NuevaVida::espejado() const{return false;};

const Rectangulo NuevaVida::obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
						obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
						ANCHOSPRITEPOWERUP,
						ALTOSPRITEPOWERUP);}



Glib::RefPtr<Gdk::Pixbuf> Habilitador::a_dibujar(){
	if(textura == 0){
		textura = Gdk::Pixbuf::create_from_file(ANIM_PODER);
	}
	return textura;
}



HabilitadorBomba::HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorBomba::aumentar(Megaman & megaman)
{
	/*
	std::list<Megaman *> megamanes = obtenerMundo().obtenerMegamanes();
	std::list<Megaman *>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		(*i++)->agregarArma(new Bomba(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);

	eliminarPowerUp();
	obtenerMundo().finalizar();
	*/
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Bomba);
}

void HabilitadorBomba::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);	
	}


const Rectangulo HabilitadorBomba::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP
				);
}

HabilitadorIman::HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorIman::aumentar(Megaman & megaman)
{
	/*
	std::list<Megaman *> megamanes = obtenerMundo().obtenerMegamanes();
	std::list<Megaman *>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		(*i++)->agregarArma(new Iman(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);

	eliminarPowerUp();
	obtenerMundo().finalizar();
	*/
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Iman);
}

void HabilitadorIman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
	
}

const Rectangulo HabilitadorIman::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP
				);
}

HabilitadorChispa::HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorChispa::aumentar(Megaman & megaman)
{
	/*
	std::list<Megaman *> megamanes = obtenerMundo().obtenerMegamanes();
	std::list<Megaman *>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		(*i++)->agregarArma(new Chispa(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);

	eliminarPowerUp();
	obtenerMundo().finalizar();
	*/
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Chispa);
}

void HabilitadorChispa::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
	
}

const Rectangulo HabilitadorChispa::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP
				);
}

HabilitadorAnillo::HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorAnillo::aumentar(Megaman & megaman)
{
	/*
	std::list<Megaman *> megamanes = obtenerMundo().obtenerMegamanes();
	std::list<Megaman *>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		(*i++)->agregarArma(new Anillo(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);

	eliminarPowerUp();
	obtenerMundo().finalizar();
	*/
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Anillo);
}

void HabilitadorAnillo::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
	
}
const Rectangulo HabilitadorAnillo::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP
				);
}

HabilitadorFuego::HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorFuego::aumentar(Megaman & megaman)
{
	/*
	std::list<Megaman *> megamanes = obtenerMundo().obtenerMegamanes();
	std::list<Megaman *>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		(*i++)->agregarArma(new Fuego(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS), CANTIDADINFINITAPLASMA);

	eliminarPowerUp();
	obtenerMundo().finalizar();
	*/
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Fuego);
}

void HabilitadorFuego::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
ImagenEscalada::dibujarEn(cr,origen,factorAmplificacion);
	
}

const Rectangulo HabilitadorFuego::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP
				);
}

CapsulaEnergiaChica::CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIACHICA, posicion, ANCHOSPRITEPOWERUP/4, ALTOSPRITEPOWERUP/4),
			Animado(&animacion),
			animacion(ANIM_ENERGIA,0.25)
{
}

void CapsulaEnergiaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(2);
	eliminarPowerUp();
}

void CapsulaEnergiaChica::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaEnergiaChica::espejado() const{return false;};

const Rectangulo CapsulaEnergiaChica::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP/2,
					ALTOSPRITEPOWERUP/2);}

CapsulaEnergiaGrande::CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIAGRANDE, posicion),
						Animado(&animacion),
						animacion(ANIM_ENERGIA,0.25)
{
}

void CapsulaEnergiaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(6);
	eliminarPowerUp();
}

void CapsulaEnergiaGrande::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaEnergiaGrande::espejado() const{return false;};

const Rectangulo CapsulaEnergiaGrande::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP);}

CapsulaPlasmaChica::CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMACHICA, posicion, ANCHOSPRITEPOWERUP/4, ALTOSPRITEPOWERUP/4),
			Animado(&animacion),
			animacion(ANIM_PLASMA,0.5)
{
}

void CapsulaPlasmaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(2);
	eliminarPowerUp();
}

void CapsulaPlasmaChica::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaPlasmaChica::espejado() const{return false;};

const Rectangulo CapsulaPlasmaChica::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP/2,
					ALTOSPRITEPOWERUP/2);}


CapsulaPlasmaGrande::CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMAGRANDE, posicion),
			Animado(&animacion),
			animacion(ANIM_PLASMA,0.5)
			
{
}

void CapsulaPlasmaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(6);
	eliminarPowerUp();
}

void CapsulaPlasmaGrande::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaPlasmaGrande::espejado() const{return false;};

const Rectangulo CapsulaPlasmaGrande::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP);}


PowerUp::PowerUp(uint ID, Mundo &mundo,
				 real probabilidadAparicion,
				 const b2Vec2 &posicion,
				 real ancho,
				 real alto) :
				 Cuerpo(ID, 
					mundo,
					ancho,
					alto,
					MASAPOWERUP,
					POWERUPS,
					CONSTRUCCIONES | PERSONAJES,
					posicion,	
					false,
					true,	
					b2Vec2 (0,VELOCIDADPOWERUP)),
				probabilidadAparicion(probabilidadAparicion)
			     
{
	if (probabilidadAparicion < 0 || probabilidadAparicion > 1)
		probabilidadAparicion = 0;

	this->probabilidadAparicion = probabilidadAparicion;
}

void PowerUp::eliminarse(Mundo& de)
{
	de.eliminar(this);
}

ushort PowerUp::tipoCuerpo() const
{
	return POWERUPS;
}

real PowerUp::obtenerProbabilidadAparicion()
{
	return probabilidadAparicion;
}

void PowerUp::eliminarPowerUp()
{
	obtenerMundo().eliminar(this);
}

void PowerUp::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(probabilidadAparicion);
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void PowerUp::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(probabilidadAparicion);
	Cuerpo::setStateFromSnapshot(sn);
}
/*
 HabilitadorBomba* HabilitadorBomba::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	HabilitadorBomba* p =new HabilitadorBomba(sn.getID(),mundo,b2Vec2(0,0));
	p->setStateFromSnapshot(sn);
	return p;
}
*/
/*
#define GENERAR_IMPLEMENTACION_DESDESNAPSHOT(clase) \
clase* clase::desdeSnapshot(const Snapshot& sn, Mundo& mundo){ \
	clase* p =new clase(sn.getID(),mundo,b2Vec2(0,0)); \
	p->setStateFromSnapshot(sn); \
	return p; \
}

GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorBomba)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorIman)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorChispa)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorAnillo)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(HabilitadorFuego)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaPlasmaGrande)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaPlasmaChica)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaEnergiaGrande)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(CapsulaEnergiaChica)
GENERAR_IMPLEMENTACION_DESDESNAPSHOT(NuevaVida)
*/
