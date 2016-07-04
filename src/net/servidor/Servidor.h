#ifndef SERVIDOR
#define SERVIDOR
#include <set>
#include "../sockets/ThreadAceptador.h"
#include "ContenedorProxies.h"
#include "../../common/Lock.h"
#include "../../common/Mutex.h"
#include "../../common/ConditionVariable.h"
#include "../../mundo/SimuladorSinVentana.h"
#include "CallbackFin.h"
#include "../../mundo/Mundo.h"
#include "../../common/Queue.h"

enum Evento{
	SALIDA_FORZADA,
	INICIO_NIVEL,
	FIN_NIVEL
};
class Servidor{
	private:
	/**
	 * Socket aceptador
	 * */
	ThreadAceptador aceptador;
	
	ContenedorProxies contenedor;
	
	
	
	/**
	 * Termina el nivel actual, limpia los recursos correspondientes y prepara la siguiente fase
	 * */
	void finalizarNivel();
	/**
	 * Cola de eventos que ejecuta el servidor
	 * */
	Queue<Evento> cola;
	
	EstadisticasMundo estadisticas;
	
	Mundo* mundo;
	
	SimuladorSinVentana* simulador;
	
	void ejecutarNivel(char nivel);
	
	bool nivelContinua;
	ConditionVariable cv_nivelContinua;
	
	ConditionVariable cv_nivelElegido;
	Mutex m_nivel;
	char nivel;
	
	
	bool continuarEjecucion;
	/**
	 * Un thread paralelo tocará este flag para señalizar que se dejen de esperar conexiones
	 * */
	 bool aceptarJugadores;
	/**
	 * Colección con todos los proxies, que tienen un par de Threads
	 * */
	std::set<ProxyJugador*> proxies;//esto va a estar recontra protegido
	
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
	
	bool algunNivelSeleccionado();
	void esperarSeleccionNivel();
	void esperarFinNivel();
	
	void liberarRecursos();
	
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
	
	/**
	 * Ejecuta el servidor, que permanece esperando eventos
	 * */
	void ejecutar();
	
	/**
	 * Genera el evento de fin de nivel
	 * */
	void finNivel();
	
	/**
	 * Genera el evento que cierra el servidor
	 * */
	void cerrar();
	
	
	
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
