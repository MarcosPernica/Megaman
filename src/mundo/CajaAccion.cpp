#include "CajaAccion.h"
#include "Megaman.h"
#include <iostream>
#include "Cuerpo.h"

#define TIMEOUTRESPAWN 10

CallbackInteraccionCajaAccion::CallbackInteraccionCajaAccion(Megaman *megaman, CajaAccion *cajaAccion) : megaman(megaman), cajaAccion(cajaAccion)
{
}

void CallbackInteraccionCajaAccion::ejecutar()
{
	cajaAccion->interactuar(megaman);
}

CajaAccion::CajaAccion(Mundo &mundo,
		 real ancho,
		 real alto,
		 const b2Vec2 &posicion) :
		 Cuerpo(NULO, 
			mundo,
			ancho,
			alto,
			MASAINFINITA,
			CAJASACCION,
			PERSONAJES,
			posicion,	
			false,
			false,	
			b2Vec2_zero,
			derecha,
			true),
			habilitada(true)
{
}

void CajaAccion::deshabilitar()
{
	habilitada = false;
}

void CajaAccion::habilitarse()
{
	habilitada = true;
}

bool CajaAccion::estaHabilitada()
{
	return habilitada;
}

ushort CajaAccion::tipoCuerpo()const
{
	return CAJASACCION;
}

ZonaMortal::ZonaMortal(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion)
			    
{
}

void ZonaMortal::interactuar(Megaman *megaman)
{
	std::cout << "Es=" << megaman->obtenerEnergiaMaxima() << std::endl;
	megaman->atacado(megaman->obtenerEnergiaMaxima());
}

ZonaTransporte::ZonaTransporte(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion,
		       const b2Vec2 &posicionDestino) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion),
			posicionDestino(posicionDestino)
			    
{
}

void ZonaTransporte::interactuar(Megaman *megaman)
{
	megaman->modificarPosicion(posicionDestino);
}

CajaSpawn::CajaSpawn(Mundo &mundo, b2Vec2 posicion) : CajaAccion(mundo,1,1,posicion), mundo(mundo), posicion(posicion)
{
}

CajaSpawnMet::CajaSpawnMet(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), cuentaRegresiva(0) 
{
}


void CajaSpawnMet::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID) || !estaHabilitada())
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = TIMEOUTRESPAWN;
			obtenerMundo().agregar(new Met(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnBumby::CajaSpawnBumby(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnBumby::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID) || !estaHabilitada())
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = TIMEOUTRESPAWN;
			obtenerMundo().agregar(new Bumby(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnSniper::CajaSpawnSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnSniper::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID) || !estaHabilitada())
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = TIMEOUTRESPAWN;
			obtenerMundo().agregar(new Sniper(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnJumpingSniper::CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnJumpingSniper::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID) || !estaHabilitada())
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = TIMEOUTRESPAWN;
			obtenerMundo().agregar(new JumpingSniper(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnBombman::CajaSpawnBombman(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), creado(false)
{
}

void CajaSpawnBombman::actualizar(real deltaT)
{
	if(!creado)
	{
		creado = true;
		obtenerMundo().agregar(new Bombman(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
	}			
}

ZonaCamara::ZonaCamara(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion) :
			posicion(posicion),
			ancho(ancho),
			alto(alto),
			mundo(mundo)
			    
{
}

real ZonaCamara::obtenerAlto()
{
	return alto;
}

real ZonaCamara::obtenerAncho()
{
	return ancho;
}
b2Vec2 ZonaCamara::obtenerPosicion()
{
	return posicion;
}

void ZonaCamara::actualizarRecinto(real deltaT)
{
	b2Vec2 posicionPromedio = b2Vec2_zero;
	real lateralIzquierdo, lateralDerecho;

	std::list<Megaman*> megamanes = mundo.obtenerMegamanes();
	std::list<Megaman*> megamanesAfuera;

	lateralIzquierdo = posicion.x;
	lateralDerecho = posicion.x + ancho;

	std::list<Megaman*>::iterator i = megamanes.begin();
	b2Vec2 posicionMegaman;

	while(i != megamanes.end())
	{
		posicionMegaman = (*i)->obtenerPosicion();
		if(posicionMegaman.x > lateralDerecho)
		{
			posicionMegaman.x = lateralDerecho;	
			(*i)->modificarPosicion(posicionMegaman);
		}
		else if(posicionMegaman.x < lateralIzquierdo)
		{
			posicionMegaman.x = lateralIzquierdo;	
			(*i)->modificarPosicion(posicionMegaman);
		}
		
		posicionPromedio += posicionMegaman;
		i++;
	}

	posicionPromedio = (1/(real)megamanes.size()) * posicionPromedio;
	posicionPromedio -= b2Vec2(ancho/2,alto/2);

	lateralIzquierdo = posicionPromedio.x - ancho/2;
	lateralDerecho = posicionPromedio.x + ancho/2;

	i = megamanes.begin();

	real posicionXMegaman, maximoAfuera = 0;
	
	while(i != megamanes.end())
	{
		posicionXMegaman = (*i)->obtenerPosicion().x;
		if(posicionXMegaman < lateralIzquierdo && -(posicionXMegaman-lateralIzquierdo) > abs(maximoAfuera))
			maximoAfuera = posicionXMegaman-lateralIzquierdo;
		else if(posicionXMegaman > lateralDerecho && (posicionXMegaman-lateralDerecho) > abs(maximoAfuera))
			maximoAfuera = (posicionXMegaman-lateralDerecho);
		i++;
	}

	posicionPromedio.x += maximoAfuera;
	posicion.x = posicionPromedio.x;
}

void ZonaCamara::actualizar(real deltaT)
{
	actualizarRecinto(deltaT);
	mundo.limpiar(posicion, ancho, alto);
}
