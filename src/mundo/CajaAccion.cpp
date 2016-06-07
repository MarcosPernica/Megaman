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

ZonaGuardado::ZonaGuardado(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion),
			ancho(ancho),
			alto(alto),
			tomada(false)
			    
{
}

void ZonaGuardado::actualizar(real deltaT)
{
	/*Posiciona los spawnPoints de los megaman, es un checkpoint.*/
	if(!tomada)
	{
		b2Vec2 posicion = obtenerPosicion(), posicionMegaman;
		bool adentro = true;

		std::list<Megaman*> megamanes = obtenerMundo().obtenerMegamanes();
		std::list<Megaman*>::iterator i = megamanes.begin();

		while(i != megamanes.end() && adentro)
		{
			posicionMegaman = (*i)->obtenerPosicion();
			adentro &= ((posicionMegaman.x > (posicion.x - ancho/2)) && (posicionMegaman.x < (posicion.x + ancho/2)));
			adentro &= ((posicionMegaman.y > (posicion.y - alto/2)) && (posicionMegaman.y < (posicion.y + alto/2)));
			i++;
		}

		if(adentro)
		{
			i = megamanes.begin();

			b2Vec2 spawn(posicion.x-ancho/2+ANCHOSPRITEMEGAMAN/2, posicion.y);
			real distanciaX = (ancho-ANCHOSPRITEMEGAMAN)/megamanes.size();

			while(i != megamanes.end())
			{
				(*i++)->modificarPosicionSpawn(spawn);
				spawn.x += distanciaX;
			}
			tomada = true;
		}
	}
}

ZonaCerradura::ZonaCerradura(Mundo &mundo,
		       real ancho,
		       real alto,
		       const b2Vec2 &posicion,
		       Puerta *puerta) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion),
			ancho(ancho),
			alto(alto),
			puerta(puerta)
			    
{
}

void ZonaCerradura::actualizar(real deltaT)
{	
	if(puerta && !puerta->estaCerrada())
	{
		b2Vec2 posicion = obtenerPosicion(), posicionMegaman;
		bool adentro = true;

		std::list<Megaman*> megamanes = obtenerMundo().obtenerMegamanes();
		std::list<Megaman*>::iterator i = megamanes.begin();

		while(i != megamanes.end() && adentro)
		{
			posicionMegaman = (*i)->obtenerPosicion();
			adentro &= ((posicionMegaman.x > (posicion.x - ancho/2)) && (posicionMegaman.x < (posicion.x + ancho/2)));
			adentro &= ((posicionMegaman.y > (posicion.y - alto/2)) && (posicionMegaman.y < (posicion.y + alto/2)));
			i++;
		}

		if(adentro)
			puerta->cerrar();
	}
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

CajaSpawnBumby::CajaSpawnBumby(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), cuentaRegresiva(0) 
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

CajaSpawnSniper::CajaSpawnSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), cuentaRegresiva(0)  
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

CajaSpawnJumpingSniper::CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), cuentaRegresiva(0)  
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

CajaSpawnBombman::CajaSpawnBombman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), creado(false), puerta(puerta) 
{
}

void CajaSpawnBombman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Bombman(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
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

void ZonaCamara::reiniciar()
{
	b2Vec2 posicionPromedio = b2Vec2_zero;

	std::list<Megaman*> megamanes = mundo.obtenerMegamanes();

	std::list<Megaman*>::iterator i = megamanes.begin();

	while(i != megamanes.end())
		posicionPromedio = (*i++)->obtenerPosicion();

	posicionPromedio = (1/(real)megamanes.size()) * posicionPromedio;
	posicionPromedio -= b2Vec2(ancho/2,alto/2);

	posicion.x = posicionPromedio.x;
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
