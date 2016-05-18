#include "Callbacks.h"
#include "Cuerpo.h"
#include "Entidad.h"
#include "Megaman.h"
#include "Disparo.h"
#include "Definiciones.h"
#include "Mundo.h"
#include <iostream>

DanarRadio::DanarRadio(uint dano) : dano(dano)
{
}

bool DanarRadio::ReportFixture(b2Fixture * fixture)
{
	Cuerpo *cuerpo = (Cuerpo*)fixture->GetUserData();

	if (cuerpo->tipoCuerpo() == PERSONAJES || cuerpo->tipoCuerpo() == ENEMIGOS)
	{
		Entidad *entidad = (Entidad*)cuerpo;
		entidad->atacado(dano);
	}

	return true;
}

void DetectarSuelo::BeginContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datos = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();

	if (datos->ID == MEGAMANJUMPBOX)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->habilitarSalto();			
		}

	datos = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datos->ID == MEGAMANJUMPBOX)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->habilitarSalto();
		}
}

void DetectarSuelo::EndContact(b2Contact * contacto)
{
	DatosColisionCuerpo *datos = (DatosColisionCuerpo*)contacto->GetFixtureA()->GetUserData();

	if (datos->ID == MEGAMANJUMPBOX)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->deshabilitarSalto();
		}

	datos = (DatosColisionCuerpo*)contacto->GetFixtureB()->GetUserData();

	if (datos->ID == MEGAMANJUMPBOX)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
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
				disparo->interactuar((Entidad*)datosB->cuerpo);
		}
		else if(datosB->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			disparo->interactuar((Entidad*)datosB->cuerpo);
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
				disparo->interactuar((Entidad*)datosA->cuerpo);
		}
		else if (datosA->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			disparo->interactuar((Entidad*)datosA->cuerpo);
		}

		if(disparo->perecedero())
			disparo->obtenerMundo().eliminar(disparo);
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
}

void ListenerColisiones::EndContact(b2Contact * contacto)
{
	detectorBalistica.EndContact(contacto);
	detectorSuelo.EndContact(contacto);
	detectorToqueEnemigos.EndContact(contacto);
}
