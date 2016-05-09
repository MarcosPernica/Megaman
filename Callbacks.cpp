#include "Callbacks.h"
#include "Cuerpo.h"
#include "Entidad.h"
#include "Megaman.h"
#include "Disparo.h"

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
	Datos *datos = (Datos*)contacto->GetFixtureA()->GetUserData();

	if (datos->esDetectorSuelo)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->habilitarSalto();
		}

	datos = (Datos*)contacto->GetFixtureB()->GetUserData();

	if (datos->esDetectorSuelo)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->habilitarSalto();
		}
}

void DetectarSuelo::EndContact(b2Contact * contacto)
{
	Datos *datos = (Datos*)contacto->GetFixtureA()->GetUserData();

	if (datos->esDetectorSuelo)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->deshabilitarSalto();
		}

	datos = (Datos*)contacto->GetFixtureB()->GetUserData();

	if (datos->esDetectorSuelo)
		if (datos->cuerpo->tipoCuerpo() == PERSONAJES)
		{
			Megaman *megaman = (Megaman*)datos->cuerpo;
			megaman->deshabilitarSalto();
		}
}

void DetectarBalistica::BeginContact(b2Contact * contacto)
{
	Datos *datosA = (Datos*)contacto->GetFixtureA()->GetUserData();
	Datos *datosB = (Datos*)contacto->GetFixtureB()->GetUserData();

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
	}
}

void DetectarTocarEnemigos::BeginContact(b2Contact * contacto)
{
	Datos *datosA = (Datos*)contacto->GetFixtureA()->GetUserData();
	Datos *datosB = (Datos*)contacto->GetFixtureB()->GetUserData();

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
