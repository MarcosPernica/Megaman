#include "Enemigo.h"
#include <time.h>
#include "PowerUp.h"
#include <stdlib.h>
#include "Mundo.h"
#include <iostream>
#include "Cuerpo.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"
#define HACIENDONADA 0

#define PISANDO 1
#define PORSALTAR 2
#define ENELAIRE 3

#define DISPARANDO 1
#define LANZANDO 2

#define AGARRADOESCALERA 1
#define BAJANDOESCALERA 2
#define SUBIENDOESCALERA 3

Enemigo::Enemigo(uint ID,
		 Mundo & mundo,
		 real ancho,
		 real alto,
		 Disparo *arma,
		 uint energiaMaxima,
		 uint escudo,
		 real masa,
		 real velocidadSalto,
		 real velocidadCorrer,
		 ushort categoria,
		 ushort colisionaCon,
		 const b2Vec2 & posicion,
		 bool rotable,
		 bool gravitacional,
		 const b2Vec2 & velocidad,
		 Orientaciones orientacion,
		 bool powerUpMorir) :
		 Entidad(ID,
			 mundo,
			 ancho,
			 alto,
			 energiaMaxima,
			 masa,
			 categoria,
			 colisionaCon,
			 posicion,
			 rotable,
			 gravitacional,
			 velocidad,
			 orientacion),
		contadorPiso(0),
		estadoSalto(PISANDO),
		estadoDisparo(HACIENDONADA),
		corriendo(false),
		tocandoIzquierda(0),
		tocandoDerecha(0),
		escudo(escudo),
		cubierto(true),
		arma(arma),
		powerUpMorir(powerUpMorir),
		velocidadSalto(velocidadSalto),
		velocidadCorrer(velocidadCorrer),
		direccionDisparo(0,0)
{
	agregarCuerpoInmaterial(ancho*0.25,0.3,b2Vec2(0,alto*0.9/2), JUMPBOX, JUMPBOX, CONSTRUCCIONES);
	agregarCuerpoInmaterial(ancho*0.25,0.3,b2Vec2(-ancho/2,0), LEFTBOX, LEFTBOX, CONSTRUCCIONES);
	agregarCuerpoInmaterial(ancho*0.25,0.3,b2Vec2(+ancho/2,0), RIGHTBOX, RIGHTBOX, CONSTRUCCIONES);
	agregarCuerpoInmaterial(ancho,alto,b2Vec2(0,0), AURAENEMIGOS, AURAENEMIGOS, PERSONAJES | DISPAROS);
}

void Enemigo::atacado(int dano, Disparo *disparo)
{
	if (!cubierto || escudo < dano)
		Entidad::atacado(dano - escudo*cubierto, disparo);
}

void Enemigo::cubrirse()
{
	cubierto = true;
}

void Enemigo::exponerse()
{
	cubierto = false;
}

bool Enemigo::estaCubierto()
{
	return cubierto;
}

void Enemigo::habilitarSalto()
{
	contadorPiso++;
	estadoSalto = PISANDO;
}

void Enemigo::deshabilitarSalto()
{
	contadorPiso--;
}

void Enemigo::tocoIzquierda()
{
	tocandoIzquierda++;
}

void Enemigo::dejoTocarIzquierda()
{
	tocandoIzquierda--;
}

void Enemigo::tocoDerecha()
{
	tocandoDerecha++;
}

void Enemigo::dejoTocarDerecha()
{
	tocandoDerecha--;
}

bool Enemigo::puedeIrDerecha()
{
	return !tocandoDerecha;
}

bool Enemigo::puedeIrIzquierda()
{
	return !tocandoIzquierda;
}

bool Enemigo::puedeCorrer()
{
	if(obtenerOrientacion() == derecha)
		return puedeIrDerecha();
	else 
		return puedeIrIzquierda();	
}

void Enemigo::alMorir()
{
	if(powerUpMorir)
		ruletaPowerUp(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion());
	Entidad::alMorir();
}

void Enemigo::ruletaPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion)
{
	mundo.agregarTareaDiferida(new CallbackCreadorPowerUp(ID,mundo,posicion));
}

bool Enemigo::puedeSaltar()
{
	return contadorPiso;
}

