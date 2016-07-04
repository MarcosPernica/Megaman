#include "Megaman.h"
#include "Disparo.h"
#include "Mundo.h"
#include <iostream>
#include "../net/snapshots/Snapshot.h"
#include <ctime>
#include <algorithm>
#include <sstream>

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

	#ifndef compiling_server
	if(estadoEscalado != AGARRADOESCALERA)
		avanzar(deltaT);
	#endif

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

		#ifndef compiling_server
		/*Puede setearse cada vez porque internamente si se le cambia la animacion a la misma que ya tiene hace nada y no gasta tiempo de CPU practicamente.*/

		if(estadoSalto == PISANDO)
		{
			if(!timeoutDisparo)
				cambiar(&animacion_corriendo);
			else 
				cambiar(&animacion_disparandoCorriendo);
		}
		#endif
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
		#ifndef compiling_server
		if(timeoutDisparo)
			cambiar(&animacion_disparandoSaltando);
		#endif
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
			#ifndef compiling_server
			if(timeoutDisparo)
				cambiar(&animacion_disparandoSubiendo);
			#endif
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

	#ifndef compiling_server
	if(estadoDisparo == HACIENDONADA && estadoEscalado == HACIENDONADA && estadoSalto == PISANDO && !corriendo)
			cambiar(&animacion_disparando);
	#endif
}

void Megaman::agregarArma(Disparo * disparo, uint cantidadPlasma)
{
	Arma arma;
	arma.arma = disparo;
	arma.plasma = cantidadPlasma;

	armas.push_back(arma);
}

void Megaman::agregarArma(int tipo, uint cantidadPlasma)
{
	Arma arma;
	arma.arma = Disparo::crearDesdeTipo(
										tipo,
										obtenerMundo().generarID(),
										obtenerMundo(), 
										AURAENEMIGOS
										);
	arma.plasma = cantidadPlasma;

	armas.push_back(arma);
}


void Megaman::alMorir()
{	
	obtenerMundo().notificarMuerteMegaman(this);
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
		uint pos,
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
		#ifndef compiling_server
		Animado(&animacion_quieto),
		animacion_corriendo(ANIM_MEGAM_CORRE,0.1),
		animacion_subiendo(ANIM_MEGAM_SUBIENDO,0.1),
		animacion_saltando(ANIM_MEGAM_SALTA,1),
		animacion_quieto(ANIM_MEGAM_QUIETO,1),
		animacion_disparando(ANIM_MEGAM_QUIETO_DISP, 0.1),
		animacion_disparandoCorriendo(ANIM_MEGAM_CORRE_DISP, 0.1),
		animacion_disparandoSaltando(ANIM_MEGAM_SALTA_DISP, 0.1),
		animacion_disparandoSubiendo(ANIM_MEGAM_SUBIENDO_DISP, 0.1),
		#endif
		armaSeleccionada(0),
		vidas(VIDASINICIALES),
		timeoutDisparo(0),
		puedeSaltar(0),
		puedeSubir(0),
		estadoSalto(PISANDO),
		estadoDisparo(HACIENDONADA),
		estadoEscalado(HACIENDONADA),
		corriendo(false),
		inmovilizado(true),
		posicionSpawn(posicion),
		mi_posicion(pos),
		agarreX(0)
{
	deshabilitarFriccion();

	agregarArma(TIPO_Plasma,CANTIDADINFINITAPLASMA);
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
		#ifndef compiling_server
		cambiar(&animacion_saltando);
		#endif
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
		#ifndef compiling_server
		cambiar(&animacion_subiendo);
		#endif
		estadoEscalado = SUBIENDOESCALERA;
	}
}

