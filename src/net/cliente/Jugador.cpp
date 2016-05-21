#include "Jugador.h"
#include <iostream>
#include "../../graficos/VentanaJuego.h"
#include "../../mundo/Megaman.h"

Jugador::Jugador(Megaman *controlado, VentanaJuego& ventana):
					controlado(controlado){
	ventana.getWindow().signal_key_press_event().connect(
			sigc::mem_fun(*this, &Jugador::detectarPresionTecla),false);

	ventana.getWindow().signal_key_release_event().connect(
			sigc::mem_fun(*this, &Jugador::detectarLiberacionTecla),false);
}

bool Jugador::detectarPresionTecla(GdkEventKey* evento){
	switch(evento->keyval)
	{
		case GDK_KEY_1: 
		{
			controlado->seleccionarArma(1);
			break;
		}
		case GDK_KEY_2: 
		{
			controlado->seleccionarArma(2);
			break;
		}
		case GDK_KEY_3: 
		{
			controlado->seleccionarArma(3);
			break;
		}
		case GDK_KEY_4: 
		{
			controlado->seleccionarArma(4);
			break;
		}
		case GDK_KEY_5: 
		{
			controlado->seleccionarArma(5);
			break;
		}
		case GDK_KEY_Up:
		{
			controlado->subirEscalera();
			break;
		}
		case GDK_KEY_Down:
		{
			controlado->bajarEscalera();
			break;
		}
		case GDK_KEY_Right:
		{
			controlado->mirarDerecha();
			controlado->correr();
			break;
		}
		case GDK_KEY_Left:
		{
			controlado->mirarIzquierda();
			controlado->correr();
			break;
		}	
		case GDK_KEY_x:
		{
			controlado->disparar();
			break;
		}
		case GDK_KEY_z:
			controlado->saltar();
			break;			
	}
	//server_proxy.enviarEvento(CODIGO_EVENTO_SALTO);
	return true;
}

bool Jugador::detectarLiberacionTecla(GdkEventKey* evento){
	switch(evento->keyval)
	{
		case GDK_KEY_Up:
		{
			controlado->dejarSubirEscalera();
			break;
		}
		case GDK_KEY_Down:
		{
			controlado->dejarBajarEscalera();
			break;
		}
		case GDK_KEY_Right:
		{
			controlado->dejarCorrer();
			break;
		}
		case GDK_KEY_Left:
		{
			controlado->dejarCorrer();
			break;
		}		
	}
	//server_proxy.enviarEvento(CODIGO_EVENTO_SALTO);
	return true;
}