bool Enemigo::estaEnElAire()
{
	return estadoSalto == ENELAIRE;
}

void Enemigo::saltar()
{
	if(contadorPiso >= 1 && estadoSalto == PISANDO)
		estadoSalto = PORSALTAR;
}

void Enemigo::correr()
{
	corriendo = true;
}

void Enemigo::dejarCorrer()
{
	corriendo = false;
	modificarVelocidad(b2Vec2_zero);
}

void Enemigo::disparar(b2Vec2 direccion)
{
	if(direccion.x || direccion.y)
		direccion.Normalize();
	else
		direccion = Cuerpo::orientacionAVector(obtenerOrientacion());

	direccionDisparo = direccion;
	estadoDisparo = DISPARANDO;
}

void Enemigo::mirarIzquierda()
{
	modificarOrientacion(izquierda);
}

void Enemigo::mirarDerecha()
{
	modificarOrientacion(derecha);
}	

void Enemigo::virar()
{
	if(obtenerOrientacion() == derecha)
		modificarOrientacion(izquierda);
	else
		modificarOrientacion(derecha);
}

void Enemigo::actualizar(real deltaT)
{
	if (corriendo)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.x = 0;
		velocidad += velocidadCorrer*Cuerpo::orientacionAVector(obtenerOrientacion());
		modificarVelocidad(velocidad);
	}

	if (estadoSalto == PORSALTAR)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.y -= velocidadSalto;

		modificarVelocidad(velocidad);	

		estadoSalto = ENELAIRE;
	}

	
	if (estadoDisparo != HACIENDONADA)
	{
		b2Vec2 posicion, velocidad;

		velocidad = arma->obtenerMultiplicadorVelocidad()*direccionDisparo;

		posicion = direccionDisparo + obtenerPosicion();
		if (arma->lanzable())
			posicion -= b2Vec2(0, POSICIONLANZAMIENTOMEGAMAN);

		obtenerMundo().agregar(arma->nuevo(obtenerMundo().generarID(),posicion, velocidad));

		estadoDisparo = HACIENDONADA;
	}
}

ushort Enemigo::tipoCuerpo() const
{
	return ENEMIGOS;
}

real Enemigo::numeroAleatorio(real desde, real hasta)
{
	srand(time(NULL)*aleatorio);

	aleatorio = ((real)rand()/RAND_MAX)*(hasta-desde)+desde;

	return aleatorio;	
}

void Enemigo::eliminarse(Mundo& de)
{
	de.eliminar(this);
}
void Enemigo::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(escudo);
	SN_AGREGAR_PROPIEDAD(cubierto);
	SN_AGREGAR_PROPIEDAD(powerUpMorir);
	SN_AGREGAR_PROPIEDAD(corriendo);
	SN_AGREGAR_PROPIEDAD(tocandoIzquierda);
	SN_AGREGAR_PROPIEDAD(tocandoDerecha);
	SN_AGREGAR_PROPIEDAD(direccionDisparo.x);
	SN_AGREGAR_PROPIEDAD(direccionDisparo.y);
	SN_AGREGAR_PROPIEDAD(velocidadSalto);
	SN_AGREGAR_PROPIEDAD(velocidadCorrer);
	SN_AGREGAR_PROPIEDAD(estadoSalto);
	SN_AGREGAR_PROPIEDAD(estadoDisparo);
	Entidad::agregarPropiedadesASnapshot(sn);
}

void Enemigo::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(escudo);
	SN_OBTENER_PROPIEDAD(cubierto);
	SN_OBTENER_PROPIEDAD(powerUpMorir);
	SN_OBTENER_PROPIEDAD(corriendo);
	SN_OBTENER_PROPIEDAD(tocandoIzquierda);
	SN_OBTENER_PROPIEDAD(tocandoDerecha);
	SN_OBTENER_PROPIEDAD(direccionDisparo.x);
	SN_OBTENER_PROPIEDAD(direccionDisparo.y);
	SN_OBTENER_PROPIEDAD(velocidadSalto);
	SN_OBTENER_PROPIEDAD(velocidadCorrer);
	SN_OBTENER_PROPIEDAD(estadoSalto);
	SN_OBTENER_PROPIEDAD(estadoDisparo);
	Entidad::setStateFromSnapshot(sn);
}
