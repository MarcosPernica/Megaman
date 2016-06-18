#include "Jugador.h"
#include <iostream>
#include "../../graficos/VentanaJuego.h"
#include "../../mundo/Megaman.h"
#include "../defines_protocolo.h"

Jugador::Jugador(Megaman* controlado, VentanaJuego& ventana, const Emisor& emi):
					ultimaTecla(0),
					controlado(controlado),
					emisor(emi){
	ventana.signal_key_press_event().connect(
			sigc::mem_fun(*this, &Jugador::detectarPresionTecla),false);

	ventana.signal_key_release_event().connect(
			sigc::mem_fun(*this, &Jugador::detectarLiberacionTecla),false);
}

bool Jugador::detectarPresionTecla(GdkEventKey* evento){
	if(!controlado->estaMuerta() && evento->keyval != ultimaTecla)
	{
		ultimaTecla = evento->keyval;
		switch(evento->keyval)
		{
			case GDK_KEY_1: 
			{
				emisor.enviar(MENSAJE_KEY_1);
				controlado->seleccionarArma(1);
				break;
			}
			case GDK_KEY_2: 
			{
				emisor.enviar(MENSAJE_KEY_2);
				controlado->seleccionarArma(2);
				break;
			}
			case GDK_KEY_3: 
			{
				emisor.enviar(MENSAJE_KEY_3);
				controlado->seleccionarArma(3);
				break;
			}
			case GDK_KEY_4: 
			{
				emisor.enviar(MENSAJE_KEY_4);
				controlado->seleccionarArma(4);
				break;
			}
			case GDK_KEY_5: 
			{
				emisor.enviar(MENSAJE_KEY_5);
				controlado->seleccionarArma(5);
				break;
			}
			case GDK_KEY_6: 
			{
				emisor.enviar(MENSAJE_KEY_6);
				controlado->seleccionarArma(6);
				break;
			}
			case GDK_KEY_Up:
			{
				emisor.enviar(MENSAJE_KEY_UP);
				controlado->subirEscalera();
				break;
			}
			case GDK_KEY_Down:
			{
				emisor.enviar(MENSAJE_KEY_DN);
				controlado->bajarEscalera();
				break;
			}
			case GDK_KEY_Right:
			{
				emisor.enviar(MENSAJE_KEY_RIGHT);
				controlado->mirarDerecha();
				controlado->correr();
				break;
			}
			case GDK_KEY_Left:
			{
				emisor.enviar(MENSAJE_KEY_LEFT);
				controlado->mirarIzquierda();
				controlado->correr();
				break;
			}	
			case GDK_KEY_x:
			{
				emisor.enviar(MENSAJE_KEY_X);
				controlado->disparar();
				break;
			}
			case GDK_KEY_z:
			{
				emisor.enviar(MENSAJE_KEY_Z);
				controlado->saltar();
				
				break;		
			}	
		}
	}
	return true;
}

bool Jugador::detectarLiberacionTecla(GdkEventKey* evento){
	if(!controlado->estaMuerta() && evento->keyval)
	{	
		ultimaTecla = 0;
		switch(evento->keyval)
		{
			case GDK_KEY_Up:
			{
				emisor.enviar(MENSAJE_KEY_UP_LIBERADA);
				controlado->pararMovimientoEscalera();
				break;
			}
			case GDK_KEY_Down:
			{
				emisor.enviar(MENSAJE_KEY_DN_LIBERADA);
				controlado->pararMovimientoEscalera();
				break;
			}
			case GDK_KEY_Right:
			{
				emisor.enviar(MENSAJE_KEY_RIGHT_LIBERADA);
				controlado->dejarCorrer();
				break;
			}
			case GDK_KEY_Left:
			{
				emisor.enviar(MENSAJE_KEY_LEFT_LIBERADA);
				controlado->dejarCorrer();
				break;
			}		
		}
	}
	return true;
}
