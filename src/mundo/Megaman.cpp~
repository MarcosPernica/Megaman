#include "Megaman.h"
#include "Disparo.h"
#include "Mundo.h"
#include <iostream>
void Megaman::seleccionarArma(char slot)
{
	if (slot <= armas.size() && slot > 0)
		armaSeleccionada = slot-1;
}

void Megaman::aumentarVida()
{
	if (vida < MAXIMACANTIDADVIDAS)
		vida++;
}

void Megaman::recuperarPlasma(int cantidadPlasma)
{
	if (armaSeleccionada)
		if (armas.at(armaSeleccionada).plasma + cantidadPlasma > MAXIMACANTIDADPLASMA)
			armas.at(armaSeleccionada).plasma = MAXIMACANTIDADPLASMA;
		else
			armas.at(armaSeleccionada).plasma += cantidadPlasma;
}

char Megaman::obtenerCantidadPlasma()
{
	return armas.at(armaSeleccionada).plasma;
}

ushort Megaman::tipoCuerpo() const
{
	return PERSONAJES;
}

void Megaman::actualizar(real deltaT)
{

	if (corriendo)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.x = 0;
		velocidad += VELOCIDADMEGAMANCORRIENDO*Cuerpo::orientacionAVector(obtenerOrientacion());
		modificarVelocidad(velocidad);
	}

	if (saltando)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.y -= 6;

		modificarVelocidad(velocidad);

		saltando = false;
	}

	if(agarrado)
	{
		if(puedeSubir >= 1)
		{
			b2Vec2 velocidad = b2Vec2_zero, posicion = obtenerPosicion();
			posicion.x = agarreX;
			modificarPosicion(posicion);

			if(subiendoEscalera)
				velocidad.y = -VELOCIDADMEGAMANESCALERA;
			else if(bajandoEscalera)
				velocidad.y = +VELOCIDADMEGAMANESCALERA;

			modificarVelocidad(velocidad);
		}
	}
	
	if (disparando || lanzando)
	{
		if (armas.at(armaSeleccionada).plasma)
		{
			b2Vec2 posicion, orientacion, velocidad;

			orientacion = Cuerpo::orientacionAVector(obtenerOrientacion());

			posicion = POSICIONDISPAROMEGAMAN*orientacion + obtenerPosicion();
			velocidad = armas.at(armaSeleccionada).arma->obtenerMultiplicadorVelocidad()*orientacion;


			if (armas.at(armaSeleccionada).arma->lanzable())
				/*Lo tira de mas arriba.*/
				posicion -= b2Vec2(0, POSICIONLANZAMIENTOMEGAMAN);
			else
				disparando = true;

			armas.at(armaSeleccionada).plasma--;
			obtenerMundo().agregar(armas.at(armaSeleccionada).arma->nuevo(obtenerMundo().generarID(),posicion, velocidad));

			disparando = false;
			lanzando = false;
		}

	}
}

void Megaman::agregarArma(Disparo * disparo, uint cantidadPlasma)
{
	Arma arma;
	arma.arma = disparo;
	arma.plasma = cantidadPlasma;

	armas.push_back(arma);
}

Megaman::Megaman(uint ID,
				Mundo & mundo,
				 const b2Vec2 & posicion,
				 const b2Vec2 & velocidad,
				 Orientaciones orientacion) :
				 Entidad(ID,
						mundo,
						 ANCHOSPRITEMEGAMAN,
						 ALTOSPRITEMEGAMAN,
					     ENERGIAMEGAMAN,
						 MASAMEGAMAN,
						 PERSONAJES,
					     CONSTRUCCIONES | POWERUPS | ENEMIGOS | DISPAROS | CAJASACCION,
						 posicion,
					     false,
					     true,
					     velocidad,
					     orientacion)
{
	vida = VIDASINICIALES;
	saltando = false;
	agarrado = false;
	puedeSaltar = 0;
	corriendo = false;
	puedeSubir = 0;
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma(obtenerMundo().generarID(),obtenerMundo());

	armas.push_back(arma);
	armaSeleccionada = 0;

	agregarCuerpoInmaterial(ANCHOSPRITEMEGAMAN*0.25,0.3,b2Vec2(-ANCHOSPRITEMEGAMAN*0.25/2,ALTOSPRITEMEGAMAN*0.9/2), JUMPBOX, JUMPBOX, CONSTRUCCIONES | DISPAROS);
}

Megaman::~Megaman()
{
	for (uint i = 0; i < armas.size(); i++)
		delete armas.at(i).arma;
}

void Megaman::habilitarSalto()
{
	bajandoEscalera = false;
	puedeSaltar++;
}

void Megaman::deshabilitarSalto()
{
	puedeSaltar--;
}

void Megaman::saltar()
{
	if (!saltando && puedeSaltar >= 1)
	{
		saltando = true;
		agarrado = false;
		gravitar();
	}
}

void Megaman::correr()
{
	corriendo = true;
}

void Megaman::dejarCorrer()
{
	corriendo = false;
}

void Megaman::mirarDerecha()
{
	modificarOrientacion(derecha);
}

void Megaman::mirarIzquierda()
{
	modificarOrientacion(izquierda);
}

void Megaman::disparar()
{
	if (armas.at(armaSeleccionada).plasma)
		if (armas.at(armaSeleccionada).arma->lanzable())
			lanzando = true;
		else
			disparando = true;
}

void Megaman::habilitarAgarre(real agarreX)
{
	this->agarreX = agarreX;
	puedeSubir++;	
}

void Megaman::deshabilitarAgarre()
{
	puedeSubir--;	
}

void Megaman::subirEscalera()
{
	if(puedeSubir >= 1)
	{
		ingravitar();
		agarrado = true;
		puedeSaltar = 1;
		subiendoEscalera = true;
		bajandoEscalera = false;
	}
}

void Megaman::dejarSubirEscalera()
{
	subiendoEscalera = false;
}

void Megaman::bajarEscalera()
{
	if(puedeSubir)
	{
		ingravitar();
		agarrado = true;
		puedeSaltar = 1;
		subiendoEscalera = false;
		bajandoEscalera = true;
	}
}

void Megaman::dejarBajarEscalera()
{
	bajandoEscalera = false;
}
