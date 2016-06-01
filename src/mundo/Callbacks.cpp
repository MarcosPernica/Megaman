#include "Callbacks.h"
#include "Cuerpo.h"
#include "Entidad.h"
#include "Megaman.h"
#include "Disparo.h"
#include "Escalera.h"
#include "PowerUp.h"
#include "Definiciones.h"
#include "CajaAccion.h"
#include "Mundo.h"
#include <iostream>
#include "../graficos/Dibujable.h"
#include "Saltador.h" 

CallbackCreadorPowerUp::CallbackCreadorPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion) : ID(ID), mundo(mundo), posicion(posicion){};

void CallbackCreadorPowerUp::ejecutar()
{
	/*Equiprobabilidad de eventos.*/

	srand(time(NULL));
	
	real aleatorio = (real)rand()/RAND_MAX, piso = 0;

	if(aleatorio >= piso && aleatorio < (piso += PROBANUEVAVIDA))
		mundo.agregar(new NuevaVida(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAENERGIACHICA))
		mundo.agregar(new CapsulaEnergiaChica(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAENERGIAGRANDE))
		mundo.agregar(new CapsulaEnergiaGrande(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAPLASMACHICA))
		mundo.agregar(new CapsulaPlasmaChica(ID,mundo,posicion));
	else if(aleatorio >= piso && aleatorio < (piso += PROBAPLASMAGRANDE))
		mundo.agregar(new CapsulaPlasmaChica(ID,mundo,posicion));
}

CallbackHabilitadorArma::CallbackHabilitadorArma(uint ID, Mundo &mundo, const b2Vec2 &posicion, uint arma) : ID(ID), mundo(mundo), posicion(posicion), arma(arma){};

void CallbackHabilitadorArma::ejecutar()
{
	switch(arma)
	{
		case BOMBA:
			mundo.agregar(new HabilitadorBomba(ID,mundo,posicion));
		break;
	}
}



ElementosEnZona::ElementosEnZona(std::list<Dibujable*> &elementos) : elementos(elementos)
{
}

bool ElementosEnZona::ReportFixture(b2Fixture * fixture)
{
	DatosColisionCuerpo *datos = (DatosColisionCuerpo*)fixture->GetUserData();

	if(datos->ID == CUERPOPRINCIPAL)
		elementos.push_back((Dibujable*)datos->cuerpo);

	return true;
}


DanarRadio::DanarRadio(uint dano) : dano(dano)
{
}

bool DanarRadio::ReportFixture(b2Fixture * fixture)
{
	DatosColisionCuerpo *datos = (DatosColisionCuerpo*)fixture->GetUserData();
	if (datos->cuerpo->tipoCuerpo() == PERSONAJES || datos->cuerpo->tipoCuerpo() == ENEMIGOS)
	{
		if(datos->ID == CUERPOPRINCIPAL)
		{
			Entidad *entidad = (Entidad*)datos->cuerpo;
			entidad->atacado(dano);
		}
	}

	return true;
}


void DetectarEscalera::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();


	if(datosA->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosB->cuerpo;

			if(datosA->ID == CUERPOPRINCIPAL)			
				megaman->habilitarAgarre(datosA->cuerpo->obtenerPosicion().x);
		}
	}

	if(datosB->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;

			if(datosB->ID == CUERPOPRINCIPAL)			
				megaman->habilitarAgarre(datosB->cuerpo->obtenerPosicion().x);		
		}
	}
}

void DetectarEscalera::EndContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if(datosA->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosB->cuerpo;

			if(datosA->ID == CUERPOPRINCIPAL)			
				megaman->deshabilitarAgarre();			
		}
	}

	if(datosB->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;

			if(datosB->ID == CUERPOPRINCIPAL)			
				megaman->deshabilitarAgarre();				
		}
	}
}



void DetectarSuelo::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->ID == JUMPBOX)
	{
		if(datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;
			megaman->habilitarSalto();
		}
		else
		{
			Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
			enemigo->habilitarSalto();
		}
			
	}


	if (datosB->ID == JUMPBOX)
	{
		if(datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosB->cuerpo;
			megaman->habilitarSalto();
		}
		else
		{
			Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
			enemigo->habilitarSalto();
		}
				
	}

	if (datosA->ID == LEFTBOX)
	{
		
		Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
		enemigo->tocoIzquierda();
	}


	if (datosB->ID == LEFTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
		enemigo->tocoIzquierda();
	}

	if (datosA->ID == RIGHTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
		enemigo->tocoDerecha();
	}


	if (datosB->ID == RIGHTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
		enemigo->tocoDerecha();
	}
}

