#include "CajaAccion.h"
#include "Megaman.h"
#include <iostream>

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
			true)
{
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

CajaSpawn::CajaSpawn(Mundo &mundo, b2Vec2 posicion) : CajaAccion(mundo,1,1,posicion), mundo(mundo), posicion(posicion)
{
}

CajaSpawnMet::CajaSpawnMet(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID), cuentaRegresiva(0) 
{
}


void CajaSpawnMet::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID))
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = 5;
			obtenerMundo().agregar(new Met(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnBumby::CajaSpawnBumby(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnBumby::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID))
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = 5;
			obtenerMundo().agregar(new Bumby(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnSniper::CajaSpawnSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnSniper::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID))
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = 5;
			obtenerMundo().agregar(new Sniper(ID,obtenerMundo(),obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnJumpingSniper::CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
{
}


void CajaSpawnJumpingSniper::actualizar(real deltaT)
{
	if(!obtenerMundo().existeElemento(ID))
	{
		cuentaRegresiva -= deltaT;

		if(cuentaRegresiva <= 0)
		{
			cuentaRegresiva = 5;
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
		       const b2Vec2 &posicion,
		       const b2Vec2 &posicionDestino) :
		       CajaAccion(mundo,
			    	  ancho,
			    	  alto,
			    	  posicion),
			posicionDestino(posicionDestino)
			    
{
	jugadoresZona1 = 0;
	jugadoresZona2 = 0;
}

void ZonaCamara::agregarJugadorZona1()
{
	jugadoresZona1++;
}

void ZonaCamara::quitarJugadorZona1()
{
	jugadoresZona1--;
}

void ZonaCamara::agregarJugadorZona2()
{
	jugadoresZona2++;
}

void ZonaCamara::quitarJugadorZona2()
{
	jugadoresZona2--;
}

void ZonaCamara::actualizar(real deltaT)
{
	
}
