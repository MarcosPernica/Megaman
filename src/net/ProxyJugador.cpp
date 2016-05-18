#include "ProxyJugador.h"
#include <iostream>
#include "../graficos/VentanaJuego.h"
#include "ServerProxy.h"
#include "../mundo/Megaman.h"
/*
ProxyJugador::ProxyJugador(Megaman *controlado, VentanaJuego& ventana, ServerProxy& serv):
					controlado(controlado),
					server_proxy(serv){
	ventana.getWindow().signal_key_press_event().connect(
			sigc::mem_fun(*this, &ProxyJugador::detectarPresionTecla));
}
*/
ProxyJugador::ProxyJugador(Megaman *controlado, VentanaJuego& ventana):
					controlado(controlado){
	ventana.getWindow().signal_key_press_event().connect(
			sigc::mem_fun(*this, &ProxyJugador::detectarPresionTecla),false);

	ventana.getWindow().signal_key_release_event().connect(
			sigc::mem_fun(*this, &ProxyJugador::detectarLiberacionTecla),false);
}

bool ProxyJugador::detectarPresionTecla(GdkEventKey* evento){
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

bool ProxyJugador::detectarLiberacionTecla(GdkEventKey* evento){
	switch(evento->keyval)
	{
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


//ProxyJugador::ProxyJugador(Megaman* controlado): controlado(controlado) { }

void ProxyJugador::recibirMensajeDeCliente(CodigoEvento evento){
	if(evento==CODIGO_EVENTO_SALTO){
		controlado->saltar();
	}
}
