#include "CajaAccion.h"
#include "Megaman.h"

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

CajaSpawnMet::CajaSpawnMet(uint ID, Mundo &mundo, b2Vec2 posicion) : CajaSpawn(mundo,posicion), ID(ID) 
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
