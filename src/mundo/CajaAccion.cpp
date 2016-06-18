#include "CajaAccion.h"
#include "Megaman.h"
#include <iostream>
#include "Cuerpo.h"

#define TIMEOUTRESPAWN 10

CallbackInteraccionCajaAccion::CallbackInteraccionCajaAccion(Megaman *megaman, 
							     CajaAccion *cajaAccion) : 
							     megaman(megaman),
							     cajaAccion(cajaAccion)
{
}

void CallbackInteraccionCajaAccion::ejecutar()
{
	/*Cumple con el objetivo de la caja de accion sea cual sea.*/
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
	megaman->atacado(megaman->obtenerEnergiaMaxima(), NULL);
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
			   tomada(false),
			   ancho(ancho),
			   alto(alto)
			    
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

		/*Si todos estaba adentro activa el checkpoint.*/
		if(adentro)
		{
			i = megamanes.begin();

			/*Pone los SpawnPoints equidistantes en el ancho de la zona.*/
			b2Vec2 spawn(posicion.x - ancho/2+ANCHOSPRITEMEGAMAN/2, posicion.y);
			real distanciaX = (ancho - ANCHOSPRITEMEGAMAN)/megamanes.size();

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
			     puerta(puerta),
			     ancho(ancho),
			     alto(alto)
			
			    
{
}

void ZonaCerradura::actualizar(real deltaT)
{	
	/*Solo si ya no estaba cerrada y solo si tiene una puerta asociada.*/
	if(puerta && !puerta->estaCerrada())
	{
		b2Vec2 posicion = obtenerPosicion(), posicionMegaman;
		bool adentro = true;

		std::list<Megaman*> megamanes = obtenerMundo().obtenerMegamanes();
		std::list<Megaman*>::iterator i = megamanes.begin();

		/*Para que algo este adentro debe estarlo en todos sus ejes, para todos lo megamanes.*/
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

CajaSpawnMet::CajaSpawnMet(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), cuentaRegresiva(0), ID(ID) 
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
			obtenerMundo().agregar(new Met(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnBumby::CajaSpawnBumby(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), cuentaRegresiva(0), ID(ID)
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
			obtenerMundo().agregar(new Bumby(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnSniper::CajaSpawnSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), cuentaRegresiva(0), ID(ID)  
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
			obtenerMundo().agregar(new Sniper(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnJumpingSniper::CajaSpawnJumpingSniper(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), cuentaRegresiva(0), ID(ID) 
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
			obtenerMundo().agregar(new JumpingSniper(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnBombman::CajaSpawnBombman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), puerta(puerta), creado(false), ID(ID) 
{
}

void CajaSpawnBombman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Bombman(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnSparkman::CajaSpawnSparkman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), puerta(puerta), creado(false), ID(ID) 
{
}

void CajaSpawnSparkman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Sparkman(ID,obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}


CajaSpawnMagnetman::CajaSpawnMagnetman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), puerta(puerta), creado(false), ID(ID)  
{
}

void CajaSpawnMagnetman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Magnetman(ID, obtenerMundo(), obtenerPosicion(),b2Vec2_zero));
		}
	}			
}

CajaSpawnRingman::CajaSpawnRingman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), puerta(puerta), creado(false), ID(ID)  
{
}

void CajaSpawnRingman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Ringman(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
		}
	}			
}

CajaSpawnFireman::CajaSpawnFireman(uint ID, Puerta *puerta, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo, posicion), puerta(puerta), creado(false), ID(ID) 
{
}

void CajaSpawnFireman::actualizar(real deltaT)
{
	if(!creado)
	{
		if(puerta->estaCerrada())
		{
			creado = true;
			obtenerMundo().agregar(new Fireman(ID, obtenerMundo(), obtenerPosicion(), b2Vec2_zero));
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

	posicionCentral.x = posicionPromedio.x;

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
		/*Si esta fuera de la zona de camara los reposiciona.*/
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

	/*Pone solo el eje X en la posicion promedio obtenida.*/
	posicionPromedio = (1/(real)megamanes.size()) * posicionPromedio;

	posicionCentral.x = posicionPromedio.x;

	posicionPromedio -= b2Vec2(ancho/2,alto/2);

	posicion.x = posicionPromedio.x;
}

void ZonaCamara::actualizar(real deltaT)
{
	actualizarRecinto(deltaT);

	/*Le dice a mundo que borre las entidades fuera de la zona.*/
	mundo.limpiar(posicionCentral, ancho, alto);
}
