#include "Entidad.h"
#include "PowerUp.h"
#include "Mundo.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"
Entidad::Entidad(uint ID, 
		     Mundo & mundo, 
	             real ancho,
			     real alto,
	             uint energiaMaxima,
	             real masa, 
			     ushort categoria,
				 ushort colisionaCon,
	             const b2Vec2 & posicion,
				 bool rotable,
	             bool gravitacional,
	             const b2Vec2 & velocidad,
	             Orientaciones orientacion) :
				 energia(energiaMaxima),
				 energiaMaxima(energiaMaxima),
				 mundo(mundo),
			     Cuerpo(ID,
						mundo,
						ancho,
						alto,
						masa,
						categoria,
						colisionaCon,
						posicion,
						rotable,
						gravitacional,
						velocidad,
						orientacion),
			 muerta(false)
{
}

bool Entidad::estaMuerta()
{
	return muerta;
}

void Entidad::revivir()
{
	muerta = false;
	energia = energiaMaxima;
}

uint Entidad::obtenerEnergiaMaxima()
{
	return energiaMaxima;
}

uint Entidad::obtenerEnergiaActual()
{
	return energia;
}

void Entidad::recuperarEnergia(uint cantidadEnergia)
{
	if (energia + cantidadEnergia > energiaMaxima)
		energia = energiaMaxima;
	else
		energia += cantidadEnergia;
}

void Entidad::alMorir()
{
	eliminarse(obtenerMundo());
}

void Entidad::atacado(uint danio)
{
	std::cout << danio << std::endl;
	PowerUp *powerUp;

	if (danio < energia)
		energia -= danio;
	else
	{	
		std::cout << "Dead" << std::endl;
		muerta = true;
		alMorir();
	}		
}

void Entidad::agregarPropiedadesASnapshot(Snapshot& sn){
	SN_AGREGAR_PROPIEDAD(energia);
	SN_AGREGAR_PROPIEDAD(energiaMaxima);
	SN_AGREGAR_PROPIEDAD(muerta);
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void Entidad::setStateFromSnapshot(const Snapshot& sn){
	SN_OBTENER_PROPIEDAD(energia);
	SN_OBTENER_PROPIEDAD(energiaMaxima);
	SN_OBTENER_PROPIEDAD(muerta);
	Cuerpo::setStateFromSnapshot(sn);
}
