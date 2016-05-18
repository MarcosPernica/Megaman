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

char Megaman::tipoCuerpo() const
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
	else if (saltando)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.y -= 6;
		modificarVelocidad(velocidad);

		saltando = false;
		
	}
	else if (disparando || lanzando)
	{
		if (armas.at(armaSeleccionada).plasma)
		{
			std::cout << "Pium!" << std::endl;
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
			obtenerMundo().agregar(armas.at(armaSeleccionada).arma->nuevo(posicion, velocidad));

			disparando = false;
			lanzando = false;
		}

	}
}

void Megaman::agregarArma(Disparo * disparo)
{
	Arma arma;
	arma.arma = disparo;
	arma.plasma = MAXIMACANTIDADPLASMA;

	armas.push_back(arma);
}

Megaman::Megaman(Mundo & mundo,
				 const b2Vec2 & posicion,
				 const b2Vec2 & velocidad,
				 Orientaciones orientacion) :
				 Entidad(mundo,
						 ANCHOSPRITEMEGAMAN,
						 ALTOSPRITEMEGAMAN,
					     ENERGIAMEGAMAN,
						 MASAMEGAMAN,
						 PERSONAJES,
					     CONSTRUCCIONES | POWERUPS | ENEMIGOS | DISPAROS,
						 posicion,
					     false,
					     true,
					     velocidad,
					     orientacion)
{
	vida = VIDASINICIALES;
	saltando = false;
	puedeSaltar = false;
	corriendo = 0;
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma(obtenerMundo());

	armas.push_back(arma);

	/*Bomba para probar nada ma'.*/
	
	arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Bomba(obtenerMundo());

	armas.push_back(arma);

	armaSeleccionada = 0;

	agregarCuerpoInmaterial(ANCHOSPRITEMEGAMAN*0.25,0.3,b2Vec2(-ANCHOSPRITEMEGAMAN*0.25/2,ALTOSPRITEMEGAMAN*0.9/2),MEGAMANJUMPBOX, PERSONAJES,CONSTRUCCIONES | DISPAROS);
}

Megaman::~Megaman()
{
	for (uint i = 0; i < armas.size(); i++)
		delete armas.at(i).arma;
}

void Megaman::habilitarSalto()
{
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
		corriendo = false;
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
