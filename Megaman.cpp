#include "Megaman.h"
#include "Disparo.h"

void Megaman::seleccionarArma(char slot)
{
	if (slot < armas.size())
		armaSeleccionada = slot;
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

void Megaman::agregarArma(Disparo * disparo)
{
	Arma arma;
	arma.arma = disparo;
	arma.plasma = MAXIMACANTIDADPLASMA;

	armas.push_back(arma);
}

Megaman::Megaman(Mundo & mundo,
				 uint energiaMaxima, 
				 real masa, 
				 const Vector2D & posicion, 
				 bool gravitacional, 
				 const Vector2D & velocidad, 
				 const Vector2D & orientacion) : 
				 Entidad(mundo,
						 ANCHOSPRITEMEGAMAN,
						 ALTOSPRITEMEGAMAN,
						 energiaMaxima,
						 masa,	
					     posicion,
					     gravitacional,
					     velocidad,
					     orientacion)
{
	vida = VIDASINICIALES;
	saltando = false;
	corriendo = false;
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma();

	armas.push_back(arma);
	armaSeleccionada = 0;
}

Megaman::~Megaman()
{
	for (uint i = 0; i < armas.size(); i++)
		delete armas.at(i).arma;
}

void Megaman::disparar()
{
	/*Agregar tiempo de espera entre disparo y disparo.*/
	if (armas.at(armaSeleccionada).plasma)
	{
		Vector2D posicion, orientacion, velocidad;
		orientacion = obtenerOrientacion().normalizado();
		velocidad = orientacion*armas.at(armaSeleccionada).arma->multiplicadorVelocidad();
		posicion = obtenerAnchoCajaColision()*(orientacion + obtenerPosicion());

		if (armas.at(armaSeleccionada).arma->lanzable())
		{
			lanzando = true;
			posicion -= Vector2D(0, obtenerAltoCajaColision());
		}
		else
		{
			disparando = true;
		}

		obtenerMundo().agregar(armas.at(armaSeleccionada).arma->nuevo(posicion, velocidad));


	}
}
