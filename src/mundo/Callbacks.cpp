#include "Callbacks.h"
#include "Cuerpo.h"
#include "Entidad.h"
#include "Megaman.h"
#include "Disparo.h"
#include "PowerUp.h"
#include "Definiciones.h"
#include "CajaAccion.h"
#include "Mundo.h"
#include <iostream>
#include "../graficos/Dibujable.h"

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
			
			megaman->habilitarAgarre(datosA->cuerpo->obtenerPosicion().x);			
		}
	}

	if(datosB->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;
			
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
			
			megaman->deshabilitarAgarre();			
		}
	}

	if(datosB->cuerpo->tipoCuerpo() == ESCALERAS)
	{
		if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datosA->cuerpo;
			
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
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		megaman->habilitarSalto();			
	}


	if (datosB->ID == JUMPBOX)
	{
		Megaman *megaman = (Megaman*)datosB->cuerpo;
		megaman->habilitarSalto();			
	}
}

void DetectarSuelo::EndContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->ID == JUMPBOX)
	{
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		megaman->deshabilitarSalto();			
	}


	if (datosB->ID == JUMPBOX)
	{
		Megaman *megaman = (Megaman*)datosB->cuerpo;
		megaman->deshabilitarSalto();			
	}
}

void DetectarBalistica::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datosA = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();
	DatosColisionCuerpo *datosB = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datosA->cuerpo->tipoCuerpo() == DISPAROS)
	{
		Disparo *disparo = (Disparo*)datosA->cuerpo;
		if (disparo->megamanLoDisparo())
		{
			if (datosB->cuerpo->tipoCuerpo() == ENEMIGOS)
				disparo->danar((Entidad*)datosB->cuerpo);
		}
		else if(datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			disparo->danar((Entidad*)datosB->cuerpo);
		}

		if(disparo->perecedero())
			disparo->obtenerMundo().eliminar(disparo);
	}

	if (datosB->cuerpo->tipoCuerpo() == DISPAROS)
	{
		Disparo *disparo = (Disparo*)datosB->cuerpo;
		if (disparo->megamanLoDisparo())
		{
			if (datosA->cuerpo->tipoCuerpo() == ENEMIGOS)
				disparo->danar((Entidad*)datosA->cuerpo);
		}
		else if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			disparo->danar((Entidad*)datosA->cuerpo);
		}

		if(disparo->perecedero())
			disparo->obtenerMundo().eliminar(disparo);
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

	if (datosA->cuerpo->tipoCuerpo() == PERSONAJES && datosB->cuerpo->tipoCuerpo() == ENEMIGOS)
	{
		Megaman *megaman = (Megaman*)datosA->cuerpo;
		megaman->atacado(DANOPORCONTACTO);
	}
	
	if (datosB->cuerpo->tipoCuerpo() == PERSONAJES && datosA->cuerpo->tipoCuerpo() == ENEMIGOS)
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
