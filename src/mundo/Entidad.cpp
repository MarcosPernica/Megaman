#include "Entidad.h"
#include "PowerUp.h"
#include "Mundo.h"
#include <iostream>
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
			 muerta(muerta)
{
}

bool Entidad::estaMuerta()
{
	return muerta;
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
}

void Entidad::atacado(uint danio)
{
	std::cout << danio << std::endl;
	PowerUp *powerUp;

	if (danio < energia)
		energia -= danio;
	else
	{
		alMorir();
		muerta = true;
		obtenerMundo().eliminar(this);
	}
		
}
#define PROP_ENERGIA "energia"
void Entidad::agregarPropiedadesASnapshot(Snapshot& sn){
	sn.agregarPropiedad(PROP_ENERGIA,(int)energia);
	Cuerpo::agregarPropiedadesASnapshot(sn);
}
void Entidad::setStateFromSnapshot(const Snapshot& sn){
	energia = (uint) sn.obtenerPropiedad(PROP_ENERGIA);
	Cuerpo::setStateFromSnapshot(sn);
}
