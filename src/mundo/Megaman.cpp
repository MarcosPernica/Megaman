#include "Megaman.h"
#include "Disparo.h"
#include "Mundo.h"
#include <iostream>

#define HACIENDONADA 0

#define PISANDO 1
#define PORSALTAR 2
#define ENELAIRE 3

#define DISPARANDO 1
#define LANZANDO 2

#define AGARRADOESCALERA 1
#define BAJANDOESCALERA 2
#define SUBIENDOESCALERA 3

void Megaman::seleccionarArma(unsigned char slot)
{
	if (slot <= armas.size() && slot > 0)
		armaSeleccionada = slot-1;
}

void Megaman::aumentarVida()
{
	if (vidas < MAXIMACANTIDADVIDAS)
		vidas++;
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
	avanzar(deltaT);//animacion
	
	if (corriendo)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.x = 0;
		velocidad += VELOCIDADMEGAMANCORRIENDO*Cuerpo::orientacionAVector(obtenerOrientacion());
		modificarVelocidad(velocidad);
	}

	if (estadoSalto == PORSALTAR)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.y -= VELOCIDADSALTOMEGAMAN;

		modificarVelocidad(velocidad);	

		estadoEscalado = HACIENDONADA;
		estadoSalto = ENELAIRE;
	}

	if(estadoEscalado != HACIENDONADA)
	{
		b2Vec2 velocidad = b2Vec2_zero;
		if(estadoEscalado != AGARRADOESCALERA)
		{
			b2Vec2 posicion = obtenerPosicion();
			posicion.x = agarreX;
			modificarPosicion(posicion);

			if(estadoEscalado == SUBIENDOESCALERA)
				velocidad.y = -VELOCIDADMEGAMANESCALERA;
			else if(estadoEscalado == BAJANDOESCALERA)
				velocidad.y = +VELOCIDADMEGAMANESCALERA;

			ingravitar();
		}
			modificarVelocidad(velocidad);
	}
	
	if (estadoDisparo != HACIENDONADA)
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

			armas.at(armaSeleccionada).plasma--;
			obtenerMundo().agregar(armas.at(armaSeleccionada).arma->nuevo(obtenerMundo().generarID(), posicion, velocidad));
		}
		estadoDisparo = HACIENDONADA;
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
					     CONSTRUCCIONES | POWERUPS | ENEMIGOS | DISPAROS | CAJASACCION | LEFTBOX | RIGHTBOX,
						 posicion,
					     false,
					     true,
					     velocidad,
					     orientacion),
				animacion_corriendo(ANIM_MEGAM_CORRE,0.1),
				animacion_saltando(ANIM_MEGAM_SALTA,1),
				animacion_quieto(ANIM_MEGAM_QUIETO,1),
				Animado(animacion_quieto)
				
{
	vidas = VIDASINICIALES;

	puedeSaltar = 0;
	puedeSubir = 0;
	estadoSalto = PISANDO;
	estadoDisparo = HACIENDONADA;
	estadoEscalado = HACIENDONADA;
	corriendo = false;
	
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma(obtenerMundo().generarID(),obtenerMundo(), ENEMIGOS);

	armas.push_back(arma);
	armaSeleccionada = 0;

	agregarCuerpoInmaterial(ANCHOSPRITEMEGAMAN*0.5,0.3,b2Vec2(0,ALTOSPRITEMEGAMAN*0.9/2), JUMPBOX, JUMPBOX, CONSTRUCCIONES | DISPAROS);
}

Megaman::~Megaman()
{
	for (uint i = 0; i < armas.size(); i++)
		delete armas.at(i).arma;
}

void Megaman::habilitarSalto()
{
	puedeSaltar++;
	estadoSalto = PISANDO;
	estadoEscalado = HACIENDONADA;
}

void Megaman::deshabilitarSalto()
{
	puedeSaltar--;
}

void Megaman::saltar()
{
	if (puedeSaltar >= 1 || estadoEscalado != HACIENDONADA)
	{
		gravitar();
		estadoSalto = PORSALTAR;
		cambiar(animacion_saltando);
	}
}

