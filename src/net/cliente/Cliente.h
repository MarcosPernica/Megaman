#ifndef CLIENTE
#define CLIENTE
#include "../sockets/ChannelSocket.h"
#include <set>
#include <string>
#include "../../common/Mutex.h"
#include "../sockets/Emisor.h"
class VentanaJuego;
#include "ReceptorCliente.h"
class Jugador;
/**
 * "Singleton-no-Signleton" que representa la aplicación cliente
 * */
class Cliente{
	private:
	//Mutex m_pantalla;
	Mutex m_posicion;
	Mutex m_iniciado;
	
	ChannelSocket socket;
	int posicion;
	bool flag_iniciado;
	
	ReceptorCliente receptor;
	Emisor emisor;
	
	
	/**
	 * Envia la señal de iniciar la partida
	 * */
	 void iniciarPartida();
	 
	 std::string nombre;
	public:
	
	//interfaz para ReceptorCliente
	
	void agregarEstaba(const std::string& usuario);//no se usan
	void agregarLlega(const std::string& usuario);//no se usan
	
	void definirPosicion(int posicion);
	int obtenerPosicion();
	void iniciar();
	bool iniciado();
	
	const std::string& obtenerNombre();
	Cliente();
	~Cliente();
	
	/**
	 * Pide ip y port por cmd, y conecta el Socket
	 * */
	void conectarse(const std::string& nombre);
	
	/**
	 * Le agrega un callback al receptor, 
	 * de esta forma la Ventana puede recibir "eventos" del socket
	 * */
	void agregarCallback(const std::string& tipo_mensaje, CallbackReceptor* callback);
	
	void enviarIniciar(int nivel);
	
	Jugador* configurarNivel(VentanaJuego& ventana ,Mundo& mundo);
	
	void terminarMundo();
	
};
#endif
