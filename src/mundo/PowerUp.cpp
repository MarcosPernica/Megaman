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

NuevaVida::NuevaVida(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
			#ifndef compiling_server
			,Animado(&animacion),
			animacion(ANIM_VIDA,0.5)
			#endif
{
}

void NuevaVida::aumentar(Megaman & megaman)
{
	megaman.aumentarVida();
	eliminarPowerUp();
}

void NuevaVida::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
};

#ifndef compiling_server
void NuevaVida::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool NuevaVida::espejado() const{return false;};

const Rectangulo NuevaVida::obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
						obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
						ANCHOSPRITEPOWERUP,
						ALTOSPRITEPOWERUP);}



ArchivoImagen Habilitador::a_dibujar(){
	return ArchivoImagen(ANIM_PODER);
}

#endif

HabilitadorBomba::HabilitadorBomba(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorBomba::aumentar(Megaman & megaman)
{
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Bomba);
	finalizar();
}

#ifndef compiling_server
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
#endif

HabilitadorIman::HabilitadorIman(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorIman::aumentar(Megaman & megaman)
{
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Iman);
	obtenerMundo().finalizar();
}

#ifndef compiling_server
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
#endif

HabilitadorChispa::HabilitadorChispa(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorChispa::aumentar(Megaman & megaman)
{
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Chispa);
	obtenerMundo().finalizar();
}

#ifndef compiling_server
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
#endif

HabilitadorAnillo::HabilitadorAnillo(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorAnillo::aumentar(Megaman & megaman)
{
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Anillo);
	obtenerMundo().finalizar();
}

#ifndef compiling_server
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
#endif

HabilitadorFuego::HabilitadorFuego(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBANUEVAVIDA, posicion)
{
}

void HabilitadorFuego::aumentar(Megaman & megaman)
{
	eliminarPowerUp();
	obtenerMundo().agregarArma(TIPO_Fuego);
	obtenerMundo().finalizar();
}

#ifndef compiling_server
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
#endif

CapsulaEnergiaChica::CapsulaEnergiaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIACHICA, posicion, ANCHOSPRITEPOWERUP/4, ALTOSPRITEPOWERUP/4)
			#ifndef compiling_server
			,Animado(&animacion),
			animacion(ANIM_ENERGIA,0.25)
			#endif
{
}

void CapsulaEnergiaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(2);
	eliminarPowerUp();
}

void CapsulaEnergiaChica::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
};

#ifndef compiling_server
void CapsulaEnergiaChica::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaEnergiaChica::espejado() const{return false;};

const Rectangulo CapsulaEnergiaChica::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP/2,
					ALTOSPRITEPOWERUP/2);}
#endif

CapsulaEnergiaGrande::CapsulaEnergiaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAENERGIAGRANDE, posicion)
						#ifndef compiling_server
						,Animado(&animacion),
						animacion(ANIM_ENERGIA,0.25)
						#endif
{
}

void CapsulaEnergiaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarEnergia(6);
	eliminarPowerUp();
}

void CapsulaEnergiaGrande::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
};

#ifndef compiling_server
void CapsulaEnergiaGrande::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaEnergiaGrande::espejado() const{return false;};

const Rectangulo CapsulaEnergiaGrande::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP);}
#endif

CapsulaPlasmaChica::CapsulaPlasmaChica(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMACHICA, posicion, ANCHOSPRITEPOWERUP/4, ALTOSPRITEPOWERUP/4)
			#ifndef compiling_server	
			,Animado(&animacion),
			animacion(ANIM_PLASMA,0.5)
			#endif
{
}

void CapsulaPlasmaChica::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(2);
	eliminarPowerUp();
}

void CapsulaPlasmaChica::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
};

#ifndef compiling_server
void CapsulaPlasmaChica::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaPlasmaChica::espejado() const{return false;};

const Rectangulo CapsulaPlasmaChica::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP/2,
					ALTOSPRITEPOWERUP/2);}

#endif
CapsulaPlasmaGrande::CapsulaPlasmaGrande(uint ID, Mundo &mundo, const b2Vec2 &posicion) : PowerUp(ID, mundo, PROBAPLASMAGRANDE, posicion)
			#ifndef compiling_server
			,Animado(&animacion),
			animacion(ANIM_PLASMA,0.5)
			#endif
			
{
}

void CapsulaPlasmaGrande::aumentar(Megaman & megaman)
{
	megaman.recuperarPlasma(6);
	eliminarPowerUp();
}

void CapsulaPlasmaGrande::actualizar(real deltaT)
{
	#ifndef compiling_server
	avanzar(deltaT);
	#endif
};

#ifndef compiling_server
void CapsulaPlasmaGrande::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
Imagen::dibujarEn(cr,origen,factorAmplificacion);}

bool CapsulaPlasmaGrande::espejado() const{return false;};

const Rectangulo CapsulaPlasmaGrande::obtenerRepresentacion() const{
return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEPOWERUP/2,
					obtenerPosicion().y-ALTOSPRITEPOWERUP/2,
					ANCHOSPRITEPOWERUP,
					ALTOSPRITEPOWERUP);}

#endif
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