void Megaman::correr()
{
	corriendo = true;
	cambiar(animacion_corriendo);
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
			estadoDisparo = LANZANDO;
		else
			estadoDisparo = DISPARANDO;
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
	if(puedeSubir)
		estadoEscalado = SUBIENDOESCALERA;
}

void Megaman::bajarEscalera()
{
	if(puedeSubir)
		estadoEscalado = BAJANDOESCALERA;
}

void Megaman::pararMovimientoEscalera()
{
	if(estadoEscalado != HACIENDONADA)
		estadoEscalado = AGARRADOESCALERA;
}


////--------------!!!!!!!!!!!------LO QUE VIENE ES SUCIO Y PELIGROSO
/*
 * Nótese que voy metiendo las booleanas de a 1 en el int, 
 * y luego corro el valor a la izquierda. Después cuando hago la lectura,
 * saco las variables en el orden opuesto y voy corriendo a la derecha.
 * 
 * Según el estándard de C++ false = 0 y true = 1, aprovecho eso
 * */

#define PROP_VIDAS 				"vidas"
#define PROP_PUEDE_SALTAR 		"puedeSaltar"
#define PROP_PUEDE_SUBIR 		"puedeSubir"

#define PROP_ESTADO_SALTO 		"estadoSalto"
#define PROP_ESTADO_DISPARO 	"estadoDisparo"
#define PROP_ESTADO_ESCALADO 	"estadoEscalado"
#define PROP_ESTADO_CORRIENDO 	"estadoCorriendo"

#define PROP_AGARREX 			"agarreX"
#define PROP_TOPEY 				"topeY"
//TODO: SERIALIZAR ARMAS

void Megaman::agregarPropiedadesASnapshot(Snapshot& sn){
	Entidad::agregarPropiedadesASnapshot(sn);
	sn.agregarPropiedad(PROP_VIDAS,(int)vidas);
	
	sn.agregarPropiedad(PROP_PUEDE_SALTAR,puedeSaltar);
	sn.agregarPropiedad(PROP_PUEDE_SUBIR,puedeSubir);
	
	sn.agregarPropiedad(PROP_ESTADO_SALTO,estadoSalto);
	sn.agregarPropiedad(PROP_ESTADO_DISPARO,estadoDisparo);
	sn.agregarPropiedad(PROP_ESTADO_ESCALADO,estadoEscalado);
	sn.agregarPropiedad(PROP_ESTADO_CORRIENDO,corriendo);
	
	sn.agregarPropiedad(PROP_AGARREX,(int)(agarreX*1000));
	sn.agregarPropiedad(PROP_TOPEY,(int)(topeY*1000));
}
void Megaman::setStateFromSnapshot(const Snapshot& sn){
	Entidad::setStateFromSnapshot(sn);
	
	vidas = (uint) sn.obtenerPropiedad(PROP_VIDAS);
	
	puedeSaltar = sn.obtenerPropiedad(PROP_PUEDE_SALTAR);
	puedeSubir = sn.obtenerPropiedad(PROP_PUEDE_SUBIR);
	
	estadoSalto = (char) sn.obtenerPropiedad(PROP_ESTADO_SALTO);
	estadoDisparo = (char) sn.obtenerPropiedad(PROP_ESTADO_DISPARO);
	estadoEscalado = (char) sn.obtenerPropiedad(PROP_ESTADO_ESCALADO);
	corriendo = (bool)sn.obtenerPropiedad(PROP_ESTADO_CORRIENDO);
	
	agarreX = (real)sn.obtenerPropiedad(PROP_AGARREX)/1000;
	topeY = (real)sn.obtenerPropiedad(PROP_TOPEY)/1000;
}

//------------------------------------------------------------------
const Rectangulo Megaman::obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEMEGAMAN/2,
						obtenerPosicion().y-ALTOSPRITEMEGAMAN/2,
						ANCHOSPRITEMEGAMAN,
						ALTOSPRITEMEGAMAN);
}

bool Megaman::espejado() const{
	return obtenerOrientacion()==izquierda;
}
