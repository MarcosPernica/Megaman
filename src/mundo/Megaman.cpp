#include "Megaman.h"
#include "Disparo.h"
#include "Mundo.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"
#include <ctime>

#define TIEMPODISPARO 1

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
	{
		if (armas.at(armaSeleccionada).plasma + cantidadPlasma > MAXIMACANTIDADPLASMA)
			armas.at(armaSeleccionada).plasma = MAXIMACANTIDADPLASMA;
		else
			armas.at(armaSeleccionada).plasma += cantidadPlasma;
	}
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
	if(timeoutDisparo > 0)
	{
		if(timeoutDisparo - deltaT >= 0)
			timeoutDisparo -= deltaT;
		else
			timeoutDisparo = 0;
	}

	if(estaMuerta())
		return;

	if(estadoEscalado != AGARRADOESCALERA)
		avanzar(deltaT);

	if(inmovilizado)
	{
		corriendo = false;
		inmovilizado = false;	
	}
	
	if (corriendo)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.x = 0;
		velocidad += VELOCIDADMEGAMANCORRIENDO*Cuerpo::orientacionAVector(obtenerOrientacion());
		modificarVelocidad(velocidad);

		/*Puede setearse cada vez porque internamente si se le cambia la animacion a la misma que ya tiene hace nada y no gasta tiempo de CPU practicamente.*/

		if(estadoSalto == PISANDO)
		{
			if(!timeoutDisparo)
				cambiar(&animacion_corriendo);
			else 
				cambiar(&animacion_disparandoCorriendo);
		}
	}

	if (estadoSalto == PORSALTAR)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.y -= VELOCIDADSALTOMEGAMAN;

		modificarVelocidad(velocidad);	

		estadoEscalado = HACIENDONADA;
		estadoSalto = ENELAIRE;
	}
	else if(estadoSalto == ENELAIRE)
	{
		if(timeoutDisparo)
			cambiar(&animacion_disparandoSaltando);
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
		else
		{
			if(timeoutDisparo)
				cambiar(&animacion_disparandoSubiendo);
		}
			modificarVelocidad(velocidad);
	}
	
	if (estadoDisparo != HACIENDONADA)
	{
		timeoutDisparo = TIEMPODISPARO;
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

	if(estadoDisparo == HACIENDONADA && estadoEscalado == HACIENDONADA && estadoSalto == PISANDO && !corriendo)
			cambiar(&animacion_disparando);
}

void Megaman::agregarArma(Disparo * disparo, uint cantidadPlasma)
{
	Arma arma;
	arma.arma = disparo;
	arma.plasma = cantidadPlasma;

	armas.push_back(arma);
}

void Megaman::alMorir()
{	
}

void Megaman::inmovilizar()
{
	inmovilizado = true;
}

uint Megaman::obtenerCantidadVidas()
{
	return vidas;
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
			CONSTRUCCIONES | POWERUPS | AURAENEMIGOS | DISPAROS | CAJASACCION,
			posicion,
			false,
			true,
			velocidad,
			orientacion),
		Animado(&animacion_quieto),
		animacion_corriendo(ANIM_MEGAM_CORRE,0.1),
		animacion_subiendo(ANIM_MEGAM_SUBIENDO,0.1),
		animacion_saltando(ANIM_MEGAM_SALTA,1),
		animacion_quieto(ANIM_MEGAM_QUIETO,1),
		animacion_disparando(ANIM_MEGAM_QUIETO_DISP, 0.1),
		animacion_disparandoCorriendo(ANIM_MEGAM_CORRE_DISP, 0.1),
		animacion_disparandoSaltando(ANIM_MEGAM_SALTA_DISP, 0.1),
		animacion_disparandoSubiendo(ANIM_MEGAM_SUBIENDO_DISP, 0.1),
		armaSeleccionada(0),
		vidas(VIDASINICIALES),
		puedeSaltar(0),
		puedeSubir(0),
		estadoSalto(PISANDO),
		estadoDisparo(HACIENDONADA),
		estadoEscalado(HACIENDONADA),
		corriendo(false),
		inmovilizado(true),
		posicionSpawn(posicion)
				
{
	deshabilitarFriccion();
	
	Arma arma;

	arma.plasma = CANTIDADINFINITAPLASMA;
	arma.arma = new Plasma(obtenerMundo().generarID(),obtenerMundo(), AURAENEMIGOS);

	armas.push_back(arma);

	/*Para saber si esta pisando.*/

	agregarCuerpoInmaterial(ANCHOSPRITEMEGAMAN*0.5,0.3,b2Vec2(0,ALTOSPRITEMEGAMAN*0.9/2), JUMPBOX, JUMPBOX, CONSTRUCCIONES | DISPAROS);
}

void Megaman::modificarPosicionSpawn(b2Vec2 spawn)
{
	posicionSpawn = spawn;
}

