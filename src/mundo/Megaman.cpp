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
		gravitar();
	}

	if(subiendoEscalera || bajandoEscalera)
	{
		b2Vec2 velocidad = b2Vec2_zero, posicion = obtenerPosicion();
		posicion.x = agarreX;
		modificarPosicion(posicion);

		if(subiendoEscalera)
			velocidad.y = -VELOCIDADMEGAMANESCALERA;
		else if(bajandoEscalera)
			velocidad.y = +VELOCIDADMEGAMANESCALERA;

		modificarVelocidad(velocidad);
		ingravitar();
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
	puedeSubir = 0;
	corriendo = false;
	subiendoEscalera = false;
	bajandoEscalera = false;
	disparando = false;
	lanzando = false;
	
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
	puedeSaltar++;
}

void Megaman::deshabilitarSalto()
{
	puedeSaltar--;
}

void Megaman::saltar()
{
	if (puedeSaltar >= 1)
		saltando = true;
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
		subiendoEscalera = true;
}

void Megaman::dejarSubirEscalera()
{
	subiendoEscalera = false;
}

void Megaman::bajarEscalera()
{
	if(puedeSubir)
		bajandoEscalera = true;
}

void Megaman::dejarBajarEscalera()
{
	bajandoEscalera = false;
}


////--------------!!!!!!!!!!!------LO QUE VIENE ES SUCIO Y PELIGROSO
/*
 * Nótese que voy metiendo las booleanas de a 1 en el int, 
 * y luego corro el valor a la izquierda. Después cuando hago la lectura,
 * saco las variables en el orden opuesto y voy corriendo a la derecha.
 * 
 * Según el estándard de C++ false = 0 y true = 1, aprovecho eso
 * */

#define PROP_VIDA "vida"
#define PROP_PUEDE_SALTAR "puedeSaltar"
#define PROP_PUEDE_SUBIR "puedeSubir"
#define PROP_ESTADO_GRAL "estadoGral"
#define PROP_AGARREX "agarreX"
//TODO: SERIALIZAR ARMAS
void Megaman::agregarPropiedadesASnapshot(Snapshot& sn){
	//---------------------------------------codificación del estado general
	int estado_gral = 0;
	
	estado_gral+=saltando;
	estado_gral<<=1;
	
	estado_gral+=disparando;
	estado_gral<<=1;
	
	estado_gral+=lanzando;
	estado_gral<<=1;
	
	estado_gral+=agarrado;
	estado_gral<<=1;
	
	estado_gral+=subiendoEscalera;
	estado_gral<<=1;
	
	estado_gral+=bajandoEscalera;
	estado_gral<<=1;
	
	estado_gral+=corriendo;
	//-----------------------------------------------------------------------
	
	sn.agregarPropiedad(PROP_VIDA,(int)vida);
	sn.agregarPropiedad(PROP_PUEDE_SALTAR,puedeSaltar);
	sn.agregarPropiedad(PROP_PUEDE_SUBIR,puedeSubir);
	sn.agregarPropiedad(PROP_ESTADO_GRAL,estado_gral);
	sn.agregarPropiedad(PROP_AGARREX,(int)(agarreX*1000));
	
	Entidad::agregarPropiedadesASnapshot(sn);
}
void Megaman::setStateFromSnapshot(const Snapshot& sn){
	vida = (uint) sn.obtenerPropiedad(PROP_VIDA);
	puedeSaltar = sn.obtenerPropiedad(PROP_PUEDE_SALTAR);
	puedeSubir = sn.obtenerPropiedad(PROP_PUEDE_SUBIR);
	int estado_gral = sn.obtenerPropiedad(PROP_ESTADO_GRAL);
	agarreX = (real)sn.obtenerPropiedad(PROP_AGARREX)/1000;
	
	//------------------------------------------decodificar estado gral
	corriendo = (estado_gral & 1);
	estado_gral>>=1;
	
	bajandoEscalera = (estado_gral & 1);
	estado_gral>>=1;
	
	subiendoEscalera = (estado_gral & 1);
	estado_gral>>=1;
	
	agarrado = (estado_gral & 1);
	estado_gral>>=1;
	
	lanzando = (estado_gral & 1);
	estado_gral>>=1;
	
	disparando = (estado_gral & 1);
	estado_gral>>=1;
	
	saltando = (estado_gral & 1);
	//-----------------------------------------------------------------
	
	Entidad::setStateFromSnapshot(sn);
}

//------------------------------------------------------------------
const Rectangulo Megaman::obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEMEGAMAN/2,
						obtenerPosicion().y-ALTOSPRITEMEGAMAN/2,
						ANCHOSPRITEMEGAMAN,
						ALTOSPRITEMEGAMAN);
}

const b2Vec2 Megaman::obtenerPosicion() const{
	return Cuerpo::obtenerPosicion();
}
