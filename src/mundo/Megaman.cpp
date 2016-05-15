#include "Megaman.h"
#include "Disparo.h"
#include "Mundo.h"

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
		b2Vec2 impulso(0, MASAMEGAMAN*IMPULSOSALTOMEGAMAN);
		aplicarImpulso(impulso);
	}
	else if (disparando || lanzando)
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
			obtenerMundo().agregar(armas.at(armaSeleccionada).arma->nuevo(posicion, velocidad));
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
	puedeSaltar = true;
	corriendo = 0;
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma(obtenerMundo());

	armas.push_back(arma);
	armaSeleccionada = 0;
}

Megaman::~Megaman()
{
	for (uint i = 0; i < armas.size(); i++)
		delete armas.at(i).arma;
}

void Megaman::habilitarSalto()
{
	puedeSaltar = true;
}

void Megaman::deshabilitarSalto()
{
	puedeSaltar = false;
	saltando = false;
}

void Megaman::saltar()
{
	if (!saltando && puedeSaltar)
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

void Megaman::disparar()
{
	if (armas.at(armaSeleccionada).plasma)
		if (armas.at(armaSeleccionada).arma->lanzable())
			lanzando = true;
		else
			disparando = true;
}