void DetectarSuelo::EndContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->ID == JUMPBOX)
	{
		if(datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;
			megaman->deshabilitarSalto();
		}	
		else
		{
			Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
			enemigo->deshabilitarSalto();
		}	
	}


	if (datosB->ID == JUMPBOX)
	{
		if(datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosB->cuerpo;
			megaman->deshabilitarSalto();
		}	
		else
		{
			Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
			enemigo->deshabilitarSalto();
		}	
	}

	if (datosA->ID == LEFTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
		enemigo->dejoTocarIzquierda();
	}


	if (datosB->ID == LEFTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
		enemigo->dejoTocarIzquierda();
	}

	if (datosA->ID == RIGHTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosA->cuerpo;
		enemigo->dejoTocarDerecha();
	}


	if (datosB->ID == RIGHTBOX)
	{
		Enemigo *enemigo = (Enemigo*)datosB->cuerpo;
		enemigo->dejoTocarDerecha();
	}	
}

void DetectarBalistica::BeginContact(b2Contact * contacto)
{
	
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->cuerpo->tipoCuerpo() == DISPAROS)
	{
		Disparo *disparo = (Disparo*)datosA->cuerpo;
		
		disparo->alColisionar(datosB->cuerpo);
	}

	if (datosB->cuerpo->tipoCuerpo() == DISPAROS)
	{
		Disparo *disparo = (Disparo*)datosB->cuerpo;

		disparo->alColisionar(datosA->cuerpo);
	}
	
}

void DetectarTocarPowerUp::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->cuerpo->tipoCuerpo() == POWERUPS && datosB->cuerpo->tipoCuerpo() == PERSONAJES)
	{
		Megaman *megaman = (Megaman*)datosB->cuerpo;
		PowerUp *powerUp = (PowerUp*)datosA->cuerpo;
		
		megaman->obtenerMundo().agregarTareaDiferida(new CallbackAumentador(powerUp,megaman));
	}
	
	if (datosB->cuerpo->tipoCuerpo() == POWERUPS && datosA->cuerpo->tipoCuerpo() == PERSONAJES)
	{
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		PowerUp *powerUp = (PowerUp*)datosB->cuerpo;

		megaman->obtenerMundo().agregarTareaDiferida(new CallbackAumentador(powerUp,megaman));
	}
}

void DetectarTocarCajaAccion::BeginContact(b2Contact * contacto)
{

	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->cuerpo->tipoCuerpo() == CAJASACCION)
	{
		CajaAccion *caja = (CajaAccion*)datosA->cuerpo;
		Megaman *megaman = (Megaman*)datosB->cuerpo;
		
		megaman->obtenerMundo().agregarTareaDiferida(new CallbackInteraccionCajaAccion(megaman,caja));
	}
	
	if (datosB->cuerpo->tipoCuerpo() == CAJASACCION)
	{	
		CajaAccion *caja = (CajaAccion*)datosB->cuerpo;
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		
		megaman->obtenerMundo().agregarTareaDiferida(new CallbackInteraccionCajaAccion(megaman,caja));
	}
}

void DetectarTocarEnemigos::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->cuerpo->tipoCuerpo() == PERSONAJES && datosB->cuerpo->tipoCuerpo() == AURAENEMIGOS)
	{
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		megaman->atacado(DANOPORCONTACTO);
	}
	
	if (datosB->cuerpo->tipoCuerpo() == PERSONAJES && datosA->cuerpo->tipoCuerpo() == AURAENEMIGOS)
	{
		
		Megaman *megaman = (Megaman*)datosB->cuerpo;
		megaman->atacado(DANOPORCONTACTO);
	}
}

void ListenerColisiones::BeginContact(b2Contact * contacto)
{
	detectorBalistica.BeginContact(contacto);
	detectorSuelo.BeginContact(contacto);
	detectorToqueEnemigos.BeginContact(contacto);
	detectorEscalera.BeginContact(contacto);
	detectorPowerUp.BeginContact(contacto);
	detectorCajaAccion.BeginContact(contacto);
}

void ListenerColisiones::EndContact(b2Contact * contacto)
{
	if(!contacto->GetFixtureA()->GetUserData() || !contacto->GetFixtureB()->GetUserData())
		return;

	detectorBalistica.EndContact(contacto);
	detectorEscalera.EndContact(contacto);	
	detectorSuelo.EndContact(contacto);
	detectorToqueEnemigos.EndContact(contacto);
	detectorPowerUp.EndContact(contacto);
	detectorCajaAccion.EndContact(contacto);
}
