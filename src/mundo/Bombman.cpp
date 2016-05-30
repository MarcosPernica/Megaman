#include "Bombman.h"
#include "Mundo.h"
#include "Megaman.h"
#include "PowerUp.h"
#include <iostream>

#define QUIETO 0
#define CORRIENDO 1
#define SALTANDO 2
#define DISPARANDO 4

#define REFLEJOS 0.5
#define TIEMPOCORRIENDO 1
#define TIEMPODISPARO 1

void Bombman::alMorir()
{
	obtenerMundo().agregarTareaDiferida(new CallbackHabilitadorArma(obtenerMundo().generarID(),obtenerMundo(),obtenerPosicion(),BOMBA));
}

Bombman::Bombman(uint ID,
		 Mundo & mundo, 
		 const b2Vec2 & posicion,
		 const b2Vec2 & velocidad) : 
		 arma(obtenerMundo().generarID(),obtenerMundo(), PERSONAJES),
		 Enemigo(ID,
				mundo,
				   ANCHOBOMBMAN,
				   ALTOBOMBMAN,
				   &arma,
			      	   ENERGIAMAXIMABOMBMAN,
				   ESCUDOBOMBMAN,
				   MASABOMBMAN, 
				   VELOCIDADSALTOBOMBMAN,
				   VELOCIDADCORRERBOMBMAN,
				   ENEMIGOS,
				   CONSTRUCCIONES | PERSONAJES | DISPAROS,
				   posicion, 
				   false,
				   true,
				   velocidad,
				   izquierda,
				   false)
{
	reflejos = 0;
	estadoBombman = QUIETO;
	
	megaman = obtenerMundo().obtenerMegamanCercano(obtenerPosicion());
}

void Bombman::actualizarMaquinaEstados(real deltaT)
{
	reflejos += deltaT;

	switch(estadoBombman)
	{
		case DISPARANDO | SALTANDO:
		{
			if(reflejos >= TIEMPODISPARO)
			{		
				reflejos = 0;
				disparar(megaman->obtenerPosicion()-obtenerPosicion());
				estadoBombman &= ~DISPARANDO;
			}
			break;
		}
		case SALTANDO:
		{
			if(puedeSaltar())
				estadoBombman = QUIETO;
			break;
		}
		case CORRIENDO:
		{
			if(!puedeCorrer() || reflejos >= TIEMPOCORRIENDO)
			{
				reflejos = 0;
				dejarCorrer();
				estadoBombman = QUIETO;
			}

			break;
		}
		case QUIETO:
		{
			real aleatorio = numeroAleatorio(0,1);

			if(aleatorio < 0.4)
			{
				saltar();
				estadoBombman = SALTANDO | DISPARANDO;
			}
			else
			{
				if(!puedeCorrer())
					virar();

				correr();
				estadoBombman = CORRIENDO;
			}
			reflejos = 0;
			break;
		}
	}

}

void Bombman::actualizar(real deltaT)
{
	actualizarMaquinaEstados(deltaT);
	Enemigo::actualizar(deltaT);
}

void Bombman::agregarPropiedadesASnapshot(Snapshot& sn){
	//yo aquí
	Enemigo::agregarPropiedadesASnapshot(sn);
}
void Bombman::setStateFromSnapshot(const Snapshot& sn){
	//yo aquí
	Enemigo::setStateFromSnapshot(sn);
}

Bombman* Bombman::desdeSnapshot(const Snapshot& sn, Mundo& mundo){
	Bombman* p =new Bombman(sn.getID(),mundo,b2Vec2_zero);
	p->setStateFromSnapshot(sn);
	return p;
}