bool Megaman::reSpawn()
{
	if(vidas > 0)
	{
		vidas--;
		modificarPosicion(posicionSpawn);
		modificarVelocidad(b2Vec2_zero);
		revivir();
		return true;		
	}
	return false;
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
		cambiar(&animacion_saltando);
	}
}

void Megaman::correr()
{
	corriendo = true;
}

void Megaman::dejarCorrer()
{
	corriendo = false;

	if(estadoSalto == PISANDO)
	{
		b2Vec2 velocidad = obtenerVelocidad();
		velocidad.x = 0;
		modificarVelocidad(velocidad);
	}
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
	{
		if (armas.at(armaSeleccionada).arma->lanzable())
			estadoDisparo = LANZANDO;
		else
			estadoDisparo = DISPARANDO;
	}
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
	{
		estadoSalto = HACIENDONADA;
		cambiar(&animacion_subiendo);
		estadoEscalado = SUBIENDOESCALERA;
	}
}

void Megaman::bajarEscalera()
{
	if(puedeSubir)
	{
		estadoSalto = HACIENDONADA;
		cambiar(&animacion_subiendo);
		estadoEscalado = BAJANDOESCALERA;
	}
}

void Megaman::pararMovimientoEscalera()
{
	if(estadoEscalado != HACIENDONADA)
		estadoEscalado = AGARRADOESCALERA;
}

void Megaman::atacado(uint dano, Disparo *disparo)
{
	Entidad::atacado(dano, disparo);
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
	SN_AGREGAR_PROPIEDAD(vidas);
	SN_AGREGAR_PROPIEDAD(puedeSaltar);
	SN_AGREGAR_PROPIEDAD(puedeSubir);
	SN_AGREGAR_PROPIEDAD(estadoSalto);
	SN_AGREGAR_PROPIEDAD(estadoDisparo);
	SN_AGREGAR_PROPIEDAD(estadoEscalado);
	SN_AGREGAR_PROPIEDAD(corriendo);
	SN_AGREGAR_PROPIEDAD(agarreX);
	SN_AGREGAR_PROPIEDAD(topeY);
	
	//unsigned int tam = armas.size();
	
	/* SNAPSHOTEAR LAS ARMAS ES UN POCO MÁS COMPLICADO PQ EL TAMANIO DEL VECTOR VARÍA MARCOS REVISALO
	SN_AGREGAR_PROPIEDAD(armas[0].plasma);
	//SN_AGREGAR_PROPIEDAD(armas[0].arma);
	SN_AGREGAR_PROPIEDAD(armas[1].plasma);
	//SN_AGREGAR_PROPIEDAD(armas[1].arma);
	SN_AGREGAR_PROPIEDAD(armas[2].plasma);
	//SN_AGREGAR_PROPIEDAD(armas[2].arma);
	SN_AGREGAR_PROPIEDAD(armas[3].plasma);
	//SN_AGREGAR_PROPIEDAD(armas[3].arma);
	SN_AGREGAR_PROPIEDAD(armas[4].plasma);
	//SN_AGREGAR_PROPIEDAD(armas[4].arma);
	*/
}
void Megaman::setStateFromSnapshot(const Snapshot& sn){
	Entidad::setStateFromSnapshot(sn);
	SN_OBTENER_PROPIEDAD(vidas);
	SN_OBTENER_PROPIEDAD(puedeSaltar);
	SN_OBTENER_PROPIEDAD(puedeSubir);
	SN_OBTENER_PROPIEDAD(estadoSalto);
	SN_OBTENER_PROPIEDAD(estadoDisparo);
	SN_OBTENER_PROPIEDAD(estadoEscalado);
	SN_OBTENER_PROPIEDAD(corriendo);
	SN_OBTENER_PROPIEDAD(agarreX);
	SN_OBTENER_PROPIEDAD(topeY);
	
	/* SNAPSHOTEAR LAS ARMAS ES UN POCO MÁS COMPLICADO PQ EL TAMANIO DEL VECTOR VARÍA MARCOS REVISALO
	SN_OBTENER_PROPIEDAD(armas[0].plasma);
	//SN_OBTENER_PROPIEDAD(armas[0].arma);
	SN_OBTENER_PROPIEDAD(armas[1].plasma);
	//SN_OBTENER_PROPIEDAD(armas[1].arma);
	SN_OBTENER_PROPIEDAD(armas[2].plasma);
	//SN_OBTENER_PROPIEDAD(armas[2].arma);
	SN_OBTENER_PROPIEDAD(armas[3].plasma);
	//SN_OBTENER_PROPIEDAD(armas[3].arma);
	SN_OBTENER_PROPIEDAD(armas[4].plasma);
	//SN_OBTENER_PROPIEDAD(armas[4].arma);
	*/
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