void Megaman::bajarEscalera()
{
	if(puedeSubir)
	{
		estadoSalto = HACIENDONADA;
		#ifndef compiling_server
		cambiar(&animacion_subiendo);
		#endif
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

#define PROP_ARMAS_CANTIDAD  	"cantidad_armas"
#define PROP_ARMAS_TIPO  		"tipo_arma"
#define PROP_ARMAS_PLASMA  		"plasma_arma"

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
	
	sn.agregarPropiedad(PROP_ARMAS_CANTIDAD,armas.size());
	for(uint i =0; i< armas.size(); i++){
		std::ostringstream tipo;
		tipo<<PROP_ARMAS_TIPO<<i;
		sn.agregarPropiedad(tipo.str(),armas[i].arma->getTipo());
		
		std::ostringstream plasma;
		plasma<<PROP_ARMAS_PLASMA<<i;
		sn.agregarPropiedad(plasma.str(),armas[i].plasma);
	}
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
	
	int cantidad_armas;
	sn.obtenerPropiedad(PROP_ARMAS_CANTIDAD,cantidad_armas);
	
	while(cantidad_armas>armas.size()){
		Arma nueva;
		nueva.arma = NULL;
		nueva.plasma = 0;
		armas.push_back(nueva);
	}
	
	for(int i =0; i< cantidad_armas; i++){
		delete armas[i].arma;
		
		std::ostringstream tipo;
		tipo<<PROP_ARMAS_TIPO<<i;
		int tipo_arma;
		sn.obtenerPropiedad(tipo.str(),tipo_arma);
		
		armas[i].arma = Disparo::crearDesdeTipo(
										tipo_arma,
										obtenerMundo().generarID(),
										obtenerMundo(), 
										AURAENEMIGOS
										);
		
		std::ostringstream plasma;
		plasma<<PROP_ARMAS_PLASMA<<i;
		sn.obtenerPropiedad(plasma.str(),armas[i].plasma);
	}
}

//------------------------------------------------------------------
#ifndef compiling_server
const Rectangulo Megaman::obtenerRepresentacion() const{
	return Rectangulo(	obtenerPosicion().x-ANCHOSPRITEMEGAMAN/2,
						obtenerPosicion().y-ALTOSPRITEMEGAMAN/2,
						ANCHOSPRITEMEGAMAN,
						ALTOSPRITEMEGAMAN);
}

bool Megaman::espejado() const{
	return obtenerOrientacion()==izquierda;
}

void Megaman::dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);
	std::ostringstream nombre_imagen;
	nombre_imagen<<"imagenes/P/P";
	nombre_imagen<<mi_posicion+1;
	nombre_imagen<<".png";
	
	ArchivoImagen imagen(nombre_imagen.str());
	
	b2Vec2 o = origen;
	b2Vec2 posicionP = Dibujable::mundoARender(obtenerPosicion());
	posicionP +=Dibujable::mundoARender(b2Vec2(-ANCHOSPRITEMEGAMAN,-ALTOSPRITEMEGAMAN*2));
	Dibujable::dibujarImagen(cr, 
				  o,
				  factorAmplificacion, 
				  posicionP,
				  CacheImagenes::ancho(imagen),
				  CacheImagenes::alto(imagen),
				  imagen,
				  false);
	b2Vec2 posicion_vida(20+mi_posicion*100,20);
	Dibujable::dibujarRectanguloLleno(cr, 
				  o,
				  factorAmplificacion, 
				  posicion_vida+o,
				  20,
				  100
				  );
	uint color = 0xFFFFFF;
	switch(mi_posicion){
		case 0:
			color = 0xFF0000;
			break;
		case 1:
			color = 0xFFFF00;
			break;
		case 2:
			color = 0x00FF00;
			break;
		case 3:
			color = 0x00FFFF;
			break;
	}
	//barrita de vida
	Dibujable::dibujarRectanguloLleno(cr, 
				  o,
				  factorAmplificacion, 
				  posicion_vida+o,
				  20,
				  (real)100/(real)obtenerEnergiaMaxima()*(real)obtenerEnergiaActual(),
				  color
				  );
	//barrita de plasma
	Dibujable::dibujarRectanguloLleno(cr, 
				  o,
				  factorAmplificacion, 
				  posicion_vida+o+b2Vec2(20,0),
				  5,
				  std::max(armas.at(armaSeleccionada).plasma,(char)0),
				  color
				  );
	for(uint i =0; i<obtenerCantidadVidas(); i++){
		//cantidad de vidas
		Dibujable::dibujarCirculoLleno(cr,
					o,
					factorAmplificacion,
					posicion_vida+b2Vec2(40,10+i*40),
					15,//radio
					color
					);
	}
	
	
}
#endif

void Megaman::setCantidadVidas(uint cuantas){
	vidas = cuantas;
}
