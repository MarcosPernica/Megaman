#ifndef SERVIDOR
#define SERVIDOR
#include <set>
#include "../sockets/ThreadAceptador.h"
#include "ContenedorProxies.h"
#include "../../common/Lock.h"
#include "../../mundo/SimuladorSinVentana.h"
#include "CallbackFin.h"

class Servidor{
	
	Mundo* mundo;
	
	SimuladorSinVentana* simulador;
	
	void ejecutarNivel(char nivel);
	
	Mutex m_nivelContinua;
	bool nivelContinua;
	
	Mutex m_nivel;
	char nivel;
	
	ContenedorProxies contenedor;
	/**
	 * Un thread paralelo tocará este flag para señalizar que se dejen de esperar conexiones
	 * */
	 bool aceptarJugadores;
	/**
	 * Colección con todos los proxies, que tienen un par de Threads
	 * */
	std::set<ProxyJugador*> proxies;//esto va a estar recontra protegido
	/**
	 * Socket aceptador
	 * */
	ThreadAceptador aceptador;
	/**
	 * pide port
	 * */
	//void conectar();
	/**
	 * Etapa de preparación del juego/esperar jugadores/etc.
	 * Devuelve el primer jugador.
	 * */
	//ProxyJugador* agregarJugadores();
	/**
	 * Esperar que el primer jugador desee iniciar la partida. 
	 * Este método recibirá también del jugador el nivel que será jugado. 
	 * */
	 //void esperarAlPrimero(ProxyJugador* primero);
	 
	
	/**
	 * Copia el archivo para que pueda usarse con tinyXML
	 * */ 
	//void copiarParaTiny(char nivel);
	
	void conectarProxiesConMegamanes();
	void desconectarProxiesDeMegamanes();
	
	public:
	
	~Servidor();
	
	void nueva(ChannelSocket* nuevo_channel);
	
	Servidor();
	
	/**
	 * Debe llamarse cuando se alcanza el límite de jugadores
	 * */
	void alcanzadoLimiteJugadores();
	
	/**
	 * Debe llamarse cuando se recibe la senial de iniciar desde el jugador que corresponde
	 * */
	void iniciar(char nivel);
	
	void ejecutar();
	
	void finNivel();
	
	
};
class CallbackAceptador : public CallbackNuevaConexion{
	private:
	Servidor& serv;
	public:
	CallbackAceptador(Servidor& servidor):serv(servidor){};
	virtual void nueva(ChannelSocket* nuevo_channel);
};

class CallbackIniciarPartida : public CallbackReceptor{
	private:
	Servidor& serv;
	public:
	CallbackIniciarPartida(Servidor& servidor):serv(servidor){};
	void recepcion(const std::string& tipo_mensaje,const std::string& resto_mensaje);
};

class CallbackLimite: public CallbackLimiteJugadores{
	private:
	Servidor& serv;
	public:
	CallbackLimite(Servidor& servidor):serv(servidor){};
	virtual void limiteAlcanzado();
};
#endif
